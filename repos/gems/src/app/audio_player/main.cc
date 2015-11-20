/*
 * \brief  Audio player
 * \author Josef Soentgen
 * \date   2015-11-19
 */

/*
 * Copyright (C) 2015 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* Genode includes */
#include <base/printf.h>
#include <base/sleep.h>
#include <os/attached_rom_dataspace.h>
#include <os/config.h>
#include <os/reporter.h>
#include <util/retry.h>
#include <util/xml_node.h>
#include <audio_out_session/connection.h>

/* local includes */
#include <list.h>
#include <ring_buffer.h>

/* libav includes */
extern "C" {
/*
 * UINT64_C is needed by libav headers
 *
 * Use the compiler's definition as fallback because the UINT64_C macro is only
 * defined in <machine/_stdint.h> when used with C.
 */
#ifndef UINT64_C
#define UINT64_C(c) __UINT64_C(c)
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/dict.h>
}; /* extern "C" */


static bool verbose = false;
#define PLOGV(...) do { if (verbose) PLOG(__VA_ARGS__); } while (0)

#define ASSERT(cond) do { \
	if (!(cond)) {        \
		PERR("%s:%d: assertion failed", __FILE__, __LINE__); \
		Genode::sleep_forever(); \
	} } while (0)


namespace Audio_player {
	class  Client;
	class  Playlist;
	class  Decoder;
	struct Main;

	typedef Util::Ring_buffer<64 * 1024> Frame_data;
	typedef Genode::String<1024>         Path;

	enum { LEFT, RIGHT, NUM_CHANNELS };
	enum { AUDIO_OUT_PACKET_SIZE = Audio_out::PERIOD * 2 * sizeof(int16_t) };
	enum { QUEUED_PACKET_THRESHOLD = 10 };
}


struct Audio_player::Client
{
	Audio_out::Connection  _left;
	Audio_out::Connection  _right;
	Audio_out::Connection *_out[NUM_CHANNELS];

	template <typename FUNC>
	static void for_each_channel(FUNC const &func) {
		for (int i = 0; i < Audio_player::NUM_CHANNELS; i++) func(i); }

	/**
	 * Constructor
	 */
	Client(Genode::Signal_context_capability sigh)
	:
		_left("left", true, true),
		_right("right", false, false)
	{
		/*
		 * We only care about the left (first) channel and sync all other
		 * channels with it when needed
		 */
		_left.progress_sigh(sigh);

		_out[LEFT]  = &_left;
		_out[RIGHT] = &_right;

		for_each_channel([&] (int const i) { _out[i]->start(); });
	}

	/**
	 * Return number of currently queued packets in Audio_out stream
	 */
	unsigned queued() { return _out[LEFT]->stream()->queued(); }

	/**
	 * Fetch decoded frames from frame data buffer and fill Audio_out packets
	 */
	void drain_buffer(Frame_data &frame_data)
	{
		while (frame_data.read_avail() > (AUDIO_OUT_PACKET_SIZE)) {
			Audio_out::Packet *p[NUM_CHANNELS];

			while (true) {
				try {
					p[LEFT] = _out[LEFT]->stream()->alloc();
					break;
				} catch (Audio_out::Stream::Alloc_failed) {
					_out[LEFT]->wait_for_alloc(); }
			}

			unsigned const ppos = _out[LEFT]->stream()->packet_position(p[LEFT]);
			p[RIGHT]            = _out[RIGHT]->stream()->get(ppos);

			int16_t tmp[Audio_out::PERIOD * NUM_CHANNELS];
			size_t const n = frame_data.read(tmp, sizeof(tmp));

			ASSERT(n == sizeof(tmp));

			float *left_content  = p[LEFT]->content();
			float *right_content = p[RIGHT]->content();

			for (int i = 0; i < Audio_out::PERIOD; i++) {
					left_content[i]  = (float)(tmp[i * NUM_CHANNELS + LEFT])  / 32768.0f;
					right_content[i] = (float)(tmp[i * NUM_CHANNELS + RIGHT]) / 32768.0f;
			}

			for_each_channel([&] (int const i) { _out[i]->submit(p[i]); });
		}
	}
};


class Audio_player::Playlist
{
	public:

		struct Track : public Util::List<Track>::Element
		{
			Path     path;
			unsigned id = 0;

			Track() { }
			Track(char const *path, unsigned id) : path(path), id(id) { }
			Track(Track const &track) : path(track.path), id(track.id) { }

			bool is_valid() { return path.length(); }
		};

	private:

		Genode::Allocator &_alloc;
		Util::List<Track>  _track_list;
		Track             *_curr_track = nullptr;

		typedef enum { MODE_ONCE, MODE_REPEAT } Mode;
		Mode _mode;

		void _insert(char const *path, unsigned id)
		{
			try {
				Track *t = new (&_alloc) Track(path, id);
				_track_list.append(t);
			} catch (...) { PWRN("could not insert track"); }
		}

		void _remove_all()
		{
			while (Track *t = _track_list.first()) {
				_track_list.remove(t);
				Genode::destroy(&_alloc, t);
			}
		}

	public:

		/**
		 * Constructor
		 */
		Playlist(Genode::Allocator &alloc) : _alloc(alloc), _mode(MODE_ONCE) { }

		/**
		 * Destructor
		 */
		~Playlist() { _remove_all(); }

		/**
		 * Update playlist from node
		 */
		void update(Genode::Xml_node &node)
		{
			_remove_all();
			_curr_track = nullptr;

			unsigned count = 0;
			try {
				node.for_each_sub_node("track", [&] (Genode::Xml_node &tnode) {
				try {
					Path path;
					tnode.attribute("path").value(&path);
					_insert(path.string(), ++count);
				} catch (...) { PWRN("invalid file node in playlist"); }
				});
			} catch (...) { }

			PLOGV("new playlist: %u tracks mode: %s", count,
			      _mode == MODE_ONCE ? "once" : "repeat");
		}

		/**
		 * Set playlist mode
		 */
		void set_repeat(bool v) { _mode = v ? MODE_REPEAT : MODE_ONCE; }

		/**
		 * Return track with given id
		 */
		Track get_track(unsigned id)
		{
			for (Track *t = _track_list.first(); t; t = t->next())
				if (t->id == id) {
					_curr_track = t;
					return *_curr_track;
				}

			return Track();
		}

		/**
		 * Return next track from playlist
		 */
		Track next_track()
		{
			/* first time next_track() is called */
			if (_curr_track == nullptr) {
				_curr_track = _track_list.first();

				if (_curr_track == nullptr) return Track();
				else                        return *_curr_track;
			}

			/* next time next_track() is called */
			_curr_track = _curr_track->next();
			if (_curr_track == nullptr) {
				if (_mode != MODE_REPEAT) return Track();

				_curr_track = _track_list.first();
				if (_curr_track == nullptr) return Track();
			}

			return *_curr_track;
		}
};


class Audio_player::Decoder
{
	public:

		/*
		 * Thrown as exception if the decoder could not be initialized
		 */
		struct Not_initialized { };

		/*
		 * Track_info contains metadata of the track that is currently decoded
		 */
		struct Track_info : public Playlist::Track
		{
			typedef Genode::String<256> Artist;
			typedef Genode::String<256> Album;
			typedef Genode::String<256> Title;

			Artist  artist;
			Album   album;
			Title   title;
			int64_t duration;

			Track_info(Track const &track,
			           char const *artist, char const *album,
			           char const *title, int64_t duration)
			:
				Track(track),
				artist(artist), album(album), title(title),
				duration(duration) { }
		};

	private:

		AVFrame         *_frame      = nullptr;
		AVStream        *_stream     = nullptr;
		AVFormatContext *_format_ctx = nullptr;
		AVCodecContext  *_codec_ctx  = nullptr;
		AVPacket         _packet;

		Playlist::Track const &_track;

		void _close()
		{
			avformat_close_input(&_format_ctx);
			av_free(_frame);
		}

	public:

		/*
		 * Constructor
		 */
		Decoder(Playlist::Track const &track) : _track(track)
		{
			_frame = avcodec_alloc_frame();
			if (!_frame) throw Not_initialized();

			int err = 0;
			err = avformat_open_input(&_format_ctx, _track.path.string(), NULL, NULL);
			if (err != 0) {
				PERR("could not open '%s'", _track.path.string());
				throw Not_initialized();
			}

			err = avformat_find_stream_info(_format_ctx, NULL);
			if (err < 0) {
				PERR("could not find the stream info");
				_close();
				throw Not_initialized();
			}

			for (unsigned i = 0; i < _format_ctx->nb_streams; ++i)
				if (_format_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
					_stream = _format_ctx->streams[i];
					break;
				}

			if (_stream == nullptr) {
				PERR("could not find any audio stream");
				_close();
				throw Not_initialized();
			}

			_codec_ctx        = _stream->codec;
			_codec_ctx->codec = avcodec_find_decoder(_codec_ctx->codec_id);
			if (_codec_ctx->codec == NULL) {
				PERR("could not find decoder");
				_close();
				throw Not_initialized();
			}

			err = avcodec_open2(_codec_ctx, _codec_ctx->codec, NULL);
			if (err != 0) {
				PERR("could not open decoder");
				_close();
				throw Not_initialized();
			}

			if (_codec_ctx->sample_fmt != AV_SAMPLE_FMT_S16
				|| _codec_ctx->sample_rate != Audio_out::SAMPLE_RATE) {
				PERR("cannot play '%s': only 44.1khz S16LE input is supported",
				     _track.path.string());
				_close();
				throw Not_initialized();
			}

			av_init_packet(&_packet);

			PLOGV("new decoder: '%s'", _track.path.string());
		}

		/**
		 * Destructor
		 */
		~Decoder()
		{
			avcodec_close(_codec_ctx);
			avformat_close_input(&_format_ctx);
			av_free(_frame);
		}

		/**
		 * Dump format information - needs <libc stderr="/dev/log"> configuration
		 */
		void dump_info() const { av_dump_format(_format_ctx, 0, _track.path.string(), 0); }

		/**
		 * Return metainformation of track
		 */
		Track_info track_info() const
		{
			bool const is_vorbis = _codec_ctx->codec_id == CODEC_ID_VORBIS;

			AVDictionary *md = is_vorbis ? _stream->metadata : _format_ctx->metadata;
			int const flags  = AV_DICT_IGNORE_SUFFIX;

			AVDictionaryEntry *artist = av_dict_get(md, "artist", NULL, flags);
			AVDictionaryEntry *album  = av_dict_get(md, "album", NULL, flags);
			AVDictionaryEntry *title  = av_dict_get(md, "title", NULL, flags);

			return Track_info(_track,
			                  artist ? artist->value : "", album ? album->value : "",
			                  title ? title->value : "", _format_ctx->duration / 1000);
		}

		/**
		 * Fill frame data buffer with decoded frames
		 *
		 * \param frame_data reference to destination buffer
		 * \param min minimal number of bytes that have to be decoded at least
		 */
		int fill_buffer(Frame_data &frame_data, size_t min)
		{
			size_t written = 0;
			while (written < min
			       && (av_read_frame(_format_ctx, &_packet) == 0)) {

				if (_packet.stream_index == _stream->index) {
					int finished = 0;
					avcodec_decode_audio4(_codec_ctx, _frame, &finished, &_packet);

					if (finished) {
						int            const chnum = _codec_ctx->channels;
						int            const snum  = _frame->nb_samples;
						AVSampleFormat const sfmt  = _codec_ctx->sample_fmt;

						int const size  = av_samples_get_buffer_size(NULL, chnum, snum, sfmt, 1);

						written += frame_data.write(_frame->data[0], size);
					}
				}

				av_free_packet(&_packet);
			}

			return written;
		}
};


struct Audio_player::Main
{
	Genode::Allocator       &alloc;
	Genode::Signal_receiver &sig_rec;

	void handle_progress(unsigned);

	Genode::Signal_dispatcher<Main> progress_dispatcher = {
		sig_rec, *this, &Main::handle_progress };

	Client      client { progress_dispatcher };
	Frame_data  frame_data;
	Decoder    *decoder = nullptr;

	void handle_playlist(unsigned);

	Genode::Signal_dispatcher<Main> playlist_dispatcher = {
		sig_rec, *this, &Main::handle_playlist };

	Genode::Attached_rom_dataspace playlist_rom { "playlist" };

	Playlist        playlist { alloc };
	Playlist::Track track;

	bool is_paused  = false;
	bool is_stopped = false;

	Genode::Reporter reporter { "current_track" };

	void report_track(Decoder::Track_info const &);

	void handle_config(unsigned);

	Genode::Signal_dispatcher<Main> config_dispatcher = {
		sig_rec, *this, &Main::handle_config };

	Main(Genode::Allocator &alloc, Genode::Signal_receiver &sig_rec)
	:
		alloc(alloc), sig_rec(sig_rec)
	{
		Genode::Signal_transmitter(config_dispatcher).submit();
		Genode::config()->sigh(config_dispatcher);

		Genode::Signal_transmitter(playlist_dispatcher).submit();
		playlist_rom.sigh(playlist_dispatcher);
	}
};


void Audio_player::Main::handle_playlist(unsigned)
{
	playlist_rom.update();

	if (!playlist_rom.is_valid()) return;

	Genode::Xml_node node(playlist_rom.local_addr<char>(),
	                      playlist_rom.size());

	playlist.update(node);

	track = playlist.next_track();

	/*
	 * trigger playback because playlist has changed
	 */
	Genode::Signal_transmitter(progress_dispatcher).submit();
}


void Audio_player::Main::report_track(Decoder::Track_info const &info)
{
	reporter.enabled(true);

	try {
		Genode::Reporter::Xml_generator xml(reporter, [&] () {
			xml.attribute("id",       info.id);
			xml.attribute("path",     info.path);
			xml.attribute("artist",   info.artist);
			xml.attribute("album",    info.album);
			xml.attribute("title",    info.title);
			xml.attribute("duration", info.duration);
		});
	} catch (...) { PWRN("could not report current track"); }
}


void Audio_player::Main::handle_progress(unsigned)
{
	if (is_stopped) {
		Genode::destroy(&alloc, decoder);
		decoder    = nullptr;
		is_stopped = false;
	}

	if (is_paused) return;

	/* do not bother, that is not the track you are looking for */
	if (!track.is_valid()) return;

	/* track is valid but there is no decoder yet */
	if (decoder == nullptr) {
		Genode::retry<Decoder::Not_initialized>(
			[&] {
				if (track.is_valid())
					decoder = new (&alloc) Decoder(track);
					report_track(decoder->track_info());
			},
			[&] {
				/* in case it did not work try next track */
				track = playlist.next_track();
			});
	}

	/* only decode and play if we are below the threshold */
	if (client.queued() < QUEUED_PACKET_THRESHOLD) {

		if (decoder && frame_data.read_avail() <= AUDIO_OUT_PACKET_SIZE) {
			int const n = decoder->fill_buffer(frame_data, AUDIO_OUT_PACKET_SIZE);
			if (n == 0) {
				Genode::destroy(&alloc, decoder);
				decoder = nullptr;

				track = playlist.next_track();
			}
		}

		if (frame_data.read_avail() >= AUDIO_OUT_PACKET_SIZE)
			client.drain_buffer(frame_data);
	}
}


void Audio_player::Main::handle_config(unsigned)
{
	Genode::config()->reload();

	Genode::Xml_node config = Genode::config()->xml_node();

	/* handle verbose setting */
	try { verbose = config.attribute("verbose").has_value("yes"); }
	catch (...) { verbose = false; }

	/* handle playlist mode */
	try {
		Genode::String<16> mode;
		config.attribute("playlist_mode").value(&mode);
		if      (mode == "repeat") playlist.set_repeat(true);
		else if (mode == "once")   playlist.set_repeat(false);
		else {
			PWRN("playlist mode invalid, fallback to 'once'");
			playlist.set_repeat(false);
		}
	} catch (...) { }

	/* handle state */
	try {
		Genode::String<16> state;
		config.attribute("state").value(&state);

		if      (state == "playing") is_paused = false;
		else if (state == "paused")  is_paused = true;
		else /*(state == "stopped")*/ {
			is_stopped = true;
			is_paused  = true;
		}
	} catch (...) {
		/* if there is no state attribute we are stopped */
		PWRN("player state invalid, player is stopped");
		is_stopped = true;
		is_paused  = true;
	}

	/* handle selected track */
	try {
		unsigned id = 0;
		config.attribute("selected_track").value(&id);
		if (id != track.id) {
			is_stopped = true;
			track = playlist.get_track(id);

			if (!track.is_valid()) PERR("invalid track %u selected", id);
		}
	} catch (...) { }

	/*
	 * trigger playback because state might has changed
	 */
	Genode::Signal_transmitter(progress_dispatcher).submit();
}


int main(int argc, char *argv[])
{
	/* initialise libav first so that all decoders are present */
	av_register_all();

	/* make libav quiet so we do not need stderr access */
	av_log_set_level(AV_LOG_QUIET);

	static Genode::Signal_receiver sig_rec;
	static Audio_player::Main application(*Genode::env()->heap(), sig_rec);

	/* process incoming signals */
	for (;;) {
		using namespace Genode;

		Signal sig = sig_rec.wait_for_signal();
		Signal_dispatcher_base *dispatcher =
			dynamic_cast<Signal_dispatcher_base *>(sig.context());

		if (dispatcher)
			dispatcher->dispatch(sig.num());
	}
}

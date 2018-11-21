/*
 * \brief  OSS emulation to Audio_out file system
 * \author Josef Soentgen
 * \date   2018-10-25
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <audio_out_session/connection.h>
#include <base/registry.h>
#include <base/signal.h>
#include <gems/magic_ring_buffer.h>
#include <util/xml_generator.h>
#include <vfs/device_file_system.h>
#include <vfs/readonly_value_file_system.h>
#include <vfs/value_file_system.h>

/* include libc */
#include <stdlib.h>

/* local speex includdes */
#include "contrib/speex_resampler.h"


namespace Vfs_oss {
	using namespace Vfs;

	class File_system;
} /* namespace Vfs_oss */


class Vfs_oss::File_system : public Device_file_system
{
	private:

		File_system(File_system const &);
		File_system &operator = (File_system const &);

		typedef Genode::String<64> Label;
		Label _label;
		typedef Genode::String<64> Name;
		Label _name;

		Vfs::Env               &_env;
		Io_response_handler    &_io_handler;
		Watch_response_handler &_watch_handler;

		struct Audio
		{
			private:

				Audio(Audio const &);
				Audio &operator = (Audio const &);

				Genode::Magic_ring_buffer<float> _left_buffer;
				Genode::Magic_ring_buffer<float> _right_buffer;

				bool _started { false };
				bool _buffer_full { false };

				Readonly_value_file_system<unsigned> &_avail_fs;

				Genode::int16_t _srbuffer[81920] { };
				SpeexResamplerState *_srstate { nullptr };

			public:

				enum { CHANNELS = 2, };
				const char *_channel_names[CHANNELS] = { "front left", "front right" };

				Genode::Constructible<Audio_out::Connection> _out[CHANNELS];

				Audio(Genode::Env &env, Label &,
				      Genode::Signal_context_capability alloc_sigh,
				      Genode::Signal_context_capability progress_sigh,
				      Readonly_value_file_system<unsigned> &avail_fs)
				: _left_buffer(env, 1u << 20), _right_buffer(env, 1u << 20), _avail_fs(avail_fs)
				{
					for (int i = 0; i < CHANNELS; i++) {
						try {
							_out[i].construct(env, _channel_names[i], false, false);
						} catch (...) {
							Genode::error("could not create Audio_out channel ", i);
							throw;
						}
					}
					_out[0]->alloc_sigh(alloc_sigh);
					_out[0]->progress_sigh(progress_sigh);

					_avail_fs.value(Audio_out::QUEUE_SIZE);
				}

				bool request_rate(int rate)
				{
					if (_started) { return false; }

					if (_srstate) {
						speex_resampler_destroy(_srstate);
						_srstate = nullptr;
					}

					if (rate == Audio_out::SAMPLE_RATE) { return true; }

					int err = 0;
					_srstate = speex_resampler_init(Audio::CHANNELS, rate,
					                                Audio_out::SAMPLE_RATE, 5, &err);
					return !err && _srstate;
				}

				void pause()
				{
					for (int i = 0; i < CHANNELS; i++) { _out[i]->stop(); }
					_started = false;
				}

				unsigned queued() const
				{
					return _out[0]->stream()->queued();
				}

				bool _queue_threshold_reached() const
				{
					return _out[0]->stream()->queued() > 40;
				}

				bool need_data() const
				{
					return !_queue_threshold_reached();
				}

				bool write(char const *buf, file_size buf_size, file_size &out_size)
				{
					bool block_write = false;

					if (_queue_threshold_reached()) {
						block_write = true;
					} else {

						Genode::size_t samples = Genode::min(_left_buffer.write_avail(), buf_size/2);

						float *dest[2] = { _left_buffer.write_addr(), _right_buffer.write_addr() };

						char const *src = buf;
						if (samples && _srstate) {
							unsigned in_len  = samples / 2;
							unsigned out_len = sizeof(_srbuffer);
#define SRSPII speex_resampler_process_interleaved_int
							int const err = SRSPII(_srstate, (Genode::int16_t*)src, &in_len,
							                       _srbuffer, &out_len);
#undef SRSPII
							if (!err) {
								src     = (char const*)_srbuffer;
								samples = out_len * 2;

							} else { Genode::error("could not resample"); }
						}

						for (Genode::size_t i = 0; i < samples/2; i++) {
							for (int c = 0; c < CHANNELS; c++) {
								float *p = dest[c];
								Genode::int16_t const v = ((Genode::int16_t const*)src)[i * CHANNELS + c];
								p[i] = ((float)v) / 32768.0f;
							}
						}

						_left_buffer.fill(samples/2);
						_right_buffer.fill(samples/2);

						out_size += (samples * 2);
					}

					while (_left_buffer.read_avail() >= Audio_out::PERIOD) {

						if (!_started) {
							_started = true;

							_out[0]->start();
							_out[1]->start();
						}

						Audio_out::Packet *lp = nullptr;

						try { lp = _out[0]->stream()->alloc(); }
						catch (...) {
							Genode::error("stream full",
							              " queued: ", _out[0]->stream()->queued(),
							              " pos: ",    _out[0]->stream()->pos(),
							              " tail: ",   _out[0]->stream()->tail()
							);
							break;
						}
						unsigned const pos    = _out[0]->stream()->packet_position(lp);
						Audio_out::Packet *rp = _out[1]->stream()->get(pos);

						float const *src[CHANNELS] = { _left_buffer.read_addr(),
						                               _right_buffer.read_addr() };

						lp->content(src[0], Audio_out::PERIOD);
						_left_buffer.drain(Audio_out::PERIOD);
						rp->content(src[1], Audio_out::PERIOD);
						_right_buffer.drain(Audio_out::PERIOD);

						_out[0]->submit(lp);
						_out[1]->submit(rp);
					}

					/* update */
					_avail_fs.value(Audio_out::QUEUE_SIZE - _out[0]->stream()->queued());

					if (block_write) { throw Insufficient_buffer(); }

					return true;
				}
		};

		struct Oss_vfs_file_handle : public Device_vfs_handle
		{
			Audio &_audio;

			Oss_vfs_file_handle(Directory_service    &ds,
			                    File_io_service      &fs,
			                    Genode::Allocator    &alloc,
			                    Audio &audio, int flags)
			: Device_vfs_handle(ds, fs, alloc, flags), _audio(audio) { }

			~Oss_vfs_file_handle()
			{
				_audio.pause();
			}

			/* not supported */
			Read_result read(char *, file_size, file_size &) {
				return READ_ERR_INVALID; }

			Write_result write(char const *buf, file_size buf_size, file_size &out_count)
			{
				return _audio.write(buf, buf_size, out_count) ? WRITE_OK : WRITE_ERR_INVALID;
			}

			bool read_ready() { return true; }
		};

		typedef Genode::Registered<Oss_vfs_file_handle> Registered_handle;
		typedef Genode::Registry<Registered_handle>     Handle_registry;

		struct Post_signal_hook : Genode::Entrypoint::Post_signal_hook
		{
			Genode::Entrypoint  &_ep;
			Io_response_handler &_io_handler;
			Vfs_handle::Context *_context = nullptr;

			Post_signal_hook(Genode::Entrypoint &ep,
			                 Io_response_handler &io_handler)
			: _ep(ep), _io_handler(io_handler) { }

			void arm(Vfs_handle::Context *context)
			{
				_context = context;
				_ep.schedule_post_signal_hook(this);
			}

			void function() override
			{
				/*
				 * XXX The current implementation executes the post signal hook
				 *     for the last armed context only. When changing this,
				 *     beware that the called handle_io_response() may change
				 *     this object in a signal handler.
				 */

				_io_handler.handle_io_response(_context);
				_context = nullptr;
			}

			private:

				/*
				 * Noncopyable
				 */
				Post_signal_hook(Post_signal_hook const &);
				Post_signal_hook &operator = (Post_signal_hook const &);
		};

		Handle_registry _handle_registry { };

		Post_signal_hook _post_signal_hook { _env.env().ep(), _io_handler };

		Genode::Io_signal_handler<Vfs_oss::File_system> _alloc_avail_handler {
			_env.env().ep(), *this, &Vfs_oss::File_system::_handle_alloc_avail };

		void _handle_alloc_avail()
		{
			_handle_registry.for_each([this] (Registered_handle &h) {
				_post_signal_hook.arm(h.context);
			});
		}

		Genode::Io_signal_handler<Vfs_oss::File_system> _progress_handler {
			_env.env().ep(), *this, &Vfs_oss::File_system::_handle_progress };

		void _handle_progress()
		{
			unsigned const queued = _audio.queued();
			if (!queued) {
				Genode::error("pause");
				_audio.pause(); }

			_queued_fs.value(queued);

			// if (!_audio.need_data()) { return; }

			_handle_registry.for_each([this] (Registered_handle &h) {
				_post_signal_hook.arm(h.context);
			});
		}

		using Config = Genode::String<4096>;
		static Config _dir_config(Genode::Xml_node node)
		{
			char buf[Config::capacity()] { };

			Genode::Xml_generator xml(buf, sizeof(buf), "dir", [&] {

				using Name = Genode::String<64>;
				Name dir_name = node.attribute_value("name", Name(name()));

				xml.attribute("name", Name(".", dir_name));

				xml.node("readonly_value", [&] { xml.attribute("name", "channels"); });
				xml.node("readonly_value", [&] { xml.attribute("name", "queue_size"); });
				xml.node("readonly_value", [&] { xml.attribute("name", "sample_rate"); });

				xml.node("readonly_value", [&] { xml.attribute("name", "frag_size"); });
				xml.node("readonly_value", [&] { xml.attribute("name", "frag_avail"); });

				xml.node("value", [&] { xml.attribute("name", "ctl"); });
			});
			return Config(Genode::Cstring(buf));
		}

		Readonly_value_file_system<unsigned> _channels_fs    { _env, "channels",    Audio::CHANNELS };
		Readonly_value_file_system<unsigned> _queue_size_fs  { _env, "queue_size",  Audio_out::QUEUE_SIZE };
		Readonly_value_file_system<unsigned> _queued_fs      { _env, "queued",      0 };
		Readonly_value_file_system<unsigned> _sample_rate_fs { _env, "sample_rate", Audio_out::SAMPLE_RATE };

		Readonly_value_file_system<unsigned> _ofrag_size_fs  { _env, "frag_size",  Audio_out::PERIOD * sizeof (Genode::int16_t) };
		Readonly_value_file_system<unsigned> _ofrag_avail_fs { _env, "frag_avail", 0 };

		Genode::Io_signal_handler<Vfs_oss::File_system> _ctl_notify_handler {
			_env.env().ep(), *this, &Vfs_oss::File_system::_handle_ctl_notify };

		void _handle_ctl_notify()
		{
			char const * cmd = _ctl_fs.buffer();

			Genode::error(__func__, " ", cmd);
			if (Genode::strcmp(cmd, "sample_rate ", 12) == 0) {
				unsigned rate = atoi(cmd+12);
				if (_audio.request_rate(rate)) {
					_sample_rate_fs.value(rate);
				} else { Genode::error("could not set rate"); }
			}
		}

		Value_file_system<unsigned> _ctl_fs { _env, "ctl", 0, _ctl_notify_handler };

		Vfs::File_system *create(Vfs::Env &, Genode::Xml_node node) override
		{
			if (node.has_type(Readonly_value_file_system<unsigned>::type_name())) {
				return _channels_fs.matches(node)    ? &_channels_fs
				     : _queue_size_fs.matches(node)  ? &_queue_size_fs
				     : _queued_fs.matches(node)      ? &_queued_fs
				     : _sample_rate_fs.matches(node) ? &_sample_rate_fs
				     : _ofrag_size_fs.matches(node)  ? &_ofrag_size_fs
				     : _ofrag_avail_fs.matches(node) ? &_ofrag_avail_fs
				     : nullptr;
			} else

			if (node.has_type(Value_file_system<unsigned>::type_name())) {
				return _ctl_fs.matches(node) ? &_ctl_fs : nullptr;
			} else

			return nullptr;
		}

		Audio _audio { _env.env(), _label, _alloc_avail_handler, _progress_handler,
		               _ofrag_avail_fs };

	public:

		File_system(Vfs::Env &env, Genode::Xml_node config)
		:
			Device_file_system(NODE_TYPE_CHAR_DEVICE, name(), config),
			_label(config.attribute_value("label", Label())),
			_name(config.attribute_value("name", Name(name()))),
			_env(env), _io_handler(env.io_handler()),
			_watch_handler(env.watch_handler())
		{
			Device_file_system::construct(env, Genode::Xml_node(_dir_config(config).string()), *this);
		}

		static const char *name()   { return "oss"; }
		char const *type() override { return "oss"; }

		/*********************************
		 ** Directory service interface **
		 *********************************/

		Open_result open(char const  *path, unsigned flags,
		                 Vfs_handle **out_handle,
		                 Allocator   &alloc) override
		{
			try {
				if (_device_file(path)) {
					*out_handle = new (alloc)
						Registered_handle(_handle_registry, *this, *this, alloc, _audio, flags);
					return OPEN_OK;
				} else

				if (_device_dir_file(path)) {
					return Device_file_system::open(path, flags, out_handle, alloc);
				}
			}
			catch (Genode::Out_of_ram)  { return OPEN_ERR_OUT_OF_RAM; }
			catch (Genode::Out_of_caps) { return OPEN_ERR_OUT_OF_CAPS; }

			return OPEN_ERR_UNACCESSIBLE;
		}

		/********************************
		 ** File I/O service interface **
		 ********************************/

		Ftruncate_result ftruncate(Vfs_handle *, file_size) override
		{
			return FTRUNCATE_OK;
		}

		bool check_unblock(Vfs_handle *, bool, bool, bool) override
		{
			return true;
		}
};


extern "C" Vfs::File_system_factory *vfs_file_system_factory(void)
{
	struct Factory : Vfs::File_system_factory
	{
		Vfs::File_system *create(Vfs::Env &env, Genode::Xml_node config) override
		{
			return new (env.alloc()) Vfs_oss::File_system(env, config);
		}
	};

	static Factory f;
	return &f;
}

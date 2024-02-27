/*
 * \brief  OSS to Record and Play session translator plugin
 * \author Josef Soentgen
 * \date   2024-02-20
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/registry.h>
#include <base/signal.h>
#include <os/vfs.h>
#include <play_session/connection.h>
#include <record_session/connection.h>
#include <timer_session/connection.h>
#include <util/xml_generator.h>
#include <vfs/dir_file_system.h>
#include <vfs/readonly_value_file_system.h>
#include <vfs/single_file_system.h>
#include <vfs/value_file_system.h>

#include "ring_buffer.h"

namespace Vfs {
	using namespace Genode;

	struct Oss_file_system;
} /* namespace Vfs */


struct Vfs::Oss_file_system
{
	using Name = String<32>;

	struct Audio;

	struct Data_file_system;
	struct Local_factory;
	struct Compound_file_system;
};


struct Vfs::Oss_file_system::Audio
{
	public:

		struct Info
		{
			unsigned  channels;
			unsigned  format;
			unsigned  sample_rate;
			unsigned  ifrag_total;
			unsigned  ifrag_size;
			unsigned  ifrag_avail;
			unsigned  ifrag_bytes;
			unsigned  ofrag_total;
			unsigned  ofrag_size;
			unsigned  ofrag_avail;
			unsigned  ofrag_bytes;
			long long optr_samples;
			unsigned  optr_fifo_samples;
			unsigned  play_underruns;

			Readonly_value_file_system<unsigned>  &_channels_fs;
			Readonly_value_file_system<unsigned>  &_format_fs;
			Readonly_value_file_system<unsigned>  &_sample_rate_fs;
			Value_file_system<unsigned>           &_ifrag_total_fs;
			Value_file_system<unsigned>           &_ifrag_size_fs;
			Readonly_value_file_system<unsigned>  &_ifrag_avail_fs;
			Readonly_value_file_system<unsigned>  &_ifrag_bytes_fs;
			Value_file_system<unsigned>           &_ofrag_total_fs;
			Value_file_system<unsigned>           &_ofrag_size_fs;
			Readonly_value_file_system<unsigned>  &_ofrag_avail_fs;
			Readonly_value_file_system<unsigned>  &_ofrag_bytes_fs;
			Readonly_value_file_system<long long> &_optr_samples_fs;
			Readonly_value_file_system<unsigned>  &_optr_fifo_samples_fs;
			Value_file_system<unsigned>           &_play_underruns_fs;

			Info(Readonly_value_file_system<unsigned>  &channels_fs,
			     Readonly_value_file_system<unsigned>  &format_fs,
			     Readonly_value_file_system<unsigned>  &sample_rate_fs,
			     Value_file_system<unsigned>           &ifrag_total_fs,
			     Value_file_system<unsigned>           &ifrag_size_fs,
			     Readonly_value_file_system<unsigned>  &ifrag_avail_fs,
			     Readonly_value_file_system<unsigned>  &ifrag_bytes_fs,
			     Value_file_system<unsigned>           &ofrag_total_fs,
			     Value_file_system<unsigned>           &ofrag_size_fs,
			     Readonly_value_file_system<unsigned>  &ofrag_avail_fs,
			     Readonly_value_file_system<unsigned>  &ofrag_bytes_fs,
			     Readonly_value_file_system<long long> &optr_samples_fs,
			     Readonly_value_file_system<unsigned>  &optr_fifo_samples_fs,
			     Value_file_system<unsigned>           &play_underruns_fs)
			:
				channels              { 0 },
				format                { 0 },
				sample_rate           { 0 },
				ifrag_total           { 0 },
				ifrag_size            { 0 },
				ifrag_avail           { 0 },
				ifrag_bytes           { 0 },
				ofrag_total           { 0 },
				ofrag_size            { 0 },
				ofrag_avail           { 0 },
				ofrag_bytes           { 0 },
				optr_samples          { 0 },
				optr_fifo_samples     { 0 },
				play_underruns        { 0 },
				_channels_fs          { channels_fs },
				_format_fs            { format_fs },
				_sample_rate_fs       { sample_rate_fs },
				_ifrag_total_fs       { ifrag_total_fs },
				_ifrag_size_fs        { ifrag_size_fs },
				_ifrag_avail_fs       { ifrag_avail_fs },
				_ifrag_bytes_fs       { ifrag_bytes_fs },
				_ofrag_total_fs       { ofrag_total_fs },
				_ofrag_size_fs        { ofrag_size_fs },
				_ofrag_avail_fs       { ofrag_avail_fs },
				_ofrag_bytes_fs       { ofrag_bytes_fs },
				_optr_samples_fs      { optr_samples_fs },
				_optr_fifo_samples_fs { optr_fifo_samples_fs },
				_play_underruns_fs    { play_underruns_fs }
			{ }

			void update()
			{
				_channels_fs         .value(channels);
				_format_fs           .value(format);
				_sample_rate_fs      .value(sample_rate);
				_ifrag_total_fs      .value(ifrag_total);
				_ifrag_size_fs       .value(ifrag_size);
				_ifrag_avail_fs      .value(ifrag_avail);
				_ifrag_bytes_fs      .value(ifrag_bytes);
				_ofrag_total_fs      .value(ofrag_total);
				_ofrag_size_fs       .value(ofrag_size);
				_ofrag_avail_fs      .value(ofrag_avail);
				_ofrag_bytes_fs      .value(ofrag_bytes);
				_optr_samples_fs     .value(optr_samples);
				_optr_fifo_samples_fs.value(optr_fifo_samples);
				_play_underruns_fs   .value(play_underruns);
			}

			void print(Genode::Output &out) const
			{
				char buf[512] { };

				Genode::Xml_generator xml(buf, sizeof(buf), "oss", [&] () {
					xml.attribute("channels",          channels);
					xml.attribute("format",            format);
					xml.attribute("sample_rate",       sample_rate);
					xml.attribute("ifrag_total",       ifrag_total);
					xml.attribute("ifrag_size",        ifrag_size);
					xml.attribute("ifrag_avail",       ifrag_avail);
					xml.attribute("ifrag_bytes",       ifrag_bytes);
					xml.attribute("ofrag_total",       ofrag_total);
					xml.attribute("ofrag_size",        ofrag_size);
					xml.attribute("ofrag_avail",       ofrag_avail);
					xml.attribute("ofrag_bytes",       ofrag_bytes);
					xml.attribute("optr_samples",      optr_samples);
					xml.attribute("optr_fifo_samples", optr_fifo_samples);
					xml.attribute("play_underruns",    play_underruns);
				});

				Genode::print(out, Genode::Cstring(buf));
			}
		};

		using Read_result  = Vfs::File_io_service::Read_result;
		using Write_result = Vfs::File_io_service::Write_result;


	private:

		Audio(Audio const &);
		Audio &operator = (Audio const &);

		Info &_info;
		Readonly_value_file_system<Info, 512> &_info_fs;

		void _with_duration(size_t const bytes, auto const &fn)
		{
			unsigned const frame_size   = _info.channels * _format_size(_info.format);
			unsigned const samples      = (unsigned)bytes / frame_size;
			float    const tmp_duration = float(1'000'000u)
			                            / float(_info.sample_rate)
			                            * float(samples);

			fn(unsigned(tmp_duration), samples);
		}


		bool     const _verbose;

		enum : unsigned {
			MAX_CHANNELS   = 2u,

			/*  512 S16LE stereo -> 11.6 ms at 44.1kHz */
			MIN_OFRAG_SIZE = 2048u,
			/* 2048 S16LE stereo -> 46.4 ms at 44.1kHz */
			MAX_OFRAG_SIZE = 8192u,

			MIN_IFRAG_SIZE = MIN_OFRAG_SIZE,
			MAX_IFRAG_SIZE = MAX_OFRAG_SIZE,
		};

		/* XXX move Stereo_output object */

		Timer::Connection _play_timer;

		Genode::Constructible<Play::Connection> _play[MAX_CHANNELS];

		void _for_each_play_session(auto const &fn)
		{
			for (auto &v : _play)
				if (v.constructed())
					fn(*v);
		}

		using Ring_buffer = Util::Ring_buffer<128u << 10>;
		Ring_buffer _play_buffer[MAX_CHANNELS] { };

		Play::Duration    _play_timer_duration { 0 };
		Play::Time_window _play_time_window { };
		unsigned          _play_timer_limit { 0 };

		unsigned _output_samples_per_fragment = 0;

		void _update_output_info()
		{
			_info.ofrag_bytes = unsigned((_info.ofrag_total * _info.ofrag_size)
			                  - (_info.optr_fifo_samples * _info.channels * sizeof(short)));
			_info.ofrag_avail = _info.ofrag_bytes / _info.ofrag_size;

			_info.update();
			_info_fs.value(_info);
		}

		void _for_each_sample(Ring_buffer    &buffer,
		                      unsigned const  samples,
		                      auto     const &fn) const
		{
			for (unsigned i = 0; i < samples; i++) {
				float v = 0;
				Byte_range_ptr range { (char*)&v, sizeof(v) };
				buffer.read(range);

				fn(v);
			}
		}

		void _stereo_output(unsigned       const  samples,
		                    Play::Duration const  duration)
		{
			bool first = true;

			_for_each_play_session([&] (Play::Connection &play) {
				if (first) {
					_play_time_window = play.schedule_and_enqueue(_play_time_window, duration,
						[&] (auto &submit) {
							_for_each_sample(_play_buffer[0], samples,
								[&] (float const v) { submit(v); }); });
					first = false;
					return;
				}

				play.enqueue(_play_time_window,
					[&] (auto &submit) {
						_for_each_sample(_play_buffer[1], samples,
							[&] (float const v) { submit(v); }); });
			});
		}

		static unsigned _format_size(unsigned fmt)
		{
			if (fmt == 0x00000010u) /* S16LE */
				return 2u;

			return 0u;
		}

		unsigned _sample_count(Const_byte_range_ptr const &range) const
		{
			return (unsigned)range.num_bytes / (_format_size(_info.format) * _info.channels);
		}

		void _fill_buffer(Const_byte_range_ptr const &src, Ring_buffer &buffer, int channel)
		{
			short const *data = (short const*)(src.start);
			float const scale = 1.0f/32768;

			unsigned int const channels = _info.channels;
			size_t       const samples  = _sample_count(src);

			for (size_t i = 0; i < samples; i++) {
				float const v = scale * float(data[i * channels + channel]);
				buffer.write(Const_byte_range_ptr { (char const*)&v, sizeof(v) });
			}
		}

		bool _play_buffer_write_samples_avail(unsigned samples) const
		{
			return _play_buffer[0].samples_write_avail<float>() >= samples;
		}

		bool _play_buffer_range_avail(Const_byte_range_ptr const &src) const
		{
			return _play_buffer_write_samples_avail(_sample_count(src));
		}

		bool _play_buffer_read_samples_avail(unsigned samples) const
		{
			return _play_buffer[0].samples_read_avail<float>() >= samples;
		}

		bool _play_timer_pending { false };
		bool _play_timer_started { false };

		void _try_schedule_and_enqueue()
		{
			if (_play_timer_pending || !_play_buffer_read_samples_avail(_output_samples_per_fragment))
				return;

			_play_timer_pending = true;

			if (!_play_timer_started) {
				_play_timer_started = true;
				_play_timer.trigger_periodic(_play_timer_duration.us);
			}

			_stereo_output(_output_samples_per_fragment,
			               _play_timer_duration);

			/*
			 * For now we ignore 'optr_samples' altogether but we
			 * could use it later on to denote the samples currently
			 * played while 'optr_fifo_samples' sums up the samples
			 * in the ring-buffer.
			 */
			_info.optr_fifo_samples += _output_samples_per_fragment;
			_update_output_info();
		}


		unsigned long _last_write { 0 };
		unsigned long _play_timer_counter { 0 };

		void _halt_output()
		{
			_for_each_play_session([&] (Play::Connection &play) {
				play.stop();
			});

			_play_timer_counter = 0;

			_play_timer_pending = false;
			_play_timer_started = false;
			_play_timer.trigger_periodic(0);
			_play_time_window = Play::Time_window { };
		}

		bool     const _play_enabled;
		unsigned       _max_ofrag_size;
		unsigned       _min_ofrag_size;

		/* XXX move to Stereo_input object */

		Timer::Connection _record_timer;

		Genode::Constructible<Record::Connection> _record[MAX_CHANNELS];

		void _for_each_record_session(auto const &fn)
		{
			for (auto &v : _record)
				if (v.constructed())
					fn(*v);
		}

		Ring_buffer _record_buffer[1] { };

		unsigned _record_timer_duration { 0 };
		Record::Num_samples _input_samples_per_fragment { 0 };

		void _update_input_info()
		{
			_info.ifrag_avail = _info.ifrag_bytes / _info.ifrag_size;

			_info.update();
			_info_fs.value(_info);
		}

		short _collect_buffer[MAX_OFRAG_SIZE];

		void _stereo_input(Record::Num_samples const num_samples)
		{
			auto clamped = [&] (float v)
			{
				return (v >  1.0) ?  1.0
				     : (v < -1.0) ? -1.0
				     :  v;
			};

			auto float_to_s16 = [&] (float v) { return int16_t(clamped(v)*32767); };

			bool depleted = false;
			_record[0]->record(num_samples,
				[&] (Record::Time_window const tw,
				     Record::Connection::Samples_ptr const &samples) {
						for (unsigned i = 0; i < num_samples.value(); i++)
							_collect_buffer[i*MAX_CHANNELS] = float_to_s16(samples.start[i]);

					_record[1]->record_at(tw, num_samples,
						[&] (Record::Connection::Samples_ptr const &samples) {
							for (unsigned i = 0; i < num_samples.value(); i++)
								_collect_buffer[i*MAX_CHANNELS+1] = float_to_s16(samples.start[i]);
						});
				},
				[&] {
					/* depleted */
					memset(_collect_buffer, 0, sizeof(_collect_buffer));
					depleted = true;
				});

			if (depleted)
				return;

			size_t const collect_avail = num_samples.value() * _info.channels * _format_size(_info.format);
			size_t const write_avail   = _record_buffer[0].write_avail();
			if (write_avail < collect_avail)
				Genode::warning("overrun of ", collect_avail - write_avail, " bytes");

			size_t const write_bytes = Genode::min(collect_avail, write_avail);
			_record_buffer[0].write(Const_byte_range_ptr { (char const*)_collect_buffer,
			                                               write_bytes });
		}

		bool _record_timer_started { false };

		void _try_record()
		{
			if (!_record_timer_started) {
				_record_timer.trigger_periodic(_record_timer_duration);
				_record_timer_started = true;
			}

			_stereo_input(_input_samples_per_fragment);

			_info.ifrag_bytes = (unsigned)_record_buffer[0].read_avail();
			_update_input_info();
		}

		void _halt_input()
		{
			_info.ifrag_bytes = 0;
			_record_buffer[0].reset();

			_record_timer_started = false;
			_record_timer.trigger_periodic(0);
		}


		bool     const _record_enabled;
		unsigned       _max_ifrag_size;
		unsigned       _min_ifrag_size;

		unsigned _default_frag_size(Xml_node const &config,
		                            char const *attr, unsigned value) const
		{
			return config.attribute_value(attr, value);
		}

		void _clamp_frag_sizes()
		{
			_min_ofrag_size = Genode::max(_min_ofrag_size, MIN_OFRAG_SIZE);
			_max_ofrag_size = Genode::min(_max_ofrag_size, MAX_OFRAG_SIZE);

			if (_min_ofrag_size > _max_ofrag_size)
				_min_ofrag_size = _max_ofrag_size;

			_min_ifrag_size = Genode::max(_min_ifrag_size, MIN_OFRAG_SIZE);
			_max_ifrag_size = Genode::min(_max_ifrag_size, MAX_OFRAG_SIZE);

			if (_min_ifrag_size > _max_ifrag_size)
				_min_ifrag_size = _max_ifrag_size;
		}

	public:

		Audio(Genode::Env &env,
		      Info        &info,
		      Readonly_value_file_system<Info, 512> &info_fs,
		      Xml_node config)
		:
			_info            { info },
			_info_fs         { info_fs },

			/* XXX move into Config object */
			_verbose         { config.attribute_value("verbose",         false) },

			_play_timer      { env },
			_play_enabled    { config.attribute_value("play_enabled", true) },
			_max_ofrag_size  { _default_frag_size(config, "max_ofrag_size", MAX_OFRAG_SIZE) },
			_min_ofrag_size  { _default_frag_size(config, "min_ofrag_size", MIN_OFRAG_SIZE) },

			_record_timer    { env },
			_record_enabled  { config.attribute_value("record_enabled", true) },
			_max_ifrag_size  { _default_frag_size(config, "max_ifrag_size", MAX_IFRAG_SIZE) },
			_min_ifrag_size  { _default_frag_size(config, "min_ifrag_size", MIN_IFRAG_SIZE) }
		{
			_clamp_frag_sizes();

			_info.channels    = MAX_CHANNELS;
			_info.format      = (unsigned)0x00000010; /* S16LE */
			_info.sample_rate = 44'100u;

			if (_play_enabled) {
				_play[0].construct(env, "left");
				_play[1].construct(env, "right");

				_info.ofrag_size  = _min_ofrag_size;
				_info.ofrag_total = 4;
				_info.ofrag_avail = _info.ofrag_total;
				_info.ofrag_bytes = _info.ofrag_avail * _info.ofrag_size;

				update_output_duration(_info.ofrag_size);
			}

			if (_record_enabled) {
				_record[0].construct(env, "left");
				_record[1].construct(env, "right");

				_info.ifrag_size  = _min_ifrag_size;
				_info.ifrag_total = 4;
				_info.ifrag_avail = 0;
				_info.ifrag_bytes = 0;

				update_input_duration(_info.ifrag_size);
			}

			_info.update();
			_info_fs.value(_info);
		}

		bool verbose() const
		{
			return _verbose;
		}

		/**************************
		 ** Record session stuff **
		 **************************/

		unsigned max_ifrag_size() const { return _max_ifrag_size; }

		unsigned min_ifrag_size() const { return _min_ifrag_size; }

		void update_input_duration(unsigned const bytes)
		{
			_with_duration(bytes,
				[&] (unsigned const duration, unsigned const samples) {
					_record_timer_duration = duration;
					_input_samples_per_fragment = Record::Num_samples { samples };
				});
		}

		void record_timer_sigh(Genode::Signal_context_capability cap)
		{
			_record_timer.sigh(cap);
		}

		bool handle_record_timer()
		{
			_try_record();
			return true;
		}

		void enable_input(bool enable)
		{
			if (enable == false)
				_halt_input();
			else
				_try_record();
		}

		bool read_ready() const
		{
			if (!_record_enabled)
				return true;

			return _record_buffer[0].read_avail() >= _info.ifrag_size;
		}

		Read_result read(Byte_range_ptr const &dst, size_t &out_size)
		{
			if (!_record_enabled) {
				Genode::memset(dst.start, 0, dst.num_bytes);
				out_size = dst.num_bytes;
				return Read_result::READ_OK;
			}

			/* get the ball rolling on first read */
			if (!_record_timer_started) {
				_try_record();
			}

			unsigned long const avail = _record_buffer[0].read_avail();

			if (avail < _info.ifrag_size)
				return Read_result::READ_QUEUED;

			unsigned long const bytes_read = Genode::min((size_t)_info.ifrag_size, dst.num_bytes);
			_record_buffer[0].read(Byte_range_ptr { dst.start, bytes_read });

			_info.ifrag_bytes = (unsigned)_record_buffer[0].read_avail();

			_update_input_info();

			out_size = bytes_read;
			return Read_result::READ_OK;
		}

		/************************
		 ** Play session stuff **
		 ************************/

		unsigned max_ofrag_size() const { return _max_ofrag_size; }

		unsigned min_ofrag_size() const { return _min_ofrag_size; }

		void update_output_duration(unsigned const bytes)
		{
			_with_duration(bytes,
				[&] (unsigned const duration, unsigned const samples) {
					_play_timer_duration         = Play::Duration { duration };
					_output_samples_per_fragment = samples;
				});

			_play_timer_limit = 500'000u / _play_timer_duration.us;
		}

		void play_timer_sigh(Genode::Signal_context_capability cap)
		{
			_play_timer.sigh(cap);
		}

		bool handle_play_timer()
		{
			_play_timer_counter++;

			_info.optr_fifo_samples -= _output_samples_per_fragment;
			_update_output_info();

			/*
			 * Try to schedule the next duration if there are
			 * samples left in the buffers. If that's not the
			 * case stop the play session altogether so we
			 * start with a green slate the next time something
			 * gets played.
			 *
			 * In addition to counting the underruns we check
			 * how many timer calls we missed to detect stale
			 * sessions as some clients, e.g. cmus, do not
			 * close the device but simply omit write calls.
			 */
			_play_timer_pending = false;
			_try_schedule_and_enqueue();
			if (!_play_timer_pending) {
				if (_verbose)
					Genode::log("Buffer empty, stop playback");

				_info.play_underruns++;

				/* treat calculated number of underruns as stop */
				if ((_play_timer_counter - _last_write) > _play_timer_limit)
					_halt_output();
			}

			return true;
		}

		void enable_output(bool enable)
		{
			Genode::error(__func__, ": enable: ", enable);
			if (enable == false)
				_halt_output();
			else
				_try_schedule_and_enqueue();
		}

		bool write_ready() const
		{
			return _play_buffer_write_samples_avail(2*_output_samples_per_fragment);
		}

		Write_result write(Const_byte_range_ptr const &src, size_t &out_size)
		{
			out_size = 0;

			/* XXX document why limiting is reasonable */
			if (!_play_buffer_range_avail(src)
			  || _play_buffer_read_samples_avail(2*_output_samples_per_fragment))
				return Write_result::WRITE_ERR_WOULD_BLOCK;

			out_size = src.num_bytes;

			/* check channel has its own buffer */
			for (unsigned i = 0; i < _info.channels; i++)
				_fill_buffer(src, _play_buffer[i], i);

			_try_schedule_and_enqueue();

			_last_write = _play_timer_counter;

			return Write_result::WRITE_OK;
		}
};


class Vfs::Oss_file_system::Data_file_system : public Single_file_system
{
	private:

		Data_file_system(Data_file_system const &);
		Data_file_system &operator = (Data_file_system const &);

		Genode::Entrypoint &_ep;
		Vfs::Env::User     &_vfs_user;
		Audio              &_audio;

		struct Oss_vfs_handle : public Single_vfs_handle
		{
			Audio &_audio;

			Oss_vfs_handle(Directory_service      &ds,
			                    File_io_service   &fs,
			                    Genode::Allocator &alloc,
			                    int                flags,
			                    Audio             &audio)
			:
				Single_vfs_handle { ds, fs, alloc, flags },
				_audio { audio }
			{ }

			Read_result read(Byte_range_ptr const &dst, size_t &out_count) override
			{
				return _audio.read(dst, out_count);
			}

			Write_result write(Const_byte_range_ptr const &src, size_t &out_count) override
			{
				return _audio.write(src, out_count);
			}

			bool read_ready() const override
			{
				return _audio.read_ready();
			}

			bool write_ready() const override
			{
				return _audio.write_ready();
			}
		};

		using Registered_handle = Genode::Registered<Oss_vfs_handle>;
		using Handle_registry   = Genode::Registry<Registered_handle>;

		Handle_registry _handle_registry { };

		Genode::Io_signal_handler<Vfs::Oss_file_system::Data_file_system> _play_timer {
			_ep, *this, &Vfs::Oss_file_system::Data_file_system::_handle_play_timer };

		void _handle_play_timer()
		{
			if (_audio.handle_play_timer())
				_vfs_user.wakeup_vfs_user();
		}

		Genode::Io_signal_handler<Vfs::Oss_file_system::Data_file_system> _record_timer {
			_ep, *this, &Vfs::Oss_file_system::Data_file_system::_handle_record_timer };

		void _handle_record_timer()
		{
			if (_audio.handle_record_timer())
				_vfs_user.wakeup_vfs_user();
		}

	public:

		Data_file_system(Genode::Entrypoint &ep,
		                 Vfs::Env::User     &vfs_user,
		                 Audio              &audio,
		                 Name         const &name)
		:
			Single_file_system { Node_type::CONTINUOUS_FILE, name.string(),
			                     Node_rwx::ro(), Genode::Xml_node("<data/>") },

			_ep       { ep },
			_vfs_user { vfs_user },
			_audio    { audio }
		{
			_audio.play_timer_sigh(_play_timer);
			_audio.record_timer_sigh(_record_timer);
		}

		static const char *name()   { return "data"; }
		char const *type() override { return "data"; }

		/*********************************
		 ** Directory service interface **
		 *********************************/

		Open_result open(char const  *path, unsigned flags,
		                 Vfs_handle **out_handle,
		                 Allocator   &alloc) override
		{
			if (!_single_file(path)) {
				return OPEN_ERR_UNACCESSIBLE;
			}

			try {
				*out_handle = new (alloc)
					Registered_handle(_handle_registry, *this, *this, alloc, flags,
					                  _audio);
				return OPEN_OK;
			}
			catch (Genode::Out_of_ram)  { return OPEN_ERR_OUT_OF_RAM; }
			catch (Genode::Out_of_caps) { return OPEN_ERR_OUT_OF_CAPS; }
		}

		/********************************
		 ** File I/O service interface **
		 ********************************/

		Ftruncate_result ftruncate(Vfs_handle *, file_size) override
		{
			return FTRUNCATE_OK;
		}
};


struct Vfs::Oss_file_system::Local_factory : File_system_factory
{
	using Label = Genode::String<64>;
	Label const _label;
	Name  const _name;

	Vfs::Env &_env;

	/* RO/RW files */
	Readonly_value_file_system<unsigned>  _channels_fs          { "channels", 0U };
	Readonly_value_file_system<unsigned>  _format_fs            { "format", 0U };
	Readonly_value_file_system<unsigned>  _sample_rate_fs       { "sample_rate", 0U };
	Value_file_system<unsigned>           _ifrag_total_fs       { "ifrag_total", 0U };
	Value_file_system<unsigned>           _ifrag_size_fs        { "ifrag_size", 0U} ;
	Readonly_value_file_system<unsigned>  _ifrag_avail_fs       { "ifrag_avail", 0U };
	Readonly_value_file_system<unsigned>  _ifrag_bytes_fs       { "ifrag_bytes", 0U };
	Value_file_system<unsigned>           _ofrag_total_fs       { "ofrag_total", 0U };
	Value_file_system<unsigned>           _ofrag_size_fs        { "ofrag_size", 0U} ;
	Readonly_value_file_system<unsigned>  _ofrag_avail_fs       { "ofrag_avail", 0U };
	Readonly_value_file_system<unsigned>  _ofrag_bytes_fs       { "ofrag_bytes", 0U };
	Readonly_value_file_system<long long> _optr_samples_fs      { "optr_samples", 0LL };
	Readonly_value_file_system<unsigned>  _optr_fifo_samples_fs { "optr_fifo_samples", 0U };
	Value_file_system<unsigned>           _play_underruns_fs    { "play_underruns", 0U };
	Value_file_system<unsigned>           _enable_input_fs      { "enable_input", 1U };
	Value_file_system<unsigned>           _enable_output_fs     { "enable_output", 1U };

	/* WO files */
	Value_file_system<unsigned>           _halt_input_fs        { "halt_input", 0U };
	Value_file_system<unsigned>           _halt_output_fs       { "halt_output", 0U };

	Audio::Info _info { _channels_fs, _format_fs, _sample_rate_fs,
	                    _ifrag_total_fs, _ifrag_size_fs,
	                    _ifrag_avail_fs, _ifrag_bytes_fs,
	                    _ofrag_total_fs, _ofrag_size_fs,
	                    _ofrag_avail_fs, _ofrag_bytes_fs,
	                    _optr_samples_fs, _optr_fifo_samples_fs,
	                    _play_underruns_fs };

	Readonly_value_file_system<Audio::Info, 512> _info_fs { "info", _info };

	Audio _audio;

	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _enable_input_handler {
		_enable_input_fs, "/enable_input",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_enable_input_changed };

	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _halt_input_handler {
		_halt_input_fs, "/halt_input",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_halt_input_changed };

	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _ifrag_total_handler {
		_ifrag_total_fs, "/ifrag_total",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_ifrag_total_changed };

	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _ifrag_size_handler {
		_ifrag_size_fs, "/ifrag_size",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_ifrag_size_changed };


	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _enable_output_handler {
		_enable_output_fs, "/enable_output",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_enable_output_changed };

	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _halt_output_handler {
		_halt_output_fs, "/halt_output",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_halt_output_changed };

	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _ofrag_total_handler {
		_ofrag_total_fs, "/ofrag_total",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_ofrag_total_changed };

	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _ofrag_size_handler {
		_ofrag_size_fs, "/ofrag_size",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_ofrag_size_changed };

	Genode::Io::Watch_handler<Vfs::Oss_file_system::Local_factory> _play_underruns_handler {
		_play_underruns_fs, "/play_underruns",
		_env.alloc(),
		*this,
		&Vfs::Oss_file_system::Local_factory::_play_underruns_changed };


	/********************
	 ** Watch handlers **
	 ********************/

	void _enable_input_changed()
	{
		bool const enable = (bool)_enable_input_fs.value();
		_audio.enable_input(enable);
	}

	void _halt_input_changed()
	{
		bool const halt = (bool)_halt_input_fs.value();
		if (halt)
			_audio.enable_input(false);
	}

	void _ifrag_total_changed()
	{
		/*
		 * NOP for now as it is set in tandem with ifrag_size
		 * that in return limits number of fragments.
		 */
	}

	void _ifrag_size_changed()
	{
		unsigned const ifrag_size_max = _audio.max_ifrag_size();
		unsigned const ifrag_size_min = _audio.min_ifrag_size();

		unsigned ifrag_size_new = _ifrag_size_fs.value();

		ifrag_size_new = Genode::max(ifrag_size_new, ifrag_size_min);
		ifrag_size_new = Genode::min(ifrag_size_new, ifrag_size_max);

		_info.ifrag_size = ifrag_size_new;

		_info.ifrag_total = 4;

		_info.ifrag_avail = 0;
		_info.ifrag_bytes = _info.ifrag_avail * _info.ifrag_size;

		_audio.update_input_duration(_info.ifrag_size);

		_info.update();
		_info_fs.value(_info);

		if (_audio.verbose())
			Genode::log(_info);
	}

	void _enable_output_changed()
	{
		bool const enable = (bool)_enable_output_fs.value();
		_audio.enable_output(enable);
	}

	void _halt_output_changed()
	{
		bool const halt = (bool)_halt_output_fs.value();
		if (halt)
			_audio.enable_output(false);
	}

	void _ofrag_total_changed()
	{
		/*
		 * NOP for now as it is set in tandem with ofrag_size
		 * that in return limits number of fragments.
		 */
	}

	void _ofrag_size_changed()
	{
		unsigned const ofrag_size_max = _audio.max_ofrag_size();
		unsigned const ofrag_size_min = _audio.min_ofrag_size();

		unsigned ofrag_size_new = _ofrag_size_fs.value();

		ofrag_size_new = Genode::max(ofrag_size_new, ofrag_size_min);
		ofrag_size_new = Genode::min(ofrag_size_new, ofrag_size_max);

		_info.ofrag_size = ofrag_size_new;

		_info.ofrag_total = 4;

		_info.ofrag_avail = _info.ofrag_total;
		_info.ofrag_bytes = _info.ofrag_total * _info.ofrag_size;

		_audio.update_output_duration(_info.ofrag_size);

		_info.update();
		_info_fs.value(_info);

		if (_audio.verbose())
			Genode::log(_info);
	}

	void _play_underruns_changed()
	{
		/* reset counter */
		_info.play_underruns = 0;

		_info.update();
		_info_fs.value(_info);
	}

	static Name name(Xml_node config)
	{
		return config.attribute_value("name", Name("oss_next"));
	}

	Data_file_system _data_fs;

	Local_factory(Vfs::Env &env, Xml_node config)
	:
		_label   { config.attribute_value("label", Label("")) },
		_name    { name(config) },
		_env     { env },
		_audio  { _env.env(), _info, _info_fs, config },
		_data_fs { _env.env().ep(), env.user(), _audio, name(config) }
	{ }

	Vfs::File_system *create(Vfs::Env&, Xml_node node) override
	{
		if (node.has_type("data")) return &_data_fs;
		if (node.has_type("info")) return &_info_fs;

		if (node.has_type(Readonly_value_file_system<unsigned>::type_name())) {

			if (_channels_fs.matches(node))          return &_channels_fs;
			if (_sample_rate_fs.matches(node))       return &_sample_rate_fs;
			if (_ifrag_avail_fs.matches(node))       return &_ifrag_avail_fs;
			if (_ifrag_bytes_fs.matches(node))       return &_ifrag_bytes_fs;
			if (_ofrag_avail_fs.matches(node))       return &_ofrag_avail_fs;
			if (_ofrag_bytes_fs.matches(node))       return &_ofrag_bytes_fs;
			if (_format_fs.matches(node))            return &_format_fs;
			if (_optr_samples_fs.matches(node))      return &_optr_samples_fs;
			if (_optr_fifo_samples_fs.matches(node)) return &_optr_fifo_samples_fs;
		}

		if (node.has_type(Value_file_system<unsigned>::type_name())) {

			if (_enable_input_fs.matches(node))   return &_enable_input_fs;
			if (_enable_output_fs.matches(node))  return &_enable_output_fs;
			if (_halt_input_fs.matches(node))     return &_halt_input_fs;
			if (_halt_output_fs.matches(node))    return &_halt_output_fs;
			if (_ifrag_total_fs.matches(node))    return &_ifrag_total_fs;
			if (_ifrag_size_fs.matches(node))     return &_ifrag_size_fs;
			if (_ofrag_total_fs.matches(node))    return &_ofrag_total_fs;
			if (_ofrag_size_fs.matches(node))     return &_ofrag_size_fs;
			if (_play_underruns_fs.matches(node)) return &_play_underruns_fs;
		}

		return nullptr;
	}
};


class Vfs::Oss_file_system::Compound_file_system : private Local_factory,
                                                   public  Vfs::Dir_file_system
{
	private:

		using Name = Oss_file_system::Name;

		using Config = String<1024>;
		static Config _config(Name const &name)
		{
			char buf[Config::capacity()] { };

			/*
			 * By not using the node type "dir", we operate the
			 * 'Dir_file_system' in root mode, allowing multiple sibling nodes
			 * to be present at the mount point.
			 */
			Genode::Xml_generator xml(buf, sizeof(buf), "compound", [&] () {

				xml.node("data", [&] () {
					xml.attribute("name", name); });

				xml.node("dir", [&] () {
					xml.attribute("name", Name(".", name));
					xml.node("info", [&] () { });

					xml.node("readonly_value", [&] {
						xml.attribute("name", "channels");
					});

					xml.node("readonly_value", [&] {
							 xml.attribute("name", "sample_rate");
					});

					xml.node("readonly_value", [&] {
						xml.attribute("name", "format");
					});

					xml.node("value", [&] {
						xml.attribute("name", "enable_input");
					});

					xml.node("value", [&] {
						xml.attribute("name", "enable_output");
					});

					xml.node("value", [&] {
						xml.attribute("name", "halt_input");
					});

					xml.node("value", [&] {
						xml.attribute("name", "halt_output");
					});

					xml.node("value", [&] {
						xml.attribute("name", "ifrag_total");
					});

					xml.node("value", [&] {
						 xml.attribute("name", "ifrag_size");
					});

					xml.node("readonly_value", [&] {
						 xml.attribute("name", "ifrag_avail");
					});

					xml.node("readonly_value", [&] {
						 xml.attribute("name", "ifrag_bytes");
					});

					xml.node("value", [&] {
						xml.attribute("name", "ofrag_total");
					});

					xml.node("value", [&] {
						 xml.attribute("name", "ofrag_size");
					});

					xml.node("readonly_value", [&] {
						 xml.attribute("name", "ofrag_avail");
					});

					xml.node("readonly_value", [&] {
						 xml.attribute("name", "ofrag_bytes");
					});

					xml.node("readonly_value", [&] {
						 xml.attribute("name", "optr_samples");
					});

					xml.node("readonly_value", [&] {
						 xml.attribute("name", "optr_fifo_samples");
					});

					xml.node("value", [&] {
						 xml.attribute("name", "play_underruns");
					});
				});
			});

			return Config(Genode::Cstring(buf));
		}

	public:

		Compound_file_system(Vfs::Env &vfs_env, Genode::Xml_node node)
		:
			Local_factory { vfs_env, node },
			Vfs::Dir_file_system { vfs_env,
			                       Xml_node(_config(Local_factory::name(node)).string()),
			                       *this }
		{ }

		static const char *name() { return "oss_next"; }

		char const *type() override { return name(); }
};


extern "C" Vfs::File_system_factory *vfs_file_system_factory(void)
{
	struct Factory : Vfs::File_system_factory
	{
		Vfs::File_system *create(Vfs::Env &env, Genode::Xml_node config) override
		{
			return new (env.alloc())
				Vfs::Oss_file_system::Compound_file_system(env, config);
		}
	};

	static Factory f;
	return &f;
}

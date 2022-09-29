/*
 * \brief  Genode Audio out/in session + C-API implementation
 * \author Sebastian Sumpf
 * \date   2022-05-31
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <audio_in_session/rpc_object.h>
#include <audio_out_session/rpc_object.h>
#include <base/attached_rom_dataspace.h>
#include <base/session_label.h>
#include <base/component.h>
#include <base/heap.h>
#include <base/log.h>
#include <os/reporter.h>
#include <root/component.h>

#include "audio.h"

using namespace Genode;

namespace Audio_out {
	class  Session_component;
	class  Out;
	class  Root;
	struct Root_policy;
	enum   Channel_number { LEFT, RIGHT, MAX_CHANNELS, INVALID = MAX_CHANNELS };
	static Session_component *channel_acquired[MAX_CHANNELS];
}


/**************
 ** Playback **
 **************/

class Audio_out::Session_component : public Audio_out::Session_rpc_object
{
	private:

		Channel_number _channel;

	public:

		Session_component(Genode::Env &env, Channel_number channel, Signal_context_capability cap)
		:
			Session_rpc_object(env, cap), _channel(channel)
		{
			Audio_out::channel_acquired[_channel] = this;
		}

		~Session_component()
		{
			Audio_out::channel_acquired[_channel] = 0;
		}
};


class Audio_out::Out
{
	private:

		Genode::Env                            &_env;
		Genode::Signal_handler<Audio_out::Out>  _data_avail_dispatcher;

		Stream *left()  { return channel_acquired[LEFT]->stream(); }
		Stream *right() { return channel_acquired[RIGHT]->stream(); }

		void _advance_position(Packet *l, Packet *r)
		{
			bool full_left = left()->full();
			bool full_right = right()->full();

			left()->pos(left()->packet_position(l));
			right()->pos(right()->packet_position(r));

			left()->increment_position();
			right()->increment_position();

			Session_component *channel_left  = channel_acquired[LEFT];
			Session_component *channel_right = channel_acquired[RIGHT];

			if (full_left)
				channel_left->alloc_submit();

			if (full_right)
				channel_right->alloc_submit();
		}

		void _handle_data_avail() { }


	public:

		Out(Genode::Env &env)
		:
			_env(env),
			_data_avail_dispatcher(env.ep(), *this, &Audio_out::Out::_handle_data_avail)
		{ }

		static bool channel_number(const char     *name,
		                           Channel_number *out_number)
		{
			static struct Names {
				const char     *name;
				Channel_number  number;
			} names[] = {
				{ "left", LEFT }, { "front left", LEFT },
				{ "right", RIGHT }, { "front right", RIGHT },
				{ 0, INVALID }
			};

			for (Names *n = names; n->name; ++n)
				if (!Genode::strcmp(name, n->name)) {
					*out_number = n->number;
					return true;
				}

			return false;
		}

		Signal_context_capability data_avail() { return _data_avail_dispatcher; }

		genode_packet play_packet()
		{
			genode_packet packet = { nullptr, 0 };

			unsigned lpos = left()->pos();
			unsigned rpos = right()->pos();

			Packet *p_left  = left()->get(lpos);
			Packet *p_right = right()->get(rpos);

			if (p_left->valid() && p_right->valid()) {
				/* convert float to S16LE */
				static short data[Audio_out::PERIOD * Audio_out::MAX_CHANNELS];

				for (unsigned i = 0; i < Audio_out::PERIOD * Audio_out::MAX_CHANNELS; i += 2) {
					data[i] = int16_t(p_left->content()[i / 2] * 32767);
					data[i + 1] = int16_t(p_right->content()[i / 2] * 32767);
				}

				packet.data  = data;
				packet.size  = sizeof(data);

				p_left->invalidate();
				p_right->invalidate();

				p_left->mark_as_played();
				p_right->mark_as_played();
			} else {
				return packet;
			}

			_advance_position(p_left, p_right);

			/* always report when a period has passed */
			Session_component *channel_left  = channel_acquired[LEFT];
			Session_component *channel_right = channel_acquired[RIGHT];
			channel_left->progress_submit();
			channel_right->progress_submit();

			return packet;
		}
};


/**
 * Session creation policy for our service
 */
struct Audio_out::Root_policy
{
	void aquire(const char *args)
	{
		size_t ram_quota =
			Arg_string::find_arg(args, "ram_quota"  ).ulong_value(0);
		size_t session_size =
			align_addr(sizeof(Audio_out::Session_component), 12);

		if ((ram_quota < session_size) ||
		    (sizeof(Stream) > ram_quota - session_size)) {
			Genode::error("insufficient 'ram_quota', got ", ram_quota,
			              " need ", sizeof(Stream) + session_size);
			throw Genode::Insufficient_ram_quota();
		}

		char channel_name[16];
		Channel_number channel_number;
		Arg_string::find_arg(args, "channel").string(channel_name,
		                                             sizeof(channel_name),
		                                             "left");
		if (!Out::channel_number(channel_name, &channel_number)) {
			Genode::error("invalid output channel '",(char const *)channel_name,"' requested, "
			              "denying '",Genode::label_from_args(args),"'");
			throw Genode::Service_denied();
		}
		if (Audio_out::channel_acquired[channel_number]) {
			Genode::error("output channel '",(char const *)channel_name,"' is unavailable, "
			              "denying '",Genode::label_from_args(args),"'");
			throw Genode::Service_denied();
		}
	}

	void release() { }
};


namespace Audio_out {
	typedef Root_component<Session_component, Root_policy> Root_component;
}


/**
 * Root component, handling new session requests.
 */
class Audio_out::Root : public Audio_out::Root_component
{
	private:

		Genode::Env &_env;

		Signal_context_capability _cap;

	protected:

		Session_component *_create_session(const char *args) override
		{
			char channel_name[16];
			Channel_number channel_number = INVALID;
			Arg_string::find_arg(args, "channel").string(channel_name,
			                                             sizeof(channel_name),
			                                             "left");
			Out::channel_number(channel_name, &channel_number);

			return new (md_alloc())
				Session_component(_env, channel_number, _cap);
		}

	public:

		Root(Genode::Env &env, Allocator &md_alloc,
		     Signal_context_capability cap)
		:
			Root_component(env.ep(), md_alloc),
			_env(env), _cap(cap)
		{ }
};


static bool _audio_out_active()
{
	using namespace Audio_out;
	return  channel_acquired[LEFT] && channel_acquired[RIGHT] &&
	        channel_acquired[LEFT]->active() && channel_acquired[RIGHT]->active();
}


/***************
 ** Recording **
 ***************/

namespace Audio_in {

	class Session_component;
	class In;
	class Root;
	struct Root_policy;
	static Session_component *channel_acquired;
	enum Channel_number { LEFT, MAX_CHANNELS, INVALID = MAX_CHANNELS };

}


class Audio_in::Session_component : public Audio_in::Session_rpc_object
{
	private:

		Channel_number _channel;

	public:

		Session_component(Genode::Env &env, Channel_number channel)
		: Session_rpc_object(env, Signal_context_capability()),
		  _channel(channel)
		{ channel_acquired = this; }

		~Session_component() { channel_acquired = nullptr; }
};


class Audio_in::In
{
	private:

		bool _active() { return channel_acquired && channel_acquired->active(); }

		Stream *stream() { return channel_acquired->stream(); }

	public:

		static bool channel_number(const char     *name,
		                           Channel_number *out_number)
		{
			static struct Names {
				const char     *name;
				Channel_number  number;
			} names[] = {
				{ "left", LEFT },
				{ 0, INVALID }
			};

			for (Names *n = names; n->name; ++n)
				if (!Genode::strcmp(name, n->name)) {
					*out_number = n->number;
					return true;
				}

			return false;
		}

		void record_packet(genode_packet &packet)
		{
			if (!_active()) return;
			/*
			 * Check for an overrun first and notify the client later.
			 */
			bool overrun = stream()->overrun();

			Packet *p = stream()->alloc();

			float const scale = 32768.0f * 2;

			float * const content = p->content();
			short * const data    = packet.data;
			memset(content, 0, packet.size);

			for (unsigned long i = 0; i < packet.size; i += 2) {
				float sample = data[i] + data[i+1];
				content[i/2] = sample / scale;
			}

			stream()->submit(p);

			channel_acquired->progress_submit();

			if (overrun) channel_acquired->overrun_submit();
		}
};


struct Audio_in::Root_policy
{
	void aquire(char const *args)
	{
		size_t ram_quota = Arg_string::find_arg(args, "ram_quota").ulong_value(0);
		size_t session_size = align_addr(sizeof(Audio_in::Session_component), 12);

		if ((ram_quota < session_size) ||
		    (sizeof(Stream) > (ram_quota - session_size))) {
			Genode::error("insufficient 'ram_quota', got ", ram_quota,
			              " need ", sizeof(Stream) + session_size,
			              ", denying '",Genode::label_from_args(args),"'");
			throw Genode::Insufficient_ram_quota();
		}

		char channel_name[16];
		Channel_number channel_number;
		Arg_string::find_arg(args, "channel").string(channel_name,
		                                             sizeof(channel_name),
		                                             "left");
		if (!In::channel_number(channel_name, &channel_number)) {
			Genode::error("invalid input channel '",(char const *)channel_name,"' requested, "
			              "denying '",Genode::label_from_args(args),"'");
			throw Genode::Service_denied();
		}
		if (Audio_in::channel_acquired) {
			Genode::error("input channel '",(char const *)channel_name,"' is unavailable, "
			              "denying '",Genode::label_from_args(args),"'");
			throw Genode::Service_denied();
		}
	}

	void release() { }
};


namespace Audio_in {
	typedef Root_component<Session_component, Root_policy> Root_component;
}


/**
 * Root component, handling new session requests.
 */
class Audio_in::Root : public Audio_in::Root_component
{
	private:

		Genode::Env               &_env;

	protected:

		Session_component *_create_session(char const *args) override
		{
			char channel_name[16];
			Channel_number channel_number = INVALID;
			Arg_string::find_arg(args, "channel").string(channel_name,
			                                             sizeof(channel_name),
			                                             "left");
			In::channel_number(channel_name, &channel_number);
			return new (md_alloc()) Session_component(_env, channel_number);
		}

	public:

		Root(Genode::Env &env, Allocator &md_alloc)
		: Root_component(env.ep(), md_alloc), _env(env) { }
};


struct Audio
{
	Env       &env;
	Allocator &alloc;

	Constructible <Expanding_reporter>  mixer{ };

	Reporter devices { env, "devices" };

	Attached_rom_dataspace config { env, "config" };
	Signal_handler<Audio> config_handler { env.ep(), *this,
		&Audio::config_update };

	bool mixer_update { false };
	Jack_mode jack_mode = Jack_mode::DEFAULT;

	Audio_out::Out  out { env };
	Audio_out::Root out_root { env, alloc, out.data_avail() };

	Audio_in::In   in { };
	Audio_in::Root in_root { env, alloc };

	Audio(Env &env, Allocator &alloc)
	: env(env), alloc(alloc)
	{
		config.sigh(config_handler);
		config_update();

		env.parent().announce(env.ep().manage(out_root));
		env.parent().announce(env.ep().manage(in_root));
	}

	void config_update()
	{
		config.update();

		bool mixer_report = config.xml().attribute_value("report_mixer", false);

		if (mixer_report && !mixer.constructed())
			mixer.construct(env, "mixer", "mixer", Expanding_reporter::Initial_buffer_size { 8192 } );
		else if (!mixer_report && mixer.constructed())
			mixer.destruct();

		mixer_update = config.xml().has_sub_node("control");
		jack_mode = Jack_mode(config.xml().attribute_value("jack_mode", (unsigned) Jack_mode::DEFAULT));
		devices.enabled(config.xml().attribute_value("report_devices", false));
	}
};


Audio &_audio(Audio *audio = nullptr)
{
	static Audio &_audio = *audio;
	return _audio;
}


/**
 * C-interface
 */

extern "C" void genode_audio_init(struct genode_env *env_ptr,
                                  struct genode_allocator *alloc_ptr)
{
	Env *env = static_cast<Env*>(env_ptr);
	Allocator *alloc = static_cast<Allocator*>(alloc_ptr);

	static Audio audio { *env, *alloc };
	_audio(&audio);
}


extern "C" unsigned long genode_audio_period(void)
{
	return Audio_out::PERIOD;
}


extern "C" struct genode_packet genode_play_packet(void)
{
	
	return _audio_out_active() ? _audio().out.play_packet() : genode_packet { nullptr, 0 };
}


extern "C" void genode_record_packet(genode_packet packet)
{
	_audio().in.record_packet(packet);
}


/*
 * mixer report
 */
static void report_bool(Reporter::Xml_generator &xml, genode_mixer_control *control)
{
	for (unsigned i = 0; i < control->value_count; i++) {
		xml.node("control", [&]() {
			xml.attribute("type",    control->type_label);
			xml.attribute("id",      control->id);
			xml.attribute("channel", i);
			xml.attribute("name",    control->name);
			xml.attribute("value",   (bool)control->values[i]);
		});
	}
}


static void report_integer(Reporter::Xml_generator &xml, genode_mixer_control *control)
{
	for (unsigned i = 0; i < control->value_count; i++) {
		xml.node("control", [&]() {
			xml.attribute("type",    control->type_label);
			xml.attribute("id",      control->id);
			xml.attribute("channel", i);
			xml.attribute("name",    control->name);
			xml.attribute("value",   control->values[i]);
			xml.attribute("min",     control->min);
			xml.attribute("max",     control->max);
		});
	}
}


static void report_enum(Reporter::Xml_generator &xml, genode_mixer_control *control)
{
	xml.node("control", [&]() {
		xml.attribute("type", control->type_label);
		xml.attribute("id",   control->id);
		xml.attribute("name", control->name);
		xml.attribute("selected", control->values[0]);

		for (unsigned i = 0; i < control->enum_count; i++) {
			xml.node("value", [&]() {
				xml.attribute("id", i);
				xml.attribute("name", control->enum_strings[i]);
			});
		}
	});
};


extern "C" bool genode_mixer_update(void)
{
	return _audio().mixer_update;
}

extern "C" enum Jack_mode genode_jack_mode(void)
{
	return _audio().jack_mode;
}


typedef String<5> Type;

static Ctrl_type genode_control_type(Type const &type)
{
	if (type == "bool") return CTRL_BOOL;
	if (type == "int")  return CTRL_INTEGER;
	if (type == "enum") return CTRL_ENUMERATED;
	return CTRL_INVALID;
}


struct genode_mixer_control *mixer_control(struct genode_mixer_controls *controls,
                                           unsigned const id, unsigned const max)
{
	for (unsigned i = 0; i < controls->count; i++) {
		if (controls->control[i].id == id) return &controls->control[i];
	}

	if (controls->count >= max) return nullptr;

	genode_mixer_control *control =  &controls->control[controls->count];
	controls->count++;

	control->values[0] = ~0u;
	control->values[1] = ~0u;

	return control;
}


extern "C" void genode_mixer_update_controls(struct genode_mixer_controls *controls)
{
	unsigned const max = controls->count;
	controls->count = 0;

	if (!_audio().mixer_update) return;

	_audio().config.xml().for_each_sub_node("control", [&] (Xml_node &node) {

		unsigned id = node.attribute_value("id", ~0u);
		if (id == ~0u) return;

		Type const name = node.attribute_value("type", Type());
		Ctrl_type  type = genode_control_type(name);
		if (type == CTRL_INVALID) return;

		unsigned channel = node.attribute_value("channel", ~0u);
		if (type != CTRL_ENUMERATED && channel > 1) return;

		unsigned selected = node.attribute_value("selected", ~0u);
		if (type == CTRL_ENUMERATED && selected == ~0u) return;

		struct genode_mixer_control *control = mixer_control(controls, id, max);
		if (control == nullptr) return;

		control->id   = id;
		control->type = type;

		switch (type) {
		case CTRL_BOOL:
		{
			bool value = node.attribute_value("value", false);
			control->values[channel] = value ? 1 : 0;
			break;
		}
		case CTRL_INTEGER:
		{
			unsigned value = node.attribute_value("value", ~0u);
			control->values[channel] = value;
			break;
		}
		case CTRL_ENUMERATED:
		{
			control->values[0] = selected;
			break;
		}
		case CTRL_INVALID: break;
		}
	});

	_audio().mixer_update = false;
}


extern "C" void genode_mixer_report_controls(struct genode_mixer_controls *controls)
{
	if (!_audio().mixer.constructed()) return;

	Expanding_reporter &mixer = *_audio().mixer;

	try {
		mixer.generate([&] (Reporter::Xml_generator &xml) {
			for (unsigned i = 0; i < controls->count; i++) {
				switch (controls->control[i].type) {
				case CTRL_BOOL:       report_bool(xml, &controls->control[i]);    break;
				case CTRL_INTEGER:    report_integer(xml, &controls->control[i]); break;
				case CTRL_ENUMERATED: report_enum(xml, &controls->control[i]);    break;
				default: continue;
				}
			}
		});
	} catch (...) { warning("Could not report mixer controls"); throw; }
}


extern "C" void genode_devices_report(struct genode_devices *devices)
{
	Reporter &reporter = _audio().devices;

	if (reporter.enabled() == false) return;

	try {
		Reporter::Xml_generator xml(reporter, [&]() {
			for (unsigned i = 0; i < 64; i++)
				for (unsigned j = 0; j < 2; j++) {
					genode_device *device = &devices->device[i][j];
					if (device->valid == false) continue;
					xml.node("device", [&]() {
						xml.attribute("number", i);
						xml.attribute("direction", device->direction);
						xml.attribute("node", device->node);
						xml.attribute("name", device->name);
					});
			}
		});
	} catch (...) { }
}

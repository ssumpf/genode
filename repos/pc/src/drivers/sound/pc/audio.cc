#include <audio_in_session/rpc_object.h>
#include <audio_out_session/rpc_object.h>
#include <base/attached_rom_dataspace.h>
#include <base/session_label.h>
#include <base/component.h>
#include <base/heap.h>
#include <base/log.h>
#include <root/component.h>

#include "audio.h"

using namespace Genode;

namespace Audio_out {
	class  Session_component;
	class  Out;
	class  Root;
	struct Root_policy;
	static Session_component *channel_acquired[MAX_CHANNELS];
}


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


static Audio_out::Out &_audio_out(Audio_out::Out *out = nullptr)
{
	static Audio_out::Out &_out = *out;
	return _out;
}

/**
 * C-interface
 */
extern "C" void genode_audio_init(struct genode_env *env_ptr,
                                  struct genode_allocator *alloc_ptr)
{
	Env *env = static_cast<Env*>(env_ptr);
	Allocator *md_alloc = static_cast<Allocator*>(alloc_ptr);

	static Audio_out::Out out { *env };
	static Audio_out::Root root { *env, *md_alloc, out.data_avail() };

	_audio_out(&out);
	env->parent().announce(env->ep().manage(root));
}


extern "C" struct genode_packet genode_play_packet(void)
{
	
	return _audio_out_active() ? _audio_out().play_packet() : genode_packet { nullptr, 0 };
}

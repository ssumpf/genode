#include <base/component.h>

using namespace Genode;

struct Sender_thread : Thread
{
		Signal_context_capability cap;

		Sender_thread(Env &env, Signal_context_capability cap)
		:
			Thread(env, "sender_thread", 8*1024), cap(cap) { }
	
		void entry() override
		{
			while (true)
				Signal_transmitter(cap).submit();
		}
};


struct Main
{
	Env                  &env;
	Io_signal_handler<Main>  signal_handler { env.ep(), *this, &Main::handle };
	Sender_thread            sender { env, signal_handler };

	Main(Env &env) : env(env)
	{
		sender.start();
		while (true) {
			env.ep().wait_and_dispatch_one_io_signal();
		}
	}

	void handle()
	{
		static size_t c { 0 };
		if ((++c) % 100 == 0) Genode::log(c , " signals sent");
	}
};


void Component::construct(Genode::Env &env) { static Main main(env); }

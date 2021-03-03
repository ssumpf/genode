/**
 * Small interrupt test for RISC-V Qemu using
 * the RX IRQ of the UART as interrupt source
 */

#include <base/component.h>
#include <irq_session/connection.h>
#include <os/attached_mmio.h>

using namespace Genode;

namespace Genode { class Uart_8250; }

class Genode::Uart_8250 : Attached_mmio
{
	struct Rbr : Register<0, 8> { };
	struct Ier : Register<1, 8> { };
	struct Iir : Register<2, 8>
	{
		struct Pending : Bitfield<0, 1>  { };
	};

	public:

		Uart_8250(Env &env, addr_t base, uint32_t clock, uint32_t)
		:
		  Attached_mmio(env, base, 0x1000)
		{
			write<Ier>(0x1); /* enable RX interrupt */
		}

		void handle_irq()
		{
			if (read<Iir::Pending>() == 1) {
				Genode::error("received IRQ signal with no IRQ pending");
				return;
			}

			unsigned char c = read<Rbr>();
			log("Uart irq received: ", Hex(c));
		}
};


class Main
{
	private:

		Env                 &_env;
		Uart_8250            _uart        { _env, 0x10000000, 130, 0 };
		Irq_connection       _irq         { _env, 10 };
		Signal_handler<Main> _irq_handler { _env.ep(), *this, &Main::handle_irq };

	public:

		Main(Env &env) : _env(env)
		{
			_irq.sigh(_irq_handler);
			handle_irq();
		}

		void handle_irq()
		{
			_uart.handle_irq();
			_irq.ack_irq();
		}
};


void Component::construct(Genode::Env &env)
{
	log("--- PLIC test --");

	static Main main(env);
}

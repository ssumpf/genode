/**
 * \brief Render engine reset based on the Linux driver
 */
#include "mmio.h"

namespace Igd {
	class Reset;
}


class Igd::Reset
{
	private:

		Igd::Mmio &_mmio;
		unsigned   _generation { 0 };

		void _stop_engine_cs()
		{
			/* write stop bit to render mode */
			_mmio.write<Mmio::MI_MODE::Stop_rings>(1);

			/*
			 * Wa_22011802037 : GEN11, GNE12, Prior to doing a reset, ensure CS is
			 * stopped, set ring stop bit and prefetch disable bit to halt CS
			 */
			if (_generation == 11 || _generation == 12)
				_mmio.write<Mmio::GFX_MODE::Gen12_prefetch_disable>(1);

			try {
				_mmio.wait_for(Mmio::Attempts(10), Mmio::Microseconds(100'000), _mmio.delayer(),
				               Mmio::MI_MODE::Rings_idle::Equal(1));
			} catch(Mmio::Polling_timeout) {
				Genode::warning("stop engine cs timeout");
			}

			/* read to let GPU writes be flushed to memory */
			_mmio.read<Mmio::MI_MODE>();
		}

	public:

		Reset(Igd::Mmio &mmio) : _mmio(mmio) { }

		void execute(unsigned generation)
		{
			_generation = generation;

			_stop_engine_cs();
		}
};

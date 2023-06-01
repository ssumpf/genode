/**
 * \brief Render engine reset based on the Linux driver
 */
#include "mmio.h"
#include "workarounds.h"

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
			_mmio.write<Mmio::CS_MI_MODE_CTRL::Stop_rings>(1);

			/*
			 * Wa_22011802037 : GEN11, GNE12, Prior to doing a reset, ensure CS is
			 * stopped, set ring stop bit and prefetch disable bit to halt CS
			 */
			if (_generation == 11 || _generation == 12) {
				Mmio::GFX_MODE::access_t v = 0;
				using G = Mmio::GFX_MODE;
				v = G::set<G::Gen12_prefetch_disable>(v, 1);
				_mmio.write<Mmio::GFX_MODE>(v);
			}

			try {
				_mmio.wait_for(Mmio::Attempts(10), Mmio::Microseconds(100'000), _mmio.delayer(),
				               Mmio::CS_MI_MODE_CTRL::Rings_idle::Equal(1));
			} catch(Mmio::Polling_timeout) {
				Genode::warning("stop engine cs timeout");
			}

			/* read to let GPU writes be flushed to memory */
			_mmio.read<Mmio::CS_MI_MODE_CTRL>();
		}

		/* not documented
		 * Wa_22011802037: gen11/gen12: In addition to stopping the cs, we need
		 * to wait for any pending mi force wakeups
		 * MSG_IDLE_CS 0x8000 force wake
		 */
		void _wait_for_pending_force_wakeups()
		{
			if (_generation < 11 && _generation > 12) return;

			unsigned fw_status = _mmio.read<Mmio::MSG_IDLE_CS::Pending_status>();
			unsigned fw_mask   = _mmio.read<Mmio::MSG_IDLE_CS::Pending_mask>();

			_mmio.delayer().usleep(1);

			for (unsigned i = 0; i < 10; i++) {
				unsigned status = _mmio.read<Mmio::GEN9_PWRGT_DOMAIN_STATUS>() & fw_mask;

				_mmio.delayer().usleep(1);

				if (status == fw_status) return;

				_mmio.delayer().usleep(50000);
			}

			_mmio.delayer().usleep(1);
			Genode::warning("wait pending force wakeup timeout");
		}

		void _ready_for_reset()
		{
			if (_mmio.read<Mmio::CS_RESET_CTRL::Catastrophic_error>()) {
				/* For catastrophic errors, ready-for-reset sequence
				 * needs to be bypassed: HAS#396813
				 */
				try {
					_mmio.wait_for(Mmio::Attempts(7), Mmio::Microseconds(100'000), _mmio.delayer(),
					               Mmio::CS_RESET_CTRL::Catastrophic_error::Equal(0));
				} catch (Mmio::Polling_timeout) {
					Genode::warning("catastrophic error reset not cleared");
				}
				return;
			}

			if (_mmio.read<Mmio::CS_RESET_CTRL::Ready_for_reset>()) return;

			Mmio::CS_RESET_CTRL::access_t request = 0;
			Mmio::CS_RESET_CTRL::Mask_bits::set(request, 1);
			Mmio::CS_RESET_CTRL::Request_reset::set(request, 1);
			_mmio.write_post<Mmio::CS_RESET_CTRL>(request);
			try {
				_mmio.wait_for(Mmio::Attempts(7), Mmio::Microseconds(100'000), _mmio.delayer(),
				               Mmio::CS_RESET_CTRL::Ready_for_reset::Equal(1));
			} catch (Mmio::Polling_timeout) {
				Genode::warning("not ready for reset");
			}
		}

		void _unready_for_reset()
		{
			Mmio::CS_RESET_CTRL::access_t request = 0;
			Mmio::CS_RESET_CTRL::Mask_bits::set(request, 1);
			Mmio::CS_RESET_CTRL::Request_reset::set(request, 0);
			_mmio.write_post<Mmio::CS_RESET_CTRL>(request);
		}

		void _reset_gen8()
		{
			/* full sw reset */
			_mmio.write<Mmio::GDRST::Graphics_full_soft_reset_ctl>(1);
			try {
				/* do NOT attempt more than 2 times */
				_mmio.wait_for(Mmio::Attempts(2), Mmio::Microseconds(200'000), _mmio.delayer(),
				               Mmio::GDRST::Graphics_full_soft_reset_ctl::Equal(0));
			} catch (Mmio::Polling_timeout) {
				Genode::error("resetting device failed");
			}

			/* some devices still show volatile state */
			_mmio.delayer().usleep(50);
		}

		void _init_swizzling()
		{
			_mmio.write<Mmio::DISP_ARB_CTL::DISP_TILE_SURFACE_SWIZZLING>(1);
			_mmio.write<Mmio::TILECTL::SWZCTL>(1);

			if (_generation == 8)
				_mmio.write<Mmio::GAMTARBMODE::Arbiter_mode_control_1>(1);
		}

		void _enable_execlist()
		{
			_mmio.write_post<Mmio::HWSTAM>(~0u);

			_mmio.write<Mmio::CS_MI_MODE_CTRL::Stop_rings>(0);

			using G = Mmio::GFX_MODE;
			G::access_t v = 0;

			if (_generation >= 11)
				v = G::set<G::Gen11_gfx_disable_legacy_mode>(v, 1);
			else
				v = G::set<G::Execlist_enable>(v, 1);

			_mmio.write<G>(v);
		}

	public:

		Reset(Igd::Mmio &mmio) : _mmio(mmio) { }

		void execute(unsigned generation)
		{
			_generation = generation;

			_stop_engine_cs();
			_wait_for_pending_force_wakeups();
			_ready_for_reset();

			if (_generation < 11)
				_reset_gen8();

			_unready_for_reset();

			if (_generation < 9)
				_mmio.write<Mmio::HSW_IDICR::Idi_hash_mask>(0xf);

			apply_workarounds(_mmio, _generation);

			_init_swizzling();

			//XXX: init intel_mocs_init_engine, force_wake

			_enable_execlist();
		}
};

/*
 * \brief  Broadwell MI commands
 * \author Josef Soentgen
 * \date   2017-03-15
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _COMMANDS_H_
#define _COMMANDS_H_

/* Genode includes */
#include <util/mmio.h>
#include <util/string.h>

/* local includes */
#include <types.h>


namespace Igd {

	struct Cmd_header;
	struct Mi_noop;
	struct Mi_user_interrupt;
	struct Mi_batch_buffer_start;
	struct Pipe_control;

	void cmd_dump(uint32_t cmd, uint32_t index = 0);
}


/*
 * IHD-OS-BDW-Vol 6-11.15 p. 2
 */
struct Igd::Cmd_header : Genode::Register<32>
{
	struct Cmd_type : Bitfield<29, 3>
	{
		enum {
			MI_COMMAND = 0b000,
			MI_BCS     = 0b010,
			MI_RCS     = 0b011,
		};
	};

	struct Cmd_subtype : Bitfield<27, 2> { };
	struct Cmd_opcode  : Bitfield<24, 3> { };

	/*
	 * Actually bit 23:x seems to be the sub-opcode but opcodes
	 * include bit 23 (see p. 5).
	 */
	struct Mi_cmd_opcode : Bitfield<23, 6>
	{
		enum {
			MI_NOOP             = 0x00,
			MI_USER_INTERRUPT   = 0x02,
			MI_WAIT_FOR_EVENT   = 0x03,
			MI_FLUSH            = 0x04,
				// #define   MI_READ_FLUSH     (1 << 0)
				// #define   MI_EXE_FLUSH      (1 << 1)
				// #define   MI_NO_WRITE_FLUSH (1 << 2)
				// #define   MI_SCENE_COUNT    (1 << 3) /* just increment scene count */
				// #define   MI_END_SCENE      (1 << 4) /* flush binner and incr scene count */
				// #define   MI_INVALIDATE_ISP (1 << 5) /* invalidate indirect state pointers */
			MI_REPORT_HEAD      = 0x07,
			MI_ARB_ON_OFF       = 0x08,
				// #define   MI_ARB_ENABLE  (1<<0)
				// #define   MI_ARB_DISABLE (0<<0)
			MI_BATCH_BUFFER_END = 0x0A,
			MI_SUSPEND_FLUSH    = 0x0B,
				// #define   MI_SUSPEND_FLUSH_EN (1<<0)
			MI_SET_APPID        = 0x0E,
			MI_OVERLAY_FLIP     = 0x11,
				// #define   MI_OVERLAY_CONTINUE (0x0<<21)
				// #define   MI_OVERLAY_ON       (0x1<<21)
				// #define   MI_OVERLAY_OFF      (0x2<<21)
			MI_LOAD_SCAN_LINES_INCL = 0x12,
			MI_DISPLAY_FLIP         = 0x14, /* flags: 2 */
			MI_DISPLAY_FLIP_I915    = 0x14, /* flags: 1 */
			MI_SEMAPHORE_MBOX       = 0x16, /* flags: 1 */
				// #define   MI_SEMAPHORE_GLOBAL_GTT   (1<<22)
				// #define   MI_SEMAPHORE_UPDATE       (1<<21)
				// #define   MI_SEMAPHORE_COMPARE      (1<<20)
				// #define   MI_SEMAPHORE_REGISTER     (1<<18)
				// #define   MI_SEMAPHORE_SYNC_VR      (0<<16) /* RCS  wait for VCS  (RVSYNC) */
				// #define   MI_SEMAPHORE_SYNC_VER     (1<<16) /* RCS  wait for VECS (RVESYNC) */
				// #define   MI_SEMAPHORE_SYNC_BR      (2<<16) /* RCS  wait for BCS  (RBSYNC) */
				// #define   MI_SEMAPHORE_SYNC_BV      (0<<16) /* VCS  wait for BCS  (VBSYNC) */
				// #define   MI_SEMAPHORE_SYNC_VEV     (1<<16) /* VCS  wait for VECS (VVESYNC) */
				// #define   MI_SEMAPHORE_SYNC_RV      (2<<16) /* VCS  wait for RCS  (VRSYNC) */
				// #define   MI_SEMAPHORE_SYNC_RB      (0<<16) /* BCS  wait for RCS  (BRSYNC) */
				// #define   MI_SEMAPHORE_SYNC_VEB     (1<<16) /* BCS  wait for VECS (BVESYNC) */
				// #define   MI_SEMAPHORE_SYNC_VB      (2<<16) /* BCS  wait for VCS  (BVSYNC) */
				// #define   MI_SEMAPHORE_SYNC_BVE     (0<<16) /* VECS wait for BCS  (VEBSYNC) */
				// #define   MI_SEMAPHORE_SYNC_VVE     (1<<16) /* VECS wait for VCS  (VEVSYNC) */
				// #define   MI_SEMAPHORE_SYNC_RVE     (2<<16) /* VECS wait for RCS  (VERSYNC) */
				// #define   MI_SEMAPHORE_SYNC_INVALID (3<<16)
				// #define   MI_SEMAPHORE_SYNC_MASK    (3<<16)
			MI_SET_CONTEXT          = 0x18,
				// #define   MI_MM_SPACE_GTT            (1<<8)
				// #define   MI_MM_SPACE_PHYSICAL       (0<<8)
				// #define   MI_SAVE_EXT_STATE_EN       (1<<3)
				// #define   MI_RESTORE_EXT_STATE_EN    (1<<2)
				// #define   MI_FORCE_RESTORE           (1<<1)
				// #define   MI_RESTORE_INHIBIT         (1<<0)
				// #define   HSW_MI_RS_SAVE_STATE_EN    (1<<3)
				// #define   HSW_MI_RS_RESTORE_STATE_EN (1<<2)
			MI_SEMAPHORE_SIGNAL     = 0x1b,
				// #define   MI_SEMAPHORE_TARGET(engine)   ((engine)<<15)
			MI_SEMAPHORE_WAIT       = 0x1c, /* flags: 2 */
				// #define   MI_SEMAPHORE_POLL        (1<<15)
				// #define   MI_SEMAPHORE_SAD_GTE_SDD (1<<12)
			MI_STORE_DWORD_IMM      = 0x20, /* flags: 2 */
			MI_STORE_DWORD_INDEX    = 0x21, /* flags: 1 */
				// #define   MI_STORE_DWORD_INDEX_SHIFT 2
			MI_LOAD_REGISTER_IMM    = 0x22, /* in x, flags: 2*(x)-1 */
				// #define   MI_LRI_FORCE_POSTED       (1<<12)
			MI_STORE_REGISTER_MEM   = 0x24, /* flags: 1 old 2 gen8 */
				// #define   MI_SRM_LRM_GLOBAL_GTT     (1<<22)
			MI_FLUSH_DW             = 0x26, /* flags: 1 */
				// #define   MI_FLUSH_DW_STORE_INDEX (1<<21)
				// #define   MI_INVALIDATE_TLB       (1<<18)
				// #define   MI_FLUSH_DW_OP_STOREDW  (1<<14)
				// #define   MI_FLUSH_DW_OP_MASK     (3<<14)
				// #define   MI_FLUSH_DW_NOTIFY      (1<<8)
				// #define   MI_INVALIDATE_BSD       (1<<7)
				// #define   MI_FLUSH_DW_USE_GTT     (1<<2)
				// #define   MI_FLUSH_DW_USE_PPGTT   (0<<2)
			MI_LOAD_REGISTER_MEM    = 0x29, /* flags: 1 old 2 gen8 */
			MI_BATCH_BUFFER         = 0x30, /* flags: 1 */
				// #define   MI_BATCH_NON_SECURE       (1)
				// 			/* for snb/ivb/vlv this also means "batch in ppgtt" when ppgtt is enabled. */
				// #define   MI_BATCH_NON_SECURE_I965 (1<<8)
				// #define   MI_BATCH_PPGTT_HSW       (1<<8)
				// #define   MI_BATCH_NON_SECURE_HSW  (1<<13)
			MI_BATCH_BUFFER_START   = 0x31, /* flags: 1 */
				// #define   MI_BATCH_GTT               (2<<6) /* aliased with (1<<7) on gen4 */
				// #define   MI_BATCH_RESOURCE_STREAMER (1<<10)

		};
	};

	typename Cmd_header::access_t value;

	Cmd_header() : value(0) { }

	Cmd_header(Igd::uint32_t value) : value(value) { }
};


/*
 * IHD-OS-BDW-Vol 2a-11.15 p. 870
 */
struct Igd::Mi_noop : Cmd_header
{
	Mi_noop()
	{
		Cmd_header::Cmd_type::set(Cmd_header::value,
		                          Cmd_header::Cmd_type::MI_COMMAND);
		Cmd_header::Mi_cmd_opcode::set(Cmd_header::value,
		                               Cmd_header::Mi_cmd_opcode::MI_NOOP);
	}
};


/*
 * IHD-OS-BDW-Vol 2a-11.15 p. 948 ff.
 */
struct Igd::Mi_user_interrupt : Cmd_header
{

	Mi_user_interrupt()
	{
		Cmd_header::Cmd_type::set(Cmd_header::value,
		                          Cmd_header::Cmd_type::MI_COMMAND);
		Cmd_header::Mi_cmd_opcode::set(Cmd_header::value,
		                               Cmd_header::Mi_cmd_opcode::MI_USER_INTERRUPT);
	}
};


/*
 * IHD-OS-BDW-Vol 2a-11.15 p. 793 ff.
 */
struct Igd::Mi_batch_buffer_start : Cmd_header
{
	struct Address_space_indicator : Bitfield<8, 1>
	{
		enum { GTT = 0b0, PPGTT = 0b1, };
	};

	struct Dword_length : Bitfield<0, 8> { };

	Mi_batch_buffer_start()
	{
		Cmd_header::Cmd_type::set(Cmd_header::value,
		                          Cmd_header::Cmd_type::MI_COMMAND);
		Cmd_header::Mi_cmd_opcode::set(Cmd_header::value,
		                               Cmd_header::Mi_cmd_opcode::MI_BATCH_BUFFER_START);
		Address_space_indicator::set(Cmd_header::value, Address_space_indicator::PPGTT);

		Dword_length::set(Cmd_header::value, 1);
	}
};


/*
 * IHD-OS-BDW-Vol 2a-11.15 p. 983 ff.
 */
struct Igd::Pipe_control : Cmd_header
{
	struct Dword_length : Bitfield<0, 8> { };

	enum {
		GFX_PIPE_LINE = 0b11,
		PIPE_CONTROL  = 0b10,
	};

	enum {
		FLUSH_L3                     = (1 << 27),
		GLOBAL_GTT_IVB               = (1 << 24),
		MMIO_WRITE                   = (1 << 23),
		STORE_DATA_INDEX             = (1 << 21),
		CS_STALL                     = (1 << 20),
		TLB_INVALIDATE               = (1 << 18),
		MEDIA_STATE_CLEAR            = (1 << 16),
		QW_WRITE                     = (1 << 14),
		POST_SYNC_OP_MASK            = (3 << 14),
		DEPTH_STALL                  = (1 << 13),
		WRITE_FLUSH                  = (1 << 12),
		RENDER_TARGET_CACHE_FLUSH    = (1 << 12),
		INSTRUCTION_CACHE_INVALIDATE = (1 << 11),
		TEXTURE_CACHE_INVALIDATE     = (1 << 10),
		INDIRECT_STATE_DISABLE       = (1 <<  9),
		NOTIFY                       = (1 <<  8),
		FLUSH_ENABLE                 = (1 <<  7),
		DC_FLUSH_ENABLE              = (1 <<  5),
		VF_CACHE_INVALIDATE          = (1 <<  4),
		CONST_CACHE_INVALIDATE       = (1 <<  3),
		STATE_CACHE_INVALIDATE       = (1 <<  2),
		STALL_AT_SCOREBOARD          = (1 <<  1),
		DEPTH_CACHE_FLUSH            = (1 <<  0),
	};

	Pipe_control(Genode::uint8_t length)
	{
		Cmd_header::Cmd_type::set(Cmd_header::value,
		                          Cmd_header::Cmd_type::MI_RCS);
		Cmd_header::Cmd_subtype::set(Cmd_header::value, GFX_PIPE_LINE);
		Cmd_header::Cmd_opcode::set(Cmd_header::value, PIPE_CONTROL);

		Dword_length::set(Cmd_header::value, (length-2));
	}
};

#endif /* _COMMANDS_H_ */

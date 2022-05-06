/**
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Stefan Kalkowski
 * \date   2021-03-16
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* Needed to trace and stop */
#include <lx_emul/debug.h>

/* fix for wait_for_completion_timeout where the __sched include is missing */
#include <linux/sched/debug.h>

/* fix for missing include in linux/dynamic_debug.h */
#include <linux/compiler_attributes.h>

/* missing sound includes */
#include <linux/user_namespace.h>
#include <sound/hdaudio.h>
#include <sound/ac97_codec.h>
#include <sound/soc-acpi.h>

#ifdef __cplusplus
extern "C" {
#endif

struct hdac_device;
struct hda_codec;

void lx_backtrace(void);

#ifdef __cplusplus
}
#endif

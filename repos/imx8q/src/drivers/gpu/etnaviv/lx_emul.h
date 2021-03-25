/**
 * \brief  Linux emulation C helper functions
 * \author Josef Soentgen
 * \date   2021-03-16
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <stdarg.h>

/* Needed to trace and stop */
#include <lx_emul/debug.h>

/* Needed to print stuff */
#include <lx_emul/printf.h>

/* fix for wait_for_completion_timeout where the __sched include is missing */
#include <linux/sched/debug.h>

/* fix for missing include in linux/dynamic_debug.h */
#include <linux/compiler_attributes.h>

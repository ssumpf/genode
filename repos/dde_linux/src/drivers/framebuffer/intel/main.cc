/*
 * \brief  Intel framebuffer driver
 * \author Norman Feske
 * \author Stefan Kalkowski
 * \date   2015-08-19
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* Genode includes */
#include <base/component.h>

extern void start_framebuffer_driver(Genode::Env &env);


Genode::size_t Component::stack_size() {
	return 8*1024*sizeof(long); }


void Component::construct(Genode::Env &env) {
	start_framebuffer_driver(env); }

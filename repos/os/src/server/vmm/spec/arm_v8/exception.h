/*
 * \brief  VMM exception handling
 * \author Stefan Kalkowski
 * \date   2019-07-18
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__SERVER__VMM__EXCEPTION_H_
#define _SRC__SERVER__VMM__EXCEPTION_H_

#include <base/exception.h>
#include <base/log.h>
#include <base/snprintf.h>
#include <util/string.h>

class Exception : Genode::Exception
{
	private:

		enum { BUF_SIZE = 128 };
		char _buf[BUF_SIZE];

	public:

		Exception(const char *fmt, ...)
		{
			using namespace Genode;

			va_list args;
			va_start(args, fmt);
			String_console sc(_buf, BUF_SIZE);
			sc.vprintf(fmt, args);
			va_end(args);
		}

		Exception() : Exception("undefined") {}

		void print() { Genode::error(Genode::Cstring(_buf)); }
};

#endif /* _SRC__SERVER__VMM__EXCEPTION_H_ */


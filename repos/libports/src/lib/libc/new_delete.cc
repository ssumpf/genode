/*
 * \brief  C++ new/delete operators
 * \author Christian Helmuth
 * \date   2019-05-23
 *
 * Provide implementations of C++ new and delete operators to POSIX programs as
 * these are required in a full-fledged runtime. Note, our pthread
 * implementation also uses these operators.
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <stdlib.h> /* malloc, free */


void * operator new (__SIZE_TYPE__ size)       { return malloc(size); }

void operator delete (void * p)                { return free(p); }
void operator delete (void * p, __SIZE_TYPE__) { return free(p); }

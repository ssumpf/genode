/*
 * \brief  Test of label to path conversion
 * \author Emery Hemingway
 * \date   2016-03-10
 */

/*
 * Copyright (C) 2016 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#include <os/session_policy.h>
#include <os/path.h>

int main(void)
{
	using namespace Genode;

	Session_label label("label=\"a -> bc -> c/d/e -> efgh -> j/k/h/l/m\"");
	printf("%s\n", label.string());

	Path<64> path;
	path_from_label(path, label.string());

	printf("%s\n", path.base());
}

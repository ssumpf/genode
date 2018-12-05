/*
 * \brief  Simple stack smashing attempt
 * \author Emery Hemingway
 * \date   2018-12-05
 */

#include <base/component.h>
#include <base/log.h>
#include <util/string.h>


void Component::construct(Genode::Env &)
{
	using namespace Genode;

	char const *msg = "................ wrote into previous frame";

	char buf[16];
	char *p = buf;

	strncpy(p, msg, strlen(msg)+1);
	log((char const *)p);
}

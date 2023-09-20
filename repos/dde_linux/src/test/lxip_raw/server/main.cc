/*
 * \brief  Minimal HTTP server
 * \author lwIP Team
 * \author Stefan Kalkowski
 * \author Martin Stein
 * \date   2009-10-23
 *
 * This small example shows how to use the LwIP in Genode directly.
 * If you simply want to use LwIP's socket API, you might use
 * Genode's libc together with its LwIP backend, especially useful
 * when porting legacy code.
 */

/*
 * Copyright (C) 2009-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */
#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <util/endian.h>

#include <genode_c_api/socket_types.h>
#include <genode_c_api/socket.h>

using namespace Genode;


#define ASSERT(cond) { if (!(cond)) {\
	error("assertion failed at line ", __LINE__, ": ", #cond); \
	env.parent().exit(-1); \
	} }


struct Msg_header
{
	genode_iovec  iovec;
	genode_msghdr msg { };

	Msg_header(void const *data, unsigned long size)
	: iovec { const_cast<void *>(data), size }
	{
		msg.msg_iov    = &iovec;
		msg.msg_iovlen = 1;
	}

	genode_msghdr *header() { return &msg; }
};

extern "C" void wait_for_continue();

void http_server_serve(genode_socket_handle *handle, Env &env)
{
	constexpr unsigned long SIZE = 1024;
	char    buf[SIZE];
	String<128> http_header { "HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n" }; /* HTTP response header */ 
	String<150> http_html {"<html><head><title>Congrats!</title></head><body><h1>Welcome to our lwIP HTTP server!</h1><p>This is a small test page.</body></html>"}; /* HTML page */
	memset(buf, 0, 1024);

	Constructible<Msg_header> msg;
	msg.construct(buf, SIZE);

	/* Read the data from the port, blocking if nothing yet there.
	   We assume the request (the part we care about) is in one packet */
	unsigned long bytes = 0;
	Errno err;
	while (true) {
		err = genode_socket_recvmsg(handle, msg->header(), &bytes);
		if (err == GENODE_EAGAIN)
			genode_socket_wait_for_progress();
		else break;
	}

	msg.destruct();

	/* Ignore all receive errors */
	if (bytes > 0) {

		/* Is this an HTTP GET command? (only check the first 5 chars, since
		   there are other formats for GET, and we're keeping it very simple)*/
		if (bytes >= 5 &&
			buf[0] == 'G' &&
			buf[1] == 'E' &&
			buf[2] == 'T' &&
			buf[3] == ' ' &&
			buf[4] == '/' ) {

			log("Will send response");

			/* send http header */
			msg.construct(http_header.string(), http_header.length());
			ASSERT(genode_socket_sendmsg(handle, msg->header(), &bytes) == GENODE_ENONE);
			msg.destruct();

			/* Send http header */
			msg.construct(http_html.string(), http_html.length());
			ASSERT(genode_socket_sendmsg(handle, msg->header(), &bytes) == GENODE_ENONE);

			/* Send our HTML page */
//			send(conn, http_index_html, Genode::strlen(http_index_html), 0);
		}
	}
}


void Component::construct(Genode::Env &env)
{
	Attached_rom_dataspace config(env, "config");
	uint16_t const port = config.xml().attribute_value("port", (uint16_t)80);

	genode_socket_init(genode_env_ptr(env));

	log("Create new socket ...");
	enum Errno err;
	genode_socket_handle *handle = nullptr;
	ASSERT((handle = genode_socket(AF_INET, SOCK_STREAM, 0, &err)) != nullptr);

	log("Now, I will bind ...");
	genode_sockaddr addr;
	addr.family             = AF_INET;
	addr.in.sin_port        = host_to_big_endian(port);
	addr.in.sin_addr.s_addr = INADDR_ANY;
	ASSERT(genode_socket_bind(handle, &addr) == GENODE_ENONE);

	log("Now, I will listen ...");
	ASSERT(genode_socket_listen(handle, 5) == GENODE_ENONE);

	log("Start the server loop ...");
	genode_socket_handle *client = nullptr;

	err = GENODE_EAGAIN;
	for (unsigned i = 0; i < 100 && err == GENODE_EAGAIN; i++) {
		client = genode_socket_accept(handle, &addr, &err);

		if (err == GENODE_EAGAIN)
			genode_socket_wait_for_progress();
	}

	ASSERT(err == GENODE_ENONE && client != nullptr);
	http_server_serve(client, env);

	
#if 0
	while (true) {
		struct sockaddr addr;
		socklen_t len = sizeof(addr);
		int client = accept(s, &addr, &len);
		if(client < 0) {
			fprintf(stderr, "invalid socket from accept!\n");
			continue;
		}
		http_server_serve(client);
		close(client);
	}
	env.parent().exit(0);
#endif
}

#if 0
/* Genode includes */
#include <base/attached_rom_dataspace.h>
#include <base/log.h>
#include <libc/component.h>
#include <nic/packet_allocator.h>
#include <util/string.h>

/* Libc includes */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace Genode;

const static char http_html_hdr[] =
	"HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n"; /* HTTP response header */

const static char http_index_html[] =
	"<html><head><title>Congrats!</title></head><body><h1>Welcome to our lwIP HTTP server!</h1><p>This is a small test page.</body></html>"; /* HTML page */


/**
 * Handle a single client's request.
 *
 * \param conn  socket connected to the client
 */
void http_server_serve(int conn)
{
	char    buf[1024];
	ssize_t buflen;

	/* Read the data from the port, blocking if nothing yet there.
	   We assume the request (the part we care about) is in one packet */
	buflen = recv(conn, buf, 1024, 0);
	puts("Packet received!");

	/* Ignore all receive errors */
	if (buflen > 0) {

		/* Is this an HTTP GET command? (only check the first 5 chars, since
		   there are other formats for GET, and we're keeping it very simple)*/
		if (buflen >= 5 &&
			buf[0] == 'G' &&
			buf[1] == 'E' &&
			buf[2] == 'T' &&
			buf[3] == ' ' &&
			buf[4] == '/' ) {

			puts("Will send response");

			/* Send http header */
			send(conn, http_html_hdr, Genode::strlen(http_html_hdr), 0);

			/* Send our HTML page */
			send(conn, http_index_html, Genode::strlen(http_index_html), 0);
		}
	}
}


static void test(Libc::Env &env)
{
	Attached_rom_dataspace config(env, "config");
	uint16_t const port = config.xml().attribute_value("port", (uint16_t)80);

	puts("Create new socket ...");
	int s;
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error("no socket available!");
		env.parent().exit(-1);
	}

	puts("Now, I will bind ...");
	struct sockaddr_in in_addr;
	in_addr.sin_family = AF_INET;
	in_addr.sin_port = htons(port);
	in_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(s, (struct sockaddr*)&in_addr, sizeof(in_addr))) {
		fprintf(stderr, "bind failed!\n");
		env.parent().exit(-1);
	}

	puts("Now, I will listen ...");
	if (listen(s, 5)) {
		fprintf(stderr, "listen failed!\n");
		env.parent().exit(-1);
	}

	puts("Start the server loop ...");
	while (true) {
		struct sockaddr addr;
		socklen_t len = sizeof(addr);
		int client = accept(s, &addr, &len);
		if(client < 0) {
			fprintf(stderr, "invalid socket from accept!\n");
			continue;
		}
		http_server_serve(client);
		close(client);
	}
	env.parent().exit(0);
}


void Libc::Component::construct(Libc::Env &env) { with_libc([&] () { test(env); }); }
#endif

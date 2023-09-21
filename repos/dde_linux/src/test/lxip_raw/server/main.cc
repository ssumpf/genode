/*
 * \brief  Genode socket-interface test server part
 * \author Sebastian Sumpf
 * \date   2023-09-21
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
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


#define ASSERT(string, cond) { if (!(cond)) {\
	log("[", ++counter, "] ", string, " [failed]"); \
	error("assertion failed at line ", __LINE__, ": ", #cond); \
	throw -1;\
	} else { log("[", ++counter, "] ", string, " [ok]"); } }


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


struct Test_server
{
	Env &env;

	Attached_rom_dataspace config { env, "config" };
	uint16_t const port { config.xml().attribute_value("port", (uint16_t)80) };
	unsigned counter { 0 };

	String<128> http_header
		{ "HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n" }; /* HTTP response header */ 

	String<150> http_html
		{"<html><head><title>Congrats!</title></head><body><h1>Welcome to our HTTP server!</h1><p>This is a small test page.</body></html>"}; /* HTML page */

	Test_server(Env &env) : env(env)
	{
		genode_socket_init(genode_env_ptr(env));
	}

	void run()
	{
		enum Errno err;
		genode_socket_handle *handle = nullptr;
		ASSERT("create new socket ...",
		       (handle = genode_socket(AF_INET, SOCK_STREAM, 0, &err)) != nullptr);

		genode_sockaddr addr;
		addr.family             = AF_INET;
		addr.in.sin_port        = host_to_big_endian(port);
		addr.in.sin_addr.s_addr = INADDR_ANY;
		ASSERT("bind socket ...", genode_socket_bind(handle, &addr) == GENODE_ENONE);

		ASSERT("listen ...", genode_socket_listen(handle, 5) == GENODE_ENONE);

		genode_socket_handle *client = nullptr;

		err = GENODE_EAGAIN;
		for (unsigned i = 0; i < 100 && err == GENODE_EAGAIN; i++) {
			client = genode_socket_accept(handle, &addr, &err);

		if (err == GENODE_EAGAIN)
			genode_socket_wait_for_progress();
		}

		ASSERT("accept ...", err == GENODE_ENONE && client != nullptr);
		serve(client);
	}

	void serve(genode_socket_handle *handle)
	{
		constexpr unsigned long SIZE = 1024;
		char buf[SIZE];

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

		ASSERT("recvmsg ...", (bytes == 39 && err == GENODE_ENONE));

		msg.destruct();

		/* Is this an HTTP GET command? (only check the first 5 chars, since
		   there are other formats for GET, and we're keeping it very simple)*/
		ASSERT("message is GET command...", !strcmp(buf, "GET /", 5));

		/* send http header */
		msg.construct(http_header.string(), http_header.length());
		ASSERT("send HTTP header...",
		       genode_socket_sendmsg(handle, msg->header(), &bytes) == GENODE_ENONE
		       && bytes == http_header.length());
		msg.destruct();

		/* Send http header */
		msg.construct(http_html.string(), http_html.length());
		ASSERT("send HTML...",
		       genode_socket_sendmsg(handle, msg->header(), &bytes) == GENODE_ENONE
		       && bytes == http_html.length());
	}
};


void Component::construct(Genode::Env &env)
{
	Test_server server { env };

	try {
		server.run();
		log("Success");
	} catch (...) {
		log("Failure");
	}
}

/*
 * \brief  Genode socket-interface test client part
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
#include <net/ipv4.h>
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


struct Test_client
{
	Env &env;

	using Ipv4_string = String<16>;

	Attached_rom_dataspace config { env, "config"};

	uint16_t const port
		{ config.xml().attribute_value("port", (uint16_t)80) };

	Net::Ipv4_address ip_addr
		{ config.xml().attribute_value("ip", Net::Ipv4_address()) };

	unsigned long counter { 0 };

	Test_client(Env &env) : env(env)
	{
		genode_socket_init(genode_env_ptr(env));
	}

	void run()
	{
		enum Errno err;
		genode_socket_handle *handle = nullptr;
		ASSERT("create new socket...",
		       (handle = genode_socket(AF_INET, SOCK_STREAM, 0, &err)) != nullptr);

		genode_sockaddr addr;
		addr.family             = AF_INET;
		addr.in.sin_port        = host_to_big_endian(port);
		addr.in.sin_addr.s_addr = ip_addr.to_uint32_big_endian();
		ASSERT("connect...", connect(handle, &addr) == true);

		/* send request */

		String<64> request { "GET / HTTP/1.0\r\nHost: localhost:80\r\n\r\n" };
		Msg_header msg { request.string(), request.length() };
		unsigned long bytes_send;
		ASSERT("send GET request...",
		       genode_socket_sendmsg(handle, msg.header(), &bytes_send) == GENODE_ENONE
		       && bytes_send == request.length());

		char buf[150];
		/* http header */
		ASSERT("receive HTTP header...", receive(handle, buf, 150) == 45);
		ASSERT("check HTTP header...", !strcmp("HTTP/1.0 200 OK", buf, 15));
		/* html */
		ASSERT("receive HTML...", receive(handle, buf, 150) == 129);
		ASSERT("check HTML...", !strcmp(buf + 121, "</html>", 7));

		ASSERT("shutdown...", genode_socket_shutdown(handle, SHUT_RDWR) == GENODE_ENONE);
		ASSERT("release socket ...", genode_socket_release(handle) == GENODE_ENONE);
	}

	/* connect blocking version */
	bool connect(genode_socket_handle *handle, genode_sockaddr *addr)
	{
		enum Errno err;
		/* is non-blocking */
		err = genode_socket_connect(handle, addr);
		if (err == GENODE_ENONE) return true;
		if (err != GENODE_EINPROGRESS) return false;

		/* proceed with protocol described in manpage */
		bool success = false;
		for (unsigned i = 0; i < 100; i++) {
			if(genode_socket_poll(handle) & genode_socket_pollout_set()) {
				success = true; break;
			}
			genode_socket_wait_for_progress();
		}

		if (!success) return false;

		enum Errno socket_err;
		unsigned size = sizeof(enum Errno);
		err = genode_socket_getsockopt(handle, GENODE_SOL_SOCKET, GENODE_SO_ERROR,
		                               &socket_err, &size);

		if (err || socket_err) return false;

		return true;
	}

	unsigned long  receive(genode_socket_handle *handle, char *buf, unsigned long length)
	{
		Msg_header msg_recv { buf, length };
		unsigned long bytes = 0;
		Errno err;
		while (true) {
			err = genode_socket_recvmsg(handle, msg_recv.header(), &bytes);
			if (err == GENODE_EAGAIN)
				genode_socket_wait_for_progress();
			else break;
		}
		return bytes;
	}
};


void Component::construct(Genode::Env &env)
{
	Test_client client { env };

	try {
		client.run();
		log("Success");
	} catch (...) {
		log("Failure");
	}
}

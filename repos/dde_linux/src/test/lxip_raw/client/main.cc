/*
 * \brief  HTTP client test
 * \author Ivan Loskutov
 * \author Martin Stein
 * \date   2012-12-21
 */

/*
 * Copyright (C) 2012 Ksys Labs LLC
 * Copyright (C) 2012-2017 Genode Labs GmbH
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

#define ASSERT(cond) { if (!(cond)) {\
	error("assertion failed at line ", __LINE__, ": ", #cond); \
	env.parent().exit(-1); \
	} }


/* connect blocking version */
static bool connect(genode_socket_handle *handle, genode_sockaddr *addr)
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


void receive(genode_socket_handle *handle)
{
	char buf[1024];
	Msg_header msg_recv { buf, 1024 };
	unsigned long bytes = 0;
	Errno err;
	while (true) {
		err = genode_socket_recvmsg(handle, msg_recv.header(), &bytes);
		if (err == GENODE_EAGAIN)
			genode_socket_wait_for_progress();
		else break;
	}
	warning("received ", bytes, " bytes");
	String<150> s { buf };
	Genode::log(s);
}

void Component::construct(Genode::Env &env)
{
	using Ipv4_string = String<16>;

	Attached_rom_dataspace config(env, "config");
	uint16_t     const port      { config.xml().attribute_value("port", (uint16_t)80) };
	Ipv4_string  const ip_string { config.xml().attribute_value("ip", Ipv4_string("0.0.0.0")) };

	genode_socket_init(genode_env_ptr(env));

	log("Create new socket ...");
	enum Errno err;
	genode_socket_handle *handle = nullptr;
	ASSERT((handle = genode_socket(AF_INET, SOCK_STREAM, 0, &err)) != nullptr);

	log("Connect ", ip_string, "...");
	Net::Ipv4_address ip_addr { config.xml().attribute_value("ip", Net::Ipv4_address()) };
	genode_sockaddr addr;
	addr.family             = AF_INET;
	addr.in.sin_port        = host_to_big_endian(port);
	addr.in.sin_addr.s_addr = ip_addr.to_uint32_big_endian();
	ASSERT(connect(handle, &addr) == true);

	/* send request */

	String<64> request { "GET / HTTP/1.0\r\nHost: localhost:80\r\n\r\n" };
	Msg_header msg { request.string(), request.length() };
	unsigned long bytes_send;
	ASSERT(genode_socket_sendmsg(handle, msg.header(), &bytes_send) == GENODE_ENONE);
	ASSERT(bytes_send == request.length());
	warning("send: err: ", (unsigned)err, " bytes: ", bytes_send, "/", request.length());

	/* http header */
	receive(handle);
	/* html */
	receive(handle);
#if 0
	/* receive reply */
	enum { REPLY_BUF_SZ = 1024 };
	char          reply_buf[REPLY_BUF_SZ];
	size_t        reply_sz     = 0;
	bool          reply_failed = false;
	char   const *reply_end    = "</html>";
	size_t const  reply_end_sz = Genode::strlen(reply_end);
	for (; reply_sz <= REPLY_BUF_SZ; ) {
		char         *rcv_buf    = &reply_buf[reply_sz];
		size_t const  rcv_buf_sz = REPLY_BUF_SZ - reply_sz;
		signed long   rcv_sz     = ::recv(sd, rcv_buf, rcv_buf_sz, 0);
		if (rcv_sz < 0) {
			reply_failed = true;
			break;
		}
		reply_sz += rcv_sz;
		if (reply_sz >= reply_end_sz) {
			if (!strcmp(&reply_buf[reply_sz - reply_end_sz], reply_end, reply_end_sz)) {
				break; }
		}
	}
	/* ignore failed replies */
	if (reply_failed) {
		error("failed to receive reply");
		close_socket(env, sd);
		continue;
	}
	/* handle reply */
	reply_buf[reply_sz] = 0;
	log("Received \"", Cstring(reply_buf), "\"");
	if (++reply_cnt == NR_OF_REPLIES) {
		log("Test done");
		env.parent().exit(0);
	}
#endif
}

#if 0
void close_socket(Libc::Env &env, int sd)
{
	if (::shutdown(sd, SHUT_RDWR)) {
		error("failed to shutdown");
		env.parent().exit(-1);
	}
	if (::close(sd)) {
		error("failed to close");
		env.parent().exit(-1);
	}
}


static void test(Libc::Env &env)
{
	using Ipv4_string = String<16>;
	enum { NR_OF_REPLIES = 5 };
	enum { NR_OF_TRIALS  = 15 };

	/* read component configuration */
	Attached_rom_dataspace  config_rom  { env, "config" };
	Xml_node                config_node { config_rom.xml() };
	Ipv4_string       const srv_ip      { config_node.attribute_value("server_ip", Ipv4_string("0.0.0.0")) };
	uint16_t          const srv_port    { config_node.attribute_value("server_port", (uint16_t)0) };

	/* construct server socket address */
	struct sockaddr_in srv_addr;
	srv_addr.sin_port        = htons(srv_port);
	srv_addr.sin_family      = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(srv_ip.string());

	/* try several times to request a reply */
	for (unsigned trial_cnt = 0, reply_cnt = 0; trial_cnt < NR_OF_TRIALS;
	     trial_cnt++)
	{
		/* pause a while between each trial */
		usleep(1000000);

		/* create socket */
		int sd = ::socket(AF_INET, SOCK_STREAM, 0);
		if (sd < 0) {
			error("failed to create socket");
			continue;
		}
		/* connect to server */
		if (::connect(sd, (struct sockaddr *)&srv_addr, sizeof(srv_addr))) {
			error("Failed to connect to server");
			close_socket(env, sd);
			continue;
		}
		/* send request */
		char   const *req    = "GET / HTTP/1.0\r\nHost: localhost:80\r\n\r\n";
		size_t const  req_sz = Genode::strlen(req);
		if (::send(sd, req, req_sz, 0) != (int)req_sz) {
			error("failed to send request");
			close_socket(env, sd);
			continue;
		}
		/* receive reply */
		enum { REPLY_BUF_SZ = 1024 };
		char          reply_buf[REPLY_BUF_SZ];
		size_t        reply_sz     = 0;
		bool          reply_failed = false;
		char   const *reply_end    = "</html>";
		size_t const  reply_end_sz = Genode::strlen(reply_end);
		for (; reply_sz <= REPLY_BUF_SZ; ) {
			char         *rcv_buf    = &reply_buf[reply_sz];
			size_t const  rcv_buf_sz = REPLY_BUF_SZ - reply_sz;
			signed long   rcv_sz     = ::recv(sd, rcv_buf, rcv_buf_sz, 0);
			if (rcv_sz < 0) {
				reply_failed = true;
				break;
			}
			reply_sz += rcv_sz;
			if (reply_sz >= reply_end_sz) {
				if (!strcmp(&reply_buf[reply_sz - reply_end_sz], reply_end, reply_end_sz)) {
					break; }
			}
		}
		/* ignore failed replies */
		if (reply_failed) {
			error("failed to receive reply");
			close_socket(env, sd);
			continue;
		}
		/* handle reply */
		reply_buf[reply_sz] = 0;
		log("Received \"", Cstring(reply_buf), "\"");
		if (++reply_cnt == NR_OF_REPLIES) {
			log("Test done");
			env.parent().exit(0);
		}
		/* close socket and retry */
		close_socket(env, sd);
	}
	log("Test failed");
	env.parent().exit(-1);
}
#endif


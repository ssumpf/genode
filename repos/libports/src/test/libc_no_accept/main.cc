/*
 * \brief  libc listen for connection but do not 'accept'
 * \author Sebastian Sumpf
 * \date   2023-12-11
 *
 * Used to test 'connect' timeouts
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>



int main(int argc, char *argv[])
{

	int s = socket(AF_INET, SOCK_STREAM, 0);

	int port = 80;

	sockaddr_in const  addr { 0, AF_INET, htons(port), { INADDR_ANY } };
	sockaddr    const *paddr = reinterpret_cast<sockaddr const *>(&addr);

	int ret = bind(s, paddr, sizeof(addr));
	if (ret == -1) {
		printf("error: could not bind\n");
		return -1;
	}

	ret = listen(s, 0);
	if (ret == -1) {
		printf("error: could not listen\n");
		return -2;
	}
	
	while (true) {
		sleep(1);
	}

	return 0;
}

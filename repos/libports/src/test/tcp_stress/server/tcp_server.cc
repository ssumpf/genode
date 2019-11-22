#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "tcp_server.h"

void RunServer() {
	int server_fd, new_socket, valread;
	sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)	{
		perror("socket failed");
		return;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( 8899 );

	if (bind(server_fd, (sockaddr *)&address,
		sizeof(address)) < 0) {
		perror("bind failed");
		return;
	}

	if (listen(server_fd, 3) < 0) {
		perror("listen");
		return;
	}

	printf("listing...\n");

	while (true) {
		printf("read to accept\n");

		if ((new_socket = accept(server_fd, (sockaddr *)&address,
			(socklen_t*)&addrlen)) < 0) {
			perror("accept");
			return;
		}
		printf("accepted %i\n", new_socket);

		memset(buffer, 0, 1024);
		valread = read(new_socket , buffer, 1023);
		printf("readed %s\n", buffer);

		send(new_socket, buffer, valread, 0);
		printf("written\n");

		close(new_socket);
		printf("closed\n");
	}

	return;
}


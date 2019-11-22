#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void connect(int ctr) {
	int sock = 0, valread;
	sockaddr_in serv_addr;
	char buffer[1024] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8899);

	if(inet_pton(AF_INET, "10.10.10.55", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return;
	}

	if (connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return;
	}

	memset(buffer, 0, 1024);
	snprintf(buffer, 1023, "%s %i", "echo", ctr);
	send(sock, buffer, strlen(buffer), 0);

	memset(buffer, 0, 1024);
	valread = read(sock, buffer, 1023);
	if (valread > 0) {
		printf("%s\n", buffer);
	} else {
		printf("received nothing\n");
	}

	close(sock);

	return;
}

int main(int argc, char** argv)
{
	int ctr = 0;
	while (true) {
		connect(ctr);
		ctr++;
	}
	return 0;
}

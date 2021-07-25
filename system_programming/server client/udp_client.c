#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "udp.h"

#define PORT	 8080
#define MAX_LINE 1024


int main()
{
	int socket = CrerateSocket(SOCK_DGRAM);
	UdpClientPingPong(socket);
	struct sockaddr_in servaddr = ServerInfo(UDP_CLIENT);
	int is_done = 1;
    socklen_t len = sizeof(servaddr);

	while (is_done)
	{
		UdpSend(&servaddr, socket, len, MSG_DONTWAIT);

		is_done = UdpRecv(&servaddr, socket, &len);
	}

	close(socket);

	return 0;
}
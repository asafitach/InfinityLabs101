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
	int socket = UdpCrerateSocket(AF_INET, SOCK_DGRAM, 0);
	UdpClientPingPong(socket);

	return 0;
}
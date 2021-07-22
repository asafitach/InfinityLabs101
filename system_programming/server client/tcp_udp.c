#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "tcp_udp.h"

#define PORT	 8080
#define MAX_LINE 1024

int CrerateSocket(int socket_type)
{
	int sockfd = 0;

	if ((sockfd = socket(AF_INET, socket_type, 0)) < 0) 
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	return (sockfd);
}

struct sockaddr_in ServerInfo(connection_type_side_t side)
{
	struct sockaddr_in servaddr;

	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
    if (TCP_CLIENT == side)
    {
    	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    else if (UDP_BROADCAST == side)
    {
        servaddr.sin_addr.s_addr=inet_addr("255.255.255.255");
    }
    else 
    {
    	servaddr.sin_addr.s_addr = INADDR_ANY;
    }

	return (servaddr);
}

char *UserInput()
{
    char *ping = (char *)malloc(MAX_LINE);
    int index = 0;

    memset(ping, 0, MAX_LINE);

    printf("Please write your message\n");

    ping[index] = getchar();
    while ('\n' != ping[index])
    {
        ++index;
        ping[index] = getchar();
    }

    printf("string: %s\n", ping);

    return (ping);
}

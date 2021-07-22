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


void UdpClientPingPong(int socket_fd)
{
	struct sockaddr_in servaddr = ServerInfo(UDP_CLIENT);
	int is_done = 1;
    socklen_t len = sizeof(servaddr);

	while (is_done)
	{
		UdpSend(&servaddr, socket_fd, len, MSG_CONFIRM);

		is_done = UdpRecv(&servaddr, socket_fd, &len);
	}

	close(socket_fd);
}

void UdpServerPingPong(int socket_fd)
{
	struct sockaddr_in servaddr = ServerInfo(UDP_SERVER);
	struct sockaddr_in cliaddr;
	int is_done = 1;
    socklen_t len = 0;

	memset(&cliaddr, 0, sizeof(cliaddr));

    if ( bind(socket_fd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    len = sizeof(cliaddr);

	while (is_done)
	{
		is_done = UdpRecv(&cliaddr, socket_fd, &len);

		UdpSend(&cliaddr, socket_fd, len, MSG_CONFIRM);
	}

	close(socket_fd);
}

void UdpSend(struct sockaddr_in *other_address, int socket_fd, socklen_t len, int flag)
{
    char *ping = UserInput();
/*     char *ping = "hello";
 */
	sendto(socket_fd, (const void *)ping, strlen(ping),flag, (const struct sockaddr *) other_address,len);
	printf("Message sent.\n");
    free(ping);
}

int UdpRecv(struct sockaddr_in *other_address, int socket_fd, socklen_t *len)
{
	int n = 0;
	char buffer[MAX_LINE];
	char *exit = "exit";

    memset(buffer, 0, MAX_LINE);


	n = recvfrom(socket_fd, (char *)buffer, MAX_LINE, MSG_WAITALL, (struct sockaddr *) other_address, len);
	
	buffer[n] = '\0';
	
	printf("Message recived: %s\n", buffer);

	return (strcmp(buffer, exit));
}

void UdpBroadcastConfig(int socket_fd)
{
	int yes=1;
	if(setsockopt(socket_fd,SOL_SOCKET,SO_BROADCAST,&yes,sizeof(yes))<0)
	{
		perror("setsockopt failed\n");
		exit (1);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "tcp.h"

#define PORT	 8080
#define MAX_LINE 80

/* special */
void TcpPingPong(int socket_fd, connection_side_t side)
{
    int is_done = 1;

	if (client == side)
	{
        TcpSend(socket_fd);
	}

    while(0 != is_done)
    {
        is_done = TcpRecv(socket_fd);

        TcpSend(socket_fd);
	}

	// if (client == side)
	// {
		close(socket_fd);
	// }
}


/* special */
void TcpSend(int socket_fd)
{
    char *ping = UserInput();
/*     char *ping = "hello";
 */
	write(socket_fd, ping, strlen(ping));
	printf("Message sent.\n");
    free(ping);
}
/* special */
int TcpRecv(int socket_fd)
{
	char buffer[MAX_LINE];
	char *exit = "exit";

    memset(buffer, 0, MAX_LINE);

    read(socket_fd, buffer, sizeof(buffer));
	printf("Message : %s", buffer);

	return (strncmp(buffer, exit, 4));
}
/* special */
int TcpServerConnect(struct sockaddr_in *server_address, struct sockaddr_in *client_address, int server_socket_fd)
{
    socklen_t len = 0;
    int connfd = 0;

	if ((bind(server_socket_fd, (const struct sockaddr *)server_address, sizeof(*server_address))) != 0) {
		perror("socket bind failed\n");
		exit(0);
	}

	if ((listen(server_socket_fd, 5)) != 0) {
		perror("Listen failed\n");
		exit(0);
	}
	len = sizeof(*client_address);

	connfd = accept(server_socket_fd, (struct sockaddr *)client_address, &len);
	if (connfd < 0) 
	{
		printf("server acccept failed\n");
		exit(0);
	}
	return (connfd);
}
/* special */
void TcpClientConnect(struct sockaddr_in *server_address, int socket_fd)
{
	if (connect(socket_fd, (const struct sockaddr *)server_address, sizeof(*server_address)) != 0) 
    {
		printf("connection with the server failed\n");
		exit(0);
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "tcp.h"

#define MAX 80
#define PORT 8080
#define SA struct sockaddr




/* int main()
{
    int sock = CrerateSocket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address = ServerInfo(tcp_client);

    TcpClientConnect(&server_address, sock);

    TcpPingPong(sock, client);

    return 0;
} */

#define SA struct sockaddr
void func(int sockfd)
{
	char buff[MAX];
    char *ptr;
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		// while ((buff[n++] = getchar()) != '\n')
		// 	;
        // ptr = UserInput();
        TcpSend(sockfd);
		// write(sockfd, ptr, strlen(ptr));
		// bzero(buff, sizeof(buff));
		// read(sockfd, buff, sizeof(buff));
		// printf("From Server : %s", buff);
		// if ((strncmp(buff, "exit", 4)) == 0) {
		// 	printf("Client Exit...\n");
		// 	break;
		// }
        if (0 == TcpRecv(sockfd));
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	sockfd = CrerateSocket(AF_INET, SOCK_STREAM, 0);


	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	// servaddr.sin_family = AF_INET;
	// servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// servaddr.sin_port = htons(PORT);
    servaddr = ServerInfo(tcp_client);

	// connect the client socket to server socket
	TcpClientConnect(&servaddr, sockfd);

	// function for chat
	// func(sockfd);

	// // close the socket
	// close(sockfd);
    TcpPingPong(sockfd, tcp_client);
}

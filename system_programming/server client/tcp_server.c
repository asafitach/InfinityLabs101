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
    socklen_t len = 0;
    int sock = CrerateSocket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address = ServerInfo(tcp_server);
    
    struct sockaddr_in client_address;
    memset(&client_address, 0, sizeof(client_address));


    TcpServerConnect(&server_address, &client_address, sock);

    TcpPingPong(sock, server);

    return 0;
} */



// Function designed for chat between client and server.
void func(int sockfd)
{
	char buff[MAX];
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
        if (0 == TcpRecv(sockfd))
        {
            exit(1);
        }
		// read(sockfd, buff, sizeof(buff));
		// print buffer which contains the client contents
		// printf("From client: %s\t To client : ", buff);
		// bzero(buff, MAX);
		// n = 0;
		// copy server message in the buffer
		// while ((buff[n++] = getchar()) != '\n')
			// ;

		// and send that buffer to client
		// write(sockfd, buff, sizeof(buff));
        TcpSend(sockfd);

		// if msg contains "Exit" then server exit and chat ended.
		// if (strncmp("exit", buff, 4) == 0) {
		// 	printf("Server Exit...\n");
		// 	break;
		// }
	}
}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = CrerateSocket(SOCK_STREAM);

	// assign IP, PORT
	// servaddr.sin_family = AF_INET;
	// servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// servaddr.sin_port = htons(PORT);
    servaddr = ServerInfo(tcp_server);

	// // Binding newly created socket to given IP and verification
	// if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
	// 	printf("socket bind failed...\n");
	// 	exit(0);
	// }
	// else
	// 	printf("Socket successfully binded..\n");

	// // Now server is ready to listen and verification
	// if ((listen(sockfd, 5)) != 0) {
	// 	printf("Listen failed...\n");
	// 	exit(0);
	// }
	// else
	// 	printf("Server listening..\n");
	// len = sizeof(cli);

	// // Accept the data packet from client and verification
	// connfd = accept(sockfd, (SA*)&cli, &len);
	// if (connfd < 0) {
	// 	printf("server acccept failed...\n");
	// 	exit(0);
	// }
	// else
	// 	printf("server acccept the client...\n");


	// Function for chatting between client and server
    TcpPingPong(TcpServerConnect(&servaddr, &cli, sockfd), tcp_server);
	// After chatting close the socket
	// close(sockfd);
}
/* 

 client$ gcc tcp_server.c tcp.c tcp_udp.c  -I . -o server.out
asafitach@asafitach-Inspiron-7391-2n1:~/asaf-itach/system_programming/server client$ gcc tcp_client.c tcp.c tcp_udp.c  -I . -o client.out
 */
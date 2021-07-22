#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include "tcp.h"
#include "udp.h"

#define TCP_COM_PORT 16

int main(void)
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    struct sockaddr_in tcp_server;
    struct sockaddr_in tcp_client;
    struct sockaddr_in udp_server;
    struct sockaddr_in broadcast_server;
    int udp_server_fd = 0;
    int tcp_server_fd = 0;
    int broadcast_server_fd = 0;
    int flag = 1;
    int tcp_ports[TCP_COM_PORT] = {0};

    udp_server_fd = CrerateSocket(SOCK_DGRAM);
    tcp_server_fd = CrerateSocket(SOCK_STREAM);
    broadcast_server_fd = CrerateSocket(SOCK_DGRAM);

    tcp_server = ServerInfo(TCP_SERVER);
    TcpServerConnect(&tcp_server, &tcp_client, tcp_server_fd);
    UdpBroadcastConfig(broadcast_server_fd);

while(flag)
    /* Watch stdin (fd 0) to see when it has input. */

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(tcp_server_fd, &rfds);
    FD_SET(udp_server_fd, &rfds);
    FD_SET(broadcast_server_fd, &rfds);


    /* Wait up to five seconds. */

    tv.tv_sec = 7;
    tv.tv_usec = 0;

    retval = select(1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */

    if (retval == -1)
        perror("select()");
    else if (retval)
        printf("Data is available now.\n");
        /* FD_ISSET(0, &rfds) will be true. */
    else
        printf("No data within five seconds.\n");

    exit(EXIT_SUCCESS);
}
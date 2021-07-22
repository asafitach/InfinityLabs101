#ifndef __ILRD_RD101_TCP_H
#define __ILRD_RD101_TCP_H

#include <sys/socket.h>
#include "tcp_udp.h"

typedef enum connection_side
{
    client,
    server
}connection_side_t;

void TcpPingPong(int socket_fd, connection_side_t side);

void TcpSend(int socket_fd);

int TcpRecv(int socket_fd);

int TcpServerConnect(struct sockaddr_in *server_address, struct sockaddr_in *client_address, int server_socket_fd);

void TcpClientConnect(struct sockaddr_in *server_address, int socket_fd);



#endif /* __ILRD_RD101_TCP_H */
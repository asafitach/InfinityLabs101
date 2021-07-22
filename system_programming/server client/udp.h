#ifndef __ILRD_RD101_UDP_H
#define __ILRD_RD101_UDP_H

#include <sys/socket.h>
#include "tcp_udp.h"
	
void UdpClientPingPong(int socket_fd);

void UdpServerPingPong(int socket_fd);

void UdpSend(struct sockaddr_in *other_address, int socket_fd, socklen_t len, int flag);

int UdpRecv(struct sockaddr_in *other_address, int socket_fd, socklen_t *len);

void UdpBroadcastConfig(int socket_fd);



#endif /* __ILRD_RD101_UDP_H */
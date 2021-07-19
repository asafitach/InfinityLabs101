#ifndef __ILRD_RD101_UDP_H
#define __ILRD_RD101_UDP_H

#include <sys/socket.h>


int UdpCrerateSocket(int domain, int socket_type, int protocol);

struct sockaddr_in UdPServerInfo();
	
void UdpClientPingPong(int socket_fd);

void UdpServerPingPong(int socket_fd);

char *UserInput();

void UdpSend(struct sockaddr_in *other_address, int socket_fd, socklen_t len);
		
int UdpRecv(struct sockaddr_in *other_address, int socket_fd, socklen_t *len);



#endif /* __ILRD_RD101_UDP_H */
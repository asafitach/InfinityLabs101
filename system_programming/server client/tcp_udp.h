#ifndef __ILRD_RD101_TCP_UDP_H
#define __ILRD_RD101_TCP_UDP_H

#include <sys/socket.h>

typedef enum connection_type_side
{ 
    UDP_CLIENT,
    UDP_SERVER,
    TCP_CLIENT,
    TCP_SERVER,
    UDP_BROADCAST
}connection_type_side_t;

int CrerateSocket(int socket_type);

struct sockaddr_in ServerInfo(connection_type_side_t side);

char *UserInput();


#endif /* __ILRD_RD101_TCP_UDP_H */
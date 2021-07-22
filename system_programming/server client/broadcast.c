#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "udp.h"

#define PORT     8080


int main(int argc,char *argv[])
{
	struct sockaddr_in b_addr;
	
	int socked = CrerateSocket(SOCK_DGRAM);

	UdpBroadcastConfig(socked);

	b_addr = ServerInfo(udp_broadcast);

	
	UdpSend(&b_addr, socked, sizeof(b_addr), 0);
	UdpSend(&b_addr, socked, sizeof(b_addr), 0);
	UdpSend(&b_addr, socked, sizeof(b_addr), 0);
	// int b_addr_len=sizeof(b_addr);
	// int send_len=0;
	// char buf[128];
	// memset(buf,'\0',128);
	// stpcpy(buf,"This is a broadcase UDP!");
	// send_len = sendto(socked, buf, strlen(buf), 0,(struct sockaddr *)&b_addr, b_addr_len);
    //     if (send_len < 0) {
    //             printf("\n\rsend error.\n\r");
    //             exit(EXIT_FAILURE);
    //     }
    //     printf("send success %d.\n\r",send_len);
	return 0;
}
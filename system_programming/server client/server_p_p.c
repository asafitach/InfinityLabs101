#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <time.h>
#include "tcp.h"
#include "udp.h"

#define TCP_COM_PORT 16
#define TOTAL_PORTS 3 + TCP_COM_PORT
#define TERMINAL 0
#define UDP 1
#define TCP_LISTEN 2
#define BROADCAST 3
#define INTERVAL 7
#define BUFF_SIZE 256

struct sockaddr_in g_tcp_server;
struct sockaddr g_tcp_client;
struct sockaddr_in g_udp_server;

typedef void (respond_func_t)(int *, int);

void PostActionToFile(const char *str);

int main(void)
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    int flag = 1;
    int len = 0;
    int ports[TOTAL_PORTS] = {0};
    int num_of_tcp_ports = TCP_LISTEN + 1;
    char buffer[BUFF_SIZE] = {0};

    for (int i = 1; i < TOTAL_PORTS; ++i)
    {
        ports[i] = -1; 
    }

    ports[UDP] = CrerateSocket(SOCK_DGRAM);
    ports[TCP_LISTEN] = CrerateSocket(SOCK_STREAM);

    /* bind - servers */
    g_tcp_server = ServerInfo(TCP_SERVER);
    g_udp_server = ServerInfo(UDP_SERVER);
    /* tcp */
    if ((bind(ports[TCP_LISTEN], (const struct sockaddr *)&g_tcp_server, sizeof(g_tcp_server))) != 0) 
    {
		perror("socket bind failed\n");
		exit(0);
	}
    if ((listen(ports[TCP_LISTEN], TCP_COM_PORT)) != 0) 
    {
		perror("Listen failed\n");
		exit(0);
	}
    /* udp */
    if ((bind(ports[UDP], (const struct sockaddr *)&g_udp_server, sizeof(g_udp_server))) != 0) 
    {
		perror("socket bind failed\n");
		exit(0);
	}


while(flag)
{

    tv.tv_sec = INTERVAL;
    tv.tv_usec = 0;

    FD_ZERO(&rfds);

    for (size_t i = 0; i < TOTAL_PORTS; ++i)
    {
        FD_SET(ports[i], &rfds);
    }

    /* Wait up to seven seconds. */
    retval = select(TOTAL_PORTS, &rfds, NULL, NULL, &tv);

    if (retval == -1)
    {
        perror("select()");
    }
    else if (retval)
    {
        if (FD_ISSET(ports[TCP_LISTEN], &rfds))
        {
            PostActionToFile("New Tcp Connection");
            ports[num_of_tcp_ports] = accept(ports[TCP_LISTEN], &g_tcp_client, &len);
            ++num_of_tcp_ports;
        }
        
        if (FD_ISSET(ports[UDP], &rfds))
        {
            PostActionToFile("Udp Contect");
            memset(buffer, 0, BUFF_SIZE);
            recvfrom(ports[UDP], buffer, BUFF_SIZE, MSG_DONTWAIT, 
                    (struct sockaddr *)&g_tcp_client, (socklen_t *)&len);
            
            printf("UDP_Client: %s\n", buffer);
            
            sendto(ports[UDP], "pong UDP server", strlen("pong UDP server"), 
                  MSG_DONTWAIT, (const struct sockaddr *)&g_tcp_client, len);
        }

        if (FD_ISSET(TERMINAL, &rfds))
        {
    /* Don't rely on the value of tv now! */
            PostActionToFile("Terminal Activity Detected");
            memset(buffer, 0, BUFF_SIZE);
            fgets(buffer, BUFF_SIZE, stdin);
            
            if(strcmp(buffer, "ping\n") == 0)
            {
                printf("stdin_pong\n");
            }
            if(strcmp(buffer, "quit\n") == 0)
            {
                flag = 1;
            }
            else
            {
                printf("%s\n", buffer);
            }
        }

        for(int i = TCP_LISTEN + 1; i < TOTAL_PORTS; ++i)
        {
            if(FD_ISSET(ports[i], &rfds))
            {
                memset(buffer, 0, BUFF_SIZE);
            
                if (0 == recv(ports[i], buffer, BUFF_SIZE, MSG_DONTWAIT))
                {
                    PostActionToFile("TCP Client died");
                    close(ports[i]);
                    FD_CLR(ports[i], &rfds);
                    ports[i] = ports[num_of_tcp_ports];
/*                     --i;
 */                    --num_of_tcp_ports;
                    printf("TCP_Client %d: Closed\n", i);
                }
                else
                {
                    printf("TCP_Client %d: %s\n", i, buffer);
                    PostActionToFile("Tcp Contect");

                    send(ports[i], "pong TCP server", strlen("pong TCP server"),
                    MSG_DONTWAIT);
                }
            }
        }
    }
    else if (0 == retval)
    {
        PostActionToFile("No Action For Seven Sec");
        printf("No data within seven seconds.\n");
    }
}

    exit(EXIT_SUCCESS);
}

void PostActionToFile(const char *str)
{
    FILE *fd = fopen("./LOG.txt", "a");
    time_t cur = time(NULL);
    
    fprintf(fd, "time: %ld\n", cur);
    fprintf(fd, "%s", str);
    fprintf(fd, "\n");
    fclose(fd);
}
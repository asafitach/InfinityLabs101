#include <stdio.h>   /* printf */

#include "dhcp.h"

/***********************color macros for printf*********************************/

#define RED "\033[1;31m"  /* print in red */

#define GREEN "\033[1;5;32m" /* print in green */

#define BLUE "\033[1;34m"  /* print in blue */

#define YELLOW "\033[1;4:1;33m" /* print in yellow  */

#define PURPLE "\033[1;35m" /* print in purple */

#define CYAN "\033[1;3;36m" /* print in cyan */

#define RESET "\033[0m" /* reset print color  */

/**********************************Test MACROs*********************************/

#define TEST_ARE_EQUAL(name, real, expected) printf("%s: %s\n", name, real == expected\
                                                                ? GREEN"SUCCESS\n"RESET\
                                                                : RED"\aFAILURE\n"RESET)

#define TEST_ARE_NOT_EQUAL(name, real, expected) printf("%s: %s\n", name, real != expected\
                                                                ? GREEN"SUCCESS\n"RESET\
                                                                : RED"\aFAILURE\n"RESET)  


unsigned char subnet_ip_g[IPV] = {255, 127, 63, 0};

#define CREATE_DHCP dhcp_t *dhcp = DhcpCreate(subnet_ip_g, NUM_OF_SUBNET_BITS)

#define DESTROY_DHCP DhcpDestroy(dhcp)

/********************* Test function signitures ***************************/

void TestDhcpCreate(void);
void TestDhcpCountFree(void);
void TestDhcpAllocateIp(void);
void TestDhcpFreeIp(void);

/********************* Main ***************************/

int main ()
{
    TestDhcpCreate();

    TestDhcpCountFree();

    TestDhcpAllocateIp();

    TestDhcpFreeIp();

    return (0);
}

/********************* TestDhcpCreate ***************************/

void TestDhcpCreate(void)
{
    CREATE_DHCP;

    TEST_ARE_NOT_EQUAL("TestDhcpCreate1", dhcp, NULL);

    PrintDhcpSubnet(dhcp);

    TEST_ARE_EQUAL("TestDhcpCreate2", DhcpCountFree(dhcp), 253);

    DESTROY_DHCP;

    return ;
}

/********************* TestDhcpCountFree ***************************/

void TestDhcpCountFree(void)
{
    CREATE_DHCP;

    printf(YELLOW"\n******Testing DhcpCountFree by creating a\n"RESET);
	printf(YELLOW"\nDhcp and checking if return value is not equal to NULL.******\n\n"RESET);

    TEST_ARE_EQUAL("TestDhcpCountFree", DhcpCountFree(dhcp), 253);

    DESTROY_DHCP;

    return ;
}

/********************* TestDhcpAllocateIp ***************************/

void TestDhcpAllocateIp(void)
{
    CREATE_DHCP;

    unsigned char requested_ip[IPV] = {255, 127, 63, 1};

    unsigned char allocated1[IPV] = {0};

    unsigned char allocated2[IPV] = {0};

    printf(YELLOW"\n******Testing DhcpAllocateIp by creating a\n"RESET);
	printf(YELLOW"\nDhcp and checking by two ways.******\n\n"RESET);

    printf("\nTestDhcpAllocateIp1: by checking if the return value of DhcpAllocateIp\n");
    printf("\non avaliable ip is equal to OK and printing the requested and allocated ips.\n");

    TEST_ARE_EQUAL("TestDhcpAllocateIp1", DhcpAllocateIp(dhcp, requested_ip, allocated1), OK);

    PrintIp(requested_ip);
    PrintIp(allocated1);

    TEST_ARE_EQUAL("TestDhcpAllocateIp2", DhcpAllocateIp(dhcp, requested_ip, allocated2), OK);

    PrintIp(allocated2);

    DESTROY_DHCP;

    return ;
}

/********************* TestDhcpFreeIp ***************************/

void TestDhcpFreeIp(void)
{
    CREATE_DHCP;

    unsigned char unallocated_ip[IPV] = {255, 127, 63, 9};

    unsigned char requested_ip[IPV] = {255, 127, 63, 1};

    unsigned char allocated1[IPV] = {0};

    PrintIp(requested_ip);

    DhcpAllocateIp(dhcp, requested_ip, allocated1);

    TEST_ARE_EQUAL("TestDhcpFreeIp1",DhcpFreeIp(dhcp, unallocated_ip), DOUBLE_FREE);

    TEST_ARE_EQUAL("TestDhcpFreeIp2",DhcpFreeIp(dhcp, requested_ip), OK);

    TEST_ARE_EQUAL("TestDhcpFreeIp3",DhcpAllocateIp(dhcp, requested_ip, allocated1), OK);

    PrintIp(allocated1);

    DESTROY_DHCP;

    return ;
}

/********************* End ***************************/




#include <stdio.h> /*printf*/
#include <string.h> /*memset*/ 
#include <math.h>

#include "utilities.h"
#include "dhcp.h"

void  SecondTest();
void FirstTest(void);	
void PrintIpTest(unsigned char *str)
;

int main()
{
    SecondTest();
	FirstTest();
	return 0; 
}


void  SecondTest()
{
    int i = 0;
    int status = 0; 

    unsigned char ip[IPV] = {10, 20, 30, 0};
    unsigned char requested_id[IPV] = {10, 20, 30, 1};
    unsigned char allocted[IPV] = {0};
    
    dhcp_t *dhcp = DhcpCreate(ip, 24); 
    
    printf(CYAN"\t dhcp Test 2\n\n"RESET);
    
    TEST_ARE_EQUAL("count when empty Test", DhcpCountFree(dhcp), pow(2, 8)-3); 

    for (i = 1; i < 254; i++)
    {
        requested_id[3] = i;    
        printf("status: %d\n",DhcpAllocateIp(dhcp, requested_id, allocted)); 
        PrintIpTest(allocted);
        TEST_ARE_EQUAL("DhcpAllocateIp Test", allocted[3], i);  
        printf("inserted = %d \n", i); 
        memset(allocted, 0, 4); 
    }

    TEST_ARE_EQUAL("count when full", DhcpCountFree(dhcp), 0); 

    requested_id[3] = 250; 
    status = DhcpAllocateIp(dhcp, requested_id, allocted);

    TEST_ARE_EQUAL("insert when full", status, FAIL);  
    TEST_ARE_EQUAL("try to remove special number 0", DhcpFreeIp(dhcp, ip), FAIL);

    ip[3] = 250; 
    TEST_ARE_EQUAL("try to remove 250", DhcpFreeIp(dhcp, ip), OK);
    TEST_ARE_EQUAL("try to remove 250 again", DhcpFreeIp(dhcp, ip), DOUBLE_FREE);

    DhcpDestroy(dhcp); 
}


void FirstTest()
{
    unsigned char ip[IPV] = {1, 1, 1, 0};
    
    unsigned char requested_id[IPV] = {1, 1, 1, 1};
    unsigned char allocted[IPV] = {0};
    
    dhcp_t *dhcp = DhcpCreate(ip, 24); 
    
	printf(CYAN"\t dhcp Test\n\n"RESET); 
	
	TEST_ARE_EQUAL("dhcpCreate Test", (dhcp ? 1:0), 1);  
    TEST_ARE_EQUAL("count Test", DhcpCountFree(dhcp), pow(2, 8)-3);  

    DhcpAllocateIp(dhcp, requested_id, allocted); 
    TEST_ARE_EQUAL("DhcpAllocateIp Test", allocted[0], 1);  

    memset(allocted, 0, 4); 

    DhcpAllocateIp(dhcp, requested_id, allocted);
    TEST_ARE_EQUAL("DhcpAllocateIp Test", allocted[3], 2);  

    memset(allocted, 0, 4); 

    DhcpAllocateIp(dhcp, requested_id, allocted);
    TEST_ARE_EQUAL("DhcpAllocateIp Test", allocted[3], 3);  

    memset(allocted, 0, 4); 
    requested_id[3] = 75; 
    DhcpAllocateIp(dhcp, requested_id, allocted);
    TEST_ARE_EQUAL("DhcpAllocateIp Test", allocted[3], 75);  

    TEST_ARE_EQUAL("count Test before Remove", DhcpCountFree(dhcp), 249);  

    DhcpFreeIp(dhcp, allocted); 

    TEST_ARE_EQUAL("count Test After Remove", DhcpCountFree(dhcp), 250); 
    TEST_ARE_EQUAL("DOUBLE_FREE Test",  DhcpFreeIp(dhcp, allocted), DOUBLE_FREE); 

    DhcpDestroy(dhcp); 
}

void PrintIpTest(unsigned char *str)
{
    size_t index = 4;
    while (index)
    {
        --index;
        printf("%d.", str[index - 1]);
    }
}
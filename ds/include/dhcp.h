#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>      /* size_t */

# define IPV 4

#define BITS_IN_BYTE 8

/******************************************************************/
typedef struct dhcp dhcp_t;

typedef enum dhcp_status
{
	OK = 0,
    DOUBLE_FREE,
	FAIL
} dhcp_status_t;


/*************************************************************************/

/*Description: 
@return: 
@errors:  
*/
dhcp_t *DhcpCreate(const unsigned char subnet_ip[IPV], size_t num_of_subnet_bits); 
 
/*Description: 
@return: 
@errors:  
*/
void DhcpDestroy(dhcp_t *dhcp); 

/*Description: 
@return:
@errors: 
*/
dhcp_status_t DhcpAllocateIp(dhcp_t *dhcp, const unsigned char requested_id[IPV], unsigned char allocted[IPV]); 

/*Description:
@return: 
@errors: 
*/
dhcp_status_t DhcpFreeIp(dhcp_t *dhcp, unsigned char ip[IPV]);

/*Description:
@return: 
@errors: 
*/
size_t DhcpCountFree(dhcp_t *dhcp); 

#ifndef NDEBUG

void PrintSubnet(dhcp_t *dhcp);

#endif

#endif /* __DHCP_H__ */
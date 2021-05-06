#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>      /* size_t */
#include "trie.h"
# define IPV 4

/******************************************************************/
typedef enum children
{
	LEFT = 0,
	RIGHT ,
	NUM_OF_CHILDREN 
}children_t;

typedef struct dhcp 
{
	unsigned char subnet_ip[IPV]; 
    size_t num_of_subnet_bits;
    trie_node_t *root;
} dhcp_t;

typedef trie_node trie_node_t; 

struct trie_node
{
    int is_occupied;
	trie_node_t *parent; /*for iterative implementation only*/ 
	trie_node_t *children[NUM_OF_CHILDREN];
};

/*************************************************************************/

typedef enum dhcp_status
{
	OK = 0,
    DOUBLE_FREE,
	FAIL,
}dhcp_status_t;


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


#endif /* __DHCP_H__ */
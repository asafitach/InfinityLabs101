#include <assert.h>   /* assert */
#include <stddef.h>   /* NULL size_t */
#include <stdlib.h>   /* malooc free */
#include <stdio.h>   /* printf */
#include <math.h>   /* pow */
#include <sys/types.h>  /* ssize_t */

#include "trie.h"
#include "dhcp.h"

#define WORD_SIZE sizeof(size_t)

/********************* struct ***************************/

struct dhcp 
{
	unsigned char subnet_ip[IPV]; 

    size_t num_of_subnet_bits;
	
    trie_t *trie;
};

/********************* service function signitures ***************************/

static void CopyArray(unsigned char *dest, unsigned char *src, size_t size);
static size_t StrToSize_t(unsigned char *requested_ip);
static void BuildIp(dhcp_t *dhcp, size_t data, unsigned char allocted[IPV]);
static size_t Pow(size_t arg);

/********************* DhcpCreate ***************************/

dhcp_t *DhcpCreate(const unsigned char subnet_ip[IPV], size_t num_of_subnet_bits)
{
    dhcp_t *dhcp = NULL;
    trie_status_t status = SUCCESS;

    assert(IPV * BITS_IN_BYTE != num_of_subnet_bits);

    dhcp = malloc(1 * sizeof(dhcp_t));
    if (NULL == dhcp)
    {
        return (NULL);
    }

    dhcp->trie = TrieCreate(IPV * BITS_IN_BYTE - num_of_subnet_bits);
    if (NULL == dhcp->trie)
    {
        free(dhcp);
        dhcp = NULL;

        return (NULL);
    }

    dhcp->num_of_subnet_bits = num_of_subnet_bits;

    CopyArray(dhcp->subnet_ip, (unsigned char *)subnet_ip, IPV);

    status = TrieInsert(dhcp->trie, (size_t)0);
    status = status ? status: TrieInsert(dhcp->trie, Pow(IPV * BITS_IN_BYTE - num_of_subnet_bits) - 1);
    status = status ? status: TrieInsert(dhcp->trie, Pow(IPV * BITS_IN_BYTE - num_of_subnet_bits) - 2);

    if (SUCCESS != status)
    {
        DhcpDestroy(dhcp);
        return (NULL);
    }

    return (dhcp);
}

/********************* DhcpDestroy ***************************/

void DhcpDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    TrieDestroy(dhcp->trie);

    free(dhcp);
    dhcp = NULL;

    return ;
}

/********************* DhcpAllocateIp ***************************/

dhcp_status_t DhcpAllocateIp(dhcp_t *dhcp, const unsigned char requested_ip[IPV], unsigned char allocted[IPV])
{
    size_t data = 0;
    trie_t *trie = NULL;
    trie_status_t status = SUCCESS;

    assert(NULL != dhcp);

    trie = dhcp->trie;

    data = StrToSize_t((unsigned char *)requested_ip);
 
    status = TrieInsert(trie, data);
    if (PATH_OCCUPIED == status)
    {
        if (SUCCESS != TrieNextAvailable(trie, &data))
        {
            return (FAIL);
        }
        status = TrieInsert(trie, data);
    }

    if (SUCCESS != status)
    {
        return (FAIL);
    }

    BuildIp(dhcp, data, allocted);
    
    return (OK);
}

/********************* StrToSize_t ***************************/

static size_t StrToSize_t(unsigned char *requested_ip)
{
    size_t data = 0;

    size_t index = 0;

    for (index = IPV; index > 0; --index)
    {
        data <<= BITS_IN_BYTE;

        data |= requested_ip[index - 1];
    }

    return (data);
}

/********************* BuildIp ***************************/

static void BuildIp(dhcp_t *dhcp, size_t data, unsigned char allocted[IPV])
{
    size_t final_ip = 0;

    size_t index = 0;

    unsigned char *subnet = dhcp->subnet_ip;

    for (index = IPV; index > 0; --index)
    {
        final_ip |= (size_t)subnet[index - 1] << ((index - 1) * BITS_IN_BYTE);
    }

    final_ip |= data;

    for (index = IPV; index > 0; index--)
    {
        allocted[index - 1] = *(char *)&final_ip;
        final_ip >>= BITS_IN_BYTE;
    }
}

/********************* DhcpFreeIp ***************************/

dhcp_status_t DhcpFreeIp(dhcp_t *dhcp, unsigned char ip_to_free[IPV])
{
    size_t data = 0;

    assert(NULL != dhcp);

    data = StrToSize_t(ip_to_free);

/*     if (0 == data )
 */
    if (SUCCESS == TrieRemove(dhcp->trie, data))
    {
        return (OK);
    }

    return (DOUBLE_FREE);
}

/********************* DhcpCountFree ***************************/

size_t DhcpCountFree(dhcp_t *dhcp)
{
    double max_capacity = 0;

    assert(NULL != dhcp);

    max_capacity = Pow(IPV * BITS_IN_BYTE - dhcp->num_of_subnet_bits);
    
    return (max_capacity - TrieCount(dhcp->trie));
}

/********************* CopyArray ***************************/

static void CopyArray(unsigned char *dest, unsigned char *src, size_t size)
{
    size_t i = 0;

    assert(NULL != dest);
    assert(NULL != src);

    for (i = size; i > 0; i--)
    {
        dest[i - 1] = src[i - 1];
    }

    return ;
}

/********************* PowerSize_t ***************************/

static size_t Pow(size_t arg)
{
    return (1 << arg);
}

#ifndef NDEBUG

/********************* PrintDhcpSubnet ***************************/

void PrintDhcpSubnet(dhcp_t *dhcp)
{
    PrintIp(dhcp->subnet_ip);
}

/********************* PrintIp ***************************/

void PrintIp(unsigned char ip[IPV])
{
    size_t i = 0;

    for (i = 0; i < IPV - 1; i++)
    {
        printf("%u.", ip[i]);
    }

    printf("%u", ip[i]);
    printf("\n\n");
}

#endif

/********************* End ***************************/

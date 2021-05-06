#include <assert.h>   /* assert */
#include <stddef.h>   /* NULL size_t */
#include <stdlib.h>   /* malooc free */
#include <stdio.h>   /* printf */
#include <math.h>   /* pow */

#include "trie.h"
#include "dhcp.h"

/********************* struct ***************************/

struct dhcp 
{
	unsigned char subnet_ip[IPV]; 

    size_t num_of_subnet_bits;
	
    trie_t *trie;
};

#define WORD sizeof(size_t)

/********************* service function signitures ***************************/

static void CopyArray(unsigned char *dest, unsigned char *src, size_t size);

static size_t GetIpWithoutSubnet(dhcp_t *dhcp, unsigned char *requested_ip);

static void BuildIp(dhcp_t *dhcp, size_t data, unsigned char allocted[IPV]);

/********************* DhcpCreate ***************************/

dhcp_t *DhcpCreate(const unsigned char subnet_ip[IPV], size_t num_of_subnet_bits)
{
    dhcp_t *dhcp = NULL;

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


dhcp_status_t DhcpAllocateIp(dhcp_t *dhcp, const unsigned char requested_ip[IPV], unsigned char allocted[IPV])
{
    size_t data = 0;
    trie_t *trie = NULL;
    trie_status_t status = SUCCESS;


    assert(NULL != dhcp);

    trie = dhcp->trie;

/*     if (1 != CheckSubNet(dhcp, requested_ip))
    {
        return (FAIL);
    } */

    data = GetIpWithoutSubnet(dhcp, requested_ip);

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
    
    return (SUCCESS);
}


dhcp_status_t DhcpFreeIp(dhcp_t *dhcp, unsigned char ip[IPV])
{
    size_t data = 0;

    assert(NULL != dhcp);

    data = GetIpWithoutSubnet(dhcp, ip);

    if (SUCCESS == TrieRemove(dhcp->trie, data))
    {
        return (SUCCESS);
    }

    return (DOUBLE_FREE);
}

size_t DhcpCountFree(dhcp_t *dhcp)
{
    double max_capacity = 0;

    assert(NULL != dhcp);

    max_capacity = pow(2, IPV * BITS_IN_BYTE - dhcp->num_of_subnet_bits);
    
    return (max_capacity - TrieCount(dhcp->trie));
}

/********************* CopyArray ***************************/

static void CopyArray(unsigned char *dest, unsigned char *src, size_t size)
{
    size_t i = 0;

    assert(NULL != dest);
    assert(NULL != src);

    for (i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }

    return ;
}

/* int IsSubNetValid(dhcp_t *dhcp, unsigned char *requested_ip)
{
    size_t index = 0;
    unsigned char *mask = dhcp->mask;
    unsigned char *subnet = dhcp->subnet_ip;
    unsigned char subnet_requsted[IPV] = {0};

    for (index = 0; index < IPV; ++index)
    {
        subnet_requsted[index] = requested_ip[index] & mask[index];
    }

    for (index = 0; index < IPV; ++index)
    {
        if (subnet_requsted[index] != subnet_requsted[index] & subnet[index])
        {
            return (0);
        }
    }

    return (1);
}

void CreateMask(unsigned char subnet[IPV], size_t num_of_subnet_bits, unsigned char mask[IPV])
{
    size_t index = 0;
    size_t tmp_num_of_bits = 0;
    unsigned char lut[9] = {0};

    lut[1] = 128;
    lut[2] = 192;
    lut[3] = 224;
    lut[4] = 240;
    lut[5] = 248;
    lut[6] = 252;
    lut[7] = 254;
    lut[8] = 255;

    for(index = IPV - 1; index >= 0; --index)
    {
        tmp_num_of_bits = (num_of_subnet_bits >= 8) ? 8: num_of_subnet_bits;
        mask[index] = lut[tmp_num_of_bits];
        num_of_subnet_bits -= tmp_num_of_bits;
    }
} */


static size_t GetIpWithoutSubnet(dhcp_t *dhcp, unsigned char *requested_ip)
{
    size_t data = 0;
    size_t index = 0;

    for (index = 0; index < IPV; ++index)
    {
        data <<= BITS_IN_BYTE;
        data += requested_ip[index];
    }

    data <<= (WORD * BITS_IN_BYTE - (IPV * BITS_IN_BYTE - dhcp->num_of_subnet_bits));/* get rid of subnet bits */
    data >>= (WORD * BITS_IN_BYTE - (IPV * BITS_IN_BYTE - dhcp->num_of_subnet_bits));/* bringing back the ip to the right place */

    return (data);
}

static void BuildIp(dhcp_t *dhcp, size_t data, unsigned char allocted[IPV])
{
    size_t final_ip = 0;
    size_t index = 0;
    unsigned char *subnet = dhcp->subnet_ip;

    for (index = 0; index < IPV; ++index)
    {
        final_ip <<= BITS_IN_BYTE;
        final_ip += subnet[index];
    }

    final_ip += data;

    for (index = 0; index < IPV; ++index)
    {
        allocted[index] = (unsigned char)final_ip;
        final_ip >>= BITS_IN_BYTE;
    }
}

#ifndef NDEBUG

void PrintSubnet(dhcp_t *dhcp)
{
    size_t i = 0;

    for (i = 0; i < IPV - 1; i++)
    {
        printf("%u.", dhcp->subnet_ip[i]);
    }

    printf("%u", dhcp->subnet_ip[i]);
    printf("\n\n");
}

#endif
#include <stdio.h>
#include <assert.h>

#define LEN (15)/*cant work with less then 4 - due to hardcoded instructions*/

typedef struct node
{
    int data;
    struct node *next;
} node_t;

void PrintList (node_t *head);
node_t *Flip(node_t *head);
int HasLoop(const node_t *head);
node_t *FindIntersection(node_t *head_1, node_t *head_2);




int main()
{
	int res = 0;
	node_t *ptr = NULL;
	node_t arr2[LEN];/*used in the intersection function*/
	node_t arr[LEN];
	int index = 0;
	
	for (index = 0; index < LEN - 1 ; index++)/*initializing the first array of nodes*/
	{
	  arr[index].data = index;
	  arr[index].next = &arr[index+1];
	}
	arr[LEN - 1].data = *(int*)&arr[0];
	arr[LEN - 1].next = NULL;
	
	
	for (index = 0; index < LEN - 1 ; index++)
	{
	  arr2[index].data = index;
	  arr2[index].next = &arr2[index+1];
	}
	arr2[LEN - 1].data = *(int*)&arr2[0];
	arr2[LEN - 1].next = NULL;
	
	
	
	PrintList(arr);
	ptr = Flip(arr);
	PrintList(ptr);
	
	res = HasLoop(ptr);
	printf("0 is SUCCESS %d\n", res);	
	
	arr[2].next = &arr[3];/*creating loop*/
	res = HasLoop(ptr);
	printf("1 is SUCCESS %d\n", res);
	
	arr[2].next = &arr[1];/*change bake to helthy list*/
	ptr = FindIntersection(ptr, &arr[2]);
	if (NULL != ptr)
	printf("intersection success\n");
	
	ptr = FindIntersection(ptr, arr2);
	if (NULL == ptr)
	printf("intersection success\n");
	
	return (0);
}





void PrintList (node_t *head)
{
	while (head->next != NULL)
	{
		printf("%d\t", head->data);
		head = head->next;
	}
	printf("\n");
}

node_t *Flip(node_t *head)
{
	node_t *pre = head;/*i think all 3 pointers are required*/
	node_t *cur = head->next;
	node_t *nex = cur->next;

	assert(head);	
	
	while (nex->next != NULL)
	{
		cur->next = pre;
		pre = cur;
		cur = nex;
		nex = nex->next;	
	}
	head->next = nex;
	cur->next = pre;
	nex->data = cur;
	
	return (cur);
}

int HasLoop(const node_t *head)
{
	node_t *ptr1 = (node_t*)head;
	node_t *ptr2 = (node_t*)head->next;

	assert(head);

	while (ptr1 != ptr2)
	{
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		if (NULL == ptr2)
		{
			return (0);
		}
		ptr2 = ptr2->next;
		if(NULL == ptr2)
		{
			return (0);
		}
	}
			
	return (1);
}

int Count(node_t *head)
{
	int count = 0;
	
	while (head->next != NULL)
	{
	count++;
	head= head->next;
	}
	return (count);
}


node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	int count1 = Count(head_1);
	int count2 = Count(head_2);
	
	assert(head_1);
	assert(head_2);
	
	while (count1<count2)
	{
		count2--;
		head_2 = head_2->next;
	}

	while (count1>count2)
	{
		count1--;
		head_1 = head_1->next;
	}

	while (head_1 != NULL)
	{
		if (head_1 == head_2)
		{
			return (head_1);
		}
		head_1 = head_1->next;
		head_2 = head_2->next;
	}
	
	return (head_1);
}


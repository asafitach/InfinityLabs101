/*****************************************************************************
 *	FILENAME:	ex4.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:   ex4.							      	 						 *
 *																			 *
 *****************************************************************************/

#include <iostream>
#include <cstdio>

#define LIST_SIZE 10

typedef struct person 
{ 
	int age;
	size_t key;
} person_t;

typedef struct list
{
	person_t **arr;
	size_t size;
} list_t;

//person_t *ll_find(list_t *ll, int key);
//void foo(list_t *ll, int key, int age);
//void foo2(list_t *ll, int key, int age);
/*****************************************************************************/
int main(void)
{
	list_t *lst = NULL;
	size_t i = 0;

	lst = (list_t *)malloc(sizeof(list_t));
	if (NULL == lst)
	{
		return 1;
	}
	
	lst->arr = (person_t **)malloc(sizeof(person_t *) * LIST_SIZE);
	lst->size = LIST_SIZE;

	for (i = 0; i < LIST_SIZE; ++i)
	{
		lst->arr[i] = (person_t *)malloc(sizeof(person_t));

		lst->arr[i]->key = i;
		lst->arr[i]->age = 10 + i;	
	}

	
	foo(lst, 5, 10);
	puts("");
	
	// will cause compilation error
	/*foo2(lst, 10, 10);
	puts("");*/

	return 0;
}
/*********************************** struct **********************************/
person_t *ll_find(list_t *ll, int key)
{
	size_t i = 0;

	for (i = 0; i < ll->size; ++i)
	{
		if (key == ll->arr[i]->key)
		{
			return ll->arr[i];
		}
	}

	return NULL;
}
/*****************************************************************************/
void foo(list_t *ll, int key, int age)
{
	void *vv = ll_find(ll, key);

	printf("normal: %d \n", ((person_t *)vv)->age);

	person_t *p = (person_t *)ll;

	printf("casting mistake: %d \n", p->age);

	p->age = age;

	printf("change age: %d \n", p->age);
}

void foo2(list_t *ll, int key, int age)
{
	void *vv = ll_find(ll, key);

	person_t *p = static_cast<person_t *>(ll);

	printf("new syntax: %d \n", p->age);

	p->age = age;

	printf("change age: %d \n", p->age);
}
/*****************************************************************************/
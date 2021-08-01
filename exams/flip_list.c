#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node
{
    int data;
    struct node *next;
}node_t;

void NewNode(node_t *prev, int data)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    prev->next = new;
    new->next = NULL;
    new->data = data;
}

void Flip(node_t *node, node_t **new_head)
{
    static int flag = 0;
    static node_t *head = NULL;

    if(0 == flag)
    {
        head = node;
    }
    ++flag;

    if (NULL == node->next->next)
    {
        node->next->next = node;
        *new_head = node->next;
        head->next = NULL;
        return;
    }

    Flip(node->next, new_head);
    --flag;
    if (1 < flag)
    {
        node->next->next = node;
    }
}

int main()
{
    node_t first = {1, NULL};
    node_t *head = &first;
    node_t *new_head = &first;
    node_t **tmp = NULL;

    NewNode(head, 2);
    NewNode(head->next, 3);
    NewNode(head->next->next, 4);
    NewNode(head->next->next->next, 5);
    NewNode(head->next->next->next->next, 6);
    NewNode(head->next->next->next->next->next, 7);

    while (NULL != new_head)
    {
        printf("%d\t", new_head->data);
        new_head = new_head->next;
    }
    printf("\n");

    Flip(head, tmp);
    new_head = *tmp;

    while (NULL != new_head)
    {
        printf("%d\t", new_head->data);
        new_head = new_head->next;
    }
    printf("\n");


    return 0;
}
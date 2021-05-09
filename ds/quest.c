#include<stdio.h>
#include<stdlib.h>

struct node
{
        struct node *lchild;
        int info;
        struct node *rchild;
};
int flag;
struct node *root = NULL;
struct node *insert(struct node *ptr, int ikey);
void in_order_search(struct node *ptr, int val);
void display(struct node *ptr,int level);

int main( )
{
        struct node *root=NULL,*ptr;
        int choice,k,v;

        while(1)
        {
                printf("\n");
                printf("1.Insert\n");
                printf("2.Display\n");
                printf("3.Search\n");
                printf("\nEnter your choice : ");
                scanf("%d",&choice);

                switch(choice)
                {
                case 1:
                        printf("\nEnter the key to be inserted : ");
                        scanf("%d",&k);
                        root = insert(root, k);
                        break;

                case 2:
                        printf("\n");
                        display(root,0);
                        printf("\n");
                        break;

                case 3:
                        printf("\nEnter the key to be searched : ");
                        scanf("%d",&v);
                        in_order_search(root, v);
                        if (flag==1)
                        {
                            printf("Element present in the binary tree\n");
                        }
                        else
                        {
                            printf("Element not present in the binary tree\n");
                        }
                        break;
                 default:
                        exit(1);
                }
        }

        return 0;

}


struct node *insert(struct node *ptr, int ikey )
{
        if(ptr==NULL)
        {
                ptr = (struct node *) malloc(sizeof(struct node));
                ptr->info = ikey;
                ptr->lchild = NULL;
                ptr->rchild = NULL;
        }
        else if(ikey < ptr->info) /*Insertion in left subtree*/
                ptr->lchild = insert(ptr->lchild, ikey);
        else if(ikey > ptr->info) /*Insertion in right subtree */
                ptr->rchild = insert(ptr->rchild, ikey);
        else
                printf("\nDuplicate key\n");
        return ptr;
}

void in_order_search(struct node *ptr, int val)
{
    if (!ptr)
    {
        return;
    }
    in_order_search(ptr->lchild, val);
    if(ptr->info == val)
    {
/*         printf("\nElement present in the binary tree.\n"); to prevent double printing
 */        flag = 1;
            return;/* no need to go to the next line*/
    }
    in_order_search(ptr->rchild, val);
}

void display(struct node *ptr,int level)
{
        int i;
        if(ptr == NULL )
                return;
        else
    {
                display(ptr->rchild, level+1);
                printf("\n");
                for (i=0; i<level; i++)
                        printf("    ");
                printf("%d", ptr->info);
                display(ptr->lchild, level+1);
        }
}
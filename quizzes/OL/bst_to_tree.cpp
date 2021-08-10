#include <iostream>
using namespace std;

typedef struct node
{
    int data;
    struct node *parent;
    struct node *left;
    struct node *right;
}node_t;

void ConvertTreeToList(node_t *prev, node_t *next)
{
    static int is_head = 1;
    if (1 == is_head)
    {
        is_head = 0;
        prev->parent = NULL;
    }
    if (NULL == prev || NULL == next)
    {
        return;
    }
    prev->left = next;
    next->parent = prev;
    next->left = NULL;
}

node_t *BstToList(node_t *root)
{
    node_t *return_node = NULL;
    if (NULL == root)
    {
        return (NULL);
    }
    if (NULL == root->left && NULL == root->right)
    {
        return (root);
    }

    return_node = BstToList(root->left);
    ConvertTreeToList(return_node, root);
    return_node = BstToList(root->right);
    ConvertTreeToList(root, return_node);

    return (return_node);
}

node_t* newNode(int key)
{
    node_t* node = new node_t;
    node->data = key;
    node->left = node->right = NULL;
    node->parent = NULL;
    return (node);
}

void inorder(node_t* root)
{
    // base condition
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
/*     inorder(root->parent);
 */}


int main()
{
    node_t* root = newNode(10);
    node_t *rt = NULL;
    root->left = newNode(4);    
    root->left->left = newNode(2);
    root->left->right = newNode(5);
    root->left->left->left = newNode(1);
    rt = root->left->left->left;
    root->left->left->right = newNode(3);
    root->left->right->right = newNode(6);
 
    inorder(root);
    cout<<endl;
    
    BstToList(root);
 
    cout << "The Inorder traversal after "
            "flattening binary tree ";
    while (NULL != rt)
    {
        cout<<" "<<rt->data<<" ";
        rt = rt->left;
    }
    
}
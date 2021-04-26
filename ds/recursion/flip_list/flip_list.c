
node_t *FlipList(node_t *node)
{
    node_t *head = NULL;
    if (NULL == node->next)
    {
        return (head);
    }
    head = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;
    return (head);
}


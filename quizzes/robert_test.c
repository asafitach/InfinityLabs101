void CheckEndianess()
{
	int x = 0x00020304;
	char *p = (char *)&x;
	
	++p;
	
	p = (size_t)p - 1;
	
	if (2 == *p)
	{
		printf("Little Endianess\n");
	}
	
	printf("Big Endianess\n");
}


list_t *FilterListFromDuplicatedData(list_t *list)
{
	node_t *runner = NULL;
	hash_t *table = NULL;
	
	assert(NULL != list);
	
	runner = list->root;
	table = HashCreate(ListSize(list), list->hash_func);/*/*/
	if (NULL == table)
	{
		return (NULL);
	}
	
	while (NULL != runner)
	{
		if (1 == HashFind(table, runner->data))
		{
			runner = ListRemove(runner);
		}
		else
		{
			HashInsert(table, runner->data);
			runner = runner->next;
		}
	}
	
	HashDestroy(table);
	
	return (list);
}

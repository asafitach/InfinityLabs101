void Largest(vsa_t *vsa_o)
{
	size_t *vsa = vsa_o;
	ssize_t current_val = 0;
	ssize_t cmp_val = 0;
	
	current_val = (vsa_t *)vsa->block_size;
	
	while (current_val != 0x90909090)
	{
		while (current_val < 0)
		{
			cmp_val = ((vsa_t *)(vsa - current_val))->block_size;
			if (cmp_val < 0)
			{
				current_val += cmp_val - BLOCK;
				(vsa_t *)vsa->block_size += current_val;
			}
			else
			{
				vsa -= current_val;
				current_val = (vsa_t *)vsa->block_size; 
				break;
			}
		}
		while (current_val != 0x90909090)
		{
			vsa += current_val;
			current_val = (vsa_t *)vsa->block_size;
			if (current_val < 0)
			{
				break;
			}
		}
	}
}

void *VsaAlloc(vsa_t *vsa, size_t size)
{
	size_t current_val = 0;
	size_t *run = (size_t *)vsa;
	
	size = -((size - 1) / WORD_SIZE + 1);
	
	current_val = vsa->block_size;

	while (current_val != 0x90909090 && current_val > size)
	{
		current_val = (current_val > 0) ? current_val : -current_val;
		run += current_val;
		current_val = (vsa_t *)run->block_size;
	} 
			
	if (current_val == 0x90909090)
	{
		return (NULL);
	}
	
	if (size - current_val <= BLOCK)	
	{
		(vsa_t *)run->block_size - -current_val;
		return ((vsa_t *)run);
	}
	
	current_val -= (size - BLOCK);
	(vsa_t *)run->block_size = -size;
	run -= (size - BLOCK);
	(vsa_t *)run->block_size = current_val;
	
	return ((vsa_t *)(run + size));
}
	

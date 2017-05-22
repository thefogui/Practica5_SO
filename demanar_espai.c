p_block demanar_espai(size_t size) 
{
    p_block block;

    block = sbrk(0);

    if (sbrk(META_SIZE + size) == (void *) -1)
        return (NULL);

    block->size = size;
    block->next = NULL;
    block->free = 0;

    if (last_element)
      last_element->next = block;

    last_element = block;

    return block;
}

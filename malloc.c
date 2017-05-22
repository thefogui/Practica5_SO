p_block first_element = NULL;
p_block last_element  = NULL;

void *malloc(size_t size) 
{
    void *p;
    p_block block;

    if (size <= 0) {
        return NULL;
    }

    if (first_element){
        block = cercar_bloc_lliure(size);
        if (block) { // block found
            block->free = 0;
        } else {     // no block found
            block = demanar_espai(size);
            if (!block)
                return (NULL);
        }
    } 
    else  // This is done the first time malloc is called
    {
        block = demanar_espai(size);
        if (!block)
            return(NULL);
        first_element = block;
    }

    p = (void *) block;
    return (p + META_SIZE); 
}


p_block cercar_bloc_lliure(size_t size) {
    p_block current = first_element;

    while (current && !(current->free && current->size >= size)) 
        current = current->next;

    return current;
}

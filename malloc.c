#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <unistd.h>
#include "struct.h"

p_block first_element = NULL; //apunta al primer bloc reservat
p_block last_element  = NULL; //apunta al darrer element de la llista

p_block cercar_bloc_lliure(size_t size) {
    p_block current = first_element;

    while (current && !(current->free && current->size >= size))
        current = current->next;

    return current;
}

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





void *malloc(size_t size)
{
    void *p;
    p_block block;

    if (size <= 0) {
        return NULL;
    }

    if (first_element){
        block = cercar_bloc_lliure(size);//mira si a la llista de blocs disponibles n'hi algun
                                        // que sigui prou gran
        if (block) { // block found
            block->free = 0;
        } else { // si no hi bloc es demana espai(demana espai similar al sbrk(size))
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






//Ha de posar el valor 'free' a 1
void free(void *ptr){
    if(!ptr) //si es NULL
        return; //es ignora la llamada
    struct p_block* current = (struct p_block*)ptr -1;
    current->free = 1;
}




//permet reservar varis elements de memoria i els deixa inicialitzats a zero
void calloc(size_t nelem, size_t elsiza){
    size_t total = nelem * elsiza;
    void *p = malloc(total);
    if (!p) return NULL;
    return memset(p, 0, total);
}




//reajusta la mida d'un bloc de momemoria obtingut amb malloc a una nova mida
 void *realloc(void * ptr, size_t size){
    void *new;

    if (!ptr) {
        new = malloc(size);
        if (!new) { goto error; }
    } else {
        if (malloc_size(ptr) < size) {
            new = malloc(size);
            if (!new) { goto error; }

            memcpy(new, ptr, malloc_size(ptr));

            free(ptr);
        } else {
            new = ptr;
        }
    }

    return new;
error:
    return NULL;
}


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h> /* memset */
#include <unistd.h>
#include "struct.h"

p_block first_element = NULL; //apunta al primer bloc reservat
p_block last_element  = NULL; //apunta al darrer element de la llista

p_block cercar_bloc_lliure(size_t size) {
    p_block current = first_element;
	p_block best_fit;

    while (current && !(current->free && current->size >= size)){
	//Cuando encuentre el libre buscar el que tenga el espacio minimo y que quepa el block dema-
	//nado... siempre comparando con el actual
        current = current->next;
	
	}
	best_fit = current;
	while(current != 0){
		current = current->next;
		if(current->size < best_fit->size && current->size >= size)
			best_fit = current;
	}
    return best_fit;
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
	printf("Soc a la crida de free\n");
    if(!ptr) //si es NULL
        return; //es ignora la llamada
    p_block current = (p_block)ptr -1;//cast del puntero void a puntero p_block
    current->free = 1; //pasa el indicador a 1
}


//permet reservar varis elements de memoria i els deixa inicialitzats a zero
void *calloc(size_t nelem, size_t elsiza){
    size_t total = nelem * elsiza;
    p_block p = malloc(total); 
    if (!p) //si dona error retorna null
		return NULL;
    return memset(p, 0, total); // per inicialitzar el bloc de memòria a zero.
}

//reajusta la mida d'un bloc de momemoria obtingut amb malloc a una nova mida
 void *realloc(void * ptr, size_t size){
    p_block new;

    if (!ptr) //si el null actua como un malloc normal y corriente
        return malloc(size);
    else {
        if (sizeof(ptr) < size) { //si el tamaño del puntero es menor 
            new = malloc(size); //se hace un bloc mas grande
            if (!new) 
				return NULL; //si dona error retorna nulll
            memcpy(new, ptr, sizeof(ptr)); //copies n characters from memory area str2 to memory area str1.
			//copiar el contingut d’un bloc en un altre.
            free(ptr); //libera el espacio del puntero 
        } else //sino retorna el block
            return new;
    }
    return new;
}

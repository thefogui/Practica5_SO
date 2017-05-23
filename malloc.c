p_block first_element = NULL; //apunta al primer bloc reservat
p_block last_element  = NULL; //apunta al darrer element de la llista

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

}

//reajusta la mida d'un bloc de momemoria obtingut amb malloc a una nova mida
 void *realloc(void *ptr, size_t size){
     if(!ptr) //si es null el punter actua como una malloc normal i corrent
        return malloc(size);
     //si la mida que demananen es suficient amb el bloc que ja te reservat no fa res
     //en cas contrari reservar espai per un bloc y usar la funcion memcpy per
     //copiar el contigut d'un bloc en un altre
 }

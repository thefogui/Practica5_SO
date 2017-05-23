typedef struct m_block *p_block;

/**
* next serveix per encadenar el bloc
*
**/
//meta data
struct m_block {
    size_t  size; //mida del bloc en bytes
    p_block next; //adreça del seguent bloc
    int     free; //indicador de que si el bloc esta ocupat o no
};

#define META_SIZE  sizeof(struct m_block)

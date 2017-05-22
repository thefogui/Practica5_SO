typedef struct m_block *p_block;

struct m_block {
    size_t  size;
    p_block next;
    int     free;
};

#define META_SIZE  sizeof(struct m_block)




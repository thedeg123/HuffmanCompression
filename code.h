#ifndef code
#define code
    struct node{
    char letter;
    char *bitstring;
    int count;
    struct node *lchild, *rchild, *right;
    };
    void freeTree(struct node *n);
#endif

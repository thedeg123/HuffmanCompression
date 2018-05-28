#ifndef decode
#define decode
#include "code.h"    
    void printOut(FILE **file, struct node *n, FILE **outfile);
    int toDec(char *binData);
    struct node * addNode(char c, int count);
    void buildTree(FILE **file, struct node *n);
    FILE * skipSpaces(FILE *file, int num_spaces);
#endif

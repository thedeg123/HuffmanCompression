#ifndef encode
#define encode
#include "code.h"    
//struct node{
    //char letter;
    //char *bitstring;
    //int count;
    //struct node *lchild, *rchild, *right;
    //};
    int getsize(char *s);
    void padOut(FILE * outfile, int letterCount);
    void printBinary(FILE * outfile, int i);
    int printBinTree(struct node *n, int letterCount, FILE * outfile);
    char * doubleSize(char * usrIn, int size);
    void getBitString(struct node *n);
    void printBitString(struct node *n, FILE * outfile);
    int heapify();
    struct node * insertionSort(struct node *n,struct node *comp);
    struct node * addNode(char c, int count);
    struct node * printLL(struct node *n);
#endif

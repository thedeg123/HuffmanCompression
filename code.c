#include <stdio.h>
#include <stdlib.h>
#include "code.h"
//David Gold 
//Methods used by both encode and decode
void freeTree(struct node *n){
    if(n==NULL)
	return;
    freeTree(n->lchild);
    freeTree(n->rchild);
    if(n->letter!=0){
    if(n->bitstring)
	free(n->bitstring);
    }
    free(n);
}

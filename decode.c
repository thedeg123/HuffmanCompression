#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "decode.h"
#include "code.h"
#include <limits.h>
#include <string.h>
//David Gold 
struct node * nodeLetters[256];
struct node *tree;
//EOF IS NOT IN ARRAY. SKIP PASSED ARRAY ELEMENTS OF 0
int main(int argc, char * argv[]){
    char * inputFile=NULL;
    char * outputFile=NULL;
    switch(argc){
	case 1: 
	    perror("Please enter a file to read from in the program call.\n");
	    exit(1);
	case 2:
	    inputFile=argv[1];
	    break;
	case 3:
	    inputFile=argv[1];
	    outputFile=argv[2];
	    break;
	default:
	    perror("Too many arguments specified. Allowed: 1 or 2.\n");
	    exit(2);
    }
    //this way all values will be initalized to 0.
FILE * infile=fopen(inputFile,"r");
if(!infile){
perror("Could not find file");
exit(4);
}
infile=skipSpaces(infile,2);
tree=addNode(0,0);
getc(infile);
buildTree(&infile, tree);
fclose(infile);
infile=fopen(inputFile,"r");
FILE * outfile= (outputFile)? fopen(outputFile,"w"): stdout;
printOut(&infile, tree,&outfile);
fclose(infile);
fclose(outfile);
freeTree(tree);
}
void printOut(FILE **file, struct node *n, FILE **outfile){
if(n->letter!=0){
    if(n->letter==EOF)
	return;
    fprintf(*outfile, "%c", n->letter);
    printOut(file, tree, outfile);
    return;
}
char c = getc(*file);
if(c == '0')
    printOut(file, n->lchild, outfile);

else
    printOut(file, n->rchild, outfile);
}
FILE * skipSpaces(FILE *file, int num_spaces){
    char c;
    while(num_spaces>0 && (c=getc(file))!=EOF){
    if(c==' ')
        num_spaces--;
    }
    return file;
}
void buildTree(FILE **file, struct node *n){
    char c = getc(*file);
    struct node **nextChild= (n->lchild)? &n->rchild: &n->lchild; 
    if(c == '0'){
    *nextChild=addNode(0,0);
    buildTree(file, (*nextChild));
    if(!n->rchild)
	buildTree(file,n);
    }
    else{
    char binData[9]={0};
    for(int i=0;i<8;i++){
    binData[i]=getc(*file);
    }
    *nextChild=addNode(toDec(binData),1);
    if(*nextChild==n->lchild)
	buildTree(file,n);
    }
}
int toDec(char * binData){
int num=0;
for(int i=0;i<=7;i++){
    if(binData[i]=='1')
	num+=(int) pow(2,7-i);
}
return num;
}
struct node * addNode(char c, int count){
struct node *new=malloc(sizeof(struct node));
if(!new){
perror("Could not allocate memory");
exit(3);
}
new->letter=c;
nodeLetters[c-0]=new;
new->count=count;
new->bitstring=NULL;
new->lchild=new->rchild=new->right=NULL;
return new;
}


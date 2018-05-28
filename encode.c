#include <stdio.h>
#include <stdlib.h>
#include "encode.h"
#include "code.h"
#include <math.h>
#include <limits.h>
#include <string.h>
//David Gold 
struct node *head;
struct node *tail;
//the node assoceated with a certain letter
struct node * nodeLetters[256];
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
    int inputArray[256]={0};
    int c;
    if(infile){
	while((c=getc(infile))!=EOF){
	    inputArray[c]+=1;
	}
	fclose(infile);
    }
    else{ 
	perror("Could not find file\n"); 
	exit(4);
    }
    //adding sentinal nodes as well as EOF node
    //hard coding added EOF
    struct node *eof=addNode(EOF, 1);
    tail=addNode(0,INT_MAX);
    head=addNode(0,INT_MAX);
    head->right=eof;
    eof->right=tail;
    for(int i=0;i<256;i++){
    if(inputArray[i]!=0){
    //puts new node at beginning of linked list then sorts it.
    struct node *new=addNode((char) i,inputArray[i]);
    insertionSort(new, head);
    } 
    }
    heapify();
    getBitString(head->right);
    //Printing each char's bitstring
    infile=fopen(inputFile,"r");
    //for 0 padding
    int letterCount=1;
    //lets all just take a second to appreceate how cool the ?: operator is
    FILE * outfile = (outputFile)? fopen(outputFile,"w") : stdout;
    if(!outfile){
	perror("Could not find file\n"); 
	exit(4);
    }
    while((c=getc(infile))!=EOF){
    fprintf(outfile, "%s",nodeLetters[c]->bitstring);
    letterCount+=getsize(nodeLetters[c]->bitstring);
    }
    fprintf(outfile, "%s",eof->bitstring);
    padOut(outfile, letterCount);
    if(c==EOF)
	fprintf(outfile, " EOF:%s ",eof->bitstring);
    fclose(infile);
    letterCount=0;
    letterCount = printBinTree(head->right,letterCount,  outfile);
    padOut(outfile,letterCount);
    fprintf(outfile, "\n");
    fclose(outfile);
    freeTree(head->right);
    free(head);
    free(tail);
    return 0;
}
int getsize(char * s){
int ticker=0;
while(s[ticker]!='\0'){ticker++;}
return ticker;
}
void padOut(FILE * outfile, int letterCount){
    while(letterCount%8!=0){
    fprintf(outfile, "0");
    letterCount++;
    }
}
int heapify(){
    if(head->right->right==tail)
	return 0;
    struct node *heap=addNode((char) 0, head->right->count+head->right->right->count);
    heap->lchild=head->right;
    heap->rchild=head->right->right;
    head->right=head->right->right->right;
    heap->lchild->right=NULL;
    heap->rchild->right=NULL;
    insertionSort(heap,head);
    return heapify();
}
void getBitString(struct node *n){
    static char str[512];
    static int size=0;
    if(n->letter!=0){
	strcat(str,"\0");
	n->bitstring=malloc(size+1*sizeof(char));
	if(!n->bitstring){
	perror("Could not allocate memory for bitstring");
	exit(3);
	}
	strcpy(n->bitstring,str);
	for(int i=size-1;i>=0;i--){
	if(str[i]=='1'){
	size--;
	str[i]='\0';
	continue;
	}
	else break;
	}
	size--;
	str[size]='\0';
	return;
    }
    strcat(str,"0");
    size++;
    getBitString(n->lchild);
    strcat(str,"1");
    size++;
    getBitString(n->rchild);
}

//insertion sort which takes in the node to sort and where to start sorting it from (ushally head)
struct node * insertionSort(struct node *n, struct node *comp){
    if(n->count<comp->right->count){
    n->right=comp->right;
    comp->right=n;
    return NULL;
    }
    return insertionSort(n,comp->right);
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
    new->lchild=new->rchild=new->right=NULL;
    return new;
}
//prints binary tree in base 2 and returns the number of chars printed excluding binary for chars (leaf nodes)
int printBinTree(struct node *n, int letterCount, FILE * outfile){
    if(n->letter!=0){
    fprintf(outfile, "1");
    letterCount++;
    //Because printf has no built in way to print binary
    printBinary(outfile,n->letter-0); 
    return letterCount;
    }
    letterCount++;
    fprintf(outfile, "0");
    letterCount+=printBinTree(n->lchild, letterCount, outfile);
    letterCount+=printBinTree(n->rchild, letterCount, outfile);
    return letterCount;
}
//takes in an int and prints it out in binary
void printBinary( FILE * outfile,int i){
    if(i<0){
    fprintf(outfile, "11111111");
    return;
    }
    int binNum[10];
    int ticker=0;
    while(i>0){
    binNum[ticker] = i%2;
    i=i/2;
    ticker++;
    }
    padOut(outfile,ticker);
    for(int j=ticker-1;j>=0;j--){
        fprintf(outfile, "%i",binNum[j]);
    }
}
//SOME PRINT METHODS LEFT IN FOR FUTURE TWEAKS.
//prints tree in pre order traversal
void printBitString(struct node *n, FILE * outfile){
    if(n->letter!=0){
    fprintf(outfile, "%s,%c ",n->bitstring, n->letter);
    return;
    }
    printBitString(n->lchild, outfile);
    printBitString(n->rchild, outfile);
}

//prints Linked List
struct node * printLL(struct node *n){
    
    if(n==tail){
	printf("\n");
	return NULL;
    }
    if(n->letter==0){
    printf("[INTERNAL,%i] -> ", n->count);
    }

    else if(n->letter==EOF){
    printf("[EOF,%i] -> ", n->count);
    }
    else if(n->letter=='\n'){
    printf("[\\n,%i] -> ", n->count);
    }
    else{
    printf("[%c,%i] -> ", n->letter,n->count);
    }
    return printLL(n->right);
}



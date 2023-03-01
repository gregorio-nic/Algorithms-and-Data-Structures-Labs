//
//  ST.c
//  Lab11_Es3
//
//  Created by Gregorio Nicora on 10/01/22.
//

#include "ST.h"

struct symboltable{
    char** vett;
    int N;
    int maxN;
};

static void InsertionSort(char** A,  int N){
    int i, j, l=0, r=N-1;
    char* x;
    for(i=l+1;i<=r;i++){
        x=A[i];
        j=i-1;
        while(j>=l && strcmp(A[j], x)>0){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=x;
    }
}

ST STinit(int maxN){
    int i;
    
    ST st=malloc(sizeof(*st));
    st->N=0;
    st->maxN=maxN;
    st->vett=malloc(st->maxN*sizeof(char*));
    
    for(i=0;i<maxN;i++)
        st->vett[i]=strdup("");
    return st;
}

void STfree(ST st){
    int i;
    for(i=0;i<st->N;i++)
        free(st->vett[i]);
    free(st->vett);
    free(st);
}

void STdisplay(ST st){
    int i;
    for(i=0;i<st->N;i++)
        printf("%s -> %d\n", st->vett[i], i);
}

int STcount(ST st){
    return st->N;
}

int STsearch(ST st, char* name){
    int i;
    for(i=0;i<st->N;i++){
        if(strcmp(st->vett[i], name)==0)
            return i;
    }
    return -1;
}

char* STsearchByIndex(ST st, int pos){
    if(strcmp(st->vett[pos], "")!=0)
        return st->vett[pos];
    return NULL;
}

int STinsert(ST st, char* name){
    int i=st->N;
    st->vett[st->N]=strcpy(st->vett[st->N], name);
    st->N++;
    return i;
}

void STdisplayOrdered(ST st, char** vertexNames, int size){
    int i;
    for(i=0;i<size;i++){
        vertexNames[i]=strdup(st->vett[i]);
    }
    InsertionSort(vertexNames, size);
}



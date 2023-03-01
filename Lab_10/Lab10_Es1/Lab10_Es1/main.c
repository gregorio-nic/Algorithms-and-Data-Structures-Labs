//
//  main.c
//  Lab10_Es1
//
//  Created by Gregorio Nicora on 23/11/21.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int start;
    int finish;
}att;

//HEADER FUNZIONI
att* carica_att(int*);
int trova_best(int**, att*, int, int, int);
int max(int, int);
void insertion_sort(att*, int);
int** malloc2dR(int, int);
void free_matr(int**,int);
void init_matr(att*, int**, int, int);
void stampa_sol(int**, int, int, int);

int main(int argc, const char * argv[]) {
    int num_att;
    att* el_att=carica_att(&num_att);
    int i;
    int best=0;
    insertion_sort(el_att, num_att);
    for(i=0;i<num_att;i++){
        printf("%d %d\n", el_att[i].start, el_att[i].finish);
    }
    
    int r=3,c=num_att;
    int** matr=malloc2dR(r, c);
    init_matr(el_att,matr,r,c);
    
    
    for(i=0;i<num_att;i++){
        best=max(trova_best(matr, el_att, r, c, i), best);
    }
    
    printf("La soluzione migliore ha durata %d\n", best);
    stampa_sol(matr,r,c,best);
    free_matr(matr, r);
    free(el_att);
    return 0;
}

int trova_best(int** matr, att* el_att, int r, int c, int n){
    int i,j;
    if(n==0){
        matr[2][n]=matr[0][n];
        return matr[2][n];
    }else{
        for(i=1;i<=n;i++){
            for(j=i-1;j>=0;j--){
                if(!((el_att[i].start<el_att[j].finish)&&(el_att[j].start<el_att[i].finish))){
                    matr[2][i]=max(matr[2][i],matr[0][i]+matr[2][j]);
                    if(matr[2][i]==matr[0][i]+matr[2][j])
                        matr[1][i]=j;
                }
            }
        }
        if(matr[2][i-1]==0){
            matr[2][i-1]=matr[0][i-1];
            matr[1][i-1]=-1;
        }
    }
    return matr[2][i-1];
}

void stampa_sol(int** matr, int r, int c, int  best){
    int i;
    for(i=c-1;i>=0;i--){
        if(matr[2][i]==best)
            break;
    }
    
    while(i>=0){
        printf("%d ", i);
        i=matr[1][i];
    }
    printf("\n");
}

int max(int a, int b){
    if(a>b)
        return a;
    return b;
}

void insertion_sort(att* el_att, int n){
    int l=0,r=n-1;
    int i,j;
    att x;
    for(i=l+1;i<=r;i++){
        x=el_att[i];
        j=i-1;
        while((x.finish<el_att[j].finish)&&(j>=l)){
            el_att[j+1]=el_att[j];
            j--;
        }
        el_att[j+1]=x;
    }
}

void init_matr(att* el_att,int** matr, int r, int c){
    int i;
    for(i=0;i<c;i++){
        matr[0][i]=el_att[i].finish-el_att[i].start;
        matr[1][i]=-1;
        matr[2][i]=0;
    }
    return;
}

int** malloc2dR(int nr, int nc){
    int** temp;
    int i;
    temp=(int**)malloc(nr*sizeof(int*));
    for(i=0;i<nr;i++){
        temp[i]=(int*)malloc(nc*sizeof(int));
    }
    return temp;
}

void free_matr(int** matr, int nr){
    int i;
    for(i=0;i<nr;i++){
        free(matr[i]);
    }
    return;
}


att* carica_att(int* num_att){
    int i;
    FILE* fp=fopen("att2.txt", "r");
    fscanf(fp, "%d", num_att);
    att* el_att=(att*)malloc(*num_att*sizeof(att));
    
    for(i=0;i<*num_att;i++){
        fscanf(fp,"%d %d", &(el_att[i].start), &(el_att[i].finish));
    }
    fclose(fp);
    return el_att;
}

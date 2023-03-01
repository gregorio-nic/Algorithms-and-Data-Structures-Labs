//
//  main.c
//  Lab9_Es1
//
//  Created by Gregorio Nicora on 18/11/21.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int start;
    int finish;
}att;

typedef struct{
    int* vett;
    int d;
}best_sol;

att* carica_att(int*);
void attSel(int, att*);
void attSel_r(int, int*, att*, int, best_sol*);

int check(int, int*, att*);
int is_best(int*, int, att*, best_sol*);
void change(int*, int, att*, best_sol*);
void stampa_best(best_sol*, att*, int);

int main(int argc, const char * argv[]) {
    int num_att;
    att* el_att=carica_att(&num_att);
    int i;
    for(i=0;i<num_att;i++){
        printf("%d %d\n", el_att[i].start, el_att[i].finish);
    }
    attSel(num_att, el_att);
    free(el_att);
    return 0;
}

void attSel(int num_att, att* el_att){
    best_sol best;
    best.vett=(int*)calloc(num_att,sizeof(int));
    best.d=0;
    
    int* sol=(int*)malloc(num_att*sizeof(int));
    
    attSel_r(0,sol,el_att,num_att,&best);
    
    stampa_best(&best,el_att,num_att);
    
    free(sol);
    free(best.vett);
    return;
}

void attSel_r(int pos, int* sol, att* el_att, int n, best_sol* best){
    if(pos>=n){
        if(is_best(sol,n,el_att,best)){
            change(sol,n,el_att,best);
            return;
        }
        return;
    }
    
    sol[pos]=1;
    if(check(pos,sol,el_att))
        attSel_r(pos+1,sol,el_att,n,best);
    sol[pos]=0;
    attSel_r(pos+1, sol, el_att, n, best);
    return;
}

int check(int pos, int* sol, att* el_att){
    if(pos==0)
        return 1;
    int i=pos-1;
    while(sol[i]==0)
        i--;
    if((el_att[pos].start<el_att[i].finish)&&(el_att[i].start<el_att[pos].finish))
        return 0;
    return 1;
}

int is_best(int* sol, int n, att* el_att, best_sol* best){
    int i;
    int d=0;
    for(i=0;i<n;i++){
        if(sol[i]==1)
            d+=((el_att[i].finish)-(el_att[i].start));
    }
    if(d>best->d)
        return 1;
    return 0;
}

void change(int* sol, int n, att* el_att, best_sol* best){
    int i;
    int d=0;
    for(i=0;i<n;i++){
        best->vett[i]=sol[i];
        if(sol[i]==1)
            d+=((el_att[i].finish)-(el_att[i].start));
    }
    best->d=d;
    return;
}

att* carica_att(int* num_att){
    int i;
    FILE* fp=fopen("att.txt", "r");
    fscanf(fp, "%d", num_att);
    att* el_att=(att*)malloc(*num_att*sizeof(att));
    
    for(i=0;i<*num_att;i++){
        fscanf(fp,"%d %d", &(el_att[i].start), &(el_att[i].finish));
    }
    fclose(fp);
    return el_att;
}

void stampa_best(best_sol* best, att* el_att, int n){
    int i;
    printf("\nS= (");
    
    for(i=0;i<n;i++){
        if(best->vett[i]==1){
            printf(" (%d,%d) ",el_att[i].start, el_att[i].finish);
        }
    }
    printf(")\n");
    printf("Con durata pari a %d\n", best->d);
    return;
}

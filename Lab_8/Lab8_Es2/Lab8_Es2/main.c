 //
//  main.c
//  Lab8_Es2
//
//  Created by Gregorio Nicora on 13/11/21.
//

#include <stdio.h>
#include <stdlib.h>

#define NUM_PIETRE 4

typedef struct{
    int* chain;
    int size;
    int value;
} Sol;

void leggiTest(FILE*, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*);
void longestChain(int, int, int, int, int, int, int, int, int, int, int);
void longestChain_r(int, Sol*, int*, int*, int, int, int, int, Sol*);
int check_prev(int*, int, int);
int check_max_rip(int*, int, int);
int check_z_min_s(int*, int);
void update_best(Sol*, int, Sol*);
void stampa_sol(Sol*);

int main(int argc, const char * argv[]) {
    int i, num_test, tot_pietre, z, r, t, s, val_z, val_r, val_t, val_s, val, max_rip;
            
    FILE* fp;
    fp=fopen("test_set.txt", "r");
    fscanf(fp, "%d", &num_test);
            
    for(i=0;i<num_test;i++){
        leggiTest(fp, &z, &r, &t, &s, &val_z, &val_r, &val_t, &val_s, &tot_pietre, &val, &max_rip);
        printf("TEST #%d\nzaffiro = %d [%d], rubino = %d [%d], topazio = %d [%d], smeraldo = %d [%d], TOT = %d [%d](max_rip = %d)\n", i+1, z, val_z, r, val_r, t, val_t, s, val_s, tot_pietre, val, max_rip);
        longestChain(z, r, t, s, tot_pietre, val_z, val_r, val_t, val_s, val, max_rip);
    }
    
    fclose(fp);
    return 0;
}

void longestChain(int z, int r, int t, int s, int tot_pietre, int val_z, int val_r, int val_t, int val_s, int val, int max_rip){
    int i;
    int mark[NUM_PIETRE];
    int values[NUM_PIETRE];
    Sol temp, best;
    
    mark[0]=z;
    mark[1]=r;
    mark[2]=t;
    mark[3]=s;
    values[0]=val_z;
    values[1]=val_r;
    values[2]=val_t;
    values[3]=val_s;
    
    best.chain=malloc(tot_pietre*sizeof(int));
    best.size=0;
    best.value=0;
    for(i=1; i<=tot_pietre; i++){
        temp.chain=(int*)malloc(i*sizeof(int));
        temp.value=0;
        longestChain_r(0, &temp, mark, values, val, max_rip, NUM_PIETRE, i, &best);
        free(temp.chain);
    }
    stampa_sol(&best);
    free(best.chain);
    return;
}

void longestChain_r(int pos, Sol* temp, int* mark, int* values, int val, int max_rip, int n, int k, Sol* best){
    int i;
    //condizione terminale
    if(pos>=k){
        //controllo sulla sequenza di pietre
        if(check_prev(temp->chain, pos, k)&&check_max_rip(temp->chain, pos, max_rip)&&check_z_min_s(temp->chain, k)){
            if(temp->value>best->value){
                update_best(temp,k,best);
            }
        }
        return;
    }
    
    for(i=0;i<n;i++){
        if(mark[i]>0){
            mark[i]--;
            temp->chain[pos]=i;
            temp->value+=values[i];
            if(check_prev(temp->chain, pos, k)&&check_max_rip(temp->chain, pos, max_rip))
                longestChain_r(pos+1, temp, mark, values, val, max_rip, n, k, best);
            temp->value-=values[i];
            mark[i]++;
        }
    }
    
    return;
}

void update_best(Sol* temp, int size_sol, Sol* best){
    int i;
    for(i=0;i<size_sol;i++){
        best->chain[i]=temp->chain[i];
        best->value=temp->value;
        best->size=size_sol;
    }
    return;
}

int check_max_rip(int* sol, int pos, int max_rip){
    int count=0, val, i;
    
    val=sol[pos];
    count++;
    i=pos-1;
    while(i>=0){
        if(sol[i]!=val)
            return 1;
        count++;
        if(count>max_rip)
            return 0;
        i--;
    }
    return 1;
}

int check_z_min_s(int* sol, int size){
    int count_z=0, count_s=0, i;
    for(i=0;i<size;i++){
        if(sol[i]==0)
            count_z++;
        if(sol[i]==3)
            count_s++;
    }
    if(count_z<=count_s)
        return 1;
    return 0;
}

int check_prev(int* sol, int pos, int n){
    if(pos==0)
        return 1;
    if(pos>n-1)
        return 1;
    switch (sol[pos-1]) {
        case 0:
            if((sol[pos]!=0)&&(sol[pos]!=1))
                return 0;
            break;
        case 1:
            if((sol[pos]!=2)&&(sol[pos]!=3))
                return 0;
            break;
        case 2:
            if((sol[pos]!=0)&&(sol[pos]!=1))
                return 0;
            break;
        case 3:
            if((sol[pos]!=2)&&(sol[pos]!=3))
                return 0;
            break;
        }
    return 1;
}

void leggiTest(FILE* fp, int* z, int* r, int* t, int* s, int* val_z, int* val_r, int* val_t, int* val_s, int* tot_pietre, int* val, int* max_rip){
    fscanf(fp, "%d %d %d %d %d %d %d %d %d", z, r, t, s, val_z, val_r, val_t, val_s, max_rip);
    *tot_pietre=(*z)+(*r)+(*t)+(*s);
    *val= (*val_z)*(*z)+(*val_r)*(*r)+(*val_t)*(*t)+(*val_s)*(*s);
    return;
}

void stampa_sol(Sol* best){
    int i;
    printf("Catena di valore massimo pari a %d e di lunghezza %d:\n", best->value, best->size);
    printf("{");
    for(i=0;i<best->size;i++){
        printf(" %d ", best->chain[i]);
    }
    printf("}\n");
    return;
}


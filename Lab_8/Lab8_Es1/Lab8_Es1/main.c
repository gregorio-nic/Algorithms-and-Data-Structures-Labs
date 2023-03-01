//
//  main.c
//  Lab8_Es1
//
//  Created by Gregorio Nicora on 11/11/21.
//

#include <stdio.h>
#include <stdlib.h>

#define NUM_PIETRE 4

void leggiTest(FILE*, int*, int*, int*, int*, int*);
void longestChain(int, int, int, int, int);
int longestChain_r(int, int*, int*, int, int);
int check(int*, int, int);
void stampa_sol(int*, int);

int main(int argc, const char * argv[]) {
    int i, num_test, tot_pietre, z, r, t, s;
            
    FILE* fp;
    fp=fopen("easy_test_set.txt", "r");
    fscanf(fp, "%d", &num_test);
            
    for(i=0;i<num_test;i++){
        leggiTest(fp, &z, &r, &t, &s, &tot_pietre);
        printf("TEST #%d\nzaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n", i+1, z, r, t, s, tot_pietre);
        longestChain(z, r, t, s, tot_pietre);
    }
    
    fclose(fp);
    return 0;
}

void longestChain(int z, int r, int t, int s, int tot_pietre){
    int i;
    int mark[NUM_PIETRE];
    int* sol;
    mark[0]=z;
    mark[1]=r;
    mark[2]=t;
    mark[3]=s;
    for(i=tot_pietre; i>1; i--){
        sol=(int*)malloc(i*sizeof(int));
        if(longestChain_r(0, sol, mark, NUM_PIETRE, i)){
            free(sol);
            break;
        }
        free(sol);
    }
    return;
}

int longestChain_r(int pos, int* sol, int* mark, int n, int k){
    int i;
    if(pos>=k){
        if(check(sol, pos, k)){
            printf("Collana massima di lunghezza %d:\n", k);
            stampa_sol(sol, k);
            printf("\n");
            return 1;
        }else{
            return 0;
        }
    }
    
    for(i=0;i<n;i++){
        if(mark[i]>0){
            mark[i]--;
            sol[pos]=i;
            if(check(sol, pos, k)){
                if (longestChain_r(pos+1, sol, mark, n, k)) {
                    return 1;
                }
            }
            mark[i]++;
        }
    }
    return 0;
}

int check(int* sol, int pos, int n){
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

void leggiTest(FILE* fp, int* z, int* r, int* t, int* s, int* tot_pietre){
    fscanf(fp, "%d %d %d %d", z, r, t, s);
    *tot_pietre=(*z)+(*r)+(*t)+(*s);
    return;
}

void stampa_sol(int* sol, int size){
    int i;
    printf("{");
    for(i=0;i<size;i++){
        printf(" %d ", sol[i]);
    }
    printf("}\n");
    return;
}

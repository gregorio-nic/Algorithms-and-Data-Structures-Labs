//
//  main.c
//  Lab10_Es2
//
//  Created by Gregorio Nicora on 09/12/21.
//

#include <stdio.h>
#include <stdlib.h>

#define NUM_PIETRE 4

//HEADER FUNZIONI
void leggiTest(FILE*, int*, int*, int*, int*, int*);
void longestChain(int, int, int, int, int);
int longestChain_r(int, int*, int);


int fZ(int*);
int fR(int*);
int fT(int*);
int fS(int*);

int main(int argc, const char * argv[]) {
    int i, num_test, tot_pietre, z, r, t, s;
            
    FILE* fp;
    fp=fopen("very_very_easy_test_set.txt", "r");
    fscanf(fp, "%d", &num_test);
            
    for(i=0;i<num_test;i++){
        leggiTest(fp, &z, &r, &t, &s, &tot_pietre);
        printf("TEST #%d\nzaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n", i+1, z, r, t, s, tot_pietre);
        //longestChain(z, r, t, s, tot_pietre);
    }
    
    fclose(fp);
    return 0;
}

void longestChain(int z, int r, int t, int s, int tot_pietre){
    int i;
    int mark[NUM_PIETRE];
    mark[0]=z;
    mark[1]=r;
    mark[2]=t;
    mark[3]=s;
    
    int count[NUM_PIETRE];
    count[0]=0;
    count[1]=0;
    count[2]=0;
    count[3]=0;
    
    
    for(i=tot_pietre; i>1; i--){
        
        //INIZIO CON Z
        if(fZ(mark))
            longestChain_r(1,mark,i-1);
        //INIZIO CON R
        if(fR(mark))
            longestChain_r(1,mark,i-1);
        //INIZIO CON T
        if(fT(mark))
            longestChain_r(2,mark,i-1);
        //INIZIO CON S
        if(fS(mark))
            longestChain_r(3,mark,i-1);

    }
    return;
}

int longestChain_r(int gemma, int* mark, int p){
//    if(pos>=p){
//        printf("Collana massima di lunghezza %d:\n", p);
//        printf("\n");
//        return 1;
//    }
    switch (gemma) {
        case 0:
            if(fZ(mark))
                longestChain_r(1,mark,p-1);
        case 1:
            fR(mark);
            break;
        case 2:
            fT(mark);
            break;
        case 3:
            fS(mark);
            break;
    }
    
    return 0;
}

int fZ(int* mark){
    if(mark[0]>0){
        mark[0]--;
        return 1;
    }else
        return 0;
}

int fR(int* mark){
    if(mark[1]>0){
        mark[1]--;
        return 1;
    }else
        return 0;
}

int fT(int* mark){
    if(mark[2]>0){
        mark[2]--;
        return 1;
    }else
        return 0;
}

int fS(int* mark){
    if(mark[3]>0){
        mark[3]--;
        return 1;
    }else
        return 0;
}

void leggiTest(FILE* fp, int* z, int* r, int* t, int* s, int* tot_pietre){
    fscanf(fp, "%d %d %d %d", z, r, t, s);
    *tot_pietre=(*z)+(*r)+(*t)+(*s);
    return;
}

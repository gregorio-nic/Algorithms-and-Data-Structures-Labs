//
//  main.c
//  Lab0_Es1
//
//  Created by Gregorio Nicora on 07/09/21.
//

#include <stdio.h>
#include <stdlib.h>
#define N 8

int acquisici_valore(void);
void stampa_vettore(int*, int);
int trova_max(int*);
void stampa_vect_max(int*, int);

int main(int argc, const char * argv[]) {
    int i;
    int vect[N];
    for(i=0; i<N; i++){
        vect[i] = acquisici_valore();
    }
    stampa_vettore(vect, N);
    
    int max;
    max = trova_max(vect);
    printf("La lunghezza massima di un sottovettore non nullo é: %d\n", max);
    stampa_vect_max(vect, max);
    return 0;
}

int acquisici_valore(void){
    int n;
    printf("Inserire valore: ");
    fscanf(stdin, "%d", &n);
    return n;
}

void stampa_vettore(int* vect, int n){
    int i;
    printf("{");
    for(i=0; i<n; i++){
        printf("%d ", vect[i]);
    }
    printf("} \n");
}

int trova_max(int* vect){
    int i, j, count, max = 0;
    for(i=0; i<N; i++){
        count=0;
        j = i;
        while(vect[j]!=0 && j < N){
            count++;
            j++;
        }
        if(count>=max)
            max=count;
    }
    return max;
}

void stampa_vect_max(int* vect, int max){
    int i, j;
    int test[N];
    for(i=0; i<N; i++){
        j=i;
        while(vect[j]!=0 && j < N){
            test[j-i] = vect[j];
            j++;
        }
        if((j-i)==max)
            stampa_vettore(test, max);
    }
}

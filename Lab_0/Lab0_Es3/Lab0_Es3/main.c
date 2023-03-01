//
//  main.c
//  Lab0_Es3
//
//  Created by Gregorio Nicora on 08/09/21.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXN 30


void ruota(int*, int, int, int);
void stampa_vettore(int*, int);

int main(int argc, const char * argv[]) {
    int n, i;
    int vett[MAXN];
    
//    acquisisco lunghezza effettiva vettore
    printf("Inserire la dimensione del vettore: ");
    scanf("%d", &n);
    
    
//    acquisisco vettore da tastiera
    printf("Inserire gli %d elementi del vettore: ", n);
    for(i=0; i<n; i++){
        scanf("%d", &vett[i]);
    }
    
//    ristampo vettore appena acquisito per verifica
    printf("{ ");
    for(i=0; i<n; i++){
        printf("%d ", vett[i]);
    }
    printf("}\n");
    
    
    int p, dir;
    printf("Digitare numero di cifre di cui ruotare altrimenti digitare 0 per terminare: ");
    scanf("%d", &p);
    while( p != 0 && p < n){
        printf("Digitare 1 per ruotare a sinistra e -1 per ruotare a destra: ");
        scanf("%d", &dir);
        ruota(vett, n, p, dir);
        printf("Digitare nuovamente numero di cifre di cui ruotare altrimenti digitare 0 per terminare: ");
        scanf("%d", &p);
    }
    
    return 0;
}

void ruota(int* vett, int n, int p, int dir){
    int v_final[n];
    int i;
    if(dir == -1){
        for(i=0; i<n; i++){
            v_final[(i+p)%n] = vett[i];
        }
        stampa_vettore(v_final, n);
    }
    if(dir == 1){
        for(i=0; i<n; i++){
            v_final[(n+i-p)%n] = vett[i];
        }
        stampa_vettore(v_final, n);
    }
    return;
}

void stampa_vettore(int* v_final, int n){
    int i;
    printf("Vettore ruotato: { ");
    for(i=0;i<n;i++){
        printf("%d ", v_final[i]);
    }
    printf("}\n");
}

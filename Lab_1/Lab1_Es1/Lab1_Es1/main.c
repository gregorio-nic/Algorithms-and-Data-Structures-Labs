//
//  main.c
//  Lab1_Es1
//
//  Created by Gregorio Nicora on 28/09/21.
//

#include <stdio.h>
#include <stdlib.h>

#define N 20

typedef struct{
    int righe;
    int col;
} dim;

typedef struct{
    int index;
    int points;
} cap;

dim leggi_mat(FILE*, int[][N]);
void stampa_mat(FILE*, int[][N], dim);
int capol_giornata(int[][N], dim, int);

int main(int argc, const char * argv[]) {
    FILE* fp = fopen("mat.txt", "r");
    int k, cap, mat[N][N];
    dim dimensioni;
    
//    acquisisco le dim e la matrice e la stampo
    dimensioni=leggi_mat(fp, mat);
    printf("Le dimensioni della matrice sono %d righe e %d colonne\n", dimensioni.righe, dimensioni.col);
    stampa_mat(stdout, mat, dimensioni);
    
//    trovo la capolista di giornata e la stampo
    for(k = 1; k <= dimensioni.col; k++){
        cap = capol_giornata(mat, dimensioni, k);
        printf("La capolista alla giornata %d è %d\n", k, cap+1);
    }
    
    return 0;
}

dim leggi_mat(FILE* fp, int mat[][N]){
    int i, j;
    dim dimensione;
    fscanf(fp, "%d %d", &dimensione.righe, &dimensione.col);
    for(i = 0; i < dimensione.righe; i++){
        for(j = 0; j < dimensione.col; j++){
            fscanf(fp, "%d ", &mat[i][j]);
        }
    }
    return dimensione;
}

void stampa_mat(FILE* fp, int mat[][N], dim dimensioni){
    int i, j;
    
    for(i = 0; i < dimensioni.righe; i++){
        for(j = 0; j < dimensioni.col; j++){
            fprintf(fp, "%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int capol_giornata(int mat[][N], dim dimensioni, int k){
    int i, j, temp=0;
    cap capol;
    capol.points=0;
    
    for(i=0;i<dimensioni.righe;i++){
        temp=0;
        for(j=0;j<k;j++){
            temp+=mat[i][j];
        }
//        verifico se è maggiore del capolista trovato fino ad ora
        if(temp>capol.points){
            capol.index=i;
            capol.points=temp;
        }
    }
    return capol.index;
}

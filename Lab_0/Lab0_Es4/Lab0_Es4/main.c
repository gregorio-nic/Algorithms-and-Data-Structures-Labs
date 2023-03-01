//
//  main.c
//  Lab0_Es4
//
//  Created by Gregorio Nicora on 09/09/21.
//

#include <stdio.h>
#include <stdlib.h>

#define N 20

void leggi_mat(int);


int main(int argc, const char * argv[]) {
    int dim;
    
    printf("Digitare 0 per terminare oppure digitare il valore della dimensione della sottomatrice quadrata: ");
    scanf("%d", &dim);

    while(dim != 0){
        leggi_mat(dim);
        printf("Digitare 0 per terminare oppure digitare il valore della dimensione della sottomatrice quadrata: ");
        scanf("%d", &dim);
    }
    
    
    return 0;
}

void leggi_mat(int dim){
    int nr, nc, i, j;
    int mat[N][N];
    char nome_file[20];
    FILE* fp;
    
    printf("Inserire il nome del file: ");
    scanf("%s", nome_file);
    fp = fopen(nome_file,"r");
    fscanf(fp,"%d %d", &nr, &nc);
    
    
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    
    printf("Matrice letta:\n");
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    
    if(dim<=nr && dim<=nc && dim>=1){
        //troviamo ste cazzo di sottomatrici
        //aggiornamento: mi viene da piangere, sento che è una virgola che mi sto perdendo ma vorrei trovarla PD
        printf("porcodio");
    }else{
        printf("ma sei scemo così grandfe!!!");
    }
    
    fclose(fp);
    return;
}


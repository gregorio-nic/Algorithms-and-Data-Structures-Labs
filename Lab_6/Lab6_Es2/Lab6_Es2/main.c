//
//  main.c
//  Lab6_Es2
//
//  Created by Gregorio Nicora on 29/10/21.
//

#include <stdio.h>
#include <stdlib.h>

int** malloc2dR(int, int);
void malloc2dP(int***, int, int);
void read_matr(FILE*, int**, int, int);
void print_matr(int**, int, int);
void separa(int**, int, int, int*, int*);
void free_matr(int**, int);

int main(int argc, const char * argv[]) {
    int nr, nc;
    int** matr;
    int* white, *black;
    FILE* fp;
    fp=fopen("mat.txt", "r");
    fscanf(fp,"%d %d" , &nr, &nc);
    
    //matr = malloc2dR(nr, nc);
    malloc2dP(&matr, nr, nc);
    read_matr(fp, matr, nr, nc);
    fclose(fp);
    
    print_matr(matr, nr, nc);
    
    separa(matr, nr, nc, white, black);
    
    free_matr(matr, nr);
    free(matr);
    return 0;
}

void separa(int** matr, int nr, int nc, int* white, int* black){
    int i, j, w=0, b=0;
    //allochiamo i due vettori destinazione bianco e nero
    white=(int*)malloc(((nr*nc/2)+1)*sizeof(int));
    black=(int*)malloc(((nr*nc/2)+1)*sizeof(int));
    
    //separiamo i bianchi dai neri :(
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if((i+j)%2==0){
                black[b]=matr[i][j];
                b++;
            }else{
                white[w]=matr[i][j];
                w++;
            }
        }
    }
    
    printf("Vettore nero: {");
    for(i=0;i<b;i++){
        printf("%d ", black[i]);
    }
    printf("}\n");
    
    printf("Vettore bianco: {");
    for(i=0;i<w;i++){
        printf("%d ", white[i]);
    }
    printf("}\n");
    
    free(black);
    free(white);
    return;
}

void malloc2dP(int*** matr, int nr, int nc){
    int** temp;
    int i;
    temp=(int**)malloc(nr*sizeof(int*));
    for(i=0;i<nr;i++){
        temp[i]=(int*)malloc(nc*sizeof(int));
    }
    *matr=temp;
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

void read_matr(FILE* fp, int** matr, int nr, int nc){
    int i, j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            fscanf(fp,"%d", &matr[i][j]);
        }
    }
    return;
}

void print_matr(int** matr, int nr, int nc){
    int i, j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d", matr[i][j]);
        }
        printf("\n");
    }
    return;
}

//
//  main.c
//  Lab3_Es1
//
//  Created by Gregorio Nicora on 13/10/21.
//



#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val,flag;
} Item;

typedef struct {
    int row, col, len, height, area;
} Max;

#define N 50

void inizializzo_mat(Item[][N]);
void leggi_file(FILE*, Item[][N], int*, int*);
void stampa_mat(Item[][N], int, int);
void max_len(Item[][N], int, int);
void stampa_max(Max);
void inizializzo_max(Max*);
void max_height(Item mat[][N], int nr, int nc);
void max_area(Item mat[][N], int nr, int nc);

int main(int argc, const char * argv[]) {
    int nr, nc;
    Item mat[N][N];
    
//    inizializzo i valori dei flag della matrice
    inizializzo_mat(mat);
    
//    leggo matrice da file e stampo risultato
    FILE* fp=fopen("mat.txt", "r");
    leggi_file(fp, mat, &nr, &nc);
    fclose(fp);
    printf("Matrice: \n");
    stampa_mat(mat, nr, nc);
    
//    trovo la regione massima per lunghezza
    max_len(mat, nr, nc);
    
//    trovo la regione massima per altezza
    inizializzo_mat(mat);
    max_height(mat, nr, nc);
    
//    trovo la regione massima per area
    inizializzo_mat(mat);
    max_area(mat, nr, nc);
    return 0;
}

void max_len(Item mat[][N], int nr, int nc){
    int i, j, k;
    Max max;
    inizializzo_max(&max);
    
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(mat[i][j].val==1){
                if(mat[i][j].flag==0){
                    mat[i][j].flag=1;
                    k=1;
                    while(mat[i][j+k].val==1){
                        mat[i][j+k].flag=1;
                        k++;
                    }
                    if(k>=max.len){
                        max.row=i;
                        max.col=j;
                        max.len=k;
                        k=1;
                        while(mat[i+k][j].val==1){
                            mat[i+k][j].flag=1;
                            k++;
                        }
                        max.height=k;
                        max.area=max.height*max.len;
                    }
                }
            }
        }
    }
    printf("La regione nera di massima lunghezza è: \n");
    stampa_max(max);
    return;
}

void max_height(Item mat[][N], int nr, int nc){
    int i, j, k;
    Max max;
    inizializzo_max(&max);
    
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(mat[i][j].val==1){
                if(mat[i][j].flag==0){
                    mat[i][j].flag=1;
                    k=1;
                    while(mat[i+k][j].val==1){
                        mat[i+k][j].flag=1;
                        k++;
                    }
                    if(k>=max.height){
                        max.row=i;
                        max.col=j;
                        max.height=k;
                        k=1;
                        while(mat[i][j+k].val==1){
                            mat[i][j+k].flag=1;
                            k++;
                        }
                        max.len=k;
                        max.area=max.height*max.len;
                    }
                }
            }
        }
    }
    printf("La regione nera di massima altezza è: \n");
    stampa_max(max);
    return;
}

void max_area(Item mat[][N], int nr, int nc){
    int i, j, l, h;
    Max max;
    inizializzo_max(&max);
    
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(mat[i][j].val==1){
                if(mat[i][j].flag==0){
                    mat[i][j].flag=1;
                    l=1;
                    while(mat[i][j+l].val==1){
                        mat[i][j+l].flag=1;
                        l++;
                    }
                    h=1;
                    while(mat[i+h][j].val==1){
                        mat[i+h][j].flag=1;
                        h++;
                    }
                    if(l*h>=max.area){
                        max.row=i;
                        max.col=j;
                        max.height=h;
                        max.len=l;
                        max.area=max.height*max.len;
                    }
                }
            }
        }
    }
    printf("La regione nera di massima area è: \n");
    stampa_max(max);
    return;
}

void inizializzo_max(Max* max){
    max->row=0;
    max->col=0;
    max->len=0;
    max->height=0;
    max->area=0;
    return;
}


void stampa_max(Max max){
    printf("Inizio in mat[%d][%d]\n", max.row, max.col);
    printf("Dimensioni:\n l:%d h:%d A:%d\n", max.len, max.height, max.area);
}

void inizializzo_mat(Item mat[][N]){
    int i, j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            mat[i][j].flag=0;
        }
    }
}

void leggi_file(FILE* fp, Item mat[][N], int* nr, int* nc){
    int i, j;
    fscanf(fp,"%d %d", nr, nc);
    for(i=0;i<*nr;i++){
        for(j=0;j<*nc;j++){
            fscanf(fp, " %d ", &(mat[i][j].val));
        }
    }
    return;
}

void stampa_mat(Item mat[][N], int nr, int nc){
    int i, j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d ", mat[i][j].val);
        }
        printf("\n");
    }
    return;
}

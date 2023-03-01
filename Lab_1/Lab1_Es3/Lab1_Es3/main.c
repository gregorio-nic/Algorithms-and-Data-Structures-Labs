//
//  main.c
//  Lab1_Es3
//
//  Created by Gregorio Nicora on 29/09/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

void stampa_mat(int[][N], int, int);
int controlla_ruota_mat(int[][N], int, int, char[], int, char[], int);
void leggi_comando(char*, int*, char*, int*);
void ruota_riga(int*, int, int, int);
void ruota_colonna(int*[], int, int, int);


int main(int argc, const char * argv[]) {
    int mat[N][N] = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    int index, num_pos;
    char selettore[10], direzione[10];
    stampa_mat(mat, 3, 3);
    
    leggi_comando(selettore, &index, direzione, &num_pos);
    printf("comandi digitati: %s %d %s %d\n", selettore, index, direzione, num_pos);
    
    while(controlla_ruota_mat(mat, 3, 3, selettore, index, direzione, num_pos)!=-1){
        stampa_mat(mat, 3, 3);
        leggi_comando(selettore, &index, direzione, &num_pos);
        printf("comandi digitati: %s %d %s %d\n", selettore, index, direzione, num_pos);
    }
    stampa_mat(mat, 3, 3);
    return 0;
}



int controlla_ruota_mat(int mat[][N], int nr, int nc, char selettore[], int index, char dir[], int num_pos){
    if(strcmp(selettore,"fine")!=0){
        if(strcmp(selettore, "riga")==0){
            if(index<nr){
                if(strcmp("destra", dir)==0){
                    ruota_riga(&mat[index], nc, num_pos, -1);
                }
                else if(strcmp("sinistra", dir)==0){
                    ruota_riga(&mat[index], nc, num_pos, 1);
                }else{
                    printf("ERRORE, direzione non valida per selettore selezionato!\n");
                }

            }else{
                printf("ERRORE, indice più grande del numero di righe!\n");
            }
        }else{
            if(index<nc){
                if(strcmp("su", dir)==0){
                    int i;
                    int* v_p[nc];
                    for(i=0;i<nc;i++){
                        v_p[i]=&mat[i][index];
                    }
                    ruota_colonna(v_p, nr, num_pos, 1);
                }
                else if(strcmp("giu", dir)==0){
                    int i;
                    int* v_p[nc];
                    for(i=0;i<nc;i++){
                        v_p[i]=&mat[i][index];
                    }
                    ruota_colonna(v_p, nr, num_pos, -1);
                }else{
                    printf("ERRORE, direzione non valida per selettore selezionato!\n");
                }

            }else{
                printf("ERRORE, indice più grande del numero di colonne!\n");
            }
        }
    }else{
        return -1;
    }
    return 0;
}

void ruota_riga(int* vett, int n, int p, int dir){
    int v_final[n];
    int i;
    if(dir == -1){
        for(i=0; i<n; i++){
            v_final[(i+p)%n] = vett[i];
        }
    }
    if(dir == 1){
        for(i=0; i<n; i++){
            v_final[(n+i-p)%n] = vett[i];
        }
    }
    for(i=0;i<n;i++){
        vett[i]=v_final[i];
    }
    return;
}

void ruota_colonna(int* vett[], int n, int p, int dir){
    int v_final[n];
    int i;
    if(dir == -1){
        for(i=0; i<n; i++){
            v_final[(i+p)%n] = *(vett[i]);
        }
    }
    if(dir == 1){
        for(i=0; i<n; i++){
            v_final[(n+i-p)%n] = *(vett[i]);
        }
    }
    for(i=0;i<n;i++){
        *vett[i]=v_final[i];
    }
    return;
}

void stampa_mat(int mat[][N], int nr, int nc){
    int i, j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return;
}

void leggi_comando(char* selettore, int* index, char* direzione, int* num_pos){
    printf("<selettore> <indice> <direzione> <posizioni> (fine in <selettore> per terminare): ");
    scanf("%s %d %s %d", selettore, index, direzione, num_pos);
    return;
}

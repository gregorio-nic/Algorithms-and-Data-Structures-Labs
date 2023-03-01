//
//  main.c
//  Lab9_Es2
//
//  Created by Gregorio Nicora on 18/11/21.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char color_t1, color_t2;
    int value_t1, value_t2;
    int usata;
}Tessera;

typedef struct{
    int indice_tessera;
    int is_ruotato;
}Casella;

typedef struct{
    int r_pos;
    int c_pos;
}Casella_vuota;

typedef struct{
    Casella** scacchiera;
    int punteggio;
}Best;

Tessera* carica_tessere(FILE*, int*);
void stampa_tessere(Tessera*, int);
Casella** carica_scacchiera(FILE*, int*, int*);
void stampa_scacchiera(Casella**, int, int);
void libera_scacchiera(Casella**, int, int);
int caselle_libere_e_flagga_usate(Casella_vuota*, Tessera*, Casella**, int, int);
int* vettore_indici_tessere_non_usate(Tessera*, int, int);
void inserisci_tessere_r(int, Casella_vuota*, int*, int, Casella**, int, int, Tessera*, Best*);
int check(Casella**, int, int, Tessera*);
int is_best(Best*, int);
void update_best(Best*, Casella**, int, int, int);


int main(int argc, const char * argv[]) {
    int num_tessere;
    FILE* fp=fopen("tiles.txt", "r");
    fscanf(fp,"%d",&num_tessere);
    Tessera* el_tessere=carica_tessere(fp,&num_tessere);
    fclose(fp);
    stampa_tessere(el_tessere, num_tessere);
    
    fp=fopen("board.txt", "r");
    int r, c;
    Casella** scacchiera=carica_scacchiera(fp,&r,&c);
    fclose(fp);
    stampa_scacchiera(scacchiera,r,c);
    
    
    Casella_vuota* el_caselle_libere=(Casella_vuota*)malloc((r*c)*sizeof(Casella_vuota));
    int caselle_libere;
    
    caselle_libere=caselle_libere_e_flagga_usate(el_caselle_libere,el_tessere,scacchiera,r,c);
    printf("%d caselle da riempire\n", caselle_libere);
    
    int* tessere_tbi=vettore_indici_tessere_non_usate(el_tessere,num_tessere,caselle_libere);
    
    Best best_sol;
    best_sol.scacchiera=carica_scacchiera(stdin, &r, &c);
    best_sol.punteggio=0;
    
    
    inserisci_tessere_r(0, el_caselle_libere, tessere_tbi, caselle_libere, scacchiera, r, c, el_tessere, &best_sol);
    
    printf("La migliore scacchiera ha somma: %d\n", best_sol.punteggio);
    stampa_scacchiera(best_sol.scacchiera, r, c);
    
    
    libera_scacchiera(best_sol.scacchiera, r, c);
    free(el_caselle_libere);
    free(tessere_tbi);
    libera_scacchiera(scacchiera,r,c);
    free(el_tessere);
    return 0;
}


void inserisci_tessere_r(int pos, Casella_vuota* el_caselle_libere, int* tessere_tbi, int size, Casella** scacchiera, int r, int c, Tessera* el_tessere, Best* best_sol){
    int i,punteggio;
    
    if(pos>=size){
        if((punteggio=check(scacchiera,r,c,el_tessere))>0){
            if(is_best(best_sol,punteggio)){
                update_best(best_sol, scacchiera, r, c, punteggio);
            }
        }
        return;
    }
    
    for(i=0;i<size;i++){
        if(el_tessere[tessere_tbi[i]].usata==0){
            el_tessere[tessere_tbi[i]].usata=1;
            scacchiera[el_caselle_libere[pos].r_pos][el_caselle_libere[pos].c_pos].indice_tessera=tessere_tbi[i];
            scacchiera[el_caselle_libere[pos].r_pos][el_caselle_libere[pos].c_pos].is_ruotato=0;
            inserisci_tessere_r(pos+1, el_caselle_libere, tessere_tbi, size, scacchiera, r, c, el_tessere, best_sol);
            scacchiera[el_caselle_libere[pos].r_pos][el_caselle_libere[pos].c_pos].is_ruotato=1;
            inserisci_tessere_r(pos+1, el_caselle_libere, tessere_tbi, size, scacchiera, r, c, el_tessere, best_sol);
            el_tessere[tessere_tbi[i]].usata=0;
        }
    }
    return;
}

int is_best(Best* best_sol, int punteggio){
    if(punteggio>best_sol->punteggio)
        return 1;
    return 0;
}

int check(Casella** scacchiera, int r, int c, Tessera* el_tessere){
    int i, j;
    int punteggio_tot=0, punteggio_r, punteggio_c;
    
    
    //calcolo righe
    for(i=0;i<r;i++){
        punteggio_r=0;
        for(j=0;j<c;j++){
            if(j==0){
                if(scacchiera[i][j].is_ruotato==0){
                    punteggio_r+=el_tessere[scacchiera[i][j].indice_tessera].value_t1;
                }else{
                    punteggio_r+=el_tessere[scacchiera[i][j].indice_tessera].value_t2;
                }
            }else{
                if(scacchiera[i][j].is_ruotato==0&&scacchiera[i][j-1].is_ruotato==0){
                    if(el_tessere[scacchiera[i][j].indice_tessera].color_t1==el_tessere[scacchiera[i][j-1].indice_tessera].color_t1){
                        punteggio_r+=el_tessere[scacchiera[i][j].indice_tessera].value_t1;
                    }else{
                        punteggio_r=0;
                        break;
                    }
                }else if (scacchiera[i][j].is_ruotato==0&&scacchiera[i][j-1].is_ruotato==1){
                    if(el_tessere[scacchiera[i][j].indice_tessera].color_t1==el_tessere[scacchiera[i][j-1].indice_tessera].color_t2){
                        punteggio_r+=el_tessere[scacchiera[i][j].indice_tessera].value_t1;
                    }else{
                        punteggio_r=0;
                        break;
                    }
                }else if (scacchiera[i][j].is_ruotato==1&&scacchiera[i][j-1].is_ruotato==0){
                    if(el_tessere[scacchiera[i][j].indice_tessera].color_t2==el_tessere[scacchiera[i][j-1].indice_tessera].color_t1){
                        punteggio_r+=el_tessere[scacchiera[i][j].indice_tessera].value_t2;
                    }else{
                        punteggio_r=0;
                        break;
                    }
                }else if (scacchiera[i][j].is_ruotato==1&&scacchiera[i][j-1].is_ruotato==1){
                    if(el_tessere[scacchiera[i][j].indice_tessera].color_t2==el_tessere[scacchiera[i][j-1].indice_tessera].color_t2){
                        punteggio_r+=el_tessere[scacchiera[i][j].indice_tessera].value_t2;
                    }else{
                        punteggio_r=0;
                        break;
                    }
                }
            }
        }
        punteggio_tot+=punteggio_r;
    }
    
    //calcolo colonne
    for(j=0;j<c;j++){
        punteggio_c=0;
        for(i=0;i<r;i++){
            if(i==0){
                if(scacchiera[i][j].is_ruotato==0){
                    punteggio_c+=el_tessere[scacchiera[i][j].indice_tessera].value_t2;
                }else{
                    punteggio_c+=el_tessere[scacchiera[i][j].indice_tessera].value_t1;
                }
            }else{
                if(scacchiera[i][j].is_ruotato==0&&scacchiera[i-1][j].is_ruotato==0){
                    if(el_tessere[scacchiera[i][j].indice_tessera].color_t2==el_tessere[scacchiera[i-1][j].indice_tessera].color_t2){
                        punteggio_c+=el_tessere[scacchiera[i][j].indice_tessera].value_t2;
                    }else{
                        punteggio_c=0;
                        break;
                    }
                }else if (scacchiera[i][j].is_ruotato==0&&scacchiera[i-1][j].is_ruotato==1){
                    if(el_tessere[scacchiera[i][j].indice_tessera].color_t2==el_tessere[scacchiera[i-1][j].indice_tessera].color_t1){
                        punteggio_c+=el_tessere[scacchiera[i][j].indice_tessera].value_t2;
                    }else{
                        punteggio_c=0;
                        break;
                    }
                }else if (scacchiera[i][j].is_ruotato==1&&scacchiera[i-1][j].is_ruotato==0){
                    if(el_tessere[scacchiera[i][j].indice_tessera].color_t1==el_tessere[scacchiera[i-1][j].indice_tessera].color_t2){
                        punteggio_c+=el_tessere[scacchiera[i][j].indice_tessera].value_t1;
                    }else{
                        punteggio_c=0;
                        break;
                    }
                }else if (scacchiera[i][j].is_ruotato==1&&scacchiera[i-1][j].is_ruotato==1){
                    if(el_tessere[scacchiera[i][j].indice_tessera].color_t1==el_tessere[scacchiera[i-1][j].indice_tessera].color_t1){
                        punteggio_c+=el_tessere[scacchiera[i][j].indice_tessera].value_t1;
                    }else{
                        punteggio_c=0;
                        break;
                    }
                }
            }
        }
        punteggio_tot+=punteggio_c;
    }
    
    return punteggio_tot;
}

void update_best(Best* best_sol, Casella** scacchiera, int r, int c, int punteggio){
    int i, j;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            best_sol->scacchiera[i][j]=scacchiera[i][j];
        }
    }
    best_sol->punteggio=punteggio;
    return;
}

int* vettore_indici_tessere_non_usate(Tessera* el_tessere, int num_tessere, int num_tessere_tbi){
    int i;
    int* tbi=(int*)malloc(num_tessere_tbi*sizeof(int));
    int j=0;
    for(i=0;i<num_tessere;i++){
        if(el_tessere[i].usata==0){
            tbi[j]=i;
            j++;
        }
    }
    return tbi;
}

int caselle_libere_e_flagga_usate(Casella_vuota* el_caselle_libere, Tessera* el_tessere, Casella** scacchiera, int r, int c){
    
    int count=0, i, j;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(scacchiera[i][j].indice_tessera!=-1)
                el_tessere[scacchiera[i][j].indice_tessera].usata=1;
            if(scacchiera[i][j].indice_tessera==-1){
                el_caselle_libere[count].r_pos=i;
                el_caselle_libere[count].c_pos=j;
                count++;
            }
        }
    }
    return count;
}

void libera_scacchiera(Casella** scacchiera, int r, int c){
    int i;
    for(i=0;i<r;i++){
        free(scacchiera[i]);
    }
    free(scacchiera);
    return;
}

void stampa_scacchiera(Casella** scacchiera, int r, int c){
    int i,j;
    printf("Scacchiera attuale:\n");
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("%d/%d ",scacchiera[i][j].indice_tessera, scacchiera[i][j].is_ruotato);
        }
        printf("\n");
    }
    return;
}

Casella** carica_scacchiera(FILE* fp, int* r, int* c){
    int i,j;
    fscanf(fp, "%d %d", r, c);
    
    Casella** scacchiera=(Casella**)malloc(*r*sizeof(Casella*));
    for(i=0;i<*r;i++){
        scacchiera[i]=(Casella*)malloc(*c*sizeof(Casella));
    }
    
    for(i=0;i<*r;i++){
        for(j=0;j<*c;j++){
            fscanf(fp,"%d/%d",&(scacchiera[i][j].indice_tessera), &(scacchiera[i][j].is_ruotato));
        }
    }
    return scacchiera;
}

Tessera* carica_tessere(FILE* fp, int* num_tessere){
    int i;
    Tessera* el_tessere=(Tessera*)malloc(*num_tessere*sizeof(Tessera));
    for(i=0;i<*num_tessere;i++){
        fscanf(fp, "\n%c %d %c %d", &(el_tessere[i].color_t1), &(el_tessere[i].value_t1), &(el_tessere[i].color_t2), &(el_tessere[i].value_t2));
        el_tessere[i].usata=0;
    }
    return el_tessere;
}

void stampa_tessere(Tessera* el_tessere, int num_tessere){
    int i;
    printf("%d tessere lette:\n", num_tessere);
    for(i=0;i<num_tessere;i++){
        printf("%c %d %c %d\n", el_tessere[i].color_t1, el_tessere[i].value_t1, el_tessere[i].color_t2, el_tessere[i].value_t2);
    }
}

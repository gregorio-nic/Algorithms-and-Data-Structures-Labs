//
//  main.c
//  Lab11_Es1
//
//  Created by Gregorio Nicora on 21/12/21.
//

#include <stdio.h>
#include <stdlib.h>

//------COSTANTI------
#define MAX_S 100
#define MAX_ELEM 5
#define MAX_DIAG 3

//------STRUTTURE DATI------
typedef struct{
    char name[MAX_S];
    int type; // 0 = transizione, 1 = indietro, 2 = avanti
    int entry; // 0 = di spalle, 1 = di fronte
    int exit; // 0 = di spalle, 1 = di fronte
    int prec; // 0 = può essere eseguito come primo, 1 = deve essere preceduto
    int final; // 0 = può essere seguito da altri elementi, 1 = non può essere seguito da altri elementi
    float val; // punteggio
    int diff; // difficoltà
}element;

typedef struct{
    int lista[MAX_ELEM];
    int num_elem;
    int difficulty;
    float val;
}diagonal;

typedef struct{
    diagonal elenco_diag[MAX_DIAG];
    int difficulty;
    float val;
}program;


//------HEADERS FUNZIONI------
element* read_elements(int*);
void print_elements(element*, int);
void init_elenco_diag_valide(diagonal*);
int find_good_diagonals(diagonal*, int, element*, int);
void find_good_diagonals_r(int, int*, int, diagonal*, int, element*, int, int, float, int*);
void add_to_good_diagonals(int*, int, int, float, diagonal*, int*);
void print_diag_valide(diagonal*, int);
void init_progr(program*);
void find_best_program(diagonal*, int, element*, int, program*, program*);
void find_best_program_r(int, diagonal*, int, element*, int, program*, program*, float);
int check_progr(program*, element*, float*);
void update_best(program*, program*);
void print_best(program*, element*);


//costante per il vettore di diagonali valide
int num_diag_valide=10000;


//------MAIN------
int main(int argc, const char* argv[]){
    //acquisisco elementi in un vettore di element e li stampo a video
    int num_elem;
    element* elenco_elem=read_elements(&num_elem);
    print_elements(elenco_elem, num_elem);
    diagonal* elenco_diag_valide=(diagonal*)malloc(num_diag_valide*sizeof(diagonal));
    init_elenco_diag_valide(elenco_diag_valide);
    
    int num_tests, DD, DP, i, index_diag_valide;
    program curr_progr, best_progr;
    //leggo i test e, per ognuno, trovo prima l'elenco delle diagonali compatibili con DD e poi trovo il miglior programma che mette insieme 3 diagonali
    FILE* fp=fopen("testset.txt", "r");
        fscanf(fp,"%d",&num_tests);
        for(i=0;i<num_tests;i++){
            printf("TEST #%d:\n", i+1);
            fscanf(fp, "%d %d", &DD, &DP);
            
            index_diag_valide=find_good_diagonals(elenco_diag_valide, DD, elenco_elem, num_elem);
            //print_diag_valide(elenco_diag_valide, index_diag_valide);
            
            find_best_program(elenco_diag_valide, index_diag_valide, elenco_elem, DP, &curr_progr, &best_progr);
            
            print_best(&best_progr, elenco_elem);
            
        }
    fclose(fp);
    free(elenco_diag_valide);
    free(elenco_elem);
    return 0;
}


//------SVILUPPO FUNZIONI------
void find_best_program(diagonal* elenco_diag_valide, int index_diag_valide, element* elenco_elem, int DP, program* curr_progr, program* best_progr){
    init_progr(curr_progr);
    init_progr(best_progr);
    find_best_program_r(0, elenco_diag_valide, index_diag_valide, elenco_elem, DP, curr_progr, best_progr, curr_progr->val);
}

void find_best_program_r(int pos, diagonal* elenco_diag_valide, int index_diag_valide, element* elenco_elem, int DP, program* curr_progr, program* best_progr, float val){
    int i, j;
    
    //CONDIZIONE TERMINALE
    if(pos>=MAX_DIAG){
        if(check_progr(curr_progr, elenco_elem, &val)){
            if(val>best_progr->val){
                curr_progr->val=val;
                update_best(curr_progr, best_progr);
            }
        }
        return;
    }
    
    //CICLO DI SCELTE SULLE MIGLIORI DIAGONALI
    for(i=0;i<index_diag_valide;i++){
        if(curr_progr->difficulty+elenco_diag_valide[i].difficulty<DP){
            for(j=0;j<MAX_ELEM;j++)
                curr_progr->elenco_diag[pos].lista[j]=elenco_diag_valide[i].lista[j];
            curr_progr->elenco_diag[pos].val=elenco_diag_valide[i].val;
            curr_progr->elenco_diag[pos].num_elem=elenco_diag_valide[i].num_elem;
            curr_progr->difficulty+=elenco_diag_valide[i].difficulty;
            find_best_program_r(pos+1, elenco_diag_valide, index_diag_valide, elenco_elem, DP, curr_progr, best_progr, val+elenco_diag_valide[i].val);
            curr_progr->difficulty-=elenco_diag_valide[i].difficulty;
        }
    }
    return;
}

int check_progr(program* progr, element* elenco_elem, float* val){
    int i,j;
    int avanti_present=0, indietro_present=0;
    
    for(i=0;i<MAX_DIAG && ((avanti_present==0) || (indietro_present==0));i++){
        for(j=0;j<MAX_ELEM && ((avanti_present==0) || (indietro_present==0));j++){
            //CONTROLLO AVANTI
            if(elenco_elem[progr->elenco_diag[i].lista[j]].type==2)
                avanti_present=1;
            //CONTROLLO INDIETRO
            if(elenco_elem[progr->elenco_diag[i].lista[j]].type==1)
                indietro_present=1;
        }
    }
    
    if((avanti_present==0) || (indietro_present==0))
        return 0;
    
    int almeno_due_el_in_diag=0;
    for(i=0;i<MAX_DIAG;i++){
        if(progr->elenco_diag[i].num_elem>=2){
            almeno_due_el_in_diag=1;
            break;
        }
    }
    
    if(almeno_due_el_in_diag==0)
        return 0;
    
    //CONTROLLO CHE ULTIMO ELEMENTO ABBIA DIFF>=8 E SE SI MOLTIPLICO ULTIMO PUNTEGGIO * 1,5
    if(elenco_elem[progr->elenco_diag[MAX_DIAG-1].lista[progr->elenco_diag[MAX_DIAG-1].num_elem-1]].diff>=8){
        (*val)-=progr->elenco_diag[MAX_DIAG-1].val;
        (*val)+=(progr->elenco_diag[MAX_DIAG-1].val)*1.5;
    }
    return 1;
}

void update_best(program* curr_progr, program* best_progr){
    int i, j;
    best_progr->val=curr_progr->val;
    best_progr->difficulty=curr_progr->difficulty;
    
    for(i=0;i<MAX_DIAG;i++){
        for(j=0;j<MAX_ELEM;j++){
            best_progr->elenco_diag[i].lista[j]=curr_progr->elenco_diag[i].lista[j];
        }
    }
    return;
}

void print_best(program* progr, element* elenco_elem){
    int i, j;
    printf("Miglior programma con valore %.2f e difficoltà %d:\n", progr->val, progr->difficulty);
    for(i=0;i<MAX_DIAG;i++){
        printf("DIAG #%d:\n", i+1);
        for(j=0;j<MAX_ELEM;j++){
            if(progr->elenco_diag[i].lista[j]!=-1)
                printf("%s ", elenco_elem[progr->elenco_diag[i].lista[j]].name);
        }
        printf("\n");
    }
    return;
}

void init_progr(program* progr){
    int i, j;
    progr->val=0;
    progr->difficulty=0;
    
    for(i=0;i<MAX_DIAG;i++){
        for(j=0;j<MAX_ELEM;j++){
            progr->elenco_diag[i].lista[j]=-1;
        }
    }
}

int find_good_diagonals(diagonal* elenco_diag_valide, int max_diff, element* elenco_elem, int num_elem){
    int i,j;
    int* sol;
    int index_diag_valide=0;
    for(i=1;i<=MAX_ELEM;i++){
        sol=(int*)malloc(i*sizeof(int));
        for(j=0;j<i;j++)
            sol[j]=-1;
        find_good_diagonals_r(0, sol, i, elenco_diag_valide, max_diff, elenco_elem, num_elem, 0, 0.00, &index_diag_valide);
        free(sol);
    }
    return index_diag_valide;
}

void find_good_diagonals_r(int pos, int* sol, int dim_sol, diagonal* elenco_diag_valide, int max_diff, element* elenco_elem, int num_elem, int diff, float val, int* index_diag_valide){
    int i;
    //condizione terminale
    if(pos>=dim_sol){
        if(diff<=max_diff){
            add_to_good_diagonals(sol, dim_sol, diff, val, elenco_diag_valide, index_diag_valide);
        }
        return;
    }
    
    for(i=0;i<num_elem;i++){
        if(pos==0){
            if(elenco_elem[i].prec==1)
                continue;
            if(elenco_elem[i].entry==0)
                continue;
            if(elenco_elem[i].final==1){
                sol[pos]=i;
                diff+=elenco_elem[sol[pos]].diff;
                val+=elenco_elem[sol[pos]].val;
                if(diff<=max_diff){
                    add_to_good_diagonals(sol, dim_sol, diff, val, elenco_diag_valide, index_diag_valide);
                }
                return;
            }
            if(diff+elenco_elem[i].diff<=max_diff){
                sol[pos]=i;
                diff+=elenco_elem[sol[pos]].diff;
                val+=elenco_elem[sol[pos]].val;
                find_good_diagonals_r(pos+1, sol, dim_sol, elenco_diag_valide, max_diff, elenco_elem, num_elem, diff, val, index_diag_valide);
                diff-=elenco_elem[sol[pos]].diff;
                val-=elenco_elem[sol[pos]].val;
            }
        }else{
            if(elenco_elem[sol[pos-1]].exit==elenco_elem[i].entry){
                if(diff+elenco_elem[i].diff<=max_diff){
                    sol[pos]=i;
                    diff+=elenco_elem[sol[pos]].diff;
                    val+=elenco_elem[sol[pos]].val;
                    find_good_diagonals_r(pos+1, sol, dim_sol, elenco_diag_valide, max_diff, elenco_elem, num_elem, diff, val, index_diag_valide);
                    diff-=elenco_elem[sol[pos]].diff;
                    val-=elenco_elem[sol[pos]].val;
                }
            }
        }
    }
    return;
}

void add_to_good_diagonals(int* sol, int dim_sol, int diff, float val, diagonal* elenco_diag_valide, int* index_diag_valide){
    //-----------NON CAPISCO PERCHè NON FUNZIONI!!!!!!---------------------------
//    if((*index_diag_valide)==num_diag_valide){
//        num_diag_valide=num_diag_valide*2;
//        elenco_diag_valide=realloc(elenco_diag_valide, num_diag_valide);
//    }
    int i;
    for(i=0;i<dim_sol;i++){
        elenco_diag_valide[*index_diag_valide].lista[i]=sol[i];
    }
    elenco_diag_valide[*index_diag_valide].val=val;
    elenco_diag_valide[*index_diag_valide].num_elem=dim_sol;
    elenco_diag_valide[*index_diag_valide].difficulty=diff;
    (*index_diag_valide)++;
    return;
}

void init_elenco_diag_valide(diagonal* elenco_diag_valide){
    int i,j;
    for(i=0;i<num_diag_valide;i++){
        for(j=0;j<MAX_ELEM;j++){
            elenco_diag_valide[i].lista[j]=-1;
        }
    }
}

void print_diag_valide(diagonal* elenco_diag_valide, int index_diag_valide){
    int i, j;
    for(i=0;i<index_diag_valide;i++){
        printf("Diagonale valida con val = %f e diff = %d:", elenco_diag_valide[i].val, elenco_diag_valide[i].difficulty);
        for(j=0;j<elenco_diag_valide[i].num_elem;j++){
            printf(" %d ", elenco_diag_valide[i].lista[j]);
        }
        printf("\n");
    }
}

element* read_elements(int* num_elem){
    element* elenco_elem;
    FILE* fp=fopen("elementi.txt", "r");
    fscanf(fp,"%d",num_elem);
    elenco_elem=(element*)malloc(*num_elem*sizeof(element));
    int i;
    for(i=0;i<*num_elem;i++){
        fscanf(fp,"%s %d %d %d %d %d %f %d", elenco_elem[i].name, &(elenco_elem[i].type), &(elenco_elem[i].entry), &(elenco_elem[i].exit), &(elenco_elem[i].prec), &(elenco_elem[i].final), &(elenco_elem[i].val), &(elenco_elem[i].diff));
    }
    fclose(fp);
    return elenco_elem;
}

void print_elements(element* elenco_elem, int num_elem){
    int i;
    for(i=0;i<num_elem;i++){
        printf("%s %d %d %d %d %d %.2f %d\n", elenco_elem[i].name, elenco_elem[i].type, elenco_elem[i].entry, elenco_elem[i].exit, elenco_elem[i].prec, elenco_elem[i].final, elenco_elem[i].val, elenco_elem[i].diff);
    }
    return;
}

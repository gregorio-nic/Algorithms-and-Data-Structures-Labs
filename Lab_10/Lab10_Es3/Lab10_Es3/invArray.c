//
//  invArray.c
//  Lab10_Es3
//
//  Created by Gregorio Nicora on 16/12/21.
//

#include <stdio.h>
#include "invArray.h"

/* ADT di prima classe collezione di oggetti di inventario */
typedef struct invArray_s *invArray_t;

typedef struct invArray_s{
    inv_t* vect;
    int num_obj;
} invArray_s;

/* creatore e distruttore */
invArray_t invArray_init(void){
    invArray_t inventario =(invArray_s*)malloc(sizeof(invArray_s));
    inventario->num_obj=0;
    return inventario;
}
void invArray_free(invArray_t invArray){
    free(invArray->vect);
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray){
    int i;
    fscanf(fp, "%d", &(invArray->num_obj));
    invArray->vect=(inv_t*)malloc(invArray->num_obj*sizeof(inv_t));
    for(i=0;i<invArray->num_obj;i++){
        inv_read(fp, &(invArray->vect[i]));
    }
}
void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    fprintf(fp, "%d OBJECTS:\n", invArray->num_obj);
    for(i=0;i<invArray->num_obj;i++){
        inv_print(fp, &(invArray->vect[i]));
    }
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, &(invArray->vect[index]));
}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->vect[index]);
}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i=0;i<invArray->num_obj;i++){
        if(strcmp(invArray->vect[i].nome, name)==0)
            return i;
    }
    return -1;
}

/* Si possono aggiungere altre funzioni se ritenute necessarie */

/* Ritorna il numero di oggetti nell'inventario */
int invArray_getNumObj(invArray_t invArray){
    return invArray->num_obj;
}

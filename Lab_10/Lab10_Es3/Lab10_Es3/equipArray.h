#ifndef EQUIPARRAY_H_DEFINED
#define EQUIPARRAY_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EQUIP_SLOT 8

#include "invArray.h"

/* ADT di prima classe collezione di oggetti di equipaggiamento */
typedef struct equipArray_s *equipArray_t; 

/* creatore e disruttore */
equipArray_t equipArray_init(void);
void equipArray_free(equipArray_t equipArray);

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray);

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray);
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray);
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index);

/* Si possono aggiungere altre funzioni se ritenute necessarie */

/* Aggiunge oggetto all'equipaggiamento */
void equipArray_addObject(equipArray_t equipArray, invArray_t invArray);

/* Rimuove oggetto dall'equipaggiamento */
void equipArray_removeObject(equipArray_t equipArray, invArray_t invArray);

/* Cambia oggetto dell'equipaggiamento */
void equipArray_changeObject(equipArray_t equipArray, invArray_t invArray);

/* ritorna un elemento stat avente come campi la somma delle stat dei singoli oggetti dell'equipaggiamento */
stat_t equipArray_eqStat(equipArray_t equipArray, invArray_t invArray);

#endif

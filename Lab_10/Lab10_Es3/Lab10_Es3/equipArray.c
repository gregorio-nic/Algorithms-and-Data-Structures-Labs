//
//  equipArray.c
//  Lab10_Es3
//
//  Created by Gregorio Nicora on 17/12/21.
//

#include <stdio.h>
#include "equipArray.h"

/* ADT di prima classe collezione di oggetti di equipaggiamento */
typedef struct equipArray_s *equipArray_t;

typedef struct equipArray_s{
    int slots[EQUIP_SLOT];
    int used;
}equipArray_s;

/* creatore e disruttore */
equipArray_t equipArray_init(void){
    int i;
    equipArray_t equipArray=(equipArray_s*)malloc(sizeof(equipArray_s));
    for(i=0;i<EQUIP_SLOT;i++)
        equipArray->slots[i]=-1;
    equipArray->used=0;
    return equipArray;
}
void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->used;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    printf("OGGETTI UTILIZZATI:\n");
    for(i=0;i<EQUIP_SLOT;i++){
        if(equipArray->slots[i]!=-1)
            invArray_printByIndex(fp, invArray, equipArray_getEquipByIndex(equipArray, i));
    }
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int command;
    printf("COSA VUOI FARE? 1 = AGGIUNGI UN OGGETTO AL MIO INVENTARIO, 2 = RIMUOVI UN OGGETTO DAL MIO INVENTARIO 3 = CAMBIA UN OGGETTO DEL MIO INVENTARIO: ");
    scanf("%d", &command);
    
    switch (command) {
        case 1:
            if(equipArray->used==EQUIP_SLOT){
                printf("SPIAZE, EQUIPAGGIAMENTO PIENO, IMPOSSIBILE INSERIRE!\n");
                break;
            }
            equipArray_addObject(equipArray, invArray);
            break;
        case 2:
            if(equipArray->used==0){
                printf("SPIAZE, EQUIPAGGIAMENTO VUOTO, IMPOSSIBILE CANCELLARE!\n");
                break;
            }
            equipArray_removeObject(equipArray, invArray);
            break;
        case 3:
            if(equipArray->used==0){
                printf("SPIAZE, EQUIPAGGIAMENTO VUOTO, IMPOSSIBILE CAMBIARE!\n");
                break;
            }
            equipArray_changeObject(equipArray, invArray);
            break;
    }
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->slots[index];
}

/* Si possono aggiungere altre funzioni se ritenute necessarie */

/* Aggiunge un oggetto all'equipaggiamento*/
void equipArray_addObject(equipArray_t equipArray, invArray_t invArray){
    int index,equipArray_index;
    int i;
    printf("CHE OGGETTO VUOI INSERIRE? DIGITARE UN INDICE TRA 0 - %d: ", invArray_getNumObj(invArray));
    scanf("%d", &index);
    
    for(i=0;i<EQUIP_SLOT;i++){
        if(equipArray->slots[i]==index){
            printf("OGGETTO GIA' PRESENTE IN EQUIPAGGIAMENTO, IMPOSSIBILE INSERIRE!\n");
            return;
        }
    }
    
    printf("IN CHE SLOT VUOI INSERIRLO? DIGITARE UN INDICE TRA 0 - %d: " , EQUIP_SLOT-1);
    scanf("%d", &equipArray_index);
    
    if(equipArray_getEquipByIndex(equipArray, equipArray_index)!=-1){
        printf("SLOT GIA' OCCUPATO, IMPOSSIBILE INSERIRE!\n");
        return;
    }
    
    equipArray->slots[equipArray_index]=index;
    equipArray->used++;
}

void equipArray_removeObject(equipArray_t equipArray, invArray_t invArray){
    int index, equipArray_index=-1;
    int i;
    printf("CHE OGGETTO VUOI RIMUOVERE? DIGITARE UN INDICE TRA 0 - %d: ", invArray_getNumObj(invArray));
    scanf("%d", &index);
    
    for(i=0;i<EQUIP_SLOT;i++){
        if(equipArray->slots[i]==index)
            equipArray_index=i;
    }
    
    if(equipArray_index==-1){
        printf("OGGETTO NON PRESENTE NELL'EQUIPAGGIAMENTO, IMPOSSIBILE CANCELLARLO!\n");
        return;
    }
    
    equipArray->slots[equipArray_index]=-1;
    equipArray->used--;
}

void equipArray_changeObject(equipArray_t equipArray, invArray_t invArray){
    int index, equipArray_index=-1;
    int i;
    
    printf("CHE OGGETTO VUOI CAMBIARE? DIGITARE UN INDICE TRA 0 - %d: ", invArray_getNumObj(invArray));
    scanf("%d", &index);
    
    for(i=0;i<EQUIP_SLOT;i++){
        if(equipArray->slots[i]==index)
            equipArray_index=i;
    }
    
    if(equipArray_index==-1){
        printf("OGGETTO NON PRESENTE NELL'EQUIPAGGIAMENTO, IMPOSSIBILE CAMBIARLO!\n");
        return;
    }
    
    printf("CON QUALE OGGETTO LO VUOI CAMBIARE? DIGITARE UN INDICE TRA 0 - %d: ", invArray_getNumObj(invArray));
    scanf("%d", &index);
    
    equipArray->slots[equipArray_index]=index;
}

stat_t equipArray_eqStat(equipArray_t equipArray, invArray_t invArray){
    int i;
    stat_t stat, count;
    count.hp=0;
    count.mp=0;
    count.atk=0;
    count.def=0;
    count.mag=0;
    count.spr=0;
    for(i=0;i<EQUIP_SLOT;i++){
        if(equipArray->slots[i]!=-1){
            stat = inv_getStat(invArray_getByIndex(invArray, equipArray->slots[i]));
            count.hp+=stat.hp;
            count.mp+=stat.mp;
            count.atk+=stat.atk;
            count.def+=stat.def;
            count.mag+=stat.mag;
            count.spr+=stat.spr;
        }
    }
    return count;
}

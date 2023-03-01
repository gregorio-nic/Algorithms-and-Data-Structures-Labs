//
//  inventario.c
//  Lab9_Es3
//
//  Created by Gregorio Nicora on 22/11/21.
//

#include "inventario.h"

tabInv leggi_inventario(){
    int n_obj;
    FILE* fp=fopen("inventario.txt", "r");
    fscanf(fp,"%d",&n_obj);
    tabInv inventario=crea_inventario(n_obj);
    riempi_inventario(fp, inventario);
    fclose(fp);
    return inventario;
}

void riempi_inventario(FILE* fp, tabInv inventario){
    int i;
    for(i=0;i<inventario->numInv;i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", inventario->vettInv[i].name, inventario->vettInv[i].type, &(inventario->vettInv[i].stat.hp), &(inventario->vettInv[i].stat.mp), &(inventario->vettInv[i].stat.atk), &(inventario->vettInv[i].stat.def), &(inventario->vettInv[i].stat.mag), &(inventario->vettInv[i].stat.spr));
    }
    return;
}

tabInv crea_inventario(int n_obj){
    tabInv inventario=(tabInv_t*)malloc(sizeof(tabInv_t));
    inventario->vettInv=(Obj_t*)malloc(n_obj*sizeof(Obj_t));
    inventario->numInv=n_obj;
    return inventario;
}

void libera_inventario(tabInv inventario){
    free(inventario->vettInv);
    free(inventario);
    return;
}

void stampa_inventario(tabInv inventario){
    int i;
    fprintf(stdout, "Elenco oggetti nell'inventario:\n");
    for(i=0;i<inventario->numInv;i++){
        fprintf(stdout, "Oggetto #%d:\n", i+1);
        fprintf(stdout, "%s %s %d %d %d %d %d %d\n", inventario->vettInv[i].name, inventario->vettInv[i].type, inventario->vettInv[i].stat.hp, inventario->vettInv[i].stat.mp, inventario->vettInv[i].stat.atk, inventario->vettInv[i].stat.def, inventario->vettInv[i].stat.mag, inventario->vettInv[i].stat.spr);
    }
    return;
}


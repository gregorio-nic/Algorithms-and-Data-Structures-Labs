//
//  inventario.h
//  Lab9_Es3
//
//  Created by Gregorio Nicora on 22/11/21.
//

#ifndef inventario_h
#define inventario_h

#include <stdio.h>
#include <stdlib.h>

#define MAXS 50


typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct Obj_t Obj_t, *Obj;

struct Obj_t{
    char name[MAXS];
    char type[MAXS];
    stat_t stat;
};

typedef struct tabInv_t tabInv_t, *tabInv;

struct tabInv_t{
    Obj vettInv;
    int numInv;
};


tabInv leggi_inventario(void);
tabInv crea_inventario(int);
void riempi_inventario(FILE*, tabInv);
void stampa_inventario(tabInv);
void libera_inventario(tabInv);
#endif /* inventario_h */

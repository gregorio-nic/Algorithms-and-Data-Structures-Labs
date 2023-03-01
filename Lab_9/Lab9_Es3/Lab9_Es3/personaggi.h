//
//  personaggi.h
//  Lab9_Es3
//
//  Created by Gregorio Nicora on 22/11/21.
//

#ifndef personaggi_h
#define personaggi_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

#define MAXS 50
#define MAXCODE 7
#define MAXOBJ 8

typedef struct tabEquip_t tabEquip_t, *tabEquip;

struct tabEquip_t{
    int inUso;
    Obj vettEq[MAXOBJ];
    int nextObj;
};

typedef struct{
    char code[MAXCODE];
    char name[MAXS];
    char class[MAXS];
    tabEquip equip;
    stat_t stat;
}Pg_t;

typedef struct nodoPg_t nodoPg_t, *link;

struct nodoPg_t{
    Pg_t personaggio;
    link next;
};

typedef struct tabPg_t tabPg_t, *tabPg;

struct tabPg_t{
    link head;
    link tail;
    int num_pg;
};


void libera_nodo(link);
void stampa_personaggi(tabPg);
void stampa_personaggio(link);
tabPg leggi_personaggi(void);
link leggi_personaggio(FILE*);
void libera_personaggi(tabPg);
link crea_nodo(Pg_t, link);
void inserisci_personaggio_in_coda(tabPg, link);
void aggiungi_personaggio(tabPg);
void elimina_personaggio(tabPg, char*);
void aggiungi_oggetto_a_personaggio(tabPg, tabInv, char*, char*);
void rimuovi_oggetto_da_personaggio(tabPg, tabInv, char*, char*);

#endif /* personaggi_h */

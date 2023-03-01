//
//  pgList.c
//  Lab10_Es3
//
//  Created by Gregorio Nicora on 20/12/21.
//

#include <stdio.h>
#include "pgList.h"



typedef struct node* link;

struct node{
    pg_t player;
    link next;
};

typedef struct pgList_s{
    link lista;
    int num_pg;
}pgList_s;



/* Si possono aggiungere altre funzioni se ritenute necessarie */

/* Libera un nodo passato per reference */
void free_node(link node){
    free(node);
}

link new_node(pg_t player, link next){
    link node=(struct node*)malloc(sizeof(struct node));
    node->player=player;
    node->next=next;
    return node;
}


/* creatore e distruttore */
pgList_t pgList_init(void){
    pgList_t players=(pgList_s*)malloc(sizeof(pgList_s));
    players->lista=NULL;
    players->num_pg=0;
    return players;
}

void pgList_free(pgList_t pgList){
    link x,t;
    x=pgList->lista;
    while(x!=NULL){
        t=x->next;
        free_node(x);
        x=t;
    }
    free(pgList);
}


/* lettura e scrittura su file */
/* La funzione inserisce in coda alla lista */
void pgList_read(FILE *fp, pgList_t pgList){
    pg_t player;
    while(pg_read(fp, &player)==0){
        if(pgList->lista==NULL){
            pgList->lista=new_node(player, NULL);
        }else{
            link x;
            for(x=pgList->lista;x->next!=NULL;x=x->next);
            x->next=new_node(player, NULL);
        }
        pgList->num_pg++;
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    for(x=pgList->lista;x!=NULL;x=x->next){
        pg_print(fp, &(x->player), invArray);
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    if(pgList->lista==NULL){
        pgList->lista=new_node(pg, NULL);
    }else{
        link x;
        for(x=pgList->lista;x->next!=NULL;x=x->next);
        x->next=new_node(pg, NULL);
    }
    pgList->num_pg++;
}

/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    link x,p;
    for(p=NULL,x=pgList->lista;x!=NULL;p=x,x=x->next){
        if(strcmp(x->player.cod, cod)==0){
            if(x==pgList->lista){
                pgList->lista=x->next;
                free_node(x);
            }else{
                p=x->next;
                free_node(x);
            }
            pgList->num_pg--;
            break;
        }
    }
}

/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    for(x=pgList->lista;x!=NULL;x=x->next){
        if(strcmp(x->player.cod, cod)==0){
            return &(x->player);
        }
    }
    return NULL;
}


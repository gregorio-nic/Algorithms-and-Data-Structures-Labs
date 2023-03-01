//
//  personaggi.c
//  Lab9_Es3
//
//  Created by Gregorio Nicora on 22/11/21.
//

#include "personaggi.h"

void rimuovi_oggetto_da_personaggio(tabPg el_personaggi, tabInv inventario, char* code, char* name_obj){
    link x;
    int i;
    if(el_personaggi->head==NULL){
        printf("Elenco vuoto");
        return;
    }
    for(x=el_personaggi->head;x!=NULL;x=x->next){
        if(strcmp(x->personaggio.code, code)==0){
            for(i=0;i<x->personaggio.equip->nextObj;i++){
                if(strcmp(name_obj, x->personaggio.equip->vettEq[i]->name)==0){
                    x->personaggio.equip->vettEq[i]=NULL;
                    x->personaggio.equip->nextObj--;
                    return;
                }
            }
            printf("Oggetto non trovato nell'inventario del personaggio\n");
            return;
        }
    }
    printf("Personaggio non trovato nell'elenco\n");
    return;
}

void aggiungi_oggetto_a_personaggio(tabPg el_personaggi, tabInv inventario, char* code, char* name_obj){
    link x;
    int i;
    if(el_personaggi->head==NULL){
        printf("Elenco vuoto");
        return;
    }
    for(x=el_personaggi->head;x!=NULL;x=x->next){
        if(strcmp(x->personaggio.code, code)==0){
            for(i=0;i<inventario->numInv;i++){
                if(strcmp(name_obj, inventario->vettInv[i].name)==0){
                    if(x->personaggio.equip->nextObj==MAXOBJ){
                        printf("Impossibile aggiungere oggetto poichè inventario pieno");
                        return;
                    }
                    x->personaggio.equip->vettEq[x->personaggio.equip->nextObj]=&(inventario->vettInv[i]);
                    x->personaggio.equip->nextObj++;
                    return;
                }
            }
            printf("Nome oggetto non trovato\n");
            return;
        }
    }
    printf("Codice personaggio non trovato\n");
    return;
}

void stampa_personaggi(tabPg el_personaggi){
    link x;
    if(el_personaggi->head==NULL){
        printf("Elenco vuoto!");
        return;
    }
    printf("Stampo %d personaggi:\n", el_personaggi->num_pg);
    for(x=el_personaggi->head;x!=NULL;x=x->next){
        stampa_personaggio(x);
    }
    return;
}

void stampa_personaggio(link tbp){
    printf("%s %s %s %d %d %d %d %d %d\n", tbp->personaggio.code, tbp->personaggio.name, tbp->personaggio.class, tbp->personaggio.stat.hp, tbp->personaggio.stat.mp, tbp->personaggio.stat.atk, tbp->personaggio.stat.def, tbp->personaggio.stat.mag, tbp->personaggio.stat.spr);
    return;
}

tabPg leggi_personaggi(){
    FILE* fp=fopen("pg.txt", "r");
    tabPg el_personaggi=(tabPg_t*)malloc(sizeof(tabPg_t));
    el_personaggi->num_pg=0;
    
    link temp;
    while((temp=leggi_personaggio(fp))!=NULL){
        inserisci_personaggio_in_coda(el_personaggi, temp);
    }
    return el_personaggi;
}

void aggiungi_personaggio(tabPg el_personaggi){
    printf("Inserire dati personaggio: ");
    link nodo=leggi_personaggio(stdin);
    inserisci_personaggio_in_coda(el_personaggi, nodo);
    return;
}

void elimina_personaggio(tabPg el_personaggi, char* code){
    link x, p;
    if(el_personaggi->head==NULL){
        printf("Elenco personaggi vuoto");
        return;
    }
    
    for(p=NULL,x=el_personaggi->head;x!=NULL;p=x,x=x->next){
        if(strcmp(code,x->personaggio.code)==0){
            if(p==NULL){
                el_personaggi->head=x->next;
            }else if(x==el_personaggi->tail){
                el_personaggi->tail=p;
                p->next=NULL;
            }else{
                p->next=x->next;
            }
            printf("Personaggio cancellato:\n");
            stampa_personaggio(x);
            libera_nodo(x);
            return;
        }
    }
    printf("Codice non trovato\n");
    return;
}

link leggi_personaggio(FILE* fp){
    Pg_t temp;
    if(fscanf(fp,"%s %s %s %d %d %d %d %d %d", temp.code, temp.name, temp.class, &(temp.stat.hp), &(temp.stat.mp), &(temp.stat.atk), &(temp.stat.def), &(temp.stat.mag), &(temp.stat.spr))==EOF)
        return NULL;
    temp.equip=(tabEquip_t*)malloc(sizeof(tabEquip_t));
    temp.equip->nextObj=0;
    link nodo=crea_nodo(temp, NULL);
    return nodo;
}

void libera_personaggi(tabPg el_personaggi){
    link x, t;
    x=el_personaggi->head;
    while(x!=NULL){
        t=x;
        libera_nodo(t);
        x=x->next;
    }
    free(el_personaggi);
}

void libera_nodo(link tbf){
    free(tbf->personaggio.equip);
    free(tbf);
    return;
}

link crea_nodo(Pg_t personaggio, link next){
    link temp=(nodoPg_t*)malloc(sizeof(nodoPg_t));
    temp->personaggio=personaggio;
    temp->next=next;
    return temp;
}

void inserisci_personaggio_in_coda(tabPg el_personaggi, link tbi){
    //lista vuota
    if((el_personaggi->head==NULL) && (el_personaggi->tail==NULL)){
        el_personaggi->head=tbi;
        el_personaggi->tail=tbi;
    }else{
        el_personaggi->tail->next=tbi;
        el_personaggi->tail=tbi;
    }
    el_personaggi->num_pg++;
    return;
}

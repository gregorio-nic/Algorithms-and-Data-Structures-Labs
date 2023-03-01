//
//  main.c
//  Lab7_Es2
//
//  Created by Gregorio Nicora on 03/11/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS 50
#define CODE 6

//STRUTTURE DATI
typedef struct{
    int day;
    int month;
    int year;
} Date;

typedef struct{
    char code[CODE];
    char name[MAXS];
    char surname[MAXS];
    Date birthdate;
    char street[MAXS];
    char city[MAXS];
    int cap;
}Person;

typedef struct nodo_t nodo, *link;

struct nodo_t{
    Person p;
    link next;
};

typedef struct{
    link head;
    int num_elem;
}Lista;

//HEADER FUNZIONI
Lista* crea_lista(void);
void stampa_lista(FILE*, Lista*);
void libera_lista(Lista*);
Person leggi_persona(FILE*);
void stampa_persona(FILE*, Person);
link crea_nodo(Person, link);
void libera_nodo(link);
Date get_birthdate(Person);
int is_older(Date, Date);
int is_younger(Date, Date);
void sort_ins(Lista*, link);
void leggi_file(char*, Lista*);
int is_persona_void(Person);
Person persona_void(void);
void cerca_codice(Lista*, char*);
char* get_code(Person);
void cancella_codice(Lista*, char*);
void cancella_date(Lista*, Date, Date);
link primo_in_range(Lista*, Date, Date);


int main(int argc, const char * argv[]) {
    int comando;
    Lista *el_pers;
    el_pers=crea_lista();
    Person p;
    link t;
    char temp[10];
    char* tbs = (char*)malloc(CODE*sizeof(char));
    Date d1, d2;
    
    while(1){
        printf("Inserire comando 1|2|3|4|5|6|0: ");
        scanf("%d", &comando);
        switch (comando) {
            case 1:
                printf("Digitare dati da inserire nel database: ");
                p=leggi_persona(stdin);
                t=crea_nodo(p, NULL);
                sort_ins(el_pers, t);
                stampa_lista(stdout, el_pers);
                break;
            case 2:
                printf("Inserire nome file dal quale caricare nuove persone: ");
                scanf("%s", temp);
                leggi_file(temp, el_pers);
                stampa_lista(stdout, el_pers);
                break;
            case 3:
                printf("Inserire il codice da cercare: ");
                scanf("%s", tbs);
                cerca_codice(el_pers, tbs);
                break;
            case 4:
                printf("Inserire il codice da cercare ed eliminare: ");
                scanf("%s", tbs);
                cancella_codice(el_pers, tbs);
                break;
            case 5:
                printf("Inserire range di date entro cui cercare: ");
                scanf("%d/%d/%d %d/%d/%d", &(d1.day), &(d1.month), &(d1.year), &(d2.day), &(d2.month), &(d2.year));
                cancella_date(el_pers, d1, d2);
                break;
            case 6:
                printf("Inserire il nome del file su cui stampare la lista: ");
                scanf("%s", temp);
                FILE* fp2 = fopen(temp, "w");
                stampa_lista(fp2, el_pers);
                fclose(fp2);
                break;
            case 0:
                libera_lista(el_pers);
                return 0;
            default:
                printf("Codice comando non valido");
                break;
        }
    }
}

void cancella_date(Lista* l, Date d1, Date d2){
    link temp;
    if(l->head==NULL){
        printf("Impossibile cancellare perchè database vuoto!\n");
        return;
    }
    printf("Persone trovate e cancellate!\n");
    while ((temp=primo_in_range(l, d1, d2))!=NULL) {
        stampa_persona(stdout, temp->p);
        free(temp);
    }
    return;
}

link primo_in_range(Lista* l, Date d1, Date d2){
    link p, x;
    for(p=NULL,x=l->head;x!=NULL;p=x,x=x->next){
        if((is_younger(x->p.birthdate, d1))&&(is_older(x->p.birthdate, d2))){
            if(p==NULL){
                l->head=x->next;
                return x;
            }
            p->next=x->next;
            return x;
        }
    }
    return NULL;
}

void cancella_codice(Lista* l, char* tbd){
    link p, x;
    if(l->head==NULL){
        printf("Impossibile cercare codice pochè il database è vuoto!\n");
        return;
    }
    for(p=NULL,x=l->head;x!=NULL;p=x,x=x->next){
        if(strcmp(tbd, get_code(x->p))==0){
            if(p==NULL){
                l->head=x->next;
                printf("Persona trovata e cancellata in testa!\n");
                stampa_persona(stdout, x->p);
                free(x);
                return;
            }else{
                p->next=x->next;
                printf("Persona trovata e cancellata!\n");
                stampa_persona(stdout, x->p);
                free(x);
                return;
            }
        }
    }
    printf("Persona non presente nel database!\n");
    return;
}

void cerca_codice(Lista* l, char* tbs){
    link t;
    if(l->head==NULL){
        printf("Impossibile cercare codice pochè il database è vuoto!\n");
        return;
    }
    for(t=l->head;t!=NULL;t=t->next){
        if(strcmp(tbs, get_code(t->p))==0){
            printf("Persona trovata!\n");
            stampa_persona(stdout, t->p);
            return;
        }
    }
    printf("Nessun elemento nel database corrisponde al codice cercato!\n");
    return;
}

void leggi_file(char* nome_file, Lista* l){
    FILE* fp;
    fp=fopen(nome_file, "r");
    Person p;
    link t;
    while(!is_persona_void(p=leggi_persona(fp))){
        t=crea_nodo(p, NULL);
        sort_ins(l, t);
    }
    fclose(fp);
    return;
}

Person persona_void(void){
    Person temp;
    temp.code[0]='Z';
    return temp;
}

int is_persona_void(Person p){
    if(p.code[0]=='Z')
        return 1;
    return 0;
}

Person leggi_persona(FILE* fp){
    Person temp;
    if(fscanf(fp, "%s %s %s %d/%d/%d %s %s %d", temp.code, temp.name, temp.surname, &(temp.birthdate.day), &(temp.birthdate.month), &(temp.birthdate.year), temp.street, temp.city, &(temp.cap))==EOF)
        return persona_void();
    return temp;
}

void stampa_persona(FILE* fp, Person p){
    fprintf(fp, "%s %s %s %02d/%02d/%d %s %s %05d\n", p.code, p.name, p.surname, p.birthdate.day, p.birthdate.month, p.birthdate.year, p.street, p.city, p.cap);
    return;
}

link crea_nodo(Person p, link l){
    link node=(link)malloc(sizeof(nodo));
    node->p=p;
    node->next=l;
    return node;
}

void libera_nodo(link l){
    free(l);
    return;
}

Date get_birthdate(Person p){
    return p.birthdate;
}

char* get_code(Person p){
    return p.code;
}

int is_older(Date d1, Date d2){
    if(d1.year<d2.year)
        return 1;
    if(d1.year==d2.year)
        if(d1.month<d2.month)
            return 1;
    if(d1.year==d2.year)
        if(d1.month==d2.month)
            if(d1.day<d2.day)
                return 1;
    return 0;
    
}

int is_younger(Date d1, Date d2){
    if(d1.year>d2.year)
        return 1;
    if(d1.year==d2.year)
        if(d1.month>d2.month)
            return 1;
    if(d1.year==d2.year)
        if(d1.month==d2.month)
            if(d1.day>d2.day)
                return 1;
    return 0;
}

void sort_ins(Lista* l, link tbi){
    link p,x;
    //CASO IN CUI LA LISTA SIA VUOTA
    if(l->head==NULL){
        l->head=tbi;
        tbi->next=NULL;
        l->num_elem++;
        return;
    }else{
        //CICLO PER DETERMINARE I DUE NODI TRA CUI DEVO INSERIRE TBI
        for(p=NULL, x=l->head; x!=NULL && (is_older(get_birthdate(tbi->p), get_birthdate(x->p))); p=x, x=x->next);
        //CASO IN CUI DEBBA INSERIRE IN TESTA NON AL PRIMO COLPO
        if(p==NULL){
            tbi->next=x;
            l->head=tbi;
            l->num_elem++;
            return;
        }
        //EFFETTIVO INSERIMENTO DI TBI
        tbi->next=x;
        p->next=tbi;
        l->num_elem++;
        return;
    }
}

Lista* crea_lista(void){
    Lista* temp;
    temp=(Lista*)malloc(sizeof(Lista));
    temp->head=NULL;
    temp->num_elem=0;
    return temp;
}

void stampa_lista(FILE* fp, Lista* l){
    link t;
    if(l->head==NULL)
        printf("Lista vuota: impossibile stampare!");
    else{
        printf("Lista in stampa\n");
        for(t=l->head;t!=NULL;t=t->next){
            stampa_persona(fp, t->p);
        }
    }
    return;
}

void libera_lista(Lista* l){
    link p,t;
    p=l->head;
    while(p!=NULL){
        t=p;
        p=p->next;
        libera_nodo(t);
    }
    free(l);
    return;
}

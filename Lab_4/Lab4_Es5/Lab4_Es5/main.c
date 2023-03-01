
//
//  main.c
//  Lab4_Es5
//
//  Created by Gregorio Nicora on 27/10/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXR 1000
#define MAXS 30

typedef struct{
    int day, month, year;
} Data;

typedef struct{
    int hour, minute, second;
} Ora;


typedef struct{
    char codice_tratta[MAXS], partenza[MAXS], destinazione[MAXS];
    Data data;
    Ora ora_partenza, ora_arrivo;
    int ritardo;
} Riga;


void strToLower(char[]);


void leggi_riga(FILE*, Riga*);
int date_gt(Riga*, Riga*);
int date_lt(Data, Data);
int date_equals(Data, Data);
void stampa_riga(Riga);
void insertion_order_data(Riga**, int);
void insertion_order_code(Riga**, int);
void insertion_order_start(Riga**, int);
void insertion_order_destination(Riga**, int);
void linear_search(Riga**, int, char*);
void binary_search_wrapper(Riga**, int, char*);
void binary_search(Riga**, int, int, char*);
void initialize_vector(Riga**, int);
int time_lt(Ora, Ora);
int code_gt(char*, char*);

int main(int argc, const char * argv[]) {
    int num_righe, comando, i;
    char stringa[MAXS];
    FILE *fp;
    fp=fopen("log.txt", "r");
    fscanf(fp, "%d", &num_righe);
    
    Riga* v=(Riga*) malloc(num_righe*sizeof(Riga));
    
    for(i=0;i<num_righe;i++){
        leggi_riga(fp, &v[i]);
    }
    fclose(fp);
    
    Riga** elrif2 = (Riga**)malloc(num_righe*sizeof(Riga*));
    Riga** elrif3 = (Riga**)malloc(num_righe*sizeof(Riga*));
    Riga** elrif4 = (Riga**)malloc(num_righe*sizeof(Riga*));
    Riga** elrif5 = (Riga**)malloc(num_righe*sizeof(Riga*));
    Riga** elrif6 = (Riga**)malloc(num_righe*sizeof(Riga*));
    
    for(i=0;i<num_righe;i++){
        elrif2[i]=elrif3[i]=elrif4[i]=elrif5[i]=elrif6[i]=&v[i];
    }
    
    while(1){
        printf("Inserire comando (1|2|3|4|5|6|0 per terminare): ");
        scanf("%d", &comando);
        
        switch (comando) {
            case 1:
                printf("Righe lette:\n");
                for(i=0;i<num_righe;i++){
                    stampa_riga(v[i]);
                }
                break;
            case 2:
                insertion_order_data(elrif2, num_righe);
                for(i=0;i<num_righe;i++){
                    stampa_riga(*(elrif2[i]));
                }
                break;
            case 3:
                insertion_order_code(elrif3, num_righe);
                for(i=0;i<num_righe;i++){
                    stampa_riga(*(elrif3[i]));
                }
                break;
            case 4:
                insertion_order_start(elrif4, num_righe);
                for(i=0;i<num_righe;i++){
                    stampa_riga(*(elrif4[i]));
                }
                break;
            case 5:
                insertion_order_destination(elrif5, num_righe);
                for(i=0;i<num_righe;i++){
                    stampa_riga(*(elrif5[i]));
                }
                break;
            case 6:
                insertion_order_start(elrif6, num_righe);
                
                for(i=0;i<num_righe;i++){
                    stampa_riga(*(elrif6[i]));
                }
                printf("\n\n");
                
                printf("Inserire la stringa da cercare tra le stazioni di partenza: ");
                scanf("%s", stringa);
                
                //codice ricerca lineare
//                linear_search(elrif6,num_righe, stringa);
                //codice ricerca dicotomica
                binary_search_wrapper(elrif6, num_righe, stringa);
                break;
            default:
                free(v);
                free(elrif2);
                free(elrif3);
                free(elrif4);
                free(elrif5);
                free(elrif6);
                return 0;
        }
    }
    return 0;
}

void strToLower(char cmd[]){
    int i;
    for(i=0;cmd[i]!='\0';i++){
        cmd[i] = tolower(cmd[i]);
    }
}

int date_gt(Riga* riga_1, Riga* riga_2){
    if(riga_1->data.year>riga_2->data.year)
        return 1;
    if(riga_1->data.year==riga_2->data.year)
        if(riga_1->data.month>riga_2->data.month)
            return 1;
    if(riga_1->data.year==riga_2->data.year)
        if(riga_1->data.month==riga_2->data.month)
            if(riga_1->data.day>riga_2->data.day)
                return 1;
    if(date_equals(riga_1->data, riga_2->data)){
        if(time_lt(riga_1->ora_partenza,riga_2->ora_partenza))
            return 0;
        else
            return 1;
    }
        
    return 0;
}

int date_lt(Data data_1, Data data_2){
    if(data_1.year<data_2.year)
        return 1;
    if(data_1.year==data_2.year)
        if(data_1.month<data_2.month)
            return 1;
    if(data_1.year==data_2.year)
        if(data_1.month==data_2.month)
            if(data_1.day<data_2.day)
                return 1;
    return 0;
}

int date_equals(Data data_1, Data data_2){
    if(data_1.year==data_2.year){
        if(data_1.month==data_2.month){
            if(data_1.day==data_2.day){
                return 1;
            }
        }
    }
    return 0;
}

int code_gt(char* code_1, char* code_2){
    char* tmp_1, *tmp_2;
    int fin1, fin2;
    tmp_1=code_1+3;
    tmp_2=code_2+3;
    fin1=atoi(tmp_1);
    fin2=atoi(tmp_2);
    
    if(fin1>fin2)
        return 1;
    return 0;
}

void initialize_vector(Riga** elrif, int size){
    int i;
    for(i=0;i<size;i++){
        strcpy(elrif[i]->codice_tratta, "GTT999");
        strcpy(elrif[i]->partenza, "Zzzzzzzzzz");
        strcpy(elrif[i]->destinazione, "Zzzzzzzzzz");
        elrif[i]->data.day=31;
        elrif[i]->data.month=12;
        elrif[i]->data.year=100000;
        elrif[i]->ora_partenza.hour=25;
        elrif[i]->ora_partenza.minute=61;
        elrif[i]->ora_partenza.second=61;
    }
    return;
}

int time_lt(Ora ora_1, Ora ora_2){
    if(ora_1.hour<ora_2.hour)
        return 1;
    if(ora_1.hour==ora_2.hour){
        if(ora_1.minute<ora_2.minute)
            return 1;
    }
    if(ora_1.hour==ora_2.hour){
        if(ora_1.minute==ora_2.minute){
            if(ora_1.second<ora_2.second)
                    return 1;
        }
    }
    return 0;
}

void leggi_riga(FILE* fp, Riga* riga){
    fscanf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", riga->codice_tratta, riga->partenza, riga->destinazione, &(riga->data.year), &(riga->data.month), &(riga->data.day), &(riga->ora_partenza.hour), &(riga->ora_partenza.minute), &(riga->ora_partenza.second), &(riga->ora_arrivo.hour), &(riga->ora_arrivo.minute), &(riga->ora_arrivo.second), &(riga->ritardo));
    return;
}

void stampa_riga(Riga riga){
    printf("%s %s %s %02d/%02d/%02d %02d:%02d:%02d %02d:%02d:%02d %d\n", riga.codice_tratta, riga.partenza, riga.destinazione, riga.data.year, riga.data.month, riga.data.day, riga.ora_partenza.hour, riga.ora_partenza.minute, riga.ora_partenza.second, riga.ora_arrivo.hour, riga.ora_arrivo.minute, riga.ora_arrivo.second, riga.ritardo);
    return;
}

void insertion_order_data(Riga** elrif, int size){
    int i, j, l=0, r=size-1;
    Riga* x;
    
    for(i=l+1;i<=r;i++){
        x=elrif[i];
        j=i-1;
        while((j>=l)&&(date_gt(elrif[j], x))){
            elrif[j+1]=elrif[j];
            j--;
        }
        elrif[j+1]=x;
    }
    return;
}

void insertion_order_code(Riga** elrif, int size){
    int i, j,l=0,r=size-1;
    
    Riga* x;
    
    for(i=l+1;i<=r;i++){
        x=elrif[i];
        j=i-1;
        while((j>=l)&&(code_gt(elrif[j]->codice_tratta, x->codice_tratta))){
            elrif[j+1]=elrif[j];
            j--;
        }
        elrif[j+1]=x;
    }
    return;
}

void insertion_order_start(Riga** elrif, int size){
    int i, j, l=0, r=size-1;
    
    Riga* x;
    
    for(i=l+1;i<=r;i++){
        x=elrif[i];
        j=i-1;
        while((j>=l)&&(strcmp(elrif[j]->partenza, x->partenza)>0)){
            elrif[j+1]=elrif[j];
            j--;
        }
        elrif[j+1]=x;
    }
    return;
}

void insertion_order_destination(Riga** elrif, int size){
    int i, j, l=0, r=size-1;
    
    Riga* x;
    
    for(i=l+1;i<=r;i++){
        x=elrif[i];
        j=i-1;
        while((j>=l)&&(strcmp(elrif[j]->destinazione, x->destinazione)>0)){
            elrif[j+1]=elrif[j];
            j--;
        }
        elrif[j+1]=x;
    }
    return;
}

void linear_search(Riga** elrif,int size, char* tbs){
    int i;
    for(i=0;i<size;i++){
        if(strncmp(elrif[i]->partenza, tbs, strlen(tbs))==0)
            stampa_riga(*(elrif[i]));
    }
    return;
}

void binary_search_wrapper(Riga** elrif, int size, char* tbs){
    int l=0, r=size-1;
    binary_search(elrif, l, r, tbs);
    
    return;
}

void binary_search(Riga** elrif, int l, int r, char* tbs){
    int m;
    if(l>=r){
        if(strncmp(elrif[l]->partenza, tbs, strlen(tbs))==0)
            stampa_riga(*(elrif[l]));
        return;
    }
    m=(l+r)/2;
    
    if(strncmp(elrif[m]->partenza, tbs, strlen(tbs))==0){
        stampa_riga(*(elrif[m]));
    }
    if(strncmp(elrif[m]->partenza, tbs, strlen(tbs))>=0){
        binary_search(elrif, l, m-1, tbs);
    }
    binary_search(elrif, m+1, r, tbs);
    return;
}

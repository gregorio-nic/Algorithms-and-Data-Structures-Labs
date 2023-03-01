//
//  main.c
//  Lab4_Es4
//
//  Created by Gregorio Nicora on 21/10/21.
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
int date_gt(Data, Data);
int date_lt(Data, Data);
int date_equals(Data, Data);
void stampa_riga(Riga);
void insertion_order_data(Riga*, int, Riga);
void insertion_order_code(Riga*, int, Riga);
void insertion_order_start(Riga*, int, Riga);
void insertion_order_destination(Riga*, int, Riga);
void linear_search(Riga*, int, char*);
void binary_search_wrapper(Riga*, int, char*);
void binary_search(Riga*, int, int, char*);
void initialize_vector(Riga*, int);
int time_lt(Ora, Ora);
int code_lt(char*, char*);

int main(int argc, const char * argv[]) {
    int num_righe, comando, i;
    Riga temp;
    FILE *fp;
    
    
    while(1){
        printf("Inserire comando (1|2|3|4|5|6|0 per terminare): ");
        scanf("%d", &comando);
        
        switch (comando) {
            case 1:
                fp=fopen("log.txt", "r");
                fscanf(fp, "%d", &num_righe);
                for(i=0;i<num_righe;i++){
                    leggi_riga(fp, &temp);
                    stampa_riga(temp);
                }
                fclose(fp);
                break;
            case 2:
                fp=fopen("log.txt", "r");
                fscanf(fp, "%d", &num_righe);
                
                Riga *v= (Riga*) malloc(num_righe*sizeof(Riga));
                
                initialize_vector(v, num_righe);
                
                for(i=0;i<num_righe;i++){
                    leggi_riga(fp, &temp);
                    insertion_order_data(v, num_righe, temp);
                }
                
                for(i=0;i<num_righe;i++){
                    stampa_riga(v[i]);
                }
                free(v);
                fclose(fp);
                break;
            case 3:
                fp=fopen("log.txt", "r");
                fscanf(fp, "%d", &num_righe);
                
                v= (Riga*) malloc(num_righe*sizeof(Riga));
                
                initialize_vector(v, num_righe);
                
                for(i=0;i<num_righe;i++){
                    leggi_riga(fp, &temp);
                    insertion_order_code(v, num_righe, temp);
                }
                
                for(i=0;i<num_righe;i++){
                    stampa_riga(v[i]);
                }
                
                free(v);
                fclose(fp);
                break;
            case 4:
                fp=fopen("log.txt", "r");
                fscanf(fp, "%d", &num_righe);
                
                v= (Riga*) malloc(num_righe*sizeof(Riga));
                
                initialize_vector(v, num_righe);
                
                for(i=0;i<num_righe;i++){
                    leggi_riga(fp, &temp);
                    insertion_order_start(v, num_righe, temp);
                }
                
                for(i=0;i<num_righe;i++){
                    stampa_riga(v[i]);
                }
                
                free(v);
                fclose(fp);
                break;
            case 5:
                fp=fopen("log.txt", "r");
                fscanf(fp, "%d", &num_righe);
                
                v= (Riga*) malloc(num_righe*sizeof(Riga));
                
                initialize_vector(v, num_righe);
                
                for(i=0;i<num_righe;i++){
                    leggi_riga(fp, &temp);
                    insertion_order_destination(v, num_righe, temp);
                }
                
                for(i=0;i<num_righe;i++){
                    stampa_riga(v[i]);
                }
                
                free(v);
                fclose(fp);
                break;
            case 6:
                fp=fopen("log.txt", "r");
                fscanf(fp, "%d", &num_righe);
                char stringa[MAXS];
                v= (Riga*) malloc(num_righe*sizeof(Riga));
                
                initialize_vector(v, num_righe);
                
                for(i=0;i<num_righe;i++){
                    leggi_riga(fp, &temp);
                    insertion_order_start(v, num_righe, temp);
                }
                
                for(i=0;i<num_righe;i++){
                    stampa_riga(v[i]);
                }
                printf("\n\n");
                
                printf("Inserire la stringa da cercare tra le stazioni di partenza: ");
                scanf("%s", stringa);
                
                //codice ricerca lineare
//                linear_search(v,num_righe, stringa);
                //codice ricerca dicotomica
                binary_search_wrapper(v, num_righe, stringa);
                free(v);
                fclose(fp);
                break;
            default:
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

int date_gt(Data data_1, Data data_2){
    if(data_1.year>=data_2.year){
        if(data_1.month>=data_2.month){
            if(data_1.day>=data_2.day){
                return 1;
            }
        }
    }
    return 0;
}

int date_lt(Data data_1, Data data_2){
    if(data_1.year<data_2.year)
        return 1;
    if(data_1.month<data_2.month)
        return 1;
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

int code_lt(char* code_1, char* code_2){
    char* tmp_1, *tmp_2;
    int fin1, fin2;
    tmp_1=code_1+3;
    tmp_2=code_2+3;
    fin1=atoi(tmp_1);
    fin2=atoi(tmp_2);
    
    if(fin1<fin2)
        return 1;
    return 0;
}

void initialize_vector(Riga* v, int size){
    int i;
    for(i=0;i<size;i++){
        strcpy(v[i].codice_tratta, "GTT999");
        strcpy(v[i].partenza, "Zzzzzzzzzz");
        strcpy(v[i].destinazione, "Zzzzzzzzzz");
        v[i].data.day=31;
        v[i].data.month=12;
        v[i].data.year=100000;
        v[i].ora_partenza.hour=25;
        v[i].ora_partenza.minute=61;
        v[i].ora_partenza.second=61;
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

void insertion_order_data(Riga* v, int size, Riga tbi){
    int i, j;
    //Riga temp;
    
    for(i=0;i<size;i++){
        if(date_lt(tbi.data, v[i].data)){
            for(j=size-1;j>i;j--){
                v[j]=v[j-1];
            }
            v[i]=tbi;
            return;
        }
        
        if(date_equals(tbi.data, v[i].data)){
            if(time_lt(tbi.ora_partenza, v[i].ora_partenza)){
                for(j=size-1;j>i;j--){
                    v[j]=v[j-1];
                }
                v[i]=tbi;
                return;
            }
        }
    }
    return;
}

void insertion_order_code(Riga* v, int size, Riga tbi){
    int i, j;
    
    for(i=0;i<size;i++){
        if(code_lt(tbi.codice_tratta, v[i].codice_tratta)){
            for(j=size-1;j>i;j--){
                v[j]=v[j-1];
            }
            v[i]=tbi;
            return;
        }
    }
    return;
}

void insertion_order_start(Riga* v, int size, Riga tbi){
    int i, j;
    for(i=0;i<size;i++){
        if(strcmp(tbi.partenza, v[i].partenza)<0){
            for(j=size-1;j>i;j--){
                v[j]=v[j-1];
            }
            v[i]=tbi;
            return;
        }
    }
    return;
}

void insertion_order_destination(Riga* v, int size, Riga tbi){
    int i, j;
    for(i=0;i<size;i++){
        if(strcmp(tbi.destinazione, v[i].destinazione)<0){
            for(j=size-1;j>i;j--){
                v[j]=v[j-1];
            }
            v[i]=tbi;
            return;
        }
    }
    return;
}

void linear_search(Riga* v,int size, char* tbs){
    int i;
    for(i=0;i<size;i++){
        if(strncmp(v[i].partenza, tbs, strlen(tbs))==0)
            stampa_riga(v[i]);
    }
    return;
}

void binary_search_wrapper(Riga* v, int size, char* tbs){
    int l=0, r=size-1;
    binary_search(v, l, r, tbs);
    
    return;
}

void binary_search(Riga* v, int l, int r, char* tbs){
    int m;
    if(l>=r){
        if(strncmp(v[l].partenza, tbs, strlen(tbs))==0)
            stampa_riga(v[l]);
        return;
    }
    m=(l+r)/2;
    
    if(strncmp(v[m].partenza, tbs, strlen(tbs))==0){
        stampa_riga(v[m]);
    }
    if(strcmp(v[m].partenza, tbs)>0){
        binary_search(v, l, m-1, tbs);
        return;
    }
    binary_search(v, m+1, r, tbs);
    return;
}

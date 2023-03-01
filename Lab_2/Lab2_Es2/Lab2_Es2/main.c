//
//  main.c
//  Lab2_Es2
//
//  Created by Gregorio Nicora on 04/10/21.
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

typedef enum{
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
} Comando;

typedef struct{
    char codice_tratta[MAXS], partenza[MAXS], destinazione[MAXS];
    Data data;
    Ora ora_partenza, ora_arrivo;
    int ritardo;
} Riga;

Comando leggi_comando(void);
void strToLower(char[]);
void intervallo_date(FILE*);
void leggi_date(Data*);
void leggi_riga(FILE*, Riga*);
int date_gt(Data, Data);
int date_lt(Data, Data);
void stampa_riga(Riga);
void tutte_partenze(FILE*);
void tutti_arrivi(FILE*);
void in_ritardo(FILE*);
void ritardo_cod_tratta(FILE*);

int main(int argc, const char * argv[]) {
//    Comando c;
//
//    while(1){
//        c=leggi_comando();
//        switch (c) {
//            case r_date:
//            case r_partenza:
//            case r_capolinea:
//            case r_ritardo:
//            case r_ritardo_tot:
//            case r_fine:
//                break;
//            case r_err:
//            default:
//                printf("Comando errato\n");
//                break;
//        }
//    }
    FILE *fp;
    fp=fopen("log.txt", "r");
    //intervallo_date(fp);
    //tutte_partenze(fp);
    //tutti_arrivi(fp);
    //in_ritardo(fp);
    ritardo_cod_tratta(fp);
    fclose(fp);
    return 0;
}

Comando leggi_comando(void){
    char cmd[MAXS], *tabella[r_err]={"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    Comando c;
    scanf("%s", cmd);
    printf("Inserire il comando richiesto tra:\ndate\n partenza\n capolinea\n ritardo\n ritardo_tot\n fine\n");
    strToLower(cmd);
    c=r_date;
    while(c<r_err && strcmp(cmd, tabella[c])!=0)
        c++;
    return c;
}

void strToLower(char cmd[]){
    int i;
    for(i=0;cmd[i]!='\0';i++){
        cmd[i] = tolower(cmd[i]);
    }
}

void leggi_date(Data* data){
    scanf("%d/%d/%d", &(data->day), &(data->month), &(data->year));
    printf("Data letta: %02d %02d %02d\n", data->day, data->month, data->year);
    return;
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
    if(data_1.year<=data_2.year){
        if(data_1.month<=data_2.month){
            if(data_1.day<=data_2.day){
                return 1;
            }
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

void intervallo_date(FILE* fp){
    Data data_1, data_2;
    int righe_file, i;
    Riga temp_riga;
    printf("Inserire data 1: ");
    leggi_date(&data_1);
    printf("Inserire data 2: ");
    leggi_date(&data_2);
    fscanf(fp, "%d", &righe_file);
    for(i=0;i<righe_file;i++){
        leggi_riga(fp, &temp_riga);
        if(date_gt(temp_riga.data, data_1) && date_lt(temp_riga.data, data_2))
            stampa_riga(temp_riga);
    }
    return;
}

void tutte_partenze(FILE* fp){
    int righe_file, i;
    char stringa[MAXS];
    Riga temp_riga;
    printf("Inserire nome partenza: ");
    scanf("%s", stringa);
    fscanf(fp, "%d", &righe_file);
    for(i=0;i<righe_file;i++){
        leggi_riga(fp, &temp_riga);
        if(strcmp(temp_riga.partenza, stringa)==0)
            stampa_riga(temp_riga);
    }
    return;
}

void tutti_arrivi(FILE* fp){
    int righe_file, i;
    char stringa[MAXS];
    Riga temp_riga;
    printf("Inserire nome arrivo: ");
    scanf("%s", stringa);
    fscanf(fp, "%d", &righe_file);
    for(i=0;i<righe_file;i++){
        leggi_riga(fp, &temp_riga);
        if(strcmp(temp_riga.destinazione, stringa)==0)
            stampa_riga(temp_riga);
    }
    return;
}

void in_ritardo(FILE* fp){
    int righe_file, i;
    Data data_1, data_2;
    Riga temp_riga;
    printf("Inserire data 1: ");
    leggi_date(&data_1);
    printf("Inserire data 2: ");
    leggi_date(&data_2);
    fscanf(fp, "%d", &righe_file);
    for(i=0;i<righe_file;i++){
        leggi_riga(fp, &temp_riga);
        if(date_gt(temp_riga.data, data_1) && date_lt(temp_riga.data, data_2))
            if(temp_riga.ritardo>0)
                stampa_riga(temp_riga);
    }
    return;
}

void ritardo_cod_tratta(FILE* fp){
    int righe_file, i, ritardo_compl=0;
    char stringa[MAXS];
    Riga temp_riga;
    printf("Inserire codice tratta: ");
    scanf("%s", stringa);
    fscanf(fp,"%d", &righe_file);
    for(i=0;i<righe_file;i++){
        leggi_riga(fp, &temp_riga);
        if(strcmp(temp_riga.codice_tratta, stringa)==0)
            ritardo_compl+=temp_riga.ritardo;
    }
    printf("Il ritardo complessivo sulla tratta %s è di %d minuti\n", stringa, ritardo_compl);
    return;
}

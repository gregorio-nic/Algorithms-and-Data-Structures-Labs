//
//  main.c
//  Lab1_Es2
//
//  Created by Gregorio Nicora on 28/09/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int leggi_parola(FILE*, char*);
void stampa_riga(FILE*, char*);
void verifica_corr(FILE*, char*, int);

int main(int argc, const char * argv[]) {
    FILE* fp1, *fp2;
    int dim_diz, i;
    fp1=fopen("sorgente.txt", "r");
    fp2=fopen("dizionario.txt", "r");
    fscanf(fp2, "%d", &dim_diz);
    char string[200];
    
    
    i = leggi_parola(fp1, string);
    
    verifica_corr(fp2, string, dim_diz);
    fclose(fp2);
    
    while(leggi_parola(fp1, string)!=-1){
        fp2 = fopen("dizionario.txt", "r");
        fscanf(fp2, "%d", &dim_diz);
        verifica_corr(fp2, string, dim_diz);
        fclose(fp2);
    }
    printf("\n");
    return 0;
}

int leggi_parola(FILE* fp, char* string){
    if(fscanf(fp, "%s ", string)==EOF)
        return -1;
    return 0;
}

void stampa_riga(FILE* fp, char* string){
    fprintf(fp, "%s ", string);
}

void verifica_corr(FILE* fp2, char* string, int dim_diz){
    int i, len, j, offset;
    char trad[6], source[6], *c, final[15]="";
    for(i=0;i<dim_diz;i++){
        fscanf(fp2, "%s %s", trad, source);
        if((c = strstr(string, source))!=NULL){
            
            len = strlen(source);
            offset=c-string;
            
            j=0;
            while(j<offset){
                final[j]=string[j];
                j++;
            }
            strcat(final, trad);
            offset = strlen(final);
            strcat(final, c+len);
            printf("%s ", final);
            break;
        }
    }
    if(c==NULL)
        printf("%s ", string);
    return;
}

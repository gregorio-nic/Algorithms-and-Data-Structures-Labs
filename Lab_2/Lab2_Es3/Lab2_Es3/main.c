//
//  main.c
//  Lab2_Es3
//
//  Created by Gregorio Nicora on 12/10/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSEQ 5
#define MAXS 25

void trova_sequenze(void);
void analizza_testo(char*);
void strtolower(char*);
int main(int argc, const char * argv[]) {
    trova_sequenze();
    return 0;
}

void trova_sequenze(void){
    FILE *seq;
    int num_seq, i;
    char temp_seq[MAXSEQ];
    seq=fopen("sequenze.txt", "r");
    fscanf(seq, "%d", &num_seq);
    for(i=0;i<num_seq;i++){
        fscanf(seq, "%s", temp_seq);
        strtolower(temp_seq);
        printf("\nLa sequenza %s è contenuta in:\n", temp_seq);
        analizza_testo(temp_seq);
    }
    fclose(seq);
    return;
}

void analizza_testo(char* seq){
    FILE* testo;
    int pos, count;
    char stringa[MAXS];
    testo = fopen("testo.txt", "r");
    pos=1;
    count=1;
    while(fscanf(testo, " %s ", stringa )!= EOF){
        strtolower(stringa);
        if((strstr(stringa, seq)!=NULL)&&(count<=10)){
            count++;
            printf("%s (posizione %d) ", stringa, pos);
        }
        pos++;
    }
    fclose(testo);
    return;
}

void strtolower(char* stringa) {
    int i=0;
    while(stringa[i]!='\0'){
        stringa[i]=tolower(stringa[i]);
        i++;
    }
    return;
}

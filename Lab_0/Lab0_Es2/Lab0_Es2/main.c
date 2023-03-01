//
//  main.c
//  Lab0_Es2
//
//  Created by Gregorio Nicora on 07/09/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define V 2

int acquisici_len_substring(void);
int conta(char* , int);
int main(int argc, const char * argv[]) {
    
    // leggo il numero di caratteri che devono avere le sottostringhe
    int len;
    len = acquisici_len_substring();
    
    // apro file e leggo quante righe ci sono
    FILE*fp;
    int num_righe,i;
    fp = fopen("testo.txt", "r");
    fscanf(fp, "%d", &num_righe);
    
    // leggo riga per riga e effettuo operazioni
    char string[N];
    for(i=0; i<num_righe; i++){
        int valid_substrings;
        fscanf(fp, "%s", string);
        printf("Stringa corrente: %s \n", string);
        valid_substrings = conta(string, len);
        printf("Numero di sottostringhe: %d\n", valid_substrings);
    }
    
    // chiudo file
    fclose(fp);
    return 0;
}

int acquisici_len_substring(void){
    int n;
    printf("Inserire la lunghezza in che devono avere le sottostringhe: ");
    scanf("%d", &n);
    return n;
}

int conta(char* string, int len){
    int n = 0;
    if(strlen(string) < len)
        return 0;
    int i;
    printf("Sottostringhe trovate: ");
    for(i=0; i<strlen(string); i++){
        int j;
        char test_string[4];
        for(j=0; (j<4) && ((i+j) < strlen(string)); j++){
            test_string[j]=string[i+j];
        }
        int count = 0;
        if(strlen(string)-i >= 4){
            for(j=0; j<4; j++){
                if(test_string[j] == 'a' || test_string[j] == 'e' || test_string[j] == 'i' || test_string[j] == 'o' || test_string[j] == 'u' || test_string[j] == 'A' || test_string[j] == 'E' || test_string[j] == 'I' || test_string[j] == 'O' || test_string[j] == 'U')
                        count++;
            }
            if(count == V){
                printf("%s ", test_string);
                n++;
            }
        }
    }
    return n;
}

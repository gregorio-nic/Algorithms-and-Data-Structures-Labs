//
//  main.c
//  Lab4_Es3
//
//  Created by Gregorio Nicora on 20/10/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXCHAR 43

char* cercaRegexp(char*, char*);

int main(int argc, const char * argv[]) {
    
    //src = foto | regexp = .oto
    char src[5]="Toto", regexp[9]=".oto";
    
    char* sp = cercaRegexp(src, regexp);
    
    printf("%s\n", sp);
    return 0;
}


char* cercaRegexp(char* src, char* regexp){
    int i=0;
    while(regexp[i]!='\0'){
        
        if(regexp[i]=='.'){
            char temp;
            for(temp='a'; temp<='z'; temp++){
                regexp[i]=temp;
                if(strcmp(src, regexp)==0)
                    return src;
            }
            for(temp='A';temp<='Z';temp++){
                regexp[i]=temp;
                if(strcmp(src, regexp)==0)
                    return src;
            }
        }
        
        if(regexp[i]=='['){
            int j=1;
            char vett[MAXCHAR];
            char regexp2[strlen(src)+1];
            
            if(regexp[i+j]=='^'){
                while(regexp[i+j]!=']'){
                    //qui ci va il codice del terzo caso
                    vett[j-1] = regexp[i+j+1];
                    j++;
                }
                vett[j-2] = '\0';
                
                int k;
                for(k=0; k<strlen(src); k++){
                    regexp2[k]=regexp[k];
                    if(k==i){
                        regexp2[k]='.';
                    }
                    if(k>i)
                        regexp2[k]=regexp[k+j];
                }
                regexp2[k]='\0';
                
                char temp;
                for(i=0;i<strlen(regexp2);i++){
                    if(regexp2[i]=='.'){
                        for(temp='a'; temp<='z'; temp++){
                            k=0;
                            while(vett[k]!='\0'){
                                if(temp == vett[k])
                                    temp++;
                                k++;
                            }
                            regexp2[i]=temp;
                            
                            if(strcmp(src, regexp2)==0)
                                return src;
                        }
                    }
                }

            }else{
                while(regexp[i+j]!=']'){
                    //qui ci va il codice del secondo caso
                    vett[j-1] = regexp[i+j];
                    j++;
                }
                vett[j-1] = '\0';
                
                int k;
                for(k=0; k<strlen(src); k++){
                    regexp2[k]=regexp[k];
                    if(k==i){
                        regexp2[k]='.';
                    }
                    if(k>i)
                        regexp2[k]=regexp[k+j];
                }
                
                regexp2[k]='\0';
                
                for(i=0;i<strlen(regexp2);i++){
                    if(regexp2[i]=='.'){
                        k=0;
                        while(vett[k]!='\0'){
                            regexp2[i]=vett[k];
                            if(strcmp(src, regexp2)==0)
                                return src;
                            k++;
                        }
                    }
                }
                
            }
        }
        

        if(regexp[i]== '\a'){
            char regexp2[strlen(regexp)+1];
            int k=1;
            regexp2[0]='.';
            while(k<strlen(regexp)){
                regexp2[k]=regexp[k];
                k++;
            }
            regexp2[k]='\0';

            char temp;
            for(temp='a';temp<='z';temp++){
                regexp2[i]=temp;
                if(strcmp(src, regexp2)==0)
                    return src;
            }
        }
        
        if(regexp[i]== '\A'){
            char regexp2[strlen(regexp)+1];
            int k=1;
            regexp2[0]='.';
            while(k<strlen(regexp)){
                regexp2[k]=regexp[k];
                k++;
            }
            regexp2[k]='\0';

            char temp;
            for(temp='A';temp<='Z';temp++){
                regexp2[i]=temp;
                if(strcmp(src, regexp2)==0)
                    return src;
            }
        }
           
        i++;
    }
    return NULL;
}

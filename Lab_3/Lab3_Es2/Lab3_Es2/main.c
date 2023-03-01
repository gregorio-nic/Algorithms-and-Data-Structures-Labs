//
//  main.c
//  Lab3_Es2
//
//  Created by Gregorio Nicora on 13/10/21.
//

#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char * argv[]) {
    float af;
    double ad;
    long double ald;
    int n;
    int bigEndian=0;

    n=1;
    char* p = &n;
    
    if(*p==1){
        printf("Little Endian\n");
    }else{
        bigEndian=1;
        printf("Big Endian\n");
    }
    
    n=sizeof(n);
    printf("Int di dimensione %d byte e %d bit \n", n, n*8);
    
    n=sizeof(af);
    printf("Float di dimensione %d byte e %d bit \n", n, n*8);
    
    n=sizeof(ad);
    printf("Double di dimensione %d byte e %d bit \n", n, n*8);
    
    n=sizeof(ald);
    printf("Long double di dimensione %d byte e %d bit \n", n, n*8);
    
    printf("Inserire un numero decimale: ");
    scanf("%f", &af);
    
    printf("Inserire lo stesso numero: ");
    scanf("%lf", &ad);
    
    printf("Inserire lo stesso numero: ");
    scanf("%Lf", &ald);
    
    return 0;
}

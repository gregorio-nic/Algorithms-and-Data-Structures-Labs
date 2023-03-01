//
//  main.c
//  Lab4_Es1
//
//  Created by Gregorio Nicora on 19/10/21.
//

#include <stdio.h>
#include <stdlib.h>

int gcd(int, int);

int main(int argc, const char * argv[]) {
    int a, b, result;
    printf("Inserire i due numeri: ");
    scanf("%d %d", &a, &b);
    
    result=gcd(a, b);
    printf("%d\n", result);
    return 0;
}

int gcd(int a, int b){
    int temp;
    if(b>a){
        temp=a;
        a=b;
        b=temp;
    }
    if(a==b)
        return a;
    
    if(((a%2)==0)&&((b%2)==0))
        return 2*gcd(a/2, b/2);
    if(((a%2)!=0)&&((b%2)!=0))
        return gcd((a-b)/2,b);
    if(((a%2)!=0)&&((b%2)==0))
        return gcd(a,b/2);
    if(((a%2)==0)&&((b%2)!=0))
        return gcd(a/2,b);
    return 0;
}

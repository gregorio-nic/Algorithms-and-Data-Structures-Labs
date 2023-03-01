//
//  main.c
//  Lab4_Es2
//
//  Created by Gregorio Nicora on 19/10/21.
//

#include <stdio.h>
#include <stdlib.h>

#define N 8


int majority(int* a, int n);
int majority_real(int*a, int l, int r, int n);

int main(int argc, const char * argv[]) {
    int a[N] = {0, 1, 0, 2, 3, 4, 0, 5};
    printf("%d", majority(a, N));
    return 0;
}

int majority(int* a, int n){
    int l=0, r=n-1;
    return majority_real(a, l, r, n);
}

int majority_real(int* a, int l, int r, int n){
    int m, i;
    int maj1, maj2;
    if(l>=r){
        return a[l];
    }
    
    m=(l+r)/2;
    
    maj1 = majority_real(a, l, m, n/2);
    maj2 = majority_real(a, m+1, r, n/2);
    
    int count1 = 0, count2 = 0;
    for(i=0;i<n;i++){
        if(a[i]==maj1)
            count1++;
        if(a[i]==maj2)
            count2++;
    }
    
    if(count1>(n/2))
        return maj1;
    if(count2>(n/2))
        return maj2;
    
    return -1;
}

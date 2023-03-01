//
//  Date.h
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#ifndef Date_h
#define Date_h

#include <stdio.h>
#include <stdlib.h>

typedef struct date{
    int d;
    int m;
    int y;
} Date;

Date DATEinit(int, int, int);
Date DATEload(FILE*);
void DATEstore(Date);
int DATEearlier(Date, Date);
int DATElater(Date, Date);
int DATEeq(Date, Date);
#endif /* Date_h */

//
//  Hour.h
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#ifndef Hour_h
#define Hour_h

#include <stdio.h>
#include <stdlib.h>

typedef struct hour{
    int hh;
    int mm;
} Hour;

Hour HOURinit(int, int);
Hour HOURload(FILE*);
void HOURstore(Hour);
int HOURearlier(Hour, Hour);
int HOURlater(Hour, Hour);
int HOUReq(Hour, Hour);
#endif /* Hour_h */

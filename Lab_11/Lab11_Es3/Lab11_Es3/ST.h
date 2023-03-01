//
//  ST.h
//  Lab11_Es3
//
//  Created by Gregorio Nicora on 10/01/22.
//

#ifndef ST_h
#define ST_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct symboltable* ST;

ST STinit(int);
void STfree(ST);
void STdisplay(ST);
int STcount(ST);
int STsearch(ST, char*);
char* STsearchByIndex(ST, int);
int STinsert(ST, char*);
void STdisplayOrdered(ST, char**, int);

#endif /* ST_h */

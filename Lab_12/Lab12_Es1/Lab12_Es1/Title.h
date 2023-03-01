//
//  Title.h
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#ifndef Title_h
#define Title_h

#define MAXC 21

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "BSTquot.h"


typedef struct title* Title;

Title TITLEinit(char*);
void TITLEfree(Title);
void TITLEstore(Title);
char* TITLEgetName(Title);
Quotation* TITLEsearchQuot(Title, Date);
Quotation* TITLEinsertQuot(Title, Quotation);
void TITLEsearchInRange(Title, Date, Date, Quotation*, Quotation*);
Date TITLEsearchMin(Title);
Date TITLEsearchMax(Title);
void TITLEbalanceQuot(Title, int);

#endif /* Title_h */

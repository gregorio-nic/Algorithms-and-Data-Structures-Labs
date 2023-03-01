//
//  Titles.h
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#ifndef Titles_h
#define Titles_h

#include <stdio.h>
#include "Title.h"

typedef struct titleslist* Titles;

Titles TITLESinit(void);
void TITLESstore(Titles);
void TITLESinsert(Titles, Title);
Title TITLESsearch(Titles, char*);
void TITLESload(Titles, char*);
#endif /* Titles_h */

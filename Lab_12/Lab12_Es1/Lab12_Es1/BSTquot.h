//
//  BSTquot.h
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#ifndef BSTquot_h
#define BSTquot_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Quotation.h"


typedef struct binarysearchtree* BST;

BST BSTinit(void);
void BSTfree(BST);
void BSTstore(BST);
Quotation* BSTinsert_leafR(BST, Quotation);
Quotation* BSTsearch(BST, Date);
void BSTsearchInRange(BST, Date, Date, Quotation*, Quotation*, int*, int*);
Date BSTsearchMin(BST);
Date BSTsearchMax(BST);
int BSTsearchMaxPath(BST, Date*);
int BSTsearchMinPath(BST, Date*);
void BSTbalance(BST);

#endif /* BSTquot_h */

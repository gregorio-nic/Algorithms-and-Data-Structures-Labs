//
//  Quotation.h
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#ifndef Quotation_h
#define Quotation_h

#include <stdio.h>
#include <stdlib.h>
#include "Hour.h"
#include "Date.h"

typedef struct transaction{
    Hour hour;
    float value;
    int quantity;
} Transaction;

typedef struct transaction_node* link;

struct transaction_node{
    Transaction t;
    link next;
};

typedef struct quotation{
    float quot_val; //ogni volta che inserisco un trans va ricalc.
    Date date;
    link transaction_list;
    int size;
} Quotation;

Transaction TRANSload(FILE* fin);
Quotation QUOTinit(Date);
Quotation QUOTsetNull(void);
int QUOTcheckNull(Quotation);
void QUOTstore(Quotation);
void QUOTinsertTrans(Quotation*, Transaction);
void QUOTcalcVal(Quotation*);

#endif /* Quotation_h */

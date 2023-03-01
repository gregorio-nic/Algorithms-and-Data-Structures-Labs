//
//  Title.c
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#include "Title.h"

struct title{
    char* name;
    BST quotations;
};

Title TITLEinit(char* name){
    Title t=malloc(sizeof(*t));
    t->name=strdup(name);
    t->quotations=BSTinit();
    return t;
}

void TITLEfree(Title t){
    BSTfree(t->quotations);
    free(t->name);
    free(t);
}

void TITLEstore(Title t){
    printf("%s\n", TITLEgetName(t));
    BSTstore(t->quotations);
}

char* TITLEgetName(Title t){
    return t->name;
}

Quotation* TITLEsearchQuot(Title t, Date d){
    return BSTsearch(t->quotations, d);
}

Quotation* TITLEinsertQuot(Title t, Quotation q){
    return BSTinsert_leafR(t->quotations, q);
}

void TITLEsearchInRange(Title t, Date d1, Date d2, Quotation* max, Quotation* min){
    int min_val=INT_MAX, max_val=0;
    BSTsearchInRange(t->quotations, d1, d2, max, min, &max_val, &min_val);
}

Date TITLEsearchMin(Title t){
    return BSTsearchMin(t->quotations);
}
Date TITLEsearchMax(Title t){
    return BSTsearchMax(t->quotations);
}

void TITLEbalanceQuot(Title t, int soglia){
    //se già cammino/minimo<=Soglia
    Date d_max, d_min;
    int max=BSTsearchMaxPath(t->quotations, &d_max);
    int min=BSTsearchMinPath(t->quotations, &d_min);
    if(DATEeq(d_max, d_min))
        BSTbalance(t->quotations);
    else{
        if(max/min<=soglia){
            printf("Non è necessario bilanciare\n");
            return;
        }
        BSTbalance(t->quotations);
    }
}

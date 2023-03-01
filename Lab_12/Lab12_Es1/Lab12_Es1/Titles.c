//
//  Titles.c
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#include "Titles.h"

typedef struct TITLEnode* TITLElink;

struct TITLEnode{
    Title t;
    TITLElink next;
};

struct titleslist{
    TITLElink list;
};

static TITLElink NEWtitleNode(Title t, TITLElink next){
    TITLElink x=malloc(sizeof(*x));
    x->t=t;
    x->next=next;
    return x;
}

Titles TITLESinit(void){
    Titles t=malloc(sizeof(*t));
    t->list=NULL;
    return t;
}

void TITLESstore(Titles ts){
    TITLElink x;
    for(x=ts->list;x!=NULL;x=x->next){
        TITLEstore(x->t);
    }
}

void TITLESinsert(Titles ts, Title t){
    TITLElink x, p;
    if(ts->list==NULL)
        ts->list=NEWtitleNode(t, NULL);
    else{
        if(strcmp(TITLEgetName(t), TITLEgetName(ts->list->t))<0)
            ts->list=NEWtitleNode(t, ts->list);
        else{
            for(p=ts->list, x=ts->list->next; (x!=NULL) && (strcmp(TITLEgetName(t), TITLEgetName(x->t))>0); p=x, x=x->next);
            p->next=NEWtitleNode(t, x);
        }
    }
}

Title TITLESsearch(Titles ts, char* title_name){
    TITLElink x;
    if(ts->list==NULL)
        return NULL;
    for(x=ts->list;x!=NULL;x=x->next){
        if(strcmp(TITLEgetName(x->t), title_name)==0)
            return x->t;
    }
    return NULL;
}

void TITLESload(Titles ts, char* file_name){
    int count;
    int i, j;
    char title_name[MAXC];
    int num_transactions;
    Date d;
    Title t;
    Quotation* q;
    Transaction trans;
    
    FILE* fin=fopen(file_name, "r");
    fscanf(fin, "%d", &count);
    
    
    for(i=0;i<count;i++){
        fscanf(fin, "%s %d", title_name, &num_transactions);
        if((t=TITLESsearch(ts, title_name))==NULL){
            t=TITLEinit(title_name);
            TITLESinsert(ts, t);
        }
        
        for(j=0;j<num_transactions;j++){
            d=DATEload(fin);
            if((q=TITLEsearchQuot(t, d))==NULL){
                q=malloc(sizeof(*q));
                *q=QUOTinit(d);
                q=TITLEinsertQuot(t, *q);
            }
            trans=TRANSload(fin);
            QUOTinsertTrans(q, trans);
        }
        
    }
    
    fclose(fin);
}

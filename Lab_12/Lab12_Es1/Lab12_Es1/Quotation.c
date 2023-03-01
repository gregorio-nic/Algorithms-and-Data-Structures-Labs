//
//  Quotation.c
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#include "Quotation.h"

Transaction TRANSload(FILE* fin){
    Transaction t;
    t.hour=HOURload(fin);
    fscanf(fin, "%f %d", &t.value, &t.quantity);
    return t;
}

static Transaction TransactionSetNull(void){
    Transaction t;
    t.hour=HOURinit(-1, -1);
    t.value=-1.0;
    t.quantity=-1;
    return t;
}

static int TransactionCheckNull(Transaction t){
    Transaction null=TransactionSetNull();
    if((t.value==null.value)&&(HOUReq(t.hour,null.hour))&&(t.quantity==null.quantity))
        return 1;
    return 0;
}

static void TRANSstore(Transaction t){
    HOURstore(t.hour);
    printf("%f %d\n", t.value, t.quantity);
}

static link NEWtransNode(Transaction t, link next){
    link x=malloc(sizeof(*x));
    x->t=t;
    x->next=next;
    return x;
}

Quotation QUOTinit(Date date){
    Quotation q;
    q.quot_val=0.0;
    q.date=date;
    q.transaction_list=NEWtransNode(TransactionSetNull(), NULL);
    q.size=0;
    return q;
}

Quotation QUOTsetNull(void){
    Quotation q;
    q.quot_val=0.0;
    q.date=DATEinit(-1, -1, -1);
    q.transaction_list=NULL;
    return q;
}

int QUOTcheckNull(Quotation q){
    if((q.quot_val==0.0)&&(DATEeq(DATEinit(-1, -1, -1), q.date))&&(q.transaction_list==NULL))
        return 1;
    return 0;
}

void QUOTstore(Quotation q){
    link x;
    printf("\t");
    DATEstore(q.date);
    printf("\tValore quotazione: %f\n", q.quot_val);
    for(x=q.transaction_list;!TransactionCheckNull(x->t);x=x->next){
        printf("\t\t");
        TRANSstore(x->t);
    }
}

void QUOTinsertTrans(Quotation* q, Transaction t){
    link x=NEWtransNode(t, q->transaction_list);
    q->transaction_list=x;
    q->size++;
    QUOTcalcVal(q);
}

void QUOTcalcVal(Quotation* q){
    link x;
    int quantity=0;
    float quot_val=0.0;
    for(x=q->transaction_list;!TransactionCheckNull(x->t);x=x->next){
        quot_val+=x->t.value*x->t.quantity;
        quantity+=x->t.quantity;
    }
    q->quot_val=(quot_val/quantity);
}

//
//  BSTquot.c
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#include "BSTquot.h"

typedef struct BSTnode* BSTlink;

struct BSTnode{
    Quotation q;
    BSTlink l;
    BSTlink r;
    int N;
};

struct binarysearchtree{
    BSTlink root;
    BSTlink z;
};

static BSTlink NEWbstNode(Quotation q, BSTlink l, BSTlink r, int N){
    BSTlink x=malloc(sizeof(*x));
    x->q=q;
    x->l=l;
    x->r=r;
    x->N=N;
    return x;
}

BST BSTinit(void){
    BST bst=malloc(sizeof(*bst));
    bst->root=(bst->z=NEWbstNode(QUOTinit(DATEinit(-1, -1, -1)), NULL, NULL, 0));
    return bst;
}

static void treeFree(BSTlink h, BSTlink z){
    if(h==z)
        return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

void BSTfree(BST bst){
    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}

static void visitR(BSTlink h, BSTlink z){
    if(h==z)
        return;
    visitR(h->l, z);
    QUOTstore(h->q);
    visitR(h->r, z);
    
}

void BSTstore(BST bst){
    visitR(bst->root, bst->z);
}

static BSTlink insertR(BSTlink h, Quotation q, BSTlink z){
    if(h==z)
        return NEWbstNode(q, z, z, 1);
    h->N++;
    if(DATEearlier(q.date, h->q.date)==1)
        h->l=insertR(h->l, q, z);
    else
        h->r=insertR(h->r, q, z);
    return h;
}

Quotation* BSTinsert_leafR(BST bst, Quotation q){
    bst->root=insertR(bst->root, q, bst->z);
    return BSTsearch(bst, q.date);
}

static Quotation* searchR(BSTlink h, Date date, BSTlink z){
    if(h==z){
        return NULL;
    }
    if(DATEeq(h->q.date, date))
        return &h->q;
    if(DATEearlier(date, h->q.date)==1)
        return searchR(h->l, date, z);
    return searchR(h->r, date, z);
}

Quotation* BSTsearch(BST bst, Date date){
    return searchR(bst->root, date, bst->z);
}

static void searchInRangeR(BSTlink h, Date d1, Date d2, Quotation* max, Quotation* min, int* max_val, int* min_val, BSTlink z){
    if(h==z)
        return;
    if(DATEearlier(h->q.date, d2)&&DATElater(h->q.date, d1)){
        if(h->q.quot_val<*min_val){
            *min_val=h->q.quot_val;
            *min=h->q;
        }
        if(h->q.quot_val>*max_val){
            *max_val=h->q.quot_val;
            *max=h->q;
        }
        searchInRangeR(h->l, d1, d2, max, min, max_val, min_val, z);
        searchInRangeR(h->r, d1, d2, max, min, max_val, min_val, z);
    }else if(DATEearlier(h->q.date, d1))
        searchInRangeR(h->r, d1, d2, max, min, max_val, min_val, z);
    else if(DATElater(h->q.date, d2))
        searchInRangeR(h->l, d1, d2, max, min, max_val, min_val, z);
    else
        return;
        
}

void BSTsearchInRange(BST bst, Date d1, Date d2, Quotation* max, Quotation* min, int* max_val, int* min_val){
    searchInRangeR(bst->root, d1, d2, max, min, max_val, min_val, bst->z);
}

static Date searchMinR(BSTlink h, BSTlink z){
    if(h->l!=z)
        return searchMinR(h->l, z);
    return h->q.date;
}

Date BSTsearchMin(BST bst){
    return searchMinR(bst->root, bst->z);
}

static Date searchMaxR(BSTlink h, BSTlink z){
    if(h->r!=z)
        return searchMaxR(h->r, z);
    return h->q.date;
}

Date BSTsearchMax(BST bst){
    return searchMaxR(bst->root, bst->z);
}

static void searchMaxPathR(BSTlink h, int* max, int curr, Date* d, BSTlink z){
    if((h->l==z)&&(h->r==z)){
        if(curr>=(*max)){
            *max=curr;
            *d=h->q.date;
        }
        return;
    }
    
    if(h->l!=z)
        searchMaxPathR(h->l, max, curr+1, d, z);
    if(h->r!=z)
        searchMaxPathR(h->r, max, curr+1, d, z);
}

int BSTsearchMaxPath(BST bst, Date* d){
    int max=0, curr=0;
    searchMaxPathR(bst->root, &max, curr, d, bst->z);
    return max;
}

static void searchMinPathR(BSTlink h, int* min, int curr, Date* d, BSTlink z){
    if((h->l==z)&&(h->r==z)){
        if(curr<(*min)){
            *min=curr;
            *d=h->q.date;
        }
        return;
    }
    
    if(h->l!=z)
        searchMinPathR(h->l, min, curr+1, d, z);
    if(h->r!=z)
        searchMinPathR(h->r, min, curr+1, d, z);
}

int BSTsearchMinPath(BST bst, Date* d){
    int min=INT_MAX, curr=0;
    searchMinPathR(bst->root, &min, curr, d, bst->z);
    return min;
}

//DA IMPLEMENTARE

static BSTlink rotL(BSTlink h){
    BSTlink t;
    t=h->r;
    
    h->r=t->l;
    t->l=h;
    t->N=h->N;
    h->N=1;
    
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    
    return t;
}

static BSTlink rotR(BSTlink h){
    BSTlink t;
    t=h->l;
    
    h->l=t->r;
    t->l=h;
    t->N=h->N;
    h->N=1;
    
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;

    return t;
}

static BSTlink partR(BSTlink h, int r){
    int t=h->l->N;
    
    if(t>r){
        h->l=partR(h->l, r);
        h=rotR(h);
    }
    
    if(t<r){
        h->r=partR(h->r, r-t-1);
        h=rotL(h);
    }
    
    return h;
}

static BSTlink balanceR(BSTlink h, BSTlink z){
    int r;
    if(h==z)
        return z;
    
    //trovo la chiave mediana del sottoalbero che ha h come radice
    r=(((h->N)+1)/2)-1;
    
    h=partR(h, r);
    
    h->l=balanceR(h->l, z);
    h->r=balanceR(h->r, z);
    return h;
}

void BSTbalance(BST bst){
    bst->root=balanceR(bst->root, bst->z);
}

//
//  Hour.c
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#include "Hour.h"
Hour HOURinit(int hh, int mm){
    Hour h;
    h.hh=hh;
    h.mm=mm;
    return h;
}

Hour HOURload(FILE* fin){
    Hour h;
    fscanf(fin, "%d:%d", &h.hh, &h.mm);
    return h;
}

void HOURstore(Hour h1){
    printf("%.2d : %.2d\t", h1.hh, h1.mm);
}

int HOURearlier(Hour h1, Hour h2){
    if(h1.hh<h2.hh)
        return 1;
    if(h1.hh==h2.hh)
        if(h1.mm<h2.mm)
            return 1;
    return 0;
}

int HOURlater(Hour h1, Hour h2){
    if(h1.hh>h2.hh)
        return 1;
    if(h1.hh==h2.hh)
        if(h1.mm>h2.mm)
            return 1;
    return 0;
}

int HOUReq(Hour h1, Hour h2){
    if((h1.hh=h2.hh) && (h1.mm==h2.mm))
        return 1;
    return 0;
}

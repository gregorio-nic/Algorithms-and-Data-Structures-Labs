//
//  Date.c
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#include "Date.h"

Date DATEinit(int y, int m, int d){
    Date date;
    date.y=y;
    date.m=m;
    date.d=d;
    return date;
}

Date DATEload(FILE* fin){
    Date date;
    fscanf(fin, "%d/%d/%d", &date.y, &date.m, &date.d);
    return date;
}

void DATEstore(Date date){
    printf("%d/%.2d/%.2d\n", date.y, date.m, date.d);
}

int DATEearlier(Date date1, Date date2){
    if(date1.y<date2.y)
        return 1;
    if(date1.y==date2.y)
        if(date1.m<date2.m)
            return 1;
    if(date1.y==date2.y)
        if(date1.m==date2.m)
            if(date1.d<=date2.d)
                return 1;
    return 0;
}

int DATElater(Date date1, Date date2){
    if(date1.y>date2.y)
        return 1;
    if(date1.y==date2.y)
        if(date1.m>date2.m)
            return 1;
    if(date1.y==date2.y)
        if(date1.m==date2.m)
            if(date1.d>=date2.d)
                return 1;
    return 0;
}

int DATEeq(Date date1, Date date2){
    if((date1.y==date2.y)&&(date1.m==date2.m)&&(date1.d==date2.d))
        return 1;
    return 0;
}

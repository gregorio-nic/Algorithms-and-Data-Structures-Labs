//
//  inv.c
//  Lab10_Es3
//
//  Created by Gregorio Nicora on 16/12/21.
//

#include <stdio.h>

#include "inv.h"


/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d %d %d %d %d %d", &(statp->hp), &(statp->mp), &(statp->atk), &(statp->def), &(statp->mag), &(statp->spr));
    
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
    fprintf(fp, "HP : %d MP : %d ATK : %d DEF : %d MAG : %d SPR : %d\n", (statp->hp>soglia) ? statp->hp : soglia,
            (statp->mp>soglia) ? statp->mp : soglia,
            (statp->atk>soglia)? statp->atk : soglia,
            (statp->def>soglia)? statp->def : soglia,
            (statp->mag>soglia)? statp->mag : soglia,
            (statp->spr>soglia)? statp->spr : soglia);
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, &invp->stat);
}
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "NAME : %s TYPE : %s", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat, MIN_STAT);
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}

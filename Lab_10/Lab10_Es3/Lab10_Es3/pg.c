//
//  pg.c
//  Lab10_Es3
//
//  Created by Gregorio Nicora on 17/12/21.
//

#include <stdio.h>
#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
    if(fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe)==EOF)
        return -1;
    stat_read(fp, &(pgp->b_stat));
    pgp->eq_stat=pgp->b_stat;
    pgp->equip=equipArray_init();
    return 0;
}

/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp, "COD : %s NOME : %s CLASSE : %s\n", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &(pgp->b_stat), MIN_STAT);
    stat_print(fp, &(pgp->eq_stat), MIN_STAT);
    equipArray_print(fp, pgp->equip, invArray);
}


/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    stat_t stat;
    equipArray_update(pgp->equip, invArray);
    stat = equipArray_eqStat(pgp->equip, invArray);
    pgp->eq_stat.hp+=stat.hp;
    pgp->eq_stat.mp+=stat.mp;
    pgp->eq_stat.atk+=stat.atk;
    pgp->eq_stat.def+=stat.def;
    pgp->eq_stat.mag+=stat.mag;
    pgp->eq_stat.spr+=stat.spr;
}

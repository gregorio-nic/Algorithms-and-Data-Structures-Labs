//
//  main.c
//  Lab9_Es3
//
//  Created by Gregorio Nicora on 22/11/21.
//

#include <stdio.h>
#include "inventario.h"
#include "personaggi.h"


int main(int argc, const char * argv[]) {
    tabPg el_personaggi;
    tabInv inventario;
    inventario=leggi_inventario();
    stampa_inventario(inventario);
    printf("\n");
    el_personaggi=leggi_personaggi();
    stampa_personaggi(el_personaggi);
    
    aggiungi_personaggio(el_personaggi);
    stampa_personaggi(el_personaggi);
    
    char code[MAXCODE], nome_obj[MAXS];
    
    printf("Inserirew codice personaggio da eliminare: ");
    scanf("%s",code);
    elimina_personaggio(el_personaggi, code);
    stampa_personaggi(el_personaggi);
    
    printf("Inserire il codice del personaggio a cui aggiungere l'oggetto x: ");
    scanf("%s %s", code, nome_obj);
    aggiungi_oggetto_a_personaggio(el_personaggi, inventario, code, nome_obj);
    stampa_personaggi(el_personaggi);
    
    rimuovi_oggetto_da_personaggio(el_personaggi, inventario, code, nome_obj);
    libera_personaggi(el_personaggi);
    libera_inventario(inventario);
    return 0;
}

//
//  main.c
//  Lab12_Es1
//
//  Created by Gregorio Nicora on 12/01/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Quotation.h"
#include "Title.h"
#include "Titles.h"

int main(int argc, const char * argv[]) {
    Titles t=TITLESinit();
    char title_name[MAXC];
    TITLESload(t, "F1.txt");
    TITLESload(t, "F2.txt");
    TITLESload(t, "F3.txt");
    
    //visualizzazione dati dopo caricamento da file
    TITLESstore(t);

    //ricerca titolo inserito da tastiera e stampa con tutti i suoi attributi
    printf("Vuoi cercare un titolo? Inserisci nome: ");
    scanf("%s", title_name);
    TITLEstore(TITLESsearch(t, title_name));

    //ricerca e stampa quotazione in una certa data
    printf("Vuoi cercare una quotazione di un titolo? Inserisci nome titolo e data quotazione: ");
    scanf("%s", title_name);
    Date d1=DATEload(stdin);
    Quotation* q=TITLEsearchQuot(TITLESsearch(t, title_name), d1);
    QUOTstore(*q);

    //ricerca e stampa delle quotazioni massima e minima in un range di date
    printf("Vuoi cercare le quotazioni massima e minima in un range di date di un titolo? Inserisci nome titolo e range date quotazione: ");
    scanf("%s", title_name);
    d1=DATEload(stdin);
    Date d2=DATEload(stdin);
    Quotation max, min;
    TITLEsearchInRange(TITLESsearch(t, title_name), d1, d2, &max, &min);
    printf("Quotazione massima e minima del titolo %s nel range ", title_name);
    DATEstore(d1);
    DATEstore(d2);
    QUOTstore(max);
    QUOTstore(min);

    //ricerca e stampa delle quotazioni massima e minima lungo tutto il periodo registrato
    printf("Vuoi cercare le quotazioni massima e minima di un titolo? Inserisci titolo: ");
    scanf("%s", title_name);
    d1=TITLEsearchMin(TITLESsearch(t, title_name));
    d2=TITLEsearchMax(TITLESsearch(t, title_name));
    TITLEsearchInRange(TITLESsearch(t, title_name), d1, d2, &max, &min);
    printf("Quotazione massima e minima del titolo %s ", title_name);
    QUOTstore(max);
    QUOTstore(min);
    
    //bilanciamento albero di un certo titolo se cammino massimo/cammino minimo > Soglia (da tastiera?)
    int soglia;
    printf("Vuoi bilanciare l'albero delle quotazioni di un titolo? Inserisci il nome del titolo e la soglia che non deve superare il rapporto tra cammino massimo e cammino minimo: ");
    scanf("%s %d", title_name, &soglia);
    TITLEbalanceQuot(TITLESsearch(t, title_name), soglia);
    return 0;
}

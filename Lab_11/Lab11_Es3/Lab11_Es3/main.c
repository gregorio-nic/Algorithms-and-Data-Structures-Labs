//
//  main.c
//  Lab11_Es3
//
//  Created by Gregorio Nicora on 10/01/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define MAXC 30

Graph FILEread(char*);

int main(int argc, const char * argv[]) {
    
    Graph G=FILEread(argv[1]);
    GRAPHload(argv[1], G);
    GRAPHstore(G);
    GRAPHstoreVertexOrdered(G);
    GRAPHsubgraphConnected(G);
    GRAPHgenerateLadj(G);
    GRAPHstore2(G);
    
    GRAPHfree(G);
    return 0;
}

Graph FILEread(char* nome_file){
    FILE* fin=fopen(nome_file, "r");
    int count=0;
    char id1[MAXC], net1[MAXC], id2[MAXC], net2[MAXC];
    int data;
    while(fscanf(fin,"%s %s %s %s %d", id1, net1, id2, net2, &data)!=EOF)
        count++;
    
    printf("%d archi letti\n", count);
    Graph G = GRAPHinit(count);
    fclose(fin);
    return G;
}

//
//  Graph.h
//  Lab11_Es3
//
//  Created by Gregorio Nicora on 10/01/22.
//

#ifndef Graph_h
#define Graph_h

#define MAXC 30

#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

typedef struct graph* Graph;

typedef struct edge{
    int v;
    int w;
    int data;
}Edge;

//header funzioni
Graph GRAPHinit(int);
void GRAPHfree(Graph);
void GRAPHstore(Graph);
void GRAPHload(char*, Graph);
void GRAPHinsert(Graph, Edge);
Edge EDGEcreate(int, int, int);
void GRAPHedges(Graph, Edge*);
void GRAPHstoreVertexOrdered(Graph);
void GRAPHsubgraphConnected(Graph);
void GRAPHgenerateLadj(Graph);
void GRAPHstore2(Graph);
#endif /* Graph_h */

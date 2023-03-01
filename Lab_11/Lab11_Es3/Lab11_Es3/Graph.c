//
//  Graph.c
//  Lab11_Es3
//
//  Created by Gregorio Nicora on 10/01/22.
//

#include "Graph.h"


typedef struct node* link;

struct node{
    int id;
    int data;
    link next;
};

struct graph{
    int V;
    int E;
    int** madj;
    link* ladj;
    link z;
    ST tab;
};

static link NEWnode(int id, int data, link next){
    link x=malloc(sizeof(*x));
    x->id=id;
    x->data=data;
    x->next=next;
    return x;
}

static int** MATRIX_INT(int V){
    int i, j;
    int** t=malloc(V*sizeof(int*));
    
    for(i=0;i<V;i++)
        t[i]=malloc(V*sizeof(int));
    
    for(i=0;i<V;i++)
        for(j=0;j<V;j++)
            t[i][j]=-1;
    return t;
}

Graph GRAPHinit(int E){
    Graph G=malloc(sizeof(*G));
    G->V=0;
    G->E=E;
    
    G->madj=MATRIX_INT(2*G->E);
    G->tab=STinit(2*G->E);
    return G;
}

void GRAPHfree(Graph G){
    STfree(G->tab);
    int i;
    for(i=0;i<2*G->E;i++)
        free(G->madj[i]);
    free(G->madj);
    free(G);
}

void GRAPHstore(Graph G){
    int i;
    printf("Grafo letto:\n");
    printf("Vertici:\n");
    STdisplay(G->tab);
    Edge* a=malloc(G->E*sizeof(Edge));
    GRAPHedges(G, a);
    printf("Archi:\n");
    for(i=0;i<G->E;i++)
        printf("%d %d %d\n", a[i].v, a[i].w, a[i].data);
}

void GRAPHload(char* nome_file, Graph G){
    char id1[MAXC], net1[MAXC], id2[MAXC], net2[MAXC];
    int data, pos1, pos2;
    FILE* fin=fopen(nome_file, "r");
    while(fscanf(fin, "%s %s %s %s %d", id1, net1, id2, net2, &data)!=EOF){
        if((pos1=STsearch(G->tab, id1))==-1){
            pos1=STinsert(G->tab, id1);
            G->V++;
        }
        if((pos2=STsearch(G->tab, id2))==-1){
            pos2=STinsert(G->tab, id2);
            G->V++;
        }
        GRAPHinsert(G, EDGEcreate(pos1, pos2, data));
    }
    fclose(fin);
}

void GRAPHinsert(Graph G, Edge e){
    int v=e.v, w=e.w, data=e.data;
    G->madj[v][w]=data;
    G->madj[w][v]=data;
}

Edge EDGEcreate(int v, int w, int data){
    Edge e;
    e.v=v;
    e.w=w;
    e.data=data;
    return e;
}

void GRAPHedges(Graph G, Edge* a){
    int i, j;
    int E=0;
    for(i=0;i<G->V;i++){
        for(j=i+1;j<G->V;j++){
            if(G->madj[i][j]!=-1){
                if(E<G->E){
                    a[E]=EDGEcreate(i, j, G->madj[i][j]);
                    E++;
                }
            }
        }
    }
}

void GRAPHstoreVertexOrdered(Graph G){
    int i, j;
    int counta, countb;
    printf("Stampo vertici e loro archi in ordine alfabetico:\n");
    int* vertexIds=malloc(G->V*sizeof(int));
    char** vertexNames=malloc(G->V*sizeof(char*));
    STdisplayOrdered(G->tab, vertexNames, G->V);
    
    for(i=0;i<G->V;i++)
        vertexIds[i]=STsearch(G->tab, vertexNames[i]);
    
    for(i=0;i<G->V;i++){
        printf("%d\n", i);
        printf("%s -> %d:\n", vertexNames[i], vertexIds[i]);
        for(j=0;j<G->V;j++){
            counta=vertexIds[i];
            countb=vertexIds[j];
            
            if(G->madj[vertexIds[i]][vertexIds[j]]!=-1)
                printf("%s %d\n", STsearchByIndex(G->tab, vertexIds[j]), G->madj[vertexIds[i]][vertexIds[j]]);
        }
    }
}

void GRAPHsubgraphConnected(Graph G){
    char name1[MAXC], name2[MAXC], name3[MAXC];
    int id1, id2, id3;
    printf("Inserire nomi vertici: ");
    scanf("%s %s %s", name1, name2, name3);
    id1=STsearch(G->tab, name1);
    id2=STsearch(G->tab, name2);
    id3=STsearch(G->tab, name3);
    
    if((G->madj[id1][id2]!=-1) && (G->madj[id1][id3]!=-1) && (G->madj[id2][id3]!=-1))
        printf("Il sottografo è connesso!\n");
    else
        printf("Il sottografo non è connesso!\n");
}

void GRAPHgenerateLadj(Graph G){
    int i, j;
    G->z=NEWnode(-1, -1, NULL);
    G->ladj=malloc(G->V*sizeof(link));
    for(i=0;i<G->V;i++)
        G->ladj[i]=G->z;
    
    for(i=0;i<G->V;i++){
        for(j=i+1;j<G->V;j++){
            if(G->madj[i][j]!=-1){
                G->ladj[i]=NEWnode(j, G->madj[i][j], G->ladj[i]);
                G->ladj[j]=NEWnode(i, G->madj[i][j], G->ladj[j]);
            }
        }
    }
}

void GRAPHstore2(Graph G){
    int i;
    link x;
    for(i=0;i<G->V;i++){
        printf("VERTICE %d:\n", i);
        for(x=G->ladj[i];x!=G->z;x=x->next){
            printf("%d %d\n", x->id, x->data);
        }
    }
}

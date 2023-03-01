//
//  main.c
//  Lab7_Es1
//
//  Created by Gregorio Nicora on 03/11/21.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int u;
    int v;
} Arco;

Arco* leggi_file(int*, int*);
void stampa_arco(Arco);
int vertex_cover(Arco*, int*, int, int, int, int);
int check(Arco*, int*, int);
void stampa_sol(int*, int);

int main(int argc, const char * argv[]) {
    Arco* el_archi;
    int num_vertici, num_archi, i, count;
    
    el_archi=leggi_file(&num_vertici, &num_archi);
    
    
    for(i=0;i<num_archi;i++){
        stampa_arco(el_archi[i]);
        printf("\n");
    }
    
    int* sol=(int*)malloc(num_vertici*sizeof(int));
    
    
    count=vertex_cover(el_archi, sol, num_vertici, num_archi, 0, 0);
    
    
    printf("Totale vertex cover trovati: %d\n", count);
    
    free(el_archi);
    free(sol);
    return 0;
}

int vertex_cover(Arco* el_archi, int* sol, int num_vertici, int num_archi, int pos, int count){
    
    //condizione di terminazione ocn controllo se effettivamente è un vertexcover
    if(pos>=num_vertici){
        if(check(el_archi, sol, num_archi)){
            //stampa_soluzione
            stampa_sol(sol, num_vertici);
            return count+1;
        }
        return count;
    }
    
    //prendo il vertice pos-esimo e ricorro
    sol[pos]=0;
    count=vertex_cover(el_archi, sol, num_vertici, num_archi, pos+1, count);
    
    //non prendo il vertice pos-esimo e ricorro
    sol[pos]=1;
    count=vertex_cover(el_archi, sol, num_vertici, num_archi, pos+1, count);
    
    return count;
}

int check(Arco* el_archi, int* sol, int num_archi){
    int i;
    for(i=0;i<num_archi;i++){
        if((sol[el_archi[i].u]==0)&&(sol[el_archi[i].v]==0))
            return 0;
    }
    return 1;
}

void stampa_sol(int* sol, int num_vertici){
    int i;
    printf("Soluzione: { ");
    for(i=0;i<num_vertici;i++){
        if(sol[i]==1)
            printf("%d ", i);
    }
    printf("}\n");
    return;
}



Arco* leggi_file(int* num_vertici, int* num_archi){
    Arco* temp;
    FILE* fp;
    int i;
    
    fp=fopen("grafo.txt", "r");
    fscanf(fp, "%d %d", num_vertici, num_archi);
    
    temp=(Arco*)malloc((*num_archi)*sizeof(Arco));
    for(i=0;i<(*num_archi);i++){
        fscanf(fp, "%d %d", &temp[i].u, &temp[i].v);
    }
    
    return temp;
}

void stampa_arco(Arco arco){
    printf("%d <-> %d", arco.u, arco.v);
    return;
}

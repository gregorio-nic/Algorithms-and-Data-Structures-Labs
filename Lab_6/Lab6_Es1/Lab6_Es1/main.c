//
//  main.c
//  Lab6_Es1
//
//  Created by Gregorio Nicora on 29/10/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS 255
#define MAX_SONGS 5
typedef struct{
    int size;
    char* songs[MAX_SONGS];
} Friend;


void init_playlist(char**, int);
void free_playlist(char**, int);
void print_playlist(char**, int);
void print_friend(Friend, int);
void init_friends_songs(Friend*, int);
void free_friends_songs(Friend*, int);
void generate_friends(FILE*, Friend*, int);
int generate_playlists(char**, Friend*, int, int, int);

int main(int argc, const char * argv[]) {
    
    //lettura del numero di amici
    FILE*fp;
    int num_friends, i;
    fp=fopen("brani.txt", "r");
    fscanf(fp,"%d",&num_friends);
    printf("%d amici parteciperanno alla composizione della playlist\n", num_friends);
    
    //allocazione puntatori a strutture dati
    Friend* friends=(Friend*)malloc(num_friends*sizeof(Friend));
    char** playlist=(char**)malloc(num_friends*sizeof(char*));
    
    //inizializzazione vettori di puntatori
    init_playlist(playlist, num_friends);
    int num_playlists=0;
    init_friends_songs(friends, num_friends);
    
    
    //inserzione dei dati nel vettore di amici
    generate_friends(fp, friends, num_friends);
    
    //stampa di controllo
    for(i=0;i<num_friends;i++){
        print_friend(friends[i], i);
    }
    
    //generazione di tutte le playlists possibili con il principio di moltiplicazione
    num_playlists=generate_playlists(playlist, friends, num_friends, 0, num_playlists);
    printf("%d playlists generated\n", num_playlists);
    
    //disallocazione degli elementi dei vettori
    free_playlist(playlist, num_friends);
    free_friends_songs(friends, num_friends);
    
    //disallocazione dei vettori e chiusura dei file
    free(playlist);
    free(friends);
    fclose(fp);
    return 0;
}

int generate_playlists(char** playlist, Friend* friends, int num_friends, int pos, int num_playlists){
    int i;
    if(pos>=num_friends){
        print_playlist(playlist, num_friends);
        printf("\n");
        return num_playlists+1;
    }
    
    for(i=0;i<friends[pos].size;i++){
        playlist[pos]=strcpy(playlist[pos],friends[pos].songs[i]);
        num_playlists=generate_playlists(playlist, friends, num_friends, pos+1, num_playlists);
    }
    return num_playlists;
}

void generate_friends(FILE* fp, Friend* friends, int num_friends){
    int i,j;
    
    for(i=0;i<num_friends;i++){
        fscanf(fp,"%d", &friends[i].size);
        for(j=0;j<friends[i].size;j++){
            fscanf(fp,"%s", friends[i].songs[j]);
        }
    }
    return;
}

void print_friend(Friend friend, int num){
    int i;
    printf("Friend number %d proposed %d songs:\n", num, friend.size);
    for(i=0;i<friend.size;i++){
        printf("%s\n",friend.songs[i]);
    }
}

void init_friends_songs(Friend* friends, int num_friends){
    int i,j;
    for(i=0; i<num_friends;i++){
        for(j=0;j<MAX_SONGS;j++){
            friends[i].songs[j]=(char*)malloc(MAXS*sizeof(char));
        }
    }
    return;
}

void free_friends_songs(Friend* friends, int num_friends){
    int i, j;
    for(i=0; i<num_friends;i++){
        for(j=0;j<MAX_SONGS;j++){
            free(friends[i].songs[j]);
        }
    }
    return;
}

void init_playlist(char** playlist, int size){
    int i;
    for(i=0;i<size;i++){
        playlist[i]=(char*)malloc(MAXS*sizeof(char));
    }
    return;
}

void print_playlist(char** playlist, int size){
    int i;
    for(i=0;i<size;i++){
        if(i!=size-1)
            printf("%s, ", playlist[i]);
        else
            printf("%s", playlist[i]);
    }
    return;
}

void free_playlist(char** playlist, int size){
    int i;
    for(i=0;i<size;i++){
        free(playlist[i]);
    }
    return;
}

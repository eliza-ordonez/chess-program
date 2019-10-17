/* player.c */

#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include <assert.h>

/* allocate a player's info */
PLAYER *CreatePlayer(int color, int difficulty){
  PLAYER *p;
  p = malloc(sizeof(PLAYER)); 
  if (!p){
    perror("Out of memory. Aborting...");
    exit(10);
    }
  p->color = color;
  p->difficulty = difficulty;
  return p;

}

/* delete player info */
void DeletePlayer(PLAYER *p){
    assert(p);
    free(p);
}

/* print a player's info */
void PrintPlayer(PLAYER *p){
    assert(p);
    printf("Player Color (0 = white, 1 = black): %d\n", p->color);
    printf("Chosen Difficulty (1-4): %d\n", p->difficulty);
}



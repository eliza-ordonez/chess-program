/* player.h */

#ifndef PLAYER_H
#define PLAYER_H
typedef struct Player PLAYER;

struct Player
{   int color;
    int difficulty;
};


/* allocate a player's info */
PLAYER *CreatePlayer(int color, int difficulty);

/* delete player info */
void DeletePlayer(PLAYER *p);

/* print a player's info */
void PrintPlayer(PLAYER *p);

#endif /* PLAYER_H */

/* AI.h */

#ifndef AI_H
#define AI_H
#include "gameboard.h"
#include "pieces.h"

typedef struct
{   char color;
    int difficulty;
}AI;

typedef struct{
  int IBoard[8][8];
}IntBoard;

typedef struct{
  IntBoard *BList[999];
  int size;
}BoardList;

/* creates the AI */
AI *CreateAI(char color, int difficulty);

IntBoard *CreateIntBoard(int b[8][8]);

BoardList *CreateBoardList();

/* deletes AI info */
void DeleteAI(AI *a);

void DeleteIntBoard(IntBoard *intboard);

void DeleteBoardList(BoardList *boardlist);

void MakeMove( Game *game, int new[8][8]);

/* Takes an array of pieces and represents it as an array on integeres */
void PiecesToInt(Game *game, int a[8][8]);

/* Sums up the values in an 8x8 array*/
int GetValue(int a[8][8]);

BoardList *GeneratePosBoards(Game *game, char team); 

/*Sets the board of game2 equal to the board of game1*/
Game *CopyBoard(Game *game);

int GetH(Game *game, int depth, char team);

void PrintInt(IntBoard *intboard);

#endif

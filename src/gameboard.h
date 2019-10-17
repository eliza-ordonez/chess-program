#ifndef CHESSMOVES
#define CHESSMOVES
 
/*Checking the moves of each piece*/


#include "pieces.h"
#include "player.h"


typedef struct {
	Piece *Board[8][8];
	Piece *Pieces[32];
	PLAYER *Player;
	int turn;
}Game;


Game *CreateGame();
void DeleteGame(Game *game);
void ResetGame(Game *game);
void PrintBoard(Game *game);

void MovePiece(Game *game, unsigned int x, unsigned int y, unsigned int nx, unsigned int ny);

Piece *GetPiece(Game *game, int x, int y);
void SetPiece(Game *game, int x, int y, int nt);

int CheckPawnMove(Game *game, int x, int y, int nx, int ny);
int CheckRookMove(Game *game, int x, int y, int nx, int ny);
int CheckKnightMove(Game *game, int x, int y, int nx, int ny);
int CheckBishopMove(Game *game, int x, int y, int nx, int ny);
int CheckQueenMove(Game *game, int x, int y, int nx, int ny);
int CheckKingMove(Game *game, int x, int y, int nx, int ny);

int CheckPawnTransform(Game *game, int x, int y);

int Check(Game *game);

void RecordMove(char *in, Game *game);

typedef struct {
    int hour;
    int min;
    int sec;
    int diffW;
    int diffB;
}TIME;

TIME *CheckTime();
int Btimediff(TIME *t);
int Wtimediff(TIME *t);

/*
int GetMoveList( Game *game, ChessBoard *Board);
int RecordMove( Piece *Piece, int ix, int iy, int px, int py, Game *game, char fname[SLEN], ChessBoard *Board);
int CheckCheckmate( Game *game, Piece *OpponentPiece, ChessBoard *Board);

int CheckSquare( Piece *Piece, int x, int y, Game* game, ChessBoard *Board);
*/

#endif

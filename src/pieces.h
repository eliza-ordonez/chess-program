#ifndef PIECES
#define PIECES

typedef struct {
  unsigned int x;
  unsigned int y;
  char color;
  int type;
  int status;
  } Piece;
  
Piece *CreatePiece(int newtype, char color,int status);



void DeletePiece( Piece *piece);




#endif

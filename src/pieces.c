#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pieces.h"

Piece *CreatePiece( int newtype, char color, int status){
  
  Piece *piece;
  piece = (Piece*)malloc(sizeof(Piece)); 
  if (!piece){
    perror("Out of memory. Aborting...");
    exit(10);
    }
  piece->type = newtype;
  piece->color = color;
  piece->status = status;
  piece->x = 0;
  piece->y = 0;
  return piece;
}




void DeletePiece( Piece *piece){
 assert(piece);
 free(piece);
}




    

/* AI.c */

#include <stdio.h>
#include <stdlib.h>
#include "AI.h"
#include "player.h"
#include "gameboard.h"
#include <assert.h>

/* creates the AI */

AI *CreateAI(char color, int difficulty){
  AI *a;
  a = malloc(sizeof(AI)); 
  if (!a){
    perror("Out of memory. Aborting...");
    exit(10);
    }
  a->color = color;
  a->difficulty = difficulty;
  return a;
}

IntBoard *CreateIntBoard(int b[8][8])
{
  IntBoard *intboard;
  int x,y = 0;
  intboard = malloc(sizeof(IntBoard)); 
    if (!intboard){
    perror("Out of memory. Aborting...");
    exit(10);
    }
  for( x = 0; x<8; x++){
	for(y=0;y<8;y++){
        	 intboard->IBoard[x][y] = b[x][y];
     }
  }
  return intboard;
}

BoardList *CreateBoardList()
{
    BoardList *boardlist;
    boardlist = malloc(sizeof(IntBoard)); 
    if (!boardlist){
    perror("Out of memory. Aborting...");
    exit(10);
    }
    return boardlist;
}

/* deletes AI info */
void DeleteAI(AI *a){
  assert(a);
  free(a);
}

void DeleteIntBoard(IntBoard *intboard){
    assert(intboard);
    free(intboard);
}

void DeleteBoardList(BoardList *boardlist){
    assert(boardlist);
    free(boardlist);
}


void PiecesToInt(Game *game, int a[8][8]){
	int x, y;
	for ( x = 0; x<8; x++){
		for(y=0;y<8;y++){
      			if(game->Board[y][x]!= NULL){
        			if(game->Board[y][x] -> color == 'w'){
    					if(game->Board[y][x] ->type ==1)/*pawn*/
    						a[y][x]=1;
    					if(game->Board[y][x] ->type ==2)/*b*/
    						a[y][x]=4;
  		  			if(game->Board[y][x] ->type ==3)/*kn*/
    						a[y][x]=3;
   		 			if(game->Board[y][x] ->type ==4)/*r*/
    						a[y][x]=5;
    					if(game->Board[y][x] ->type ==5)/*q*/
    						a[y][x]=9;
    					if(game->Board[y][x] ->type ==6)/*king*/
    						a[y][x]=100;
     			     }		
				else if(game->Board[y][x] -> color == 'b'){
    					if(game->Board[y][x] ->type ==1)/*pawn*/
    						a[y][x]=-1;
    					if(game->Board[y][x] ->type ==2)/*b*/
    						a[y][x]=-4;
		    			if(game->Board[y][x] ->type ==3)/*kn*/
    						a[y][x]=-3;
    					if(game->Board[y][x] ->type ==4)/*r*/
    						a[y][x]=-5;
		    			if(game->Board[y][x] ->type ==5)/*q*/
    						a[y][x]=-9;
    					if(game->Board[y][x] ->type ==6)/*king*/
    						a[y][x]=-100;
      			      }

      			}
			else
				a[y][x] = 0;

    }
  }
}

int GetValue(int a[8][8]){
	int BoardValue =0;
	int x,y;
	for ( y = 0; y<8; y++){
		for(x=0;x<8;x++){
			BoardValue += a[y][x];
		}	
	}	
	return BoardValue;
}


BoardList *GeneratePosBoards(Game *game, char team)
{
    int a[8][8];
    int x,y  = 0;
    int r,c = 0;
    int result;
    int i = 0;
    IntBoard *intboard;
    BoardList *boardlist;
    boardlist = CreateBoardList();
    Game *DuplicateGame;
    
    for(x = 0; x <8; x++)
    {
        for(y = 0; y < 8; y++)
        {
            if(game->Board[x][y] != NULL)
            {
               
                if(game->Board[x][y]->type == 1 && game->Board[x][y]->color == team)
                {
                    for(r = 0; r <8; r++)
                    {
                        for(c = 0; c < 8; c++)
                        {
                            result = CheckPawnMove(game, game -> Board[x][y]->x, game -> Board[x][y]->y, r, c);
                            if(result)
                            {
                                
                                DuplicateGame = CopyBoard(game);
                                MovePiece(DuplicateGame, x, y, r, c);
                                PiecesToInt(DuplicateGame, a);
                                intboard = CreateIntBoard(a);
                                boardlist -> BList[i] = intboard;
                                i++;
                            }
                            
                        }
    
                    }
                }
                                   
                if(game->Board[x][y]->type == 2 && game->Board[x][y]->color == team)
                {
                    for(r = 0; r <8; r++)
                    {
                        for(c = 0; c < 8; c++)
                        {
                            result = CheckBishopMove(game, game -> Board[x][y]->x, game -> Board[x][y]->y, r, c);
                            if(result)
                            {
                                
                                DuplicateGame = CopyBoard(game);
                                MovePiece(DuplicateGame,x,y, r, c);
                                PiecesToInt(DuplicateGame, a);
                                intboard = CreateIntBoard(a);
                                boardlist -> BList[i] = intboard;
                                i++;
                            }
                            
                        }
    
                    }
                }
                                            
                if(game->Board[x][y]->type == 3 && game->Board[x][y]->color == team)
                {
                    for(r = 0; r <8; r++)
                    {
                        for(c = 0; c < 8; c++)
                        {
                            result = CheckKnightMove(game, game -> Board[x][y]->x, game -> Board[x][y]->y, r, c);
                            if(result)
                            {
                                
                                DuplicateGame = CopyBoard(game);
                                MovePiece(DuplicateGame, x, y, r, c);
                                PiecesToInt(DuplicateGame, a);
                                intboard = CreateIntBoard(a);
                                boardlist -> BList[i] = intboard;
                                i++;
                            }
                            
                        }
    
                    }
                }
                    
                if(game->Board[x][y]->type == 4 && game->Board[x][y]->color == team)
                {
                    for(r = 0; r <8; r++)
                    {
                        for(c = 0; c < 8; c++)
                        {
                            result = CheckRookMove(game, game -> Board[x][y]->x, game -> Board[x][y]->y, r, c);
                            if(result)
                            {
                                
                                DuplicateGame = CopyBoard(game);
                                MovePiece(DuplicateGame,x,y, r, c);
                                PiecesToInt(DuplicateGame, a);
                                intboard = CreateIntBoard(a);
                                boardlist -> BList[i] = intboard;
                                i++;
                            }
                            
                        }
    
                    }
                }
                
                if(game->Board[x][y]->type == 5 && game->Board[x][y]->color == team)
                {
                    for(r = 0; r <8; r++)
                    {
                        for(c = 0; c < 8; c++)
                        {
                            result = CheckQueenMove(game, game -> Board[x][y]->x, game -> Board[x][y]->y, r, c);
                            if(result)
                            {
                                
                                DuplicateGame = CopyBoard(game);
                                MovePiece(DuplicateGame,x,y, r, c);
                                PiecesToInt(DuplicateGame, a);
                                intboard = CreateIntBoard(a);
                                boardlist -> BList[i] = intboard;
                                i++;
                            }
                            
                        }
    
                    }
                }
                
                if(game->Board[x][y]->type == 6 && game->Board[x][y]->color == team)
                {
                    for(r = 0; r <8; r++)
                    {
                        for(c = 0; c < 8; c++)
                        {
                            result = CheckKingMove(game, game -> Board[x][y]->x, game -> Board[x][y]->y, r, c);
                            if(result)
                            {
                
                                DuplicateGame = CopyBoard(game);
                                MovePiece(DuplicateGame,x,y, r, c);
                                PiecesToInt(DuplicateGame, a);
                                intboard = CreateIntBoard(a);
                                boardlist -> BList[i] = intboard;
                                i++;
                            }
                            
                        }
                    }
                }            
            }
        }
    }
    boardlist -> size = i;
    return boardlist;
}

Game *CopyBoard(Game *game)
{  
    int x, y;
    Game *game2;
    game2 = TempGame();
    for(x = 0; x <8; x++)
    {
        for(y = 0; y < 8; y++)
        {
            if(game->Board[x][y] != NULL)
            {
                game2->Board[x][y] = CreatePiece(game->Board[x][y]->type, game->Board[x][y]->color , game->Board[x][y]->status);
            }
            else
                game2->Board[x][y] = NULL;
        }
    }
    return game2;
} 

void PrintInt(IntBoard *intboard){
		int x,y;
		for(y=7; y>-1; y--){
			for(x = 0; x < 8; x++){
				printf("%d", intboard->IBoard[x][y]);
				}
			printf("\n");
		}
}



void MakeMove( Game *game, int new[8][8] ){
    int x,y;
    for ( y = 0; y<8; y++){
      for(x=0;x<8;x++){
        if(game->Board[x][y]!=0){
          game->Board[x][y]= NULL;

        }  
      	/*White Pawn*/
      	if(new[x][y]==1){ 
      		game->Board[x][y] = CreatePiece(1, 'w', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	} 
      	/*Black Pawn*/
      	else if(new[x][y]==-1){
      		game->Board[x][y] = CreatePiece(1, 'b', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*White Knight*/
      	else if(new[x][y]==3){
      		game->Board[x][y] = CreatePiece(3, 'w', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*Black Knight*/
      	else if(new[x][y]==-3){
      		game->Board[x][y] = CreatePiece(3, 'b', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*White Bishop*/
      	else if(new[x][y]==4){
      		game->Board[x][y] = CreatePiece(2, 'w', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*Black Bishop*/
      	else if(new[x][y]==-4){
      		game->Board[x][y] = CreatePiece(2, 'b', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*White Rook*/
      	else if(new[x][y]==5){
      		game->Board[x][y] = CreatePiece(4, 'w', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*Black Rook*/
      	else if(new[x][y]==-5){
      		game->Board[x][y] = CreatePiece(4, 'b', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*White Queen*/
      	else if(new[x][y]==9){
      		game->Board[x][y] = CreatePiece(5, 'w', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*Black Queen*/
      	else if(new[x][y]==-9){
      		game->Board[x][y] = CreatePiece(5, 'b', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*White King*/
      	else if(new[x][y]==100){
      		game->Board[x][y] = CreatePiece(6, 'w', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
      	/*Black King*/
      	else if(new[x][y]==-100){
      		game->Board[x][y] = CreatePiece(6, 'b', 1);
      		game->Board[x][y]->x=x;
      		game->Board[x][y]->y=y;
      	}
    }
  }
}

int GetH(Game *game, int depth, char team)
{
    if(team == 'b')
    {
        int min = 99999;
        int i;
        Game *DuplicateGame;
        BoardList *boardlist;
        boardlist = GeneratePosBoards(game, 'b'); /*generates an array of all possible board states*/
  
        for(i = 0; i < boardlist->size; i++)
        {
            int curr;
            if(depth == 0)
            {
                curr = GetValue(boardlist->BList[i]->IBoard);
            } 
            else
            {   
                DuplicateGame = CopyBoard(game);
                MakeMove(DuplicateGame, boardlist->BList[i]->IBoard);
              curr = GetH(DuplicateGame, depth - 1, 'w');
  			    }
  
  			    if(curr < min) 
            {
  				      min = curr;
            }
      }
  
  		for(i = 0; i < boardlist->size; i++)
      {
  			DeleteIntBoard(boardlist->BList[i]);
  		}
  		return min;
    } 
    else
    {
  		int max = -99999;
		  int i;
      Game *DuplicateGame;
      BoardList *boardlist;
      boardlist = GeneratePosBoards(game, 'w'); /*generates an array of all possible board states*/
  
  		for(i = 0; i < boardlist->size; i++)
      {
          int curr;
  			  if(depth == 0)
          {
 	  			    curr = GetValue(boardlist->BList[i]->IBoard);
  	  		} 
           else 
          {
              DuplicateGame = CopyBoard(game);
              MakeMove(DuplicateGame, boardlist->BList[i]->IBoard);
	    curr = GetH(DuplicateGame, depth - 1, 'b');
    	}
  	  if(curr > max) 
          {
  		max = curr;
  	}
  		}
  
  		for(i = 0; i < boardlist->size; i++)
      {
  			DeleteIntBoard(boardlist->BList[i]);
  		}
  		return max;
	}
} 



void MakeBestMove(Game *game, char team) 
{
	IntBoard *best;
	if(team == 'b') 
  {
    int min = 99999;
    int i;
    Game *DuplicateGame;
    BoardList *boardlist;
    boardlist = GeneratePosBoards(game, 'b'); /*generates an array of all possible board states*/

		for(i = 0; i < boardlist->size; i++)
    {
        DuplicateGame = CopyBoard(game);
        MakeMove(DuplicateGame, boardlist->BList[i]->IBoard);
  		  int curr = GetH(DuplicateGame, 1, 'b');
  			if(curr < min) 
        {
  				best = CreateIntBoard(boardlist->BList[i]->IBoard);
  				min = curr;
  			}
		}

			for(i = 0; i < boardlist->size; i++)
      {
  			DeleteIntBoard(boardlist->BList[i]);
  		}
	}  
  else 
  {
      int max = -99999;
      int i;
      Game *DuplicateGame;
      BoardList *boardlist;
      boardlist = GeneratePosBoards(game, 'w'); /*generates an array of all possible board states*/
  
  		for(i = 0; i < boardlist->size; i++) 
      {
        DuplicateGame = CopyBoard(game);
        MakeMove(DuplicateGame, boardlist->BList[i]->IBoard);
  			int curr = GetH(DuplicateGame, 1, 'w');
  			if(curr > max) 
        {
  				best = CreateIntBoard(boardlist->BList[i]->IBoard);
  				max = curr;
  			}
  		}
  
  		for(i = 0; i < boardlist->size; i++)
      {
  			DeleteIntBoard(boardlist->BList[i]);
  		}
	}

	MakeMove(game, best->IBoard);
}

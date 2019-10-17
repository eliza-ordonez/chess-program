#include "gameboard.h"
#include "pieces.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <math.h>
void PrintBoard(Game *game){
	assert(game);
	int x, y;
	int n = 8;
	printf("    a    b    c    d    e    f    g    h   ");
	for(y = 7; y > -1; y--){
		printf("\n");
		printf(" |----|----|----|----|----|----|----|----|     \n");
		printf("%d", n);
		n--;
		for(x = 0; x < 8; x++){
		
			if(game->Board[x][y] != NULL){ 
				
				printf("| %c", game->Board[x][y]->color);
				if(game->Board[x][y]->type == 1){
					printf("P ");
				}
				if(game->Board[x][y]->type == 2){
					printf("B ");
				}
				if(game->Board[x][y]->type == 3){
					printf("N ");
				}
				if(game->Board[x][y]->type == 4){
					printf("R ");
				}
				if(game->Board[x][y]->type == 5){
					printf("Q ");
				}
				if(game->Board[x][y]->type == 6){
					printf("K ");
				}
			}
			else if(game->Board[x][y] == NULL){
				printf("|    ");
			}
      
		}
    printf("|");
	}
	printf("\n |----|----|----|----|----|----|----|----|     \n");
	printf("    a    b    c    d    e    f    g    h   \n");

}

Game *CreateGame(){
	int x;
	Game *game;
	game = (Game*)malloc(sizeof(Game));
	if (!game){
		perror("Out of memory. Aborting...");
		exit(10);
	}
	for (x = 0; x < 8; x++){
		game->Pieces[x+8] = CreatePiece(1, 'w', 1); /* 1 for alive and 0 for dead */
		game->Pieces[x+16] = CreatePiece(1, 'b', 1);
	}
	/* Rook */	
	game->Pieces[0] = CreatePiece(4, 'w', 1);
	game->Pieces[7] = CreatePiece(4, 'w', 1);
	game->Pieces[24] = CreatePiece(4, 'b', 1);
	game->Pieces[31] = CreatePiece(4, 'b', 1);
	/* Knight */
	game->Pieces[1] = CreatePiece(3, 'w', 1);
	game->Pieces[6] = CreatePiece(3, 'w', 1);
	game->Pieces[25] = CreatePiece(3, 'b', 1);
	game->Pieces[30]= CreatePiece(3, 'b', 1);
	/* Bishop */
	game->Pieces[2] = CreatePiece(2, 'w', 1);
	game->Pieces[5] = CreatePiece(2, 'w', 1);
	game->Pieces[26] = CreatePiece(2, 'b', 1);
	game->Pieces[29] = CreatePiece(2, 'b', 1);
	/*Queen*/
	game->Pieces[3] = CreatePiece(5, 'w', 1);
	game->Pieces[27] = CreatePiece(5, 'b', 1);
	/*King*/
	game->Pieces[4] = CreatePiece(6, 'w', 1);
	game->Pieces[28] = CreatePiece(6, 'b', 1);
		
	ResetGame(game);
	return game;

}

void DeleteGame(Game *game){
	assert(game);
	int x;
	for(x = 0; x < 32; x++){
		DeletePiece(game->Pieces[x]);
	}
	free(game);
}	

void CreateBoard(Game *game){
	assert(game);
	int x;
	for(x = 0; x < 8; x++){
		game->Board[x][0] = game->Pieces[x];
		game->Board[x][1] = game->Pieces[x+8];
		game->Board[x][2] = NULL;
		game->Board[x][3] = NULL;
		game->Board[x][4] = NULL;
		game->Board[x][5] = NULL;
		game->Board[x][6] = game->Pieces[x+16];
		game->Board[x][7] = game->Pieces[x+24];
	}

	for(x = 0; x < 8; x++){
		game->Board[x][0]->x = x;
		game->Board[x][0]->y = 0;
		
		game->Board[x][1]->x = x;
		game->Board[x][1]->y = 1;
		
		game->Board[x][6]->x = x;
		game->Board[x][6]->y = 6;
		
		game->Board[x][7]->x = x;
		game->Board[x][7]->y = 7;


	}
}

void ResetGame(Game *game){
	assert(game);
	int x;	
	for(x = 0; x < 32; x++){
		assert(game->Pieces[x]);
		game->Pieces[x]->status = 1;
		
	}
	CreateBoard(game);


}
Piece *GetPiece(Game* game,int x, int y){
	assert(game);
	return game->Board[x][y];
}

void SetPiece(Game* game, int x, int y, int nt){
    assert(game);
    game->Board[x][y]->type = nt;
}


void MovePiece(Game *game, unsigned int x, unsigned int y, unsigned int nx, unsigned int ny){
	assert(game);
	if(game->Board[x][y] !=NULL){
		game->Board[nx][ny] = game->Board[x][y];
		game->Board[nx][ny]->x = nx;
		game->Board[nx][ny]->y = ny;
		game->Board[x][y] = NULL;
	}
	else if (game->Board[x][y] == NULL){
		printf("try again");
	}
}

int CheckPawnMove(Game *game, int x, int y, int nx, int ny){
	assert(game);
	int r;
	assert(game);
	if(GetPiece(game, x, y)->color == 'w'){
		if(y == 1){
       if( (x - 1 >= -1 && y + 1 <= 8) && (x + 1 <= 8 && y + 1 <= 8)){
       
         if( ((ny - y) <= 2) &&  ( (ny - y) > 0) &&  (nx == x)){
				    if((abs(ny - y) == 2) && (GetPiece(game, nx, ny) == NULL) && (GetPiece(game, nx, ny - 1) == NULL) ){	
                GetPiece(game, x, y)->status = 2;
		   	        r = 1;
					}
            else if((abs(ny - y) == 1) && (GetPiece(game, nx, ny) == NULL)){	
						r = 1;
					  }
				   }
         else if ( ((ny - y) == 1) && (abs(nx - x) == 1) && (GetPiece(game, nx, ny) != NULL) && (GetPiece(game, nx, ny)->color == 'b') ){
           r = 1;
       }
        
       else {
         r = 0;
       }
       }
	  }
		else if(y != 1){
      GetPiece(game, x, y)->status = 1;
      
      if( (x - 1 >= -1 && y + 1 <= 8) && (x + 1 <= 8 && y + 1 <= 8)){
      
         if((ny - y) == 1 && (nx - x) == 0 && (GetPiece(game, x, y + 1) == NULL)){
				r = 1;
         }
      
        else if( (y == 4) && (GetPiece(game,x+1,y) != NULL) && (GetPiece(game, nx, ny) == NULL) &&(ny == y + 1) && (nx == (x+1)) && (GetPiece(game, nx, y)->type == 1) &&(GetPiece(game, nx, y)->status == 2) ){
              r = 1;        
              game->Board[nx][y] = NULL;
        }  
        
        else if( (y == 4) && (GetPiece(game,x-1,y) != NULL) && (GetPiece(game, nx, ny) == NULL) &&(ny == y + 1) && (nx == (x-1)) && (GetPiece(game, nx, y)->type == 1) &&(GetPiece(game, nx, y)->status == 2)){
              r = 1;
              game->Board[nx][y] = NULL;
        }
        
        else if ( ((ny - y) == 1) && (abs(nx - x) == 1) && (GetPiece(game, nx, ny) != NULL) && (GetPiece(game, nx, ny)->color == 'b') ){
           r = 1;
        }   
        else {
           r = 0;
        }
      }
    }
   }   
 
	if(GetPiece(game, x, y)->color == 'b'){
		if(y == 6){
        if( (x - 1 >= -1 && y + 1 <= 8) && (x + 1 <= 8 && y + 1 <= 8)){
       
         if( ((y - ny) <= 2) &&  ( (y - ny) > 0) &&  (nx == x)){
				    if((abs(ny - y) == 2) && (GetPiece(game, nx, ny) == NULL) && (GetPiece(game, nx, ny + 1) == NULL) ){	
                GetPiece(game, x, y)->status = 2;
		   	        r = 1;
					}
            else if((abs(ny - y) == 1) && (GetPiece(game, nx, ny) == NULL)){	
						r = 1;
					  }
				   }
         else if ( ((y - ny) == 1) && (abs(nx - x) == 1) && (GetPiece(game, nx, ny) != NULL) && (GetPiece(game, nx, ny)->color == 'w') ){
           r = 1;
       }
        
       else {
         r = 0;
       }
       }
	  }
		else if(y != 6){
        GetPiece(game, x, y)->status = 1;
       
      if( (x - 1 >= -1 && y + 1 <= 8) && (x + 1 <= 8 && y + 1 <= 8)){
      
         if((y - ny) == 1 && (nx - x) == 0 && (GetPiece(game, x, y - 1) == NULL)){
				  r = 1;
         }
      
        else if( (y == 3) && (GetPiece(game,x+1,y) != NULL) && (GetPiece(game, nx, ny) == NULL) &&(ny == y - 1) && (nx == (x+1)) && (GetPiece(game, nx, y)->type == 1) &&(GetPiece(game, nx, y)->status == 2) ){
              r = 1;        
              game->Board[nx][y] = NULL;
        }  
        
        else if( (y == 3) && (GetPiece(game,x-1,y) != NULL) && (GetPiece(game, nx, ny) == NULL) &&(ny == y - 1) && (nx == (x-1)) && (GetPiece(game, nx, y)->type == 1) &&(GetPiece(game, nx, y)->status == 2)){
              r = 1;
              game->Board[nx][y] = NULL;
        }
        
        else if ( ((y - ny) == 1) && (abs(nx - x) == 1) && (GetPiece(game, nx, ny) != NULL) && (GetPiece(game, nx, ny)->color == 'w') ){
           r = 1;
        }   
        else {
           r = 0;
        }
      }
		}

	}
	return r;
}

int CheckRookMove(Game *game, int x, int y, int nx, int ny){
	assert(game);
	int i, r;
	if(abs(nx - x) == 0){
		if(ny - y > 0){
			for(i = y; i < ny; i++){
		      		if(GetPiece(game, x, i+1) != NULL){
					if(GetPiece(game, x, i+1)->color != GetPiece(game, x, y)->color && 
							GetPiece(game, x, i+1)->x == nx && GetPiece(game, x, i+1)->y == ny){
						r = 1;
						break;
						
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
		
		       	}
		}
		else if (ny - y < 0){
			for(i = y; i > ny; i--){
	      			if(GetPiece(game, x, i-1) != NULL){
					if(GetPiece(game, x, i-1)->color != GetPiece(game, x, y)->color && 
							GetPiece(game, x, i-1)->x == nx && GetPiece(game, x, i-1)->y == ny){
						r = 1;
						break;
						
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}	
		}	
	}
	else if(abs(ny - y) == 0){
		if(nx - x > 0){
			for(i = x; i < nx; i++){
				if(GetPiece(game, i+1, y) != NULL){
					if(GetPiece(game, i+1, y)->color != GetPiece(game, x, y)->color && 
							GetPiece(game, i+1, y)->x == nx && GetPiece(game, i+1, y)->y == ny){
						r = 1;
						break;
						
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
		}
		else if (nx - x < 0){
			for(i = x; i > nx; i--){
				if(GetPiece(game, i-1, y) != NULL){
					if(GetPiece(game, i-1, y)->color != GetPiece(game, x, y)->color && 
							GetPiece(game, i-1, y)->x == nx && GetPiece(game, i-1, y)->y == ny){
						r = 1;
						break;
						
					}
					else{
						r = 0;
						break;
					}
				
				}
				else{
					r = 1;
				}
			}
		}
	}
	else{
		r = 0;
	}
			       	
	return r;
}

int CheckKnightMove(Game *game, int x, int y, int nx, int ny){
	assert(game);
	int r;
	if( ((nx == x + 2 || nx == x - 2) && (ny == y + 1 || ny == y - 1)) || ((ny == y + 2 || ny == y - 2) && (nx == x + 1 || nx == x - 1))){
		if(GetPiece(game, nx, ny) == NULL){
			r = 1;
		}
		else if(GetPiece(game, nx, ny) != NULL){
			if(GetPiece(game, nx, ny)->color != GetPiece(game, x, y)->color){
				r = 1;
			}
		}
	}
	else{
		r = 0;
	}
	return r;	
}

int CheckBishopMove(Game *game, int x, int y, int nx, int ny){
	assert(game);
	int r, i;
	if(abs(nx - x) == abs(ny - y)){
		for(i = 1; i < abs(ny - y)+1; i++){ 
			if(nx > x && ny > y){
				if(GetPiece(game, x+i, y+i) != NULL){	
					if(GetPiece(game, x+i, y+i)->color != GetPiece(game, x, y)->color &&
						       GetPiece(game, x+i, y+i)->x == nx && GetPiece(game, x+i, y+i)->y == ny){
						r = 1;
						break;
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
			else if (nx > x && ny < y){
				if(GetPiece(game, x+i, y-i) != NULL){	
					if(GetPiece(game, x+i, y-i)->color != GetPiece(game, x, y)->color &&
						       GetPiece(game, x+i, y-i)->x == nx && GetPiece(game, x+i, y-i)->y == ny){
						r = 1;
						break;
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
			else if (nx < x && ny > y){
				if(GetPiece(game, x-i, y+i) != NULL){	
					if(GetPiece(game, x-i, y+i)->color != GetPiece(game, x, y)->color &&
						       GetPiece(game, x-i, y+i)->x == nx && GetPiece(game, x-i, y+i)->y == ny){
						r = 1;
						break;
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
			else if (nx < x && ny < y){
				if(GetPiece(game, x-i, y-i) != NULL){	
					if(GetPiece(game, x-i, y-i)->color != GetPiece(game, x, y)->color &&
						       GetPiece(game, x-i, y-i)->x == nx && GetPiece(game, x-i, y-i)->y == ny){
						r = 1;
						break;
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
		}
	}
	else{
		r = 0;
	}
	return r;
}
int CheckQueenMove(Game *game, int x, int y, int nx, int ny){
	assert(game);
	int i, r;
	if(abs(nx - x) == 0){
		if(ny - y > 0){
			for(i = y; i < ny; i++){
		      		if(GetPiece(game, x, i+1) != NULL){
					if(GetPiece(game, x, i+1)->color != GetPiece(game, x, y)->color && 
							GetPiece(game, x, i+1)->x == nx && GetPiece(game, x, i+1)->y == ny){
						r = 1;
						break;
						
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
		
		       	}
		}
		else if (ny - y < 0){
			for(i = y; i > ny; i--){
	      			if(GetPiece(game, x, i-1) != NULL){
					if(GetPiece(game, x, i-1)->color != GetPiece(game, x, y)->color && 
							GetPiece(game, x, i-1)->x == nx && GetPiece(game, x, i-1)->y == ny){
						r = 1;
						break;
						
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}	
		}	
	}
	else if(abs(ny - y) == 0){
		if(nx - x > 0){
			for(i = x; i < nx; i++){
				if(GetPiece(game, i+1, y) != NULL){
					if(GetPiece(game, i+1, y)->color != GetPiece(game, x, y)->color && 
							GetPiece(game, i+1, y)->x == nx && GetPiece(game, i+1, y)->y == ny){
						r = 1;
						break;
						
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
		}
		else if (nx - x < 0){
			for(i = x; i > nx; i--){
				if(GetPiece(game, i-1, y) != NULL){
					if(GetPiece(game, i-1, y)->color != GetPiece(game, x, y)->color && 
							GetPiece(game, i-1, y)->x == nx && GetPiece(game, i-1, y)->y == ny){
						r = 1;
						break;
						
					}
					else{
						r = 0;
						break;
					}
				
				}
				else{
					r = 1;
				}
			}
		}
	}
	else if(abs(nx - x) == abs(ny - y)){
		for(i = 1; i < abs(ny - y)+1; i++){ 
			if(nx > x && ny > y){
				if(GetPiece(game, x+i, y+i) != NULL){	
					if(GetPiece(game, x+i, y+i)->color != GetPiece(game, x, y)->color &&
						       GetPiece(game, x+i, y+i)->x == nx && GetPiece(game, x+i, y+i)->y == ny){
						r = 1;
						break;
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
			else if (nx > x && ny < y){
				if(GetPiece(game, x+i, y-i) != NULL){	
					if(GetPiece(game, x+i, y-i)->color != GetPiece(game, x, y)->color &&
						       GetPiece(game, x+i, y-i)->x == nx && GetPiece(game, x+i, y-i)->y == ny){
						r = 1;
						break;
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
			else if (nx < x && ny > y){
				if(GetPiece(game, x-i, y+i) != NULL){	
					if(GetPiece(game, x-i, y+i)->color != GetPiece(game, x, y)->color &&
						       GetPiece(game, x-i, y+i)->x == nx && GetPiece(game, x-i, y+i)->y == ny){
						r = 1;
						break;
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
			else if (nx < x && ny < y){
				if(GetPiece(game, x-i, y-i) != NULL){	
					if(GetPiece(game, x-i, y-i)->color != GetPiece(game, x, y)->color &&
						       GetPiece(game, x-i, y-i)->x == nx && GetPiece(game, x-i, y-i)->y == ny){
						r = 1;
						break;
					}
					else{
						r = 0;
						break;
					}
				}
				else{
					r = 1;
				}
			}
		}
	}
	else{
		r = 0;
	}
	return r;
}
int CheckKingMove(Game *game, int x, int y, int nx, int ny){
	assert(game);
	int r;
	if(abs(nx - x) <= 1 && abs(ny - y) <= 1){
		if(GetPiece(game, nx, ny) == NULL){
			r = 1;
		}
		else if(GetPiece(game, nx, ny) != NULL && GetPiece(game, nx, ny)->color != GetPiece(game, x, y)->color){
			r = 1;
		}
	}
	else{
		r = 0;
	}
	return r;
}
int Check(Game *game){
	assert(game);
	int r = 0;
	int i, j;
	int w, b;
	Piece *p;
	int wx, wy, bx, by;
	for(j = 0; j < 8; j++){
		for(i = 0; i < 8; i++){
			p = GetPiece(game, i, j);
			if(p != NULL){
				if(p->color == 'w'){
					if(p->type == 6){
					       wx = p->x;
					       wy = p->y;
					}
				}
				if(p->color == 'b'){
					if(p->type == 6){
						bx = p->x;
						by = p->y;
					}
				}
			}
		}
	}
	/*White*/
	/* Checking for all horizontal and vertical spaces */
	if(r == 0){
		for(w = wx - 1;w > -1; w--){
			if(GetPiece(game, w, wy) != NULL){
				if(GetPiece(game, w, wy)->color == 'w'){
					r = 0;
					break;
				
				}
				else if(GetPiece(game, w, wy)->color == 'b' && 
						(GetPiece(game, w, wy)->type == 4 || GetPiece(game, w, wy)->type == 5)){
					r = 1;
					break;		
				}
			}
		}
		if(r == 0){
			for(w = wx + 1; w < 8; w++){
				if(GetPiece(game, w, wy) != NULL){
					if(GetPiece(game, w, wy)->color == 'w'){
						r = 0;
						break;		
					
					}
					else if(GetPiece(game, w, wy)->color == 'b' && 
							(GetPiece(game, w, wy)->type == 4 || GetPiece(game, w, wy)->type == 5)){
						r = 1;
						break;
					}
				}
			}
		}
		if(r == 0){
			for(w = wy - 1; w > -1; w--){
				if(GetPiece(game, wx, w) != NULL){
					if(GetPiece(game, wx, w)->color == 'w'){
						r = 0;
						break;			
					
					}
					else if(GetPiece(game, wx, w)->color == 'b' && 
							(GetPiece(game, wx, w)->type == 4 || GetPiece(game, wx, w)->type == 5)){
						r = 1;
						break;
					}
				}
			}
		}
		if(r == 0){
			for(w = wy + 1; w < 8; w++){
				if(GetPiece(game, wx, w) != NULL){
					if(GetPiece(game, wx, w)->color == 'w'){
						r = 0;
						break;			
					
					}
					else if(GetPiece(game, wx, w)->color == 'b' && 
							(GetPiece(game, wx, w)->type == 4 || GetPiece(game, wx, w)->type == 5)){
						r = 1;
						break;
					}
				}
			}
		}
	}
	/*Checking for all diagonal spaces*/
	if(r == 0){	
		for(i = 1; i < (8 - wx); i++){
			if(wx + i < 8 && wy + i < 8){
				if(GetPiece(game, wx + i, wy + i) != NULL){
					if(GetPiece(game, wx + i, wy + i)->color == 'w'){
						r = 0;
						break;
						
					}
					if(GetPiece(game, wx + i, wy + i)->color == 'b' &&
							(GetPiece(game, wx + i, wy + i)->type == 2 || GetPiece(game, wx + i, wy + i)->type == 5)){
						r = 1; 
						break;
					
					}
				}
			}
		}
		for(i = 1; i < 8 - wx; i++){	
			if(wx + i < 8 && wy - i > -1){
				if(GetPiece(game, wx + i, wy - i) != NULL){
					if(GetPiece(game, wx + i, wy - i)->color == 'w'){
						r = 0;
						break;
						
					}
					if(GetPiece(game, wx + i, wy - i)->color == 'b' &&
							(GetPiece(game, wx + i, wy - i)->type == 2 || GetPiece(game, wx + i, wy - i)->type == 5)){
						r = 1;
						break;
						
					}
				}
			}
		}
		
	}
	if(r == 0){
		for(i = 1; i < wx + 1; i++){
			if(wx - i > -1 && wy + i < 8){
				if(GetPiece(game, wx - i, wy + i) != NULL){
					if(GetPiece(game, wx - i, wy + i)->color == 'w'){
						r = 0;
						break;
					}
					if(GetPiece(game, wx - i, wy + i)->color == 'b' &&
							(GetPiece(game, wx - i, wy + i)->type == 2 || GetPiece(game, wx - i, wy + i)->type == 5)){
						r = 1;
						break;
					}
				}
			}
		}
		for(i = 1; i < wx + 1; i++){
			if(wx - i > -1 && wy - i > -1){
				if(GetPiece(game, wx - i, wy - i) !=NULL){
					if(GetPiece(game, wx - i, wy - i)->color == 'w'){
						r = 0;
						break;
					}
					if(GetPiece(game, wx - i, wy - i)->color == 'b' &&
							(GetPiece(game, wx - i, wy - i)->type == 2 || GetPiece(game, wx - i, wy - i)->type == 5)){
						r = 1;
						break;
					}
				}
			}
		}
	}
	/* Pawn */
	if(r == 0){
		if(GetPiece(game, wx + 1, wy+1) != NULL){
			if(GetPiece(game, wx + 1, wy+1)->color == 'b' && GetPiece(game, wx + 1, wy + 1)->type == 1){
				r = 1;	
			}
		}
		else if(GetPiece(game, wx - 1, wy+1) != NULL){
			if(GetPiece(game, wx - 1, wy+1)->color == 'b' && GetPiece(game, wx - 1, wy + 1)->type == 1){
				r = 1;
			}
		}	
		else{ 
			r = 0;
		}
	}
	/*Knight*/

	if(r == 0){
		/*Horizontally*/
		if(GetPiece(game, wx + 2, wy + 1) != NULL && r == 0){
			if(GetPiece(game, wx + 2, wy + 1)->color == 'b' && GetPiece(game, wx + 2, wy + 1)->type == 3){
				r = 1;
			}
		}
		if(GetPiece(game, wx + 2, wy - 1) != NULL && r == 0){
			if(GetPiece(game, wx + 2, wy - 1)->color == 'b' && GetPiece(game, wx + 2, wy - 1)->type == 3){
				r = 1;
			}
		}
		if(GetPiece(game, wx - 2, wy + 1) != NULL && r == 0){
			if(GetPiece(game, wx - 2, wy + 1)->color == 'b' && GetPiece(game, wx - 2, wy + 1)->type == 3){
				r = 1;
			}
		}
		if(GetPiece(game, wx - 2, wy - 1) != NULL && r == 0){
			if(GetPiece(game, wx - 2, wy - 1)->color == 'b' && GetPiece(game, wx - 2, wy - 1)->type == 3){
				r = 1;
			}
		}
		/*Vertical*/
		if(GetPiece(game, wx + 1, wy + 2) != NULL && r == 0){
			if(GetPiece(game, wx + 1, wy + 2)->color == 'b' && GetPiece(game, wx + 1, wy + 2)->type == 3){
				r = 1;
			}
		}
		if(GetPiece(game, wx - 1, wy + 2) != NULL && r == 0){
			if(GetPiece(game, wx - 1, wy + 2)->color == 'b' && GetPiece(game, wx - 1, wy + 2)->type == 3){
				r = 1;
			}
		}
		if(GetPiece(game, wx + 1, wy - 2) != NULL && r == 0){
			if(GetPiece(game, wx + 1, wy - 2)->color == 'b' && GetPiece(game, wx + 1, wy - 2)->type == 3){
				r = 1;
			}
		}
		if(GetPiece(game, wx - 1, wy - 2) != NULL && r == 0){
			if(GetPiece(game, wx - 1, wy - 2)->color == 'b' && GetPiece(game, wx - 1, wy - 2)->type == 3){
				r = 1;
			}
		}
		else{
			r = 0;
		}
	}



/*Black Pieces*/
/**********************************************************************************************/
/*Checking Horizotal and vertical spaces */
	if(r == 0){
		for(b = bx - 1;b > -1; b--){
			if(GetPiece(game, b, by) != NULL){
				if(GetPiece(game, b, by)->color == 'b'){
					r = 0;
					break;
				
				}
				else if(GetPiece(game, b, by)->color == 'w' && 
						(GetPiece(game, b, by)->type == 4 || GetPiece(game, b, by)->type == 5)){
					r = 2;
					break;		
				}
			}
		}
		if(r == 0){
			for(b = bx + 1; b < 8; b++){
				if(GetPiece(game, b, by) != NULL){
					if(GetPiece(game, b, by)->color == 'b'){
						r = 0;
						break;		
					
					}
					else if(GetPiece(game, b, by)->color == 'w' && 
							(GetPiece(game, b, by)->type == 4 || GetPiece(game, b, by)->type == 5)){
						r = 2;
						break;
					}
				}
			}
		}
		if(r == 0){
			for(b = by + 1; b < 8; b++){
				if(GetPiece(game, bx, b) != NULL){
					if(GetPiece(game, bx, b)->color == 'b'){
						r = 0;
						break;			
					
					}
					else if(GetPiece(game, bx, b)->color == 'w' && 
							(GetPiece(game, bx, b)->type == 4 || GetPiece(game, bx, b)->type == 5)){
						r = 2;
						break;
					}
				}
			}
		}
		if(r == 0){
			for(b = by - 1; b > -1; b--){
				if(GetPiece(game, bx, b) != NULL){
					if(GetPiece(game, bx, b)->color == 'b'){
						r = 0;
						break;			
					
					}
					else if(GetPiece(game, bx, b)->color == 'w' && 
							(GetPiece(game, bx, b)->type == 4 || GetPiece(game, bx, b)->type == 5)){
						r = 2;
						break;
					}
				}
			}
		}
	}
	/*Checking for all diagonal spaces*/
	if(r == 0){	
		for(i = 1; i < (8 - bx); i++){
			if(bx + i < 8 && by - i > -1){
				if(GetPiece(game, bx + i, by - i) != NULL){
					if(GetPiece(game, bx + i, by - i)->color == 'b'){
						r = 0;
						break;
						
					}
					if(GetPiece(game, bx + i, by - i)->color == 'w' &&
							(GetPiece(game, bx + i, by - i)->type == 2 || GetPiece(game, bx + i, by - i)->type == 5)){
						r = 2; 
						break;
					
					}
				}
			}
		}
		for(i = 1; i < 8 - bx; i++){	
			if(bx + i < 8 && by + i < 8){
				if(GetPiece(game, bx + i, by + i) != NULL){
					if(GetPiece(game, bx + i, by + i)->color == 'b'){
						r = 0;
						break;
						
					}
					if(GetPiece(game, bx + i, by + i)->color == 'w' &&
							(GetPiece(game, bx + i, by + i)->type == 2 || GetPiece(game, bx + i, by + i)->type == 5)){
						r = 2;
						break;
						
					}
				}
			}
		}
		
	}

	if(r == 0){
		for(i = 1; i < bx + 1; i++){
			if(bx - i > -1 && by + i < 8){
				if(GetPiece(game, bx - i, by + i) != NULL){
					if(GetPiece(game, bx - i, by + i)->color == 'b'){
						r = 0;
						break;
					}
					if(GetPiece(game, bx - i, by + i)->color == 'w' &&
							(GetPiece(game, bx - i, by + i)->type == 2 || GetPiece(game, bx - i, by + i)->type == 5)){
						r = 2;
						break;
					}
				}
			}
		}
		for(i = 1; i < bx + 1; i++){
			if(bx - i > -1 && by - i > -1){
				if(GetPiece(game, bx - i, by - i) !=NULL){
					if(GetPiece(game, bx - i, by - i)->color == 'b'){
						r = 0;
						break;
					}
					if(GetPiece(game, bx - i, by - i)->color == 'w' &&
							(GetPiece(game, bx - i, by - i)->type == 2 || GetPiece(game, bx - i, by - i)->type == 5)){
						r = 2;
						break;
					}
				}
			}
		}
	}
	/* Pawn */
	if(r == 0){
		if(GetPiece(game, bx + 1, by-1) != NULL){
			if(GetPiece(game, bx + 1, by+1)->color == 'w' && GetPiece(game, bx + 1, by + 1)->type == 1){
				r = 2;	
			}
			else{
				r = 0;
			}
		}
		else if(GetPiece(game, bx - 1, by-1) != NULL){
			if(GetPiece(game, bx - 1, by+1)->color == 'w' && GetPiece(game, bx - 1, by + 1)->type == 1){
				r = 2;
			}
			else{
				r = 0;
			}
		}	
		else{ 
			r = 0;
		}
	}
	/*Knight*/

	if(r == 0){
		/*Horizontally*/
		if(GetPiece(game, bx + 2, by + 1) != NULL && r == 0){
			if(GetPiece(game, bx + 2, by + 1)->color == 'w' && GetPiece(game, bx + 2, by + 1)->type == 3){
				r = 2;
			}
		}
		if(GetPiece(game, bx + 2, by - 1) != NULL && r == 0){
			if(GetPiece(game, bx + 2, by - 1)->color == 'w' && GetPiece(game, bx + 2, by - 1)->type == 3){
				r = 2;
			}
		}
		if(GetPiece(game, bx - 2, by + 1) != NULL && r == 0){
			if(GetPiece(game, bx - 2, by + 1)->color == 'w' && GetPiece(game, bx - 2, by + 1)->type == 3){
				r = 2;
			}
		}
		if(GetPiece(game, bx - 2, by - 1) != NULL && r == 0){
			if(GetPiece(game, bx - 2, by - 1)->color == 'w' && GetPiece(game, bx - 2, by - 1)->type == 3){
				r = 2;
			}
		}
		/*Vertical*/
		if(GetPiece(game, bx + 1, by + 2) != NULL && r == 0){
			if(GetPiece(game, bx + 1, by + 2)->color == 'w' && GetPiece(game, bx + 1, by + 2)->type == 3){
				r = 2;
			}
		}
		if(GetPiece(game, bx - 1, by + 2) != NULL && r == 0){
			if(GetPiece(game, bx - 1, by + 2)->color == 'w' && GetPiece(game, bx - 1, by + 2)->type == 3){
				r = 2;
			}
		}
		if(GetPiece(game, bx + 1, by - 2) != NULL && r == 0){
			if(GetPiece(game, bx + 1, by - 2)->color == 'w' && GetPiece(game, bx + 1, by - 2)->type == 3){
				r = 2;
			}
		}
		if(GetPiece(game, bx - 1, by - 2) != NULL){
			if(GetPiece(game, bx - 1, by - 2)->color == 'w' && GetPiece(game, bx - 1, by - 2)->type == 3){
				r = 2;
			}
		}
		else{
			r = 0;
		}



	}
       	return r;
}       
				  

void RecordMove(char *in, Game *game){       
     assert(in);
     FILE *f = NULL;

     f = fopen("/users/ugrad2/2017/winter/team11/cvs_rep/chess/bin/log.txt", "a");
     if (f == NULL){
         printf("Error!");
         exit(1);
     }
     if(game->turn% 2==0){
         fprintf(f, "Player 2: ");
         fprintf(f, in);
         fprintf(f, "\n");
                      }
     else if(game->turn %2==1){
         fprintf(f, "Player 1: ");
         fprintf(f, in);
         fprintf(f, "\n");
     }
     fclose(f);
}

int CheckPawnTransform(Game *game, int x, int y){
    assert(game);
    int r ;
    int trans = 0;
    if ((GetPiece(game, x, y)->color == 'w') && (GetPiece(game, x, y)->type == 1)){
        if (y == 7) {
            printf("\n (W) Your pawn can transform. What piece would you like to transform your pawn into?\n (Bishop = 2, Knight = 3, Rook = 4, Queen = 5)\n");
            scanf("%d", &trans);
            while ( (trans < 2) || (trans > 5)){
                printf("\nPlease input a valid number\n");
                scanf("d");
            } 
            r = trans;
        
        }
        else{
        r = 0;
        } 
    }
    
    else if ((GetPiece(game, x, y)->color == 'b') && (GetPiece(game, x, y)->type == 1)){
        if (GetPiece(game, x, y)->y == 0){
            printf("\n (B) Your pawn can transform. What piece would you like to transform your pawn into?\n (Bishop = 2, Knight = 3, Rook = 4, Queen = 5)\n");
            scanf("%d", &trans);
            while ( (trans < 2) || (trans > 5)){
                printf("\nPlease input a valid number\n");
                scanf("d");
            }
          r = trans;
        }
        else{
        r = 0;
        } 
    }
    else {
    r = 0;
    }
  return r;
}

TIME *CheckTime(){
    time_t lt;
    struct tm *info;
    TIME *t;
    time(&lt);
    info = localtime(&lt);
    t = (TIME*)malloc(sizeof(TIME));
    if (!t){
        perror("Out of memory. Aborting...");
        exit(10);
    }
    t->hour = info->tm_hour;
    t->min = info->tm_min;
    t->sec = info->tm_sec;
    t->diffB = 0;
    t->diffW = 0;
    printf("%d:%d:%d\n", t->hour , t->min, t->sec);
    
    return t;

}

int Btimediff(TIME *t){
    time_t lt;
    struct tm *info;
    int nh, nm, ns, ftot, stot, ch, cm, d; 
    time (&lt);
    info = localtime(&lt);
    nh = info->tm_hour;
    nm = info->tm_min;
    ns = info->tm_sec;
    printf("%d:%d:%d\n", nh, nm, ns);
    ch = t->hour * 3600;
    cm = t->min * 60;
    nh = info->tm_hour * 3600;
    nm = info->tm_min * 60;
    ftot = ch + cm + t->sec;
    stot = nh + nm + ns;
    t->diffB = stot - ftot;
    d = abs(t->diffB - t->diffW);
    printf("Time passed: %d seconds.\n", d);
    return 0;
}
int Wtimediff(TIME *t){
    time_t lt;
    struct tm *info;
    int nh, nm, ns, ftot, stot, ch, cm, d; 
   
    time (&lt);
    info = localtime(&lt);
    nh = info->tm_hour;
    nm = info->tm_min;
    ns = info->tm_sec;
    printf("%d:%d:%d\n", nh, nm, ns);
    ch = t->hour * 3600;
    cm = t->min * 60;
    nh = info->tm_hour * 3600;
    nm = info->tm_min * 60;
    ftot = ch + cm + t->sec;
    stot = nh + nm + ns;
    t->diffW = stot - ftot;
    d = abs(t->diffW - t->diffB);
    printf("Time passed: %d seconds.\n", d);
    return 0;
}

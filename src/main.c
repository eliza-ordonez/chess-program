#include "gameboard.h"
#include "pieces.h"
#include "player.h"
#include "AI.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(){
	Game *game;
	Piece *p;
    TIME *t;
	int KingWMove = 0, KingBMove = 0, RookWMove1 = 0, RookWMove2 = 0, RookBMove1 = 0, RookBMove2 = 0;
	int opt;
	int x, y, nx, ny;
	int r, c;
	int j, k;
	int trans;
	int emptyw1, emptyw2, emptyb1, emptyb2;
	int wcheck = 0;
       	int bcheck = 0;
	AI *a;
	printf("Welcome to the Fruit of Chess!!!\n\n");
	printf("1.	Player vs. Player\n");
	printf("2.	Player vs. AI\n");
	printf("3.	AI vs. AI\n");
	printf("Choose a game mode (e.g type 1, 2, 3)\n");
	printf("Or type 'quit' to exit:	");
	scanf("%d", &opt);
	char undo[3];
	char input[3];
	int filed;
	char *in, *in2;
	in = malloc(sizeof(char)); 
	in2 = malloc(sizeof(char));
	if(opt == 1){
		printf("Before you start your game, would you like to keep your moves in a log file?(yes or no): ");
		scanf("%s", input);
		if(strcmp(input, "yes") == 0){
			printf("Please enter the full path directory (e.g /users/ugrad2/2017/winter/team11/cvs_rep/chess/bin/log.txt): ");
			scanf("%s", in2);
			FILE *f =NULL;
      		 	f= fopen(in2, "w");
      			if (f == NULL){
      				 printf("Error!");
      				 exit(1);
       			}
			fclose(f);
				filed = 1;
		}	
		else if(strcmp(input, "no") == 0){
		       filed = 0;
		}
   }
    if(opt == 2)
    {
      printf("Before you start your game, would you like to keep your moves in a log file?(yes or no): ");
  		scanf("%s", input);
  		if(strcmp(input, "yes") == 0){
  			printf("Please enter the full path directory (e.g /users/ugrad2/2017/winter/team11/cvs_rep/chess/bin/log.txt): ");
  			scanf("%s", in2);
  			FILE *f =NULL;
        		 	f= fopen(in2, "w");
        			if (f == NULL){
        				 printf("Error!");
        				 exit(1);
         			}
  			fclose(f);
  				filed = 1;
    		  }	
		else if(strcmp(input, "no") == 0){
		       filed = 0;
		}
	printf("\n");
	char AIColor;
	int AIDifficulty;
	printf("Please choose the AI's color. 'b' = black, 'w' = white \n");
	scanf(" %c", &AIColor);
	printf("Please choose the AI's difficulty. 0 = easy, 1 = medium, 2 = hard \n");
	scanf(" %d", &AIDifficulty);
	a = CreateAI(AIColor, AIDifficulty);
    }	       
		/*commenting out because only works with team account*/ 
  
        t = CheckTime();

/*        t = CheckTime();*/

   /*     t = CheckTime();*/
		/*printf("Please make your move (W) in algebraic form (e.g a2a4, etc):   ");
		scanf("%s",in);*/
   
   
   
		game = CreateGame();
		game->turn = 0;
		PrintBoard(game);
        	t = CheckTime();
		if(opt == 2 && a->color == 'w')
		{
			MakeBestMove(game, a);
			PrintBoard(game);
                        printf("Please make your move (B) in algebraic form (e.g a2a4, etc):   ");
                        scanf("%s",in);
			game->turn++;

		}
		else
		{
			printf("Please make your move (W) in algebraic form (e.g a2a4, etc):   ");
			scanf("%s",in);
		}
   if(opt == 3)
   {
       AI *a,*b;
       int difficulty1, difficulty2;
       int turns;
       printf("Please select the difficulty of the white AI. 0 = easy, 1 = medium, 2 = hard \n");
       scanf(" %d", &difficulty1);
       printf("Please select the difficulty of the black AI. 0 = easy, 1 = medium, 2 = hard \n");
       scanf(" %d", &difficulty2);
       a = CreateAI('w', difficulty1);
       b = CreateAI('b', difficulty1);
       PrintBoard(game);
       for(turns = 0; turns < 12; turns++)
       { 
           MakeBestMove(game, a);
           PrintBoard(game);
           MakeBestMove(game, b);
       }
       
   }

		printf("Please make your move (W) in algebraic form (e.g a2a4, etc):   ");
		scanf("%s",in);
    

		while(in){
			x = in[0] - 97;
			y = in[1] - 49;
			nx = in[2] - 97;
			ny = in[3] - 49;
			p = GetPiece(game, x, y);
			if((x >= 0 || x < 8) && (y >=0 || y < 8) && (nx >= 0 || nx < 8) && (ny >= 0 || ny < 8) && (p !=NULL)){
				if(strcmp(in,"quit") == 0){
					break;
				}
				if((p->color == 'w' && game->turn % 2 == 0) || (p->color == 'b' && game->turn % 2 != 0)){
				
					
					if(p->type == 1){
						r = CheckPawnMove(game, x, y, nx, ny);	
					}
					else if(p->type == 4){
						r = CheckRookMove(game, x, y, nx, ny);
						if(x == 0 && y == 0 && r == 1){
							RookWMove1 = 1;
						}
						else if(x == 7 && y == 0 && r == 1){
							RookWMove2 = 1;
						}
						else if(x == 0 && y == 7 && r == 1){
							RookBMove1 = 1;
						}
						else if(x == 7 && y == 7 && r == 1){
							RookBMove2 = 1;
						}

					}
					else if(p->type == 3){
						r = CheckKnightMove(game, x, y, nx, ny);
					}
					else if(p->type == 2){
						r = CheckBishopMove(game, x, y, nx, ny);
					}
					else if(p->type == 5){
						r = CheckQueenMove(game, x, y, nx, ny);
					}
					else if(p->type == 6){
						r = CheckKingMove(game, x, y, nx, ny);
						emptyw1 = 0;
						emptyw2 = 0;
						emptyb1 = 0;
						emptyb2 = 0;
						for(j = 1; j < 4; j++){
							if(game->Board[j][0] == NULL){
								emptyw1++;
							}
							else if(game->Board[j][7] == NULL){
								emptyb1++;
							}
						}
						for(j = 5; j < 7; j++){
							if(game->Board[j][0] == NULL){
								emptyw2++;
							}
							else if(game->Board[j][7] == NULL){
								emptyb2++;
							}
						}
						if(x == 4 && y == 0 && r == 1){
							KingWMove = 1;
						}
						else if(x == 4 && y == 7 && r == 1){
							KingBMove = 1;
						}
						else if(p->type == 6 && p->color == 'w' && KingWMove == 0 && RookWMove1 == 0 &&
								emptyw1 == 3 && nx == 2 && (ny - y == 0) && ny == 0){
							MovePiece(game, x, y, nx, ny);
							MovePiece(game, 0, 0, 3, 0);
							KingWMove = 1;
							RookWMove1 = 1;
							k = 1;
							game->turn++;		
							PrintBoard(game);
						}
						else if(p->type == 6 && p->color == 'w' && KingWMove == 0 && RookWMove2 == 0 &&
								emptyw2 == 2 &&  nx == 6 &&  (ny - y == 0) && ny == 0){
							MovePiece(game, x, y, nx, ny);
							MovePiece(game, 7, 0, 5, 0);
							KingWMove = 1;
							RookWMove1 = 1;
							k = 1;
							game->turn++;		
							PrintBoard(game);

						}
						else if(p->type == 6 && p->color == 'b' && KingBMove == 0 && RookBMove1 == 0 &&
								emptyb1 == 3 && nx == 2 && (ny - y == 0) && ny == 7){
							printf("hi");
							MovePiece(game, x, y, nx, ny);
							MovePiece(game, 0, 7, 3, 7);
							KingWMove = 1;
							RookWMove1 = 1;
							k = 1;
							game->turn++;		
							PrintBoard(game);

						}
						else if(p->type == 6 && p->color == 'b' && KingBMove == 0 && RookBMove2 == 0 &&
								emptyb2 == 2 &&  nx == 6 && (ny - y == 0) && ny == 7){
							printf("hi");
							MovePiece(game, x, y, nx, ny);
							MovePiece(game, 7, 7, 5, 7);
							KingWMove = 1;
							RookWMove1 = 1;
							k = 1;
							game->turn++;		
							PrintBoard(game);

						}
					}
					if(r == 1){ 
						MovePiece(game, x, y, nx, ny);
						
						PrintBoard(game);
						c = Check(game);
						if(c == 1){
							wcheck++;
							if(wcheck == 2){
								printf("Checkmate!\nWhite wins!");
								break;
							}
							else if(wcheck == 1){
								printf("White is in check!\n");
							}
							
						}
						else if(c == 2){
							bcheck++;
							if(bcheck == 2){
								printf("Checkmate!\nBlack wins!");
								break;
							}
							else if(bcheck == 1){
								printf("Black is in check!\n");
							}
							
						}
						else if(c == 0){
							wcheck = 0;
							bcheck = 0;
						}	
						printf("Would you like to undo your move? (yes or no): ");
						scanf("%s",undo);
						if (strcmp(undo,"yes") == 0){
							MovePiece(game,nx,ny,x,y);
							PrintBoard(game);
						}
						else if (strcmp(undo,"no") == 0){
						trans = CheckPawnTransform(game, nx, ny);
						if (trans != 0){
							SetPiece(game, nx, ny, trans);
							PrintBoard(game);
						}
						game->turn++;						
						}
						

                		/*RecordMove(in, game);*/ 
                        /*comment out for now because only works with team account*/

				if(filed == 1){
                			RecordMove(in, game); 
				}

					}
					else if(r == 0 && k != 1){
						printf("Invalid Move!\n");
					}

				}
				else{
					printf("Wrong color!\n");
				}
			}
			else if((r = 0) && (k != 1)){
				printf("Invalid Entry!\n");
			}
			
			if(opt == 1)
			{

				if(game->turn % 2 == 0){	
					Wtimediff(t);
	                		printf("Please make your move (W):   ");
	    			}	
				else if(game->turn % 2 != 0){
					Btimediff(t);
       		         		printf("Please make your move (B):   ");
				}
				scanf("%s",in);
			}
			if(opt == 2)
			{
				
                                if(game->turn % 2 == 0 && a->color== 'w'){
                                        Wtimediff(t);
                                        printf("AI will make its move\n");
					MakeBestMove(game, a);
					PrintBoard(game);
                                }
                                else if(game->turn % 2 != 0 && a->color == 'b'){
                                        Btimediff(t);
                                        printf("AI will make its move\n");
					MakeBestMove(game,a);
					PrintBoard(game);
                                }
				else if(game->turn % 2 == 0 && a->color== 'b'){
                                        Wtimediff(t);
                                        printf("Please make your move (W):   ");
                                        scanf("%s",in);
                                }
                                else if(game->turn % 2 != 0 && a->color == 'w'){
                                        Btimediff(t);
                                        printf("Please make your move (B):   ");
                                        scanf("%s",in);
                                }

                             


			}
		}
		DeleteGame(game);
	
	return 0;

}

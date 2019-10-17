#include <stdio.h>
#include <stdlib.h>

/*int main(char *in, int turn){
    FILE *f;

    f = fopen("log.txt", "w");
    
    while(in){
        if (turn % 2 == 0){
            fputs("Player 1: ", f);
            fputs(in, f);
            fputs(" \n", f);
       
        }
        else if (turn % 2 == 1){
            fputs("Player 2: ", f);
            fputs(in, f);
            fputs(" \n", f);    
        }
    }
    fclose(f);
    return 0;

}*/

int main(void){
    int turn;
    char *in;
    FILE *f;
    
    printf("Enter turn: \n ");
    scanf("%d", &turn);
    printf("Enter move: \n");
    scanf("%s", &in);

    f = fopen("log.txt", "w");
    
    while(in){
        if (turn % 2 == 0){
            fputs("Player 1: ", f);
            fputs(in, f);
            fputs(" \n", f);
       
        }
        else if (turn % 2 == 1){
            fputs("Player 2: ", f);
            fputs(in, f);
            fputs(" \n", f);    
        }
    }
    fclose(f);
    return 0;


}


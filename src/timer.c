/* timer.c */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void){
    int sec = 0;
    int min = 0;

    while (min != 20){

        printf("%d:%d\n", min, sec);
        sleep(1);
        sec++;
        if (sec == 60) {
            min++;
            sec = 0;
        }

    }
     
    return 0;
}

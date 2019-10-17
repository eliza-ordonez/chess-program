/*time.c*/

#include <stdio.h>
#include <time.h>

int time(void){
    time_t t;
    struct tm *info;
    int h, m, s;

    time(&t);
    info = localtime(&t);
    h = info->tm_hour;
    m = info->tm_min;
    s = info->tm_sec;

    printf("%d:%d:%d\n", h , m, s);
    
    

    return h, m, s;
}

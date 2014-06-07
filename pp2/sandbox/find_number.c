#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    //int x = -2147482647;
    int x = -1000000000;

    for(; x < 0; x--) {
        int y = x * 32;
        if((y >= 21088) && (y <= 21210)) {

            printf("%d\t\t%d\n", x, y);
            //printf("%d\n", y);
        }
    }

    return 0;
}


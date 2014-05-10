#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_LOOPS 10000

int main(int argc, char* argv[])
{
    int i = 0;

    int * ptr = malloc(sizeof(int));
    printf("%p\n", ptr);

    /*
    for(i = 0; i < NUM_OF_LOOPS; i++) {

        int * ptr = malloc(sizeof(int));
        printf("%p\t", ptr);
        if((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    */

    return 0;
}

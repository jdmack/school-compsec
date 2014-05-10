#include <stdio.h>
#include <stdlib.h>
#include "../cmdb_struct.h"

#define NUM_OF_LOOPS 100

int main(int argc, char* argv[])
{
    //int i = 0;

    int * ptr = malloc(sizeof(struct cmdb_entry));
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

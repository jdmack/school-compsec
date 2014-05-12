#include <stdio.h>
#include <stdlib.h>
#include "../cmdb_struct.h"

//#define MAX_ENTRIES 16384
#define MAX_ENTRIES 8000

int main(int argc, char* argv[])
{
    int i = 0;
    struct cmdb_entry* ce_list[MAX_ENTRIES];

    //printf("%p\n", ptr);

    for(i = 0; i < MAX_ENTRIES; i++) {

        ce_list[i] = malloc(sizeof(struct cmdb_entry));
        //printf("%p\t", ptr);
        /*if((i + 1) % 8 == 0) {
            printf("\n");
        }*/
    }
    printf("%p\n", ce_list[0] + (ce_list[MAX_ENTRIES - 1] - ce_list[0]));

    return 0;
}

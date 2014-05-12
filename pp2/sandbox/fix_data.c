#include <stdlib.h>
#include <stdio.h>

void xor_field(char* field, const int fieldLen, const char* key, const int keyLen);
void permute_field(char* field, const int fieldLen, const int* perm, const int permLen);
void undo_permute(char* field, const int fieldLen, const int* perm, const int permLen);
void print_char_array(const char* array, int size);

int main(int argc, char* argv[])
{
    // writer 300 - 12
    //int size = 12;
    //char field[12] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[12] = "\xd7\xe2\xb8\x4a\x68\x9d\x7c\xd4\xe7\x66\x79\xd3";

    // star1 300 - 5
    //int size = 5;
    //char field[5] = "\x90\x90\x90\x90\x90";
    //char   key[5] = "\xcf\xe2\x6f\x57\xdb";

    // star3 300 - 1
    //int size = 1;
    //char field[1] = "\x90";
    //char   key[1] = "\x86";

    // star5 300 - 20
    //int size = 20;
    //char field[20] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[20] = "\x69\x1e\x61\x48\x92\x98\x19\xd0\x5f\xce\x14\x50\xe5\x74\xc6\xea\x7c\x8b\x8f\x15";

    // runtime 80 - 80
    int size = 80;
    char field[80] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xeb\x01\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xeb\x01\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    char   key[80] = "\xa2\xc1\xcd\xfa\xbe\x1f\xa5\xf6\x2f\xf2\x14\x9d\x42\xbd\x58\x09\x9a\x2c\x4e\x72\x98\x7b\x03\xd8\x39\xe7\x3e\x04\xc4\xe3\x43\x42\xa1\x28\xaf\x64\xb1\x1a\x33\x1b\xe3\x0a\xf0\x72\x0e\x9c\x9a\xa2\x32\x99\xd4\x61\xba\xb5\x2e\x52\xb4\x89\x88\x13\x1e\x44\x32\x50\x59\x6a\xc6\x01\x5f\xa8\x45\x1a\xa4\x94\xc9\x3f\xd4\x32\x0d\x72";

    // aspect 40 - 20
    //int size = 20;
    //char field[20] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[20] = "\x67\xa1\x62\x71\x1c\x48\x8d\xb1\xcd\x74\xda\xe9\x47\x62\xe2\x07\x84\x58\x75\x6a";

    // average_rating 3 - 1
    //int size = 1;
    //char field[1] = "\x90";
    //char   key[1] = "\x26";


    // composer 300 - 6
    //int size = 6;
    //char field[6] = "\x90";
    //char   key[6] = "";

    // shellcode in composer 300 - 6
    //int size = 6;
    //char field[6] = "";
    //char field[6] = "";
    //char field[6] = "";
    //char field[6] = "";
    //char   key[6] = "";

    printf("Before xor:\n");
    print_char_array(field, size);

    xor_field(field, size, key, size);

    printf("After xor:\n");
    print_char_array(field, size);

    xor_field(field, size, key, size);

    printf("After undo xor:\n");
    print_char_array(field, size);


    /*
    // writer 300 - 3
    int size = 3;
    char field[size] = "\x90";
    int key[size] = {1, 2, 0};

    // star1 300 - 3
    int size = 3;
    char field[size] = "\x90";
    int key[size] = {};

    // star2 300 - 3
    int size = 3;
    char field[size] = "\x90";
    int key[size] = {};

    // country 300 - 3
    int size = 3;
    char field[size] = "\x90";
    int key[size] = {};

    // budget 300 - 3
    int size = 3;
    char field[size] = "\x90";
    int key[size] = {};

    // opening_weekend 300 - 3
    int size = 3;
    char field[size] = "\x90";
    int key[size] = {};

    // runtime 300 - 3
    int size = 3;
    char field[size] = "\x90";
    int key[size] = {};
    */


    /*
    printf("Before undo_permute:\n");
    print_char_array(field, size);

    undo_permute(field, size, key, size);

    printf("After under_permute::\n");
    print_char_array(field, size);

    permute_field(field, size, key, size);

    printf("After permute:\n");
    print_char_array(field, size);
    */

    return 0;
}

void permute_field(char* field, const int fieldLen, const int* perm, const int permLen)
{
    if(fieldLen % permLen != 0) {
        fprintf(stderr, "Error: permutation length does not divide field length.");
    }

    int index;  // Index in current field. 
    int base;  // Base index of the current permutation. 
    int permItr;  // Permutation iteration we're on. 
    char* tmp = malloc(permLen);  // A temporary field for our permutation.

    // For each time we are performing our permutation.
    for(permItr = 0; permItr < fieldLen / permLen; permItr++) {

        base = permItr * permLen;

        // tmp[i] gets field[perm[i]].
        for(index = 0; index < permLen; index++) {
            tmp[index] = field[base + perm[index]];
        }

        // field[i] gets field[perm[i]].
        for(index = 0; index < permLen; index++) {
            field[base + index] = tmp[index];
        }
    }
}

void undo_permute(char* field, const int fieldLen, const int* perm, const int permLen)
{
    if(fieldLen % permLen != 0) {
        fprintf(stderr, "Error: permutation length does not divide field length.");
    }

    int index;  // Index in current field. 
    int base;  // Base index of the current permutation. 
    int permItr;  // Permutation iteration we're on. 
    char* tmp = malloc(permLen);  // A temporary field for our permutation.

    // For each time we are performing our permutation.
    for(permItr = 0; permItr < fieldLen / permLen; permItr++) {

        base = permItr * permLen;

        // tmp[i] gets field[perm[i]].
        for(index = 0; index < permLen; index++) {
            tmp[perm[index]] = field[index];
        }

        // field[i] gets field[perm[i]].
        for(index = 0; index < permLen; index++) {
            field[base + index] = tmp[index];
        }
    }
}

void xor_field(char* field, const int fieldLen, const char* key, const int keyLen)
{
    if(fieldLen % keyLen != 0) {
        fprintf(stderr, "Error: key length does not divide field length.");
    }

    int index;  // Index in current field. 
    int base;  // Base index of the current permutation. 
    int keyItr;  // Key iteration we're on. 

    // For each time we use the xor key. 
    for(keyItr = 0; keyItr < fieldLen / keyLen; keyItr++) {

        base = keyItr * keyLen;

        for(index = 0; index < keyLen; index++) {
            field[base + index] ^= key[index];
        }
    }
}

void print_char_array(const char* array, int size)
{
    int i = 0;
    for(i = 0; i < size; i++) {
        printf(" %#.2x", array[i]); 
    }
    printf("\n");
}

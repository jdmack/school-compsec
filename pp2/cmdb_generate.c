#include <stdlib.h>
#include "cmdb_generate.h"
#include "cmdb.h"
void new_entry(struct cmdb_entry* ce)
{
    char tmp[2048];
    int rd;
    puts("Title?\n");
    rd = get_line(tmp,500);
    memset(&(tmp[rd]),'\0',500-rd);
    memcpy(&(ce->Title),tmp,500);

    puts("Director?\n");
    rd = get_line(tmp,300);
    memset(&(tmp[rd]),'\0',300-rd);
    memcpy(&(ce->Director),tmp,300);

    puts("Writer?\n");
    rd = get_line(tmp,300);
    memset(&(tmp[rd]),'\0',300-rd);
    memcpy(&(ce->Writer),tmp,300);

    puts("Star_1?\n");
    rd = get_line(tmp,300);
    memset(&(tmp[rd]),'\0',300-rd);
    memcpy(&(ce->Star_1),tmp,300);

    puts("Star_2?\n");
    rd = get_line(tmp,300);
    memset(&(tmp[rd]),'\0',300-rd);
    memcpy(&(ce->Star_2),tmp,300);

    puts("Star_3?\n");
    rd = get_line(tmp,300);
    memset(&(tmp[rd]),'\0',300-rd);
    memcpy(&(ce->Star_3),tmp,300);

    puts("Star_4?\n");
    rd = get_line(tmp,300);
    memset(&(tmp[rd]),'\0',300-rd);
    memcpy(&(ce->Star_4),tmp,300);

    puts("Star_5?\n");
    rd = get_line(tmp,300);
    memset(&(tmp[rd]),'\0',300-rd);
    memcpy(&(ce->Star_5),tmp,300);

    puts("Summary?\n");
    rd = get_line(tmp,2000);
    memset(&(tmp[rd]),'\0',2000-rd);
    memcpy(&(ce->Summary),tmp,2000);

    puts("Country?\n");
    rd = get_line(tmp,30);
    memset(&(tmp[rd]),'\0',30-rd);
    memcpy(&(ce->Country),tmp,30);

    puts("Budget?\n");
    rd = get_line(tmp,80);
    memset(&(tmp[rd]),'\0',80-rd);
    memcpy(&(ce->Budget),tmp,80);

    puts("Opening_Weekend?\n");
    rd = get_line(tmp,80);
    memset(&(tmp[rd]),'\0',80-rd);
    memcpy(&(ce->Opening_Weekend),tmp,80);

    puts("Gross?\n");
    rd = get_line(tmp,80);
    memset(&(tmp[rd]),'\0',80-rd);
    memcpy(&(ce->Gross),tmp,80);

    puts("Runtime?\n");
    rd = get_line(tmp,80);
    memset(&(tmp[rd]),'\0',80-rd);
    memcpy(&(ce->Runtime),tmp,80);

    puts("Aspect?\n");
    rd = get_line(tmp,40);
    memset(&(tmp[rd]),'\0',40-rd);
    memcpy(&(ce->Aspect),tmp,40);

    puts("Composer?\n");
    rd = get_line(tmp,300);
    memset(&(tmp[rd]),'\0',300-rd);
    memcpy(&(ce->Composer),tmp,300);

    puts("Average_Rating?\n");
    rd = get_line(tmp,3);
    memset(&(tmp[rd]),'\0',3-rd);
    memcpy(&(ce->Average_Rating),tmp,3);


  
    char keyDirector[300] = "\x26\xf8\x2b\xff\x7b\x2d";
    xor_field(ce->Director, 300, keyDirector, 6);
  
  
    char keyStar_2[300] = "\xe7\x1e\x90\xa1\x80\x93\xb5\x83\x3a\xe4";
    xor_field(ce->Star_2, 300, keyStar_2, 10);
    int permStar_3[300] = {13, 1, 0, 12, 2, 11, 4, 10, 14, 5, 8, 6, 3, 7, 9};
    permute_field(ce->Star_3, 300, permStar_3, 15);
  
  
    int permSummary[2000] = {191, 59, 91, 88, 103, 109, 157, 119, 35, 38, 80, 107, 99, 153, 49, 143, 100, 33, 36, 42, 135, 44, 56, 169, 194, 28, 172, 186, 189, 19, 16, 112, 51, 165, 53, 156, 181, 144, 136, 177, 128, 126, 159, 120, 68, 176, 5, 15, 29, 84, 21, 8, 31, 166, 193, 93, 116, 179, 87, 140, 17, 146, 75, 89, 97, 134, 161, 67, 46, 55, 122, 12, 76, 86, 174, 163, 168, 34, 24, 150, 158, 45, 30, 32, 138, 82, 63, 184, 131, 39, 9, 198, 121, 3, 105, 43, 199, 18, 14, 81, 149, 164, 118, 23, 71, 178, 190, 187, 57, 78, 129, 151, 106, 73, 141, 61, 98, 11, 192, 69, 60, 182, 160, 173, 117, 58, 108, 83, 48, 27, 124, 102, 22, 185, 79, 170, 66, 96, 104, 41, 123, 40, 197, 132, 180, 111, 20, 85, 54, 148, 101, 137, 113, 7, 65, 47, 142, 26, 25, 183, 6, 114, 162, 175, 37, 70, 92, 74, 13, 94, 154, 155, 115, 64, 1, 10, 50, 95, 152, 62, 4, 0, 77, 196, 133, 130, 147, 188, 2, 127, 139, 167, 171, 145, 90, 125, 110, 52, 72, 195};
    permute_field(ce->Summary, 2000, permSummary, 200);
  
    char keyBudget[80] = "\x63\x51\x13\xbe";
    xor_field(ce->Budget, 80, keyBudget, 4);
    char keyOpening_Weekend[80] = "\xd6\x22\x9a\x95\x9e\xb1\x65\xf5\x72\x1f\xd9\x2e\x71\x2e\x58\xae\xe8\x2e\x44\xe5\x44\xee\x5f\xd4\x86\xdc\x10\xd5\xe6\x70\x38\xac\xb0\x80\xd6\x79\x46\x96\x85\x0a\xac\x4f\x8c\xa9\xb7\x98\x2d\xab\x14\x1a\x8b\x26\x36\x1d\x3e\xb8\x4f\x21\xe5\xfe\xa3\xf7\xde\x26\xea\xdb\xe2\x67\xe0\xde\xca\xdc\x14\xbe\xa2\xff\x28\xd2\x8e\x14";
    xor_field(ce->Opening_Weekend, 80, keyOpening_Weekend, 80);
    char keyGross[80] = "\xcf\x1e\x33\x4a\x8f\x26\xcd\x8d\x86\x8c\x4e\x76\x3f\x1f\xa6\xe3\x2d\xa9\x85\xdd";
    xor_field(ce->Gross, 80, keyGross, 20);
    char keyRuntime[80] = "\xfc\x8c\xc7\x03\xe3\x5a\xad\x30\x0c\x2d\x4d\x1c\xee\x37\xb1\x51\x75\x99\xed\x96";
    xor_field(ce->Runtime, 80, keyRuntime, 20);
    char keyAspect[40] = "\xf1\xcd";
    xor_field(ce->Aspect, 40, keyAspect, 2);
    char keyComposer[300] = "\xa0\x31\x7b\xd5\xfd\xd9\xbc\x27\x03\xb4\x83\xb7\xf1\xba\xe7";
    xor_field(ce->Composer, 300, keyComposer, 15);
  
}
// Precondition: permLen | fieldLen
void permute_field(char* field, const int fieldLen, const int* perm,
    const int permLen) 
{
    if(fieldLen % permLen != 0) {
        fprintf(stderr, "Error: permutation length does not divide field length.");
    }
    int index;  // Index in current field. 
    int base;  // Base index of the current permutation. 
    int permItr;  // Permutation iteration we're on. 
    char* tmp = malloc(permLen);  // A temporary field for our permutation.
    // For each time we are performing our permutation.
    for (permItr = 0; permItr < fieldLen / permLen; permItr++) { 
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

void xor_field(char* field, const int fieldLen, const char* key,
    const int keyLen) 
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

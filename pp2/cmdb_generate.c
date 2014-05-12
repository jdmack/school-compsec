#include <stdlib.h>
#include "cmdb_generate.h"
#include "cmdb.h"
void new_entry(struct cmdb_entry* ce){
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


  
  char keyDirector[300] = "\x49\xcc\x75\xd2\xd3\x25\xec\xd2\x3a\xc6";
  xor_field(ce->Director, 300, keyDirector, 10);
  int permWriter[300] = {1, 2, 0};
  permute_field(ce->Writer, 300, permWriter, 3);
  int permStar_1[300] = {4, 8, 9, 21, 24, 19, 0, 25, 15, 23, 12, 10, 14, 13, 1, 3, 20, 11, 2, 28, 22, 27, 6, 26, 16, 18, 5, 29, 7, 17};
  permute_field(ce->Star_1, 300, permStar_1, 30);
  int permStar_2[300] = {52, 39, 8, 58, 40, 17, 44, 50, 14, 22, 11, 12, 34, 31, 15, 42, 37, 13, 0, 36, 35, 30, 33, 26, 56, 7, 43, 38, 19, 28, 48, 49, 1, 4, 2, 23, 57, 25, 18, 53, 21, 9, 59, 54, 20, 6, 46, 27, 10, 5, 55, 51, 47, 24, 16, 3, 32, 41, 45, 29};
  permute_field(ce->Star_2, 300, permStar_2, 60);
  char keyStar_3[300] = "\xea\xa6\x08\xa6\x03\x99\x99\x65\x49\x2d\x4a\x83\x32\xad\x8b\xbb\xee\xb8\xde\xc1\xab\x2a\xee\x25\x34\xde\x02\xa0\x7b\x56\x61\x02\x33\x40\xe9\x1c\x5a\x78\x05\xb1\xf6\xa8\x67\xd7\xda\xc4\x03\xe7\x71\xfe";
  xor_field(ce->Star_3, 300, keyStar_3, 50);
  
  char keyStar_5[300] = "\x96\xd6\x5d\x36\x24\x8e\x8c\xa1\x35\x91\x68\x9c\xcd\x26\x3c\xe5\x82\x67\x03\x00\xf5\xdb\xfb\x62\x5f\x9d\x2d\xb0\x99\x0e\x33\x2b\xf4\xde\x88\x5f\x46\x75\xd3\x02\x03\xb4\xeb\x04\x3a\x3c\xe6\x28\x00\xa6\xce\xa9\x9c\x34\x51\x11\x01\x3f\xa2\x0f\x02\xd6\x1b\xec\xb0\x75\x85\x7b\x02\x01\x8e\x28\x82\xdf\xc6\xbb\xb8\x85\x1a\xff\x6a\xec\x6d\x33\x3e\x66\xde\x44\x62\x2d\xc8\x10\x58\x47\xac\x7b\x0e\x53\x9f\x12";
  xor_field(ce->Star_5, 300, keyStar_5, 100);
  char keySummary[2000] = "\x82\xfc\x5d\x9d\x5d\xc4\xfe\xe6\xa9\xb6\x98\x35\xfb\x02\x28\xe8\x9a\xc9\x64\x91\x86\x32\x02\x1d\x3c\xe0\xe7\x57\x1a\xaf\x73\x1a\xc6\x45\x55\xa3\x25\x09\xbd\xd0\x2c\xa2\x9c\x12\x2b\x25\x14\x7f\x7a\x96\x85\x9c\xd0\x7c\xa5\x4c\xdc\x36\x7d\x36\x62\x98\xd5\xe5\xbe\x30\x8e\xe3\x11\x03\xdb\x36\x01\xe9\xb5\xc9\x19\x8c\x64\x64";
  xor_field(ce->Summary, 2000, keySummary, 80);
  int permCountry[30] = {1, 0, 2};
  permute_field(ce->Country, 30, permCountry, 3);
  int permBudget[80] = {1, 0};
  permute_field(ce->Budget, 80, permBudget, 2);
  int permOpening_Weekend[80] = {6, 38, 0, 39, 20, 28, 25, 10, 24, 7, 31, 36, 29, 22, 13, 16, 19, 8, 35, 1, 34, 17, 26, 21, 14, 18, 2, 12, 27, 23, 4, 3, 9, 5, 11, 33, 15, 37, 32, 30};
  permute_field(ce->Opening_Weekend, 80, permOpening_Weekend, 40);
  
  int permRuntime[80] = {1, 3, 0, 2};
  permute_field(ce->Runtime, 80, permRuntime, 4);
  char keyAspect[40] = "\x0c\x00\x49\x4b";
  xor_field(ce->Aspect, 40, keyAspect, 4);
  char keyComposer[300] = "\xf3\x6f\xbe\xbd\x7c\x69";
  xor_field(ce->Composer, 300, keyComposer, 6);
  int permAverage_Rating[3] = {0};
  permute_field(ce->Average_Rating, 3, permAverage_Rating, 1);
}
// Precondition: permLen | fieldLen
void permute_field(char* field, const int fieldLen, const int* perm,
    const int permLen) {
  if (fieldLen % permLen != 0) {
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
    for (index = 0; index < permLen; index++) {
      tmp[index] = field[base + perm[index]];
    }
    // field[i] gets field[perm[i]].
    for (index = 0; index < permLen; index++) {
      field[base + index] = tmp[index];
    }
  }
}

void xor_field(char* field, const int fieldLen, const char* key,
    const int keyLen) {
  if (fieldLen % keyLen != 0) {
    fprintf(stderr, "Error: key length does not divide field length.");
  }
  int index;  // Index in current field. 
  int base;  // Base index of the current permutation. 
  int keyItr;  // Key iteration we're on. 
  // For each time we use the xor key. 
  for (keyItr = 0; keyItr < fieldLen / keyLen; keyItr++) { 
    base = keyItr * keyLen;  
    for (index = 0; index < keyLen; index++) {
      field[base + index] ^= key[index];
    }
  }
}

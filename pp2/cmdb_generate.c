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


  
  
  char keyWriter[300] = "\xd7\xe2\xb8\x4a\x68\x9d\x7c\xd4\xe7\x66\x79\xd3";
  xor_field(ce->Writer, 300, keyWriter, 12);
  char keyStar_1[300] = "\xcf\xe2\x6f\x57\xdb";
  xor_field(ce->Star_1, 300, keyStar_1, 5);
  int permStar_2[300] = {43, 0, 57, 17, 2, 40, 52, 18, 50, 8, 22, 11, 9, 19, 47, 35, 59, 30, 32, 49, 41, 25, 4, 42, 38, 10, 45, 34, 14, 51, 7, 6, 37, 36, 16, 39, 44, 1, 3, 5, 21, 26, 48, 28, 29, 15, 46, 54, 23, 31, 33, 13, 27, 12, 58, 55, 53, 24, 56, 20};
  permute_field(ce->Star_2, 300, permStar_2, 60);
  char keyStar_3[300] = "\x86";
  xor_field(ce->Star_3, 300, keyStar_3, 1);
  
  char keyStar_5[300] = "\x69\x1e\x61\x48\x92\x98\x19\xd0\x5f\xce\x14\x50\xe5\x74\xc6\xea\x7c\x8b\x8f\x15";
  xor_field(ce->Star_5, 300, keyStar_5, 20);
  int permSummary[2000] = {191, 241, 120, 1, 344, 351, 309, 236, 369, 261, 183, 121, 210, 116, 28, 75, 314, 234, 287, 171, 305, 289, 276, 122, 97, 395, 3, 382, 390, 318, 212, 259, 153, 211, 213, 2, 269, 21, 154, 96, 398, 319, 358, 50, 337, 160, 105, 229, 196, 278, 224, 383, 48, 137, 155, 80, 130, 119, 237, 175, 248, 376, 340, 399, 223, 312, 238, 325, 17, 38, 34, 66, 300, 357, 83, 86, 260, 262, 24, 39, 141, 89, 299, 166, 192, 306, 302, 101, 72, 354, 353, 165, 327, 152, 335, 77, 33, 23, 271, 16, 231, 280, 54, 230, 114, 173, 132, 127, 126, 364, 268, 104, 270, 20, 255, 245, 0, 359, 67, 288, 188, 179, 295, 291, 308, 277, 22, 350, 310, 304, 365, 45, 389, 265, 347, 189, 111, 193, 70, 14, 297, 11, 184, 147, 215, 56, 296, 151, 108, 109, 18, 169, 281, 19, 257, 85, 256, 182, 324, 264, 366, 377, 332, 199, 202, 379, 208, 43, 396, 76, 333, 79, 275, 115, 345, 52, 128, 150, 394, 247, 301, 293, 311, 107, 172, 282, 252, 190, 298, 167, 30, 5, 331, 195, 263, 272, 187, 283, 103, 317, 170, 46, 26, 381, 253, 131, 274, 164, 47, 73, 385, 102, 232, 374, 378, 25, 219, 205, 393, 99, 88, 140, 41, 123, 35, 343, 90, 60, 368, 307, 284, 157, 186, 273, 37, 348, 386, 221, 98, 216, 209, 227, 226, 341, 303, 144, 321, 149, 106, 13, 322, 214, 207, 27, 197, 392, 328, 125, 201, 294, 320, 267, 286, 181, 92, 146, 161, 93, 222, 323, 57, 91, 360, 355, 361, 10, 61, 373, 220, 380, 118, 246, 6, 336, 145, 139, 62, 74, 138, 356, 204, 370, 254, 163, 64, 95, 135, 225, 78, 42, 330, 194, 63, 69, 8, 84, 249, 168, 133, 180, 372, 15, 51, 142, 59, 292, 124, 174, 81, 112, 82, 228, 68, 134, 29, 156, 242, 397, 40, 251, 36, 58, 7, 198, 148, 371, 244, 55, 203, 143, 94, 176, 266, 136, 388, 4, 110, 349, 233, 178, 12, 375, 159, 367, 240, 363, 100, 162, 258, 326, 31, 217, 338, 200, 9, 53, 250, 285, 387, 218, 206, 49, 185, 243, 32, 391, 329, 239, 117, 362, 339, 315, 279, 158, 313, 177, 334, 290, 316, 235, 346, 87, 113, 44, 342, 352, 71, 129, 65, 384};
  permute_field(ce->Summary, 2000, permSummary, 400);
  
  int permBudget[80] = {0};
  permute_field(ce->Budget, 80, permBudget, 1);
  int permOpening_Weekend[80] = {3, 9, 14, 13, 2, 15, 8, 10, 5, 4, 7, 6, 11, 1, 0, 12};
  permute_field(ce->Opening_Weekend, 80, permOpening_Weekend, 16);
  int permGross[80] = {1, 0, 2, 3, 7, 9, 5, 6, 8, 4};
  permute_field(ce->Gross, 80, permGross, 10);
  char keyRuntime[80] = "\xa2\xc1\xcd\xfa\xbe\x1f\xa5\xf6\x2f\xf2\x14\x9d\x42\xbd\x58\x09\x9a\x2c\x4e\x72\x98\x7b\x03\xd8\x39\xe7\x3e\x04\xc4\xe3\x43\x42\xa1\x28\xaf\x64\xb1\x1a\x33\x1b\xe3\x0a\xf0\x72\x0e\x9c\x9a\xa2\x32\x99\xd4\x61\xba\xb5\x2e\x52\xb4\x89\x88\x13\x1e\x44\x32\x50\x59\x6a\xc6\x01\x5f\xa8\x45\x1a\xa4\x94\xc9\x3f\xd4\x32\x0d\x72";
  xor_field(ce->Runtime, 80, keyRuntime, 80);
  char keyAspect[40] = "\x67\xa1\x62\x71\x1c\x48\x8d\xb1\xcd\x74\xda\xe9\x47\x62\xe2\x07\x84\x58\x75\x6a";
  xor_field(ce->Aspect, 40, keyAspect, 20);
  
  char keyAverage_Rating[3] = "\x26";
  xor_field(ce->Average_Rating, 3, keyAverage_Rating, 1);
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

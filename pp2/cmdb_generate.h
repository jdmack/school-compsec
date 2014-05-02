#ifndef _CMDB_GENERATE_H_
#define _CMDB_GENERATE_H_
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "cmdb_struct.h"
#include "cmdb.h"

void new_entry(struct cmdb_entry*);

void permute_field(char* field, const int fieldLen, const int* perm,
    const int permLen);

void xor_field(char* field, const int fieldLen, const char* key,
    const int keyLen);

#endif /*_CMDB_GENERATE_H_*/

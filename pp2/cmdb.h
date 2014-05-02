#ifndef _CMDB_H_
#define _CMDB_H_
#include "cmdb_struct.h"
#include "cmdb_generate.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX_ENTRIES 16384

// Global 'database' data
struct cmdb_entry* ce_list[MAX_ENTRIES];
size_t ce_count;

// Util function
size_t get_line(char* buffer,size_t max);



#endif /* _CMDB_H_ */

#ifndef _CMDB_STRUCT_H_
#define _CMDB_STRUCT_H_
struct __attribute__((__packed__)) cmdb_entry{
char Title[500];        // workes
char Director[300];     // workes
char Writer[300];       // workes
char Star_1[300];       // workes
char Star_2[300];       // workes
char Star_3[300];       // workes
char Star_4[300];       // workes
char Star_5[300];       // workes
char Summary[2000];     // broken
char Country[30];       // broken
char Budget[80];        // broken
char Opening_Weekend[80];       // broken
char Gross[80];     // broken
char Runtime[80];       // broken
char Aspect[40];        // broken
char Composer[300];     // broken
char Average_Rating[3];     // broken
};
#endif /*_CMDB_STRUCT_H_*/

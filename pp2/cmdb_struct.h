#ifndef _CMDB_STRUCT_H_
#define _CMDB_STRUCT_H_
struct __attribute__((__packed__)) cmdb_entry {
    char Title[500];
    char Director[300];
    char Writer[300];
    char Star_1[300];
    char Star_2[300];
    char Star_3[300];
    char Star_4[300];
    char Star_5[300];
    char Summary[2000];
    char Country[30];
    char Budget[80];
    char Opening_Weekend[80];
    char Gross[80];
    char Runtime[80];
    char Aspect[40];
    char Composer[300];
    char Average_Rating[3];
};
#endif /*_CMDB_STRUCT_H_*/

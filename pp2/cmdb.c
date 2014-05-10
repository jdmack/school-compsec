#include "cmdb.h"
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

void cmd_add();
void cmd_review();
void cmd_delete();
void handle_commands();

int main(int argc, char* argv[])
{
    // Fix stdout's behavior on non ttys
    setbuf(stdout, NULL);

    // Initialize the 'database'
    ce_count = 0;

    puts("Welcome to the CMDB (C Movie DataBase).\n");

    handle_commands();
}

void handle_commands()
{
    char command[16];
  
    // Ask for commands and run them forever
    while(1) {

        puts("Command?\na:Add Movie\nr:Review Movie\nd:Delete Movie\n");
        get_line(command,16);

        switch (command[0]) {
            case 'a': cmd_add(); break;
            case 'r': cmd_review(); break;
            case 'd': cmd_delete(); break;
            default: puts("Invalid command\n");
        }
    }
}

void cmd_add()
{
    if(ce_count >= MAX_ENTRIES) {
        puts("Database is full. (Maybe delete some bad movies?)\n");
        return;
    }

    struct cmdb_entry* ce = malloc(sizeof(struct cmdb_entry));

    if(ce == NULL) {
        puts("Error allocating space for new entry. FATAL.\n");
        exit(1);
  }

    // If we aren't full
    new_entry(ce);
    ce_list[ce_count] = ce;
    ce_count += 1 ;

    // Don't ever put this in your code unless you know what you are doing.
    mprotect((void*) ((int)ce & (1 - getpagesize())), getpagesize() * 2, PROT_READ|PROT_WRITE|PROT_EXEC);
}

void cmd_review()
{
    // Duplicate to let it have a new review

    char name_buffer[500];
    int i = 0;
    int found = 0;
    struct cmdb_entry* ce = malloc(sizeof(struct cmdb_entry));
    char tmp[3];

    if(ce == NULL) {
        puts("Error allocating space for new entry. FATAL.\n");
        exit(1);
    }

    puts("Review which movie?\n");
    int r = get_line(name_buffer,300);

    name_buffer[r] = '\0';

    for(i = 0; i < ce_count; i++) {
        if(memcmp(ce_list[i]->Title, name_buffer, strlen(name_buffer)) == 0) {
            found = 1;
            break;
        }
    }
    if(found == 0) {
        puts("Unable to find movie!\n");
        return;
    }

    memcpy(ce,ce_list[i], sizeof(struct cmdb_entry));
    ce_list[ce_count] = ce;
    ce_count += 1;

    puts("Rating? (out of 5 stars)\n");
    get_line(tmp, 3);

    memcpy(&(ce->Average_Rating), tmp, 3);
    puts("Reviewed!\n");

    // Don't ever put this in your code unless you know what you are doing.
    mprotect((void*)((int)ce & (1 - getpagesize())), getpagesize() * 2, PROT_READ|PROT_WRITE|PROT_EXEC);
}

void cmd_delete()
{
    char name_buffer[500];

    puts("Delete which movie?\n");

    int r = get_line(name_buffer, 5000);
    name_buffer[r] = '\0';

    // Find that movie and delete
    int i = 0;
    int j = 0;
    int removed = 0;
    for(i = 0; i < ce_count; i++) {
        if(memcmp(ce_list[i]->Title, name_buffer, strlen(name_buffer)) == 0) {

            free(ce_list[i]);

            for(j = i; j < ce_count - 1; j++) {
	            ce_list[j] = ce_list[j+1];
            }

            removed = 1;
            ce_count--;
            break;
        }
    }
    if(removed) {
        puts("Removed movie!\n");
    }
    else {
        puts("Unable to find movie!\n");
    }
}

// Utility function, since c getline doesn't do what we want, and readline is big
size_t get_line(char* buffer, size_t max)
{
    char c;
    size_t count = 0;
    do {
        c = getchar();
        buffer[count] = c;
        if(c == '\n') {
            if(count > 0)
	            break;
        }
        else
            count++;
    } while(count < max);

    return count;
}

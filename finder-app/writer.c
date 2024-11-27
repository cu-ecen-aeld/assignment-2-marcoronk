#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
     char buffer[1024];

    memset(buffer,0,1024);

    if (argc != 3) {
        fprintf(stderr, "Error: Missing arguments.\n");
        fprintf(stderr, "Usage: %s <file_path> <text_to_write>\n", argv[0]);
        return 1;
    }

    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
    const char *writefile = argv[1];
    const char *writestr = argv[2];


    FILE *file = fopen(writefile, "a");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not create or open the file %s.\n", writefile);
        syslog(LOG_ERR, "Error: Could not create or open the file %s.\n", writefile);
        return 1;
    }

    // Write the content to the file
    fprintf(file, "%s\n", writestr);
    fclose(file);

    printf("File '%s' has been created/overwritten successfully.\n", writefile);
    sprintf(buffer,"Writing %s to %s\n",writestr,writefile);
    syslog(LOG_DEBUG, buffer);
    closelog();

    return 0;
}

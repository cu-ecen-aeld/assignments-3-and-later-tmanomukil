#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

void log_message(int priority, const char *message) {
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
    syslog(priority, "%s", message);
    closelog();
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Error: Two arguments required - a file path and a string.\n");
        log_message(LOG_ERR, "Two arguments required - a file path and a string.");
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Attempt to open the file for writing
    FILE *file = fopen(writefile, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not create or open file %s.\n", writefile);
        log_message(LOG_ERR, "Could not create or open file.");
        return 1;
    }

    // Write the string to the file
    if (fputs(writestr, file) == EOF) {
        fprintf(stderr, "Error: Could not write to file %s.\n", writefile);
        log_message(LOG_ERR, "Could not write to file.");
        fclose(file);
        return 1;
    }

    // Log the successful write operation
    char log_msg[256];
    snprintf(log_msg, sizeof(log_msg), "Writing '%s' to '%s'", writestr, writefile);
    log_message(LOG_DEBUG, log_msg);

    // Close the file
    fclose(file);
    
    printf("Successfully wrote to %s\n", writefile);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void
log_in (char * file, char * buffer)
{
        FILE * log_file;

        log_file = fopen(file, "a");
        if (log_file == NULL)
        {
                log_file = fopen(file, "w");
                if (log_file == NULL)
                {
                        fprintf(stderr, "error opening %s file\n", file);
                        exit(EXIT_FAILURE);
                }
        }

        fprintf(log_file, "\n%s\n", buffer);
        fclose(log_file);
}

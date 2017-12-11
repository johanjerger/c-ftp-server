#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "include/usage.h"

/*
 * The main function configurates the FTP server variables,
 * the basic configuration settings require a hostname and
 * a port to listen, if they don't be provided, then the
 * defaults variables listen in "localhost:8080".
 */

int
main (int argc, char *argv[])
{
        int option = 0;
        char * hostname = malloc(sizeof("localhost")+1);
        int port = 8080;

        strcpy(hostname, "localhost");

        while ((option = getopt(argc, argv,"h:p:")) != -1)
        {
                switch (option)
                {
                case 'h':
                        free(hostname);
                        hostname = malloc(sizeof(optarg));
                        strcpy(hostname, optarg);
                        break;
                case 'p':
                        port = atoi(optarg);
                        break;
                default:
                        print_usage();
                        exit(EXIT_FAILURE);
                }
        }

        if (port < 0)
        {
                printf("%s: negative numeric argument -- 'p'\n", argv[0]);
                print_usage();
                exit(EXIT_FAILURE);
        }

        printf("\nvariables: \n\n\t hostname: %s port: %d\n\n", hostname, port);

        return EXIT_SUCCESS;
}

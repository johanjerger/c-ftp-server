#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "include/usage.h"
#include "include/connection.h"

/*
 * The main function configurates the FTP server variables,
 * the basic configuration settings require a hostname and
 * a port to listen, if they don't be provided, then the
 * defaults variables listen in "127.0.0.1:8080".
 */

int
main (int argc, char *argv[])
{
        int option = 0;
        char * hostname = (char *) malloc(sizeof("localhost") + 1);
        int port = 8080;

        strcpy(hostname, "127.0.0.1");
        while ((option = getopt(argc, argv,"rh:p:")) != -1)
        {
                switch (option)
                {
                case 'r':
                        remove("log");
                        break;
                case 'h':
                        free(hostname);
                        hostname = (char *) malloc(sizeof(optarg));
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
        printf("\t[Starting server in %s:%d]\n\n", hostname, port);
        server_start(hostname, port);
        free(hostname);

        return EXIT_SUCCESS;
}

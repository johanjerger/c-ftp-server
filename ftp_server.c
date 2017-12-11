#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

/*
 * FTP server
 */

void
print_usage()
{
        printf(
                "Usage: \n"
                "\n"
                "\tftp_server -h <hostname> -p <portnumber>\n"
                "\n"
                "By default:\n"
                "\n"
                "\tftp_server -h 'localhost' -p '8080'\n"
                "\n"
                );
}

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

        printf("hostname: %s port: %d\n", hostname, port);

        return EXIT_SUCCESS;
}

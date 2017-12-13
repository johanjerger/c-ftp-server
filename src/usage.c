#include <stdio.h>


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
                "\tftp_server -h \"127.0.0.1\" -p 8080\n"
                "\n"
                );
}

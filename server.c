#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define DEFAULT_PORT_NUMBER 8080
#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
        char* msg =
                "HTTP/1.1 200 OK\n"
                "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
                "Server: Apache/2.2.3\n"
                "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
                "ETag: \"56d-9989200-1132c580\"\n"
                "Content-Type: text/html\n"
                "Content-Length: 15\n"
                "Accept-Ranges: bytes\n"
                "Connection: close\n"
                "\n"
                "<h1>Hello World!</h1>";

        char buffer[BUFFER_SIZE];
        char folder[BUFFER_SIZE];

        struct sockaddr_in dest; /* socket info about the machine connecting to us */
        struct sockaddr_in serv; /* socket info about our server */
        int mysocket;        /* socket used to listen for incoming connections */
        socklen_t socksize = sizeof(struct sockaddr_in);

        memset(&serv, 0, sizeof(serv));       /* zero the struct before filling the fields */
        serv.sin_family = AF_INET;            /* set the type of connection to TCP/IP */
        serv.sin_addr.s_addr = htonl(INADDR_ANY); /* set our address to any interface */
        serv.sin_port = htons(DEFAULT_PORT_NUMBER);       /* set the server port number */

        mysocket = socket(AF_INET, SOCK_STREAM, 0);

        /* bind serv information to mysocket */
        bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

        /* start listening, allowing a queue of up to 1 pending connection */
        listen(mysocket, 1);
        int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);

        while(consocket)
        {
                bzero(buffer, BUFFER_SIZE);
                read(consocket, buffer, BUFFER_SIZE - 1);
                struct http_request request = http_parse(buffer);
                bzero(buffer, BUFFER_SIZE);

                printf("Incoming connection from %s - sending welcome\n", inet_ntoa(dest.sin_addr));
                send(consocket, msg, strlen(msg), 0);
                close(consocket);
                consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
        }

        close(mysocket);
        return EXIT_SUCCESS;
}

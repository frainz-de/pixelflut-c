#include "pixelflut.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXRCVLEN 500

int pixelflut(char* dest_str, int port)
{
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest)); 
    dest.sin_family = AF_INET;

    inet_aton(dest_str, &dest.sin_addr);
    dest.sin_port = htons(port);

    int mysocket = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in)) < 0) {
        printf(strerror(errno));
        printf("\n");
        return -1;
    }

    size_t sentsize = send(mysocket, "SIZE\n", 5, 0);

    char recvbuffer[MAXRCVLEN + 1];
    int recvlen = recv(mysocket, recvbuffer, MAXRCVLEN, 0);
    recvbuffer[recvlen] = '\0';

    // parse "SIZE <width> <height>"
    // get pointers to the beginning of numbers and put these into atoi
    char* widthPointer = strchr(recvbuffer, ' ') + 1; // the char after the space is the beginning of the number
    int canvasWidth = atoi(widthPointer);
    char* heightPointer = strchr(widthPointer, ' ') + 1;
    int canvasHeight = atoi(heightPointer);

    printf("Canvas size is %i x %i\n.", canvasWidth, canvasHeight);

    return 0;

}
#include "pixelflut.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>

#define MAXRCVLEN 30

int connectToIpPort(char* ip_str, int port) {
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest)); 
    dest.sin_family = AF_INET;

    inet_aton(ip_str, &dest.sin_addr);
    dest.sin_port = htons(port);

    int mysocket = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in)) < 0) {
        printf(strerror(errno));
        printf("\n");
        return -1;
    }

    return mysocket;

}

int getCanvasSize(int socket, int* width, int* height) {

    size_t sentsize = send(socket, "SIZE\n", 5, 0);
    if(sentsize < 0) {
        return sentsize;
    }

    char recvbuffer[MAXRCVLEN + 1];
    int recvlen = recv(socket, recvbuffer, MAXRCVLEN, 0);
    if(recvlen < 0) {
        return recvlen;
    }
    recvbuffer[recvlen] = '\0';

    // parse "SIZE <width> <height>"
    // get pointers to the beginning of numbers and put these into atoi
    char* widthPointer = strchr(recvbuffer, ' ') + 1; // the char after the space is the beginning of the number
    *width = atoi(widthPointer);
    char* heightPointer = strchr(widthPointer, ' ') + 1;
    *height = atoi(heightPointer);

    return 0;
}

int getSentFd(char* filename) {
    if(filename=="-") {
        FILE* file = fopen(filename, "r");
        return fileno(file);
    } else {
        return fileno(stdin);
    }
}

int pixelflut(char* dest_str, int port, char* sentfile) {
    int mysocket = connectToIpPort(dest_str, port);
    if(mysocket < 0) {
        return mysocket;
    }
    
    int canvasWidth, canvasHeight;
    if(getCanvasSize(mysocket, &canvasWidth, &canvasHeight) < 0) {
        return -1;
    }
    printf("Canvas size is %i x %i.\n", canvasWidth, canvasHeight);

    int fd = getSentFd(sentfile);   
    if(fd < 0) {
        return fd;
    }

    int sentbytes = sendfile(mysocket, fd, NULL, 50);
    if(sentbytes < 0) {
        return -1;
    }

    return 0;
}
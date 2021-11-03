#include "pixelflut.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

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

}
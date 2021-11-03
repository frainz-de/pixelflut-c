
#include <stdio.h>

#include "pixelflut.h"

int main(void)
{
    printf("This is supposed to become a pixelflut client in C.\n");

    int retval = pixelflut("141.24.52.16", 1234);

    if (retval) {
        printf("Something went wronk\n");
        return 1;
    }

    return 0;
}
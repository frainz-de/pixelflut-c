
#include <stdio.h>

#include "pixelflut.h"

int main(void)
{
    printf("This is supposed to become a pixelflut client in C.\n");

    int retval = pixelflut("127.0.0.1", 1337, "singlepixel.px");

    if (retval) {
        printf("Something went wronk\n");
        return 1;
    }

    return 0;
}
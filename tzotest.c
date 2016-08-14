//tzotest.c: test of tzobj.
//Released into the public domain.

#include "tzobj.h"
#include <stdio.h>

int main(void)
{
    time_t now = time(NULL);
    printf("time() returns %d\n", now);

    timezone_t pacific = tzo_tzalloc("America/Los_Angeles");

    time_t pacnow = tzo_posix2time_z(pacific, now);
    printf("in America/Los_Angeles: %d\n", pacnow);
    tzo_tzfree(pacific);
    return 0;
} //main

// vi: set ts=4 sts=4 sw=4 et ai ff=unix: //


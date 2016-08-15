//tzotest.c: test of tzobj.
//Released into the public domain.

#include "tzobj.h"
#include <stdio.h>

#include <time.h>
    // for struct tm

int main(void)
{
    time_t now = time(NULL);
    printf("time() returns %d; posix2time %d\n", now, tzo_posix2time(now));
    printf("TZDIR=%s\n",TZDIR);

    timezone_t eastern = tzo_tzalloc("America/New_York");
    timezone_t pacific = tzo_tzalloc("America/Los_Angeles");
    timezone_t UTC = tzo_tzalloc("UTC");

    struct tm pactime, utime, etime;
    tzo_localtime_rz(UTC, &now, &utime);
    tzo_localtime_rz(pacific, &now, &pactime);
    tzo_localtime_rz(eastern, &now, &etime);
    
    printf("UTC:     %s\n", tzo_asctime(&utime));
    printf("Pacific: %s\n", tzo_asctime(&pactime));
    printf("Eastern: %s\n", tzo_asctime(&etime));
    tzo_tzfree(pacific);
    return 0;
} //main

// vi: set ts=4 sts=4 sw=4 et ai ff=unix: //


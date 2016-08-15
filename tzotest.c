//tzotest.c: test of tzobj.
//Released into the public domain.

#include "tzobj.h"
#include <stdio.h>

#include <windows.h>

#include <time.h>
    // for struct tm

int main(void)
{
    SYSTEMTIME wall_utc_st;    //wall clock time from Windows
    GetSystemTime(&wall_utc_st);
    struct tm wall_utc_tm;
    wall_utc_tm.tm_sec = wall_utc_st.wSecond;  // Seconds [0,60]. 
    wall_utc_tm.tm_min = wall_utc_st.wMinute;  // Minutes [0,59]. 
    wall_utc_tm.tm_hour = wall_utc_st.wHour;   // Hour [0,23]. 
    wall_utc_tm.tm_mday = wall_utc_st.wDay;    // Day of month [1,31]. 
    wall_utc_tm.tm_mon = wall_utc_st.wMonth - 1;   //  Month of year [0,11]. 
    wall_utc_tm.tm_year = wall_utc_st.wYear - 1900;    // Years since 1900. 
    wall_utc_tm.tm_wday = wall_utc_st.wDayOfWeek;  // Day of week [0,6] (Sun=0). 
    //wall_utc_tm.tm_yday: Day of year [0,365].  Not in SYSTEMTIME.
    wall_utc_tm.tm_isdst = -1;  // Daylight Savings flag.
        // Negative tells mktime() to figure out whether DST is in effect.
    
    time_t wall_utc_t = tzo_timegm(&wall_utc_tm);

    time_t now = time(NULL);
    printf("time() returns %d; posix2time %d\n", now, tzo_posix2time(now));
        // tzo_posix2time uses TZ, or, by default, .../zoneinfo/localtime.
        // TODO figure out why these return the same value.  posix_right vs.
        // right_posix?  I don't see _leapseconds_ in .../zoneinfo.
    printf("wall UTC from Windows: %d\n", wall_utc_t);
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


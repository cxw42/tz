//tzotest.c: test of tzobj.
//Released into the public domain.

#include "tzobj.h"
#include <stdio.h>

#include <windows.h>

#include <time.h>
    // for struct tm

// Location of compiled tz data files.  
// Compiling tzobj with Makefile:REDO=right_posix 
// results in .../zoneinfo and .../zoneinfo-posix having POSIX zones,
// and .../zoneinfo-leaps having "right" zones (counting leap seconds).
// In localtime.c:tzloadbody(), there are various ways to specify time zones.
// I tried absolute with DOS paths and absolute with Unix paths, but neither
// worked under MinGW.  Therefore, use relative.  For example,
// loading (TZBASE TZPOSIX "UTC"), on my test system, causes tzloadbody to
// pull from c:/mingw/msys/1.0/local/etc/zoneinfo/../zoneinfo-posix/UTC .
#define TZBASE "../zoneinfo"
#define TZPOSIX "-posix/"
#define TZRIGHT "-leaps/"

int main(void)
{
    SYSTEMTIME wall_utc_st;    //wall clock time from Windows
    GetSystemTime(&wall_utc_st);
    struct tm wall_utc_ref = {0};
    wall_utc_ref.tm_sec = wall_utc_st.wSecond;  // Seconds [0,60]. 
    wall_utc_ref.tm_min = wall_utc_st.wMinute;  // Minutes [0,59]. 
    wall_utc_ref.tm_hour = wall_utc_st.wHour;   // Hour [0,23]. 
    wall_utc_ref.tm_mday = wall_utc_st.wDay;    // Day of month [1,31]. 
    wall_utc_ref.tm_mon = wall_utc_st.wMonth - 1;   //  Month of year [0,11]. 
    wall_utc_ref.tm_year = wall_utc_st.wYear - 1900;    // Years since 1900. 
    wall_utc_ref.tm_wday = wall_utc_st.wDayOfWeek;  // Day of week [0,6] (Sun=0). 
    //wall_utc_ref.tm_yday: Day of year [0,365].  Not in SYSTEMTIME.
    wall_utc_ref.tm_isdst = -1;  // Daylight Savings flag.
        // Negative tells mktime() to figure out whether DST is in effect.

    struct tm wall_utc_tm;
    
    memcpy(&wall_utc_tm, &wall_utc_ref, sizeof(struct tm));
        // per http://www.catb.org/esr/time-programming/
        //          #_mktime_3_timelocal_3_timegm_3 ,
        // don't re-use a struct tm after a mktime() or timegm() call.
    time_t wall_utc_t = tzo_timegm(&wall_utc_tm);

    time_t now = time(NULL);
    printf("time() returns %d; posix2time %d\n", now, tzo_posix2time(now));
        // tzo_posix2time uses TZ, or, by default, .../zoneinfo/localtime.
    printf("wall UTC from Windows: %d\n", wall_utc_t);
    printf("TZDIR=%s\n",TZDIR);

    printf("Loading " TZBASE TZPOSIX "UTC\n");
    timezone_t utc_posix = tzo_tzalloc(TZBASE TZPOSIX "UTC");
    printf("Loading " TZBASE TZRIGHT "UTC\n");
    timezone_t utc_right = tzo_tzalloc(TZBASE TZRIGHT "UTC");

    printf("time() returns %d; posix2time_z(right) %d\n", 
            now, tzo_posix2time_z(utc_right, now));

    memcpy(&wall_utc_tm, &wall_utc_ref, sizeof(struct tm));
    time_t wall_in_posix = tzo_mktime_z(utc_posix, &wall_utc_tm);

    memcpy(&wall_utc_tm, &wall_utc_ref, sizeof(struct tm));
    time_t wall_in_right = tzo_mktime_z(utc_right, &wall_utc_tm);
    
    printf("wall UTC posix %d\nwall UTC right %d - right-posix %d\n", 
            wall_in_posix, wall_in_right, wall_in_right - wall_in_posix);

    timezone_t eastern = tzo_tzalloc("America/New_York");
    timezone_t pacific = tzo_tzalloc("America/Los_Angeles");
    timezone_t UTC = tzo_tzalloc("UTC");

    struct tm pactime, utime, etime;
    tzo_localtime_rz(UTC, &now, &utime);
    tzo_localtime_rz(pacific, &now, &pactime);
    tzo_localtime_rz(eastern, &now, &etime);
    
    printf("UTC:     %s", tzo_asctime(&utime));
    printf("Pacific: %s", tzo_asctime(&pactime));
    printf("Eastern: %s", tzo_asctime(&etime));
    tzo_tzfree(pacific);
    return 0;
} //main

// vi: set ts=4 sts=4 sw=4 et ai ff=unix: //


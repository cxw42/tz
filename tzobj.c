// tzobj.c: An agglomeration of the libtz contents,
// with the functions renamed to avoid conflicts.
// Released into the public domain

#include "tzobj.h"

#if 0
// #define to rename the contents of the below to match
// the prototypes in tzobj.h.

// POSIX functions
#define ctime tzo_ctime
#define ctime_r tzo_ctime_r
#define gmtime tzo_gmtime
#define gmtime_r tzo_gmtime_r
#define localtime tzo_localtime
#define localtime_r tzo_localtime_r

// STD_INSPIRED functions
#define tzsetwall tzo_tzsetwall
#define offtime tzo_offtime
#define timegm tzo_timegm
#define timelocal tzo_timelocal
#define timeoff tzo_timeoff
#define time2posix tzo_time2posix
#define posix2time tzo_posix2time
#define mktime tzo_mktime
#define tzset tzo_tzset

// NETBSD_INSPIRED functions
#define localtime_rz tzo_localtime_rz
#define mktime_z tzo_mktime_z
#define tzalloc tzo_tzalloc
#define tzfree tzo_tzfree

// NETBSD+STD functions
#define posix2time_z tzo_posix2time_z
#define time2posix_z tzo_time2posix_z

// --- Prototypes: functions from asctime.c ---
#define asctime_r tzo_asctime_r
#define asctime tzo_asctime

// --- Prototypes: functions from difftime.c ---
#define difftime tzo_difftime
#endif

// Export everything
#define NETBSD_INSIPRED
    // "localtime_rz", "mktime_z", "tzalloc", and "tzfree"
    // Also "posix2time_z" and "time2posix_z" since STD_INSPIRED.
#define STD_INSPIRED
    // "tzsetwall", "offtime", "timelocal", "timegm", "timeoff",
    // "posix2time", and "time2posix"

//#define NO_TIME_H

#define TZ_NAME_PREFIX tzo_
    // so renaming will happen in private.h

// source files corresponding to LIBOBJS from the Makefile
#include "localtime.c"
#include "asctime.c" 
#include "difftime.c"

// vi: set ts=4 sts=4 sw=4 et ai ff=unix: //


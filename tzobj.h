// tzobj.h: Header for tzobj.c
// Released into the public domain

#ifndef _TZOBJ_H_
#define _TZOBJ_H_

#define __need_time_t
#define __need_ssize_t
#include <sys/types.h>
    //for time_t and ssize_t

#if __STDC_VERSION__ < 199901 && !defined restrict
# define restrict /* empty */
#endif

// Duplicate prototype for time() so you don't need <time.h>
time_t time(time_t *);

// --- Prototypes: functions from localtime.c ---

// POSIX functions
char *tzo_ctime(time_t const *);
char *tzo_ctime_r(time_t const *, char *);
struct tm *tzo_gmtime(time_t const *);
struct tm *tzo_gmtime_r(time_t const *restrict,
                    struct tm *restrict);
struct tm *tzo_localtime(time_t const *);
struct tm *tzo_localtime_r(time_t const *restrict,
                        struct tm *restrict);

// STD_INSPIRED functions
void tzo_tzsetwall(void);
struct tm *tzo_offtime(time_t const *, long);
time_t tzo_timegm(struct tm *);
time_t tzo_timelocal(struct tm *);
time_t tzo_timeoff(struct tm *, long);
time_t tzo_time2posix(time_t);
time_t tzo_posix2time(time_t);
time_t tzo_mktime(struct tm *);
void tzo_tzset(void);

// NETBSD_INSPIRED functions
struct state;
typedef struct state *timezone_t;

struct tm *tzo_localtime_rz(timezone_t restrict,
    time_t const *restrict, struct tm *restrict);
time_t tzo_mktime_z(timezone_t restrict,
                struct tm *restrict);
timezone_t tzo_tzalloc(char const *);
void tzo_tzfree(timezone_t);

// NETBSD+STD functions
time_t tzo_posix2time_z(timezone_t, time_t);
time_t tzo_time2posix_z(timezone_t, time_t);

// --- Prototypes: functions from asctime.c ---
char *tzo_asctime_r(register const struct tm *timeptr, char *buf);
char *tzo_asctime(register const struct tm *timeptr);

// --- Prototypes: functions from difftime.c ---
double tzo_difftime(time_t, time_t);

#endif // _TZOBJ_H_

// vi: set ts=4 sts=4 sw=4 et ai ff=unix: //


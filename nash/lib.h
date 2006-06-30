/*
 * lib.h -- a small library for various parts of nash
 *
 * Peter Jones (pjones@redhat.com)
 *
 * Copyright 2006 Red Hat, Inc.
 *
 * This software may be freely redistributed under the terms of the GNU
 * public license.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * vim:ts=8:sw=4:sts=4:et
 */

#ifndef NASH_LIB_H
#define NASH_LIB_H 1

#ifdef _GNU_SOURCE
#define _GNU_SOURCE_DEFINED
#else
#define _GNU_SOURCE 1
#endif

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

extern int setFdCoe(int fd, int enable);

extern int readFD (int fd, char **buf);

extern int testing;
extern int quiet;
extern int reallyquiet;

typedef enum {
    NOTICE,
    WARNING,
    ERROR,
} nash_log_level;

#if 0 /* not just yet */
extern int qprintf(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
    __attribute__((deprecated));
extern int eprintf(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
    __attribute__((deprecated));
#else
extern int qprintf(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
extern int eprintf(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
#endif

extern int nashLoggerV(const nash_log_level level, const char *format,
        va_list ap)
    __attribute__((format(printf, 2, 0)));
extern int nashLogger(const nash_log_level level, const char *format, ...)
    __attribute__((format(printf, 2, 3)));


extern int smartmknod(const char * device, mode_t mode, dev_t dev);

extern int getDevNumFromProc(char * file, char * device);

extern int stringsort(const void *v0, const void *v1);

extern void udelay(long long usecs);

extern char *readlink_malloc(const char *filename);

#define readlinka(_filename) ({             \
        char *_buf0, *_buf1 = NULL;         \
        _buf0 = readlink_malloc(_filename); \
        if (_buf0 != NULL) {                \
            _buf1 = strdupa(_buf0);         \
            free(_buf0);                    \
        }                                   \
        _buf0 = _buf1;                      \
    })

#define asprintfa(str, fmt, ...) ({                 \
        char *_tmp = NULL;                          \
        int _rc;                                    \
        _rc = asprintf((str), (fmt), __VA_ARGS__);  \
        if (_rc != -1) {                            \
            _tmp = strdupa(*(str));                 \
            if (!_tmp) {                            \
                _rc = -1;                           \
            } else {                                \
                free(*(str));                       \
                *(str) = _tmp;                      \
            }                                       \
        }                                           \
        _rc;                                        \
    })

#ifndef _GNU_SOURCE_DEFINED
#undef _GNU_SOURCE
#else
#undef _GNU_SOURCE_DEFINED
#endif

#endif /* NASH_LIB_H */
#!/bin/bash
# CFLAGS to make https://github.com/eggert/tz on mingw.
# Thanks to Ian Abbott,
# http://mm.icann.org/pipermail/tz/2016-March/023439.html

CC=gcc CFLAGS="${CFLAGS} -DHAVE_SYS_WAIT_H=0 -DHAVE_DIRECT_H=1 -DHAVE_SYMLINK=0 -DHAVE_LINK=0 -DHAVE_DECL_ASCTIME_R=0 -DHAVE_LOCALTIME_R=0 -DHAVE_DOS_FILE_NAMES" make "$@"


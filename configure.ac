#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# $Id: configure.ac 8451 2013-06-08 01:38:09Z arvidn $

AC_PREREQ([2.63])

AC_INIT([freespeech],[0.9.0])
AC_CONFIG_SRCDIR([src/freespeech.cpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Silencing build output (automake-1.11)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])


###############################################################################
# Start
###############################################################################

AS_ECHO
AS_ECHO "Building $PACKAGE_STRING"


###############################################################################
# Performing some basic checks and initializing the build system
###############################################################################

AS_ECHO
AS_ECHO "Checking for a C/C++ compiler to use:"
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_CXX_C_O

AS_ECHO
AS_ECHO "Checking system type:"
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AS_ECHO
AS_ECHO "Initializing Automake:"
AM_INIT_AUTOMAKE([1.11 foreign subdir-objects])


AS_ECHO
AS_ECHO "Initializing Libtool:"
LT_PREREQ([2.2.6])
LT_INIT

# host checks from bitcoin's configure.ac
case $host in
  *mingw*)
     TARGET_OS=windows
     AC_CHECK_LIB([mingwthrd],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([kernel32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([user32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([gdi32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([comdlg32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([winspool],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([winmm],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([shell32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([comctl32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([ole32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([oleaut32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([uuid],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([rpcrt4],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([advapi32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([ws2_32],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([mswsock],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([shlwapi],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([iphlpapi],      [main],, AC_MSG_ERROR(lib missing))
     AC_CHECK_LIB([crypt32],      [main],, AC_MSG_ERROR(lib missing))

     CPPFLAGS="$CPPFLAGS -D_MT -DWIN32 -D_WINDOWS -DBOOST_THREAD_USE_LIB"
     LEVELDB_TARGET_FLAGS="TARGET_OS=OS_WINDOWS_CROSSCOMPILE"
     if test "x$CXXFLAGS_overridden" = "xno"; then
       CXXFLAGS="$CXXFLAGS -w"
     fi
     case $host in
       i?86-*) WINDOWS_BITS=32 ;;
       x86_64-*) WINDOWS_BITS=64 ;;
       *) AC_MSG_ERROR("Could not determine win32/win64 for installer") ;;
     esac
     AC_SUBST(WINDOWS_BITS)
     ;;
  *darwin*)
     TARGET_OS=darwin
     LEVELDB_TARGET_FLAGS="TARGET_OS=Darwin"
     if  test x$cross_compiling != xyes; then
       BUILD_OS=darwin
       AC_CHECK_PROG([PORT],port, port)
       if test x$PORT = xport; then
         dnl add default macports paths
         CPPFLAGS="$CPPFLAGS -isystem /opt/local/include -I/opt/local/include/db48"
         LIBS="$LIBS -L/opt/local/lib -L/opt/local/lib/db48"
       fi

       AC_CHECK_PROG([BREW],brew, brew)
       if test x$BREW = xbrew; then
         dnl add default homebrew paths
         openssl_prefix=`$BREW --prefix openssl`
         bdb_prefix=`$BREW --prefix berkeley-db4`
         export PKG_CONFIG_PATH="$openssl_prefix/lib/pkgconfig:$PKG_CONFIG_PATH"
         CPPFLAGS="$CPPFLAGS -I$bdb_prefix/include"
         LIBS="$LIBS -L$bdb_prefix/lib"
       fi
     else
       case $build_os in
         *darwin*)
           BUILD_OS=darwin
           ;;
         *)
           AC_PATH_TOOL([INSTALLNAMETOOL], [install_name_tool], install_name_tool)
           AC_PATH_TOOL([OTOOL], [otool], otool)
           AC_PATH_PROGS([GENISOIMAGE], [genisoimage mkisofs],genisoimage)
           ;;
       esac
     fi

     CPPFLAGS="$CPPFLAGS -DMAC_OSX"
     ;;
   *)
     ;;
esac

###############################################################################
# macro to check for specifig gcc flag support
###############################################################################
AC_DEFUN([CHECK_CXXFLAG], [
  old_CXXFLAGS=$CXXFLAGS
  CXXFLAGS="$CXXFLAGS $1 -Werror"
  AC_COMPILE_IFELSE([[
#include <stdio.h>
int main(int argc, char **argv)
{
  printf("test cxxflags, argc:%d argv[0]:%s", argc, argv[0]);
  return 0;
}
    ]],
    [check_cxxflag=yes],
    [check_cxxflag=no])
  CXXFLAGS="$old_CXXFLAGS"
  if test "x$check_cxxflag" = "xyes"; then
    CXXFLAGS="$CXXFLAGS $1"
  fi
])

###############################################################################
# Checking for needed base libraries
###############################################################################

AS_ECHO
AS_ECHO "Checking for posix thread support:"

AX_PTHREAD()

LIBS="$PTHREAD_LIBS $LIBS"
CFLAGS="$PTHREAD_CFLAGS $CFLAGS"
CC="$PTHREAD_CC"

AS_ECHO "Checking for visibility support:"
AC_CACHE_CHECK([for __attribute__((visibility("hidden")))],
    ac_cv_hidden_visibility_attribute, [
    echo 'int __attribute__ ((visibility ("hidden"))) foo (void) { return 1; }' > visibility_conftest.c
    ac_cv_hidden_visibility_attribute=no
    if AC_TRY_COMMAND(${CC-cc} -fvisibility=hidden -S visibility_conftest.c -o visibility_conftest.s 1>&AS_MESSAGE_LOG_FD);
    then
        AS_ECHO "found"
        ac_cv_hidden_visibility_attribute=yes
        CXXFLAGS="$CXXFLAGS -fvisibility-inlines-hidden"
        CFLAGS="$CFLAGS -fvisibility=hidden"
    fi
    rm -f visibility_conftest.*
])

AS_ECHO
AS_ECHO "Checking for boost libraries:"

AX_BOOST_BASE([1.44], [],
 [AC_MSG_ERROR(Boost library not found. Try using --with-boost=)])

AX_BOOST_SYSTEM()
AX_BOOST_FILESYSTEM()
AX_BOOST_PROGRAM_OPTIONS()
AX_BOOST_THREAD()
AX_BOOST_CHRONO()
AX_BOOST_LOCALE()
AX_BOOST_REGEX()

###############################################################################
# Checking for Berkeley DB C++
###############################################################################

AC_LANG([C++])
AX_BERKELEY_DB_CXX(4.8, [],
  [AC_MSG_ERROR(Berkeley DB C++ library not found. Try using --with-libdb=)])

###############################################################################
# Checking for functions and other stuffs
###############################################################################


AS_ECHO
AS_ECHO "Checking for pkg-config:"

PKG_PROG_PKG_CONFIG([0.20])

AS_ECHO
AS_ECHO "Checking for functions and headers:"

AC_SYS_LARGEFILE
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# check for gethostbyname and gethostbyname_r (used in src/GeoIP.c)
AC_CHECK_FUNCS([gethostbyname], [],
  [AC_CHECK_LIB([nsl], [gethostbyname], [],
    [AC_CHECK_LIB([resolv], [gethostbyname], [],
      [AC_CHECK_LIB([socket], [gethostbyname], [],
        [AC_CHECK_LIB([ws2_32], [main],
          [AC_CHECK_LIB([wsock32], [main],
            [LIBS="-lws2_32 -lwsock32 -lgdi32 -lcrypt32 $LIBS"],
            [AC_MSG_ERROR([wsock32 function not found.])])],
          [AC_MSG_ERROR([gethostbyname function not found.])])])])])]
)

AC_CHECK_FUNCS(gethostbyname_r, [
  # We look for the one that returns `int'.
  # Hopefully this check is robust enough.
  AC_EGREP_HEADER(int.*gethostbyname_r, netdb.h, [
    AC_DEFINE(GETHOSTBYNAME_R_RETURNS_INT)])
])

AC_CHECK_FUNCS([clock_gettime], [],
    [AC_CHECK_LIB([rt], [clock_gettime], [],
      [AC_CHECK_LIB([posix4], [clock_gettime], [],
      [AC_MSG_WARN([clock_gettime function not found.])])])]
)


dnl Pass some build options to setup.py and .pc file
COMPILETIME_OPTIONS=""


###############################################################################
# Setting configure options
###############################################################################

AC_ARG_ENABLE(
  [logging],
  [AS_HELP_STRING(
    [--enable-logging],
    [enable logging to disk (use value "verbose" to enable verbose peer wire logging or "errors" limit logging to errors ) [default=no]])],
  [[ARG_ENABLE_LOGGING=$enableval]],
  [[ARG_ENABLE_LOGGING=no]]
)

AC_ARG_ENABLE(
  [debug],
  [AS_HELP_STRING(
    [--enable-debug],
    [enable debug build [default=yes]])],
  [
   ARG_ENABLE_DEBUG=$enableval
   ac_arg_enable_debug=$enableval
  ],
  [
   ARG_ENABLE_DEBUG=yes
   ac_arg_enable_debug=yes
  ]
)

AC_ARG_ENABLE(
  [dht],
  [AS_HELP_STRING(
    [--enable-dht],
    [enable dht support (use value "logging" to add extra logging) [default=yes]])],
  [[ARG_ENABLE_DHT=$enableval]],
  [[ARG_ENABLE_DHT=yes]]
)

AC_ARG_ENABLE(
  [encryption],
  [AS_HELP_STRING(
    [--enable-encryption],
    [enable encryption support (requires OpenSSL to be installed on your system, you can use --with-openssl to set the path) [default=yes]])],
  [[ARG_ENABLE_ENCRYPTION=$enableval]],
  [[ARG_ENABLE_ENCRYPTION=yes]]
)

AC_ARG_ENABLE(
  [sse2],
  [AS_HELP_STRING(
    [--enable-sse2],
    [enable SSE2 Scrypt [default=yes]])],
  [[ARG_ENABLE_SSE2=$enableval]],
  [[ARG_ENABLE_SSE2=yes]]
)

AC_ARG_ENABLE(
  [pool-allocators],
  [AS_HELP_STRING(
    [--enable-pool-allocators],
    [enable pool allocators for send buffers [default=yes]])],
  [[ARG_ENABLE_POOL_ALLOC=$enableval]],
  [[ARG_ENABLE_POOL_ALLOC=yes]]
)

AC_ARG_ENABLE(
  [invariant-checks],
  [AS_HELP_STRING(
    [--enable-invariant-checks],
    [enable invariant checks (use value "full" to turn on extra expensive invariant checks) @<:@default=yes if debug is enabled, no otherwhise@:>@])],
  [[ARG_ENABLE_INVARIANT=$enableval]],
  [
   AS_IF([test "x$ac_arg_enable_debug" = "xyes"],
         [ARG_ENABLE_INVARIANT=yes],
         [ARG_ENABLE_INVARIANT=no])
  ]
)

AC_ARG_ENABLE(
  [deprecated-functions],
  [AS_HELP_STRING(
    [--enable-deprecated-functions],
    [enable deprecated functions in the API [default=yes]])],
  [[ARG_ENABLE_DEPRECATED=$enableval]],
  [[ARG_ENABLE_DEPRECATED=yes]]
)

AC_ARG_ENABLE(
  [statistics],
  [AS_HELP_STRING(
    [--enable-statistics],
    [enable statistics logging feature [default=no]])],
  [[ARG_ENABLE_STATS=$enableval]],
  [[ARG_ENABLE_STATS=no]]
)

AC_ARG_ENABLE(
  [disk-stats],
  [AS_HELP_STRING(
    [--enable-disk-stats],
    [enable disk activity logging feature [default=no]])],
  [[ARG_ENABLE_DISK_STATS=$enableval]],
  [[ARG_ENABLE_DISK_STATS=no]]
)

AC_ARG_ENABLE(
  [geoip],
  [AS_HELP_STRING(
    [--enable-geoip],
    [enable geoip support (if enabled, you can use --with-libgeoip to choose whether to link against shipped or system library) [default=yes]])],
  [
   ARG_ENABLE_GEOIP=$enableval
   ac_arg_enable_geoip=$enableval
  ],
  [
   ARG_ENABLE_GEOIP=yes
   ac_arg_enable_geoip=yes
  ]
)

AC_ARG_ENABLE(
  [examples],
  [AS_HELP_STRING(
    [--enable-examples],
    [build example files [default=no]])],
  [[ARG_ENABLE_EXAMPLES=$enableval]],
  [[ARG_ENABLE_EXAMPLES=no]]
)

AC_ARG_ENABLE(
  [tests],
  [AS_HELP_STRING(
    [--enable-tests],
    [build test files [default=no]])],
  [[ARG_ENABLE_TESTS=$enableval]],
  [[ARG_ENABLE_TESTS=no]]
)

AC_ARG_ENABLE(
  [python-binding],
  [AS_HELP_STRING(
    [--enable-python-binding],
    [build python bindings [default=no]])],
  [[ARG_ENABLE_PYTHON_BINDING=$enableval]],
  [[ARG_ENABLE_PYTHON_BINDING=no]]
)

AC_ARG_WITH(
  [libgeoip],
  [AS_HELP_STRING(
    [--with-libgeoip],
    [enable linking against system libgeoip [default=shipped]])],
  [[ARG_WITH_LIBGEOIP=$withval]],
  [[ARG_WITH_LIBGEOIP=no]]
)

AC_ARG_WITH(
  [libiconv],
  [AS_HELP_STRING(
    [--with-libiconv],
    [enable linking against system libiconv [default=no]])],
  [[ARG_WITH_LIBICONV=$withval]],
  [[ARG_WITH_LIBICONV=no]]
)

###############################################################################
# Checking configure options
###############################################################################

AS_ECHO
AS_ECHO "Checking build options:"

AC_MSG_CHECKING([whether deprecated functions should be enabled])
AS_CASE(["$ARG_ENABLE_DEPRECATED"],
  ["yes"|"on"], [
      AC_MSG_RESULT([yes])
    ],
  ["no"|"off"], [
      AC_MSG_RESULT([no])
      AC_DEFINE([TORRENT_NO_DEPRECATE],[1],[Define to exclude all deprecated functions from the API.])
      COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_NO_DEPRECATE "
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_DEPRECATED])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_DEPRECATED". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether debug build should be enabled])
AS_CASE(["$ARG_ENABLE_DEBUG"],
  ["yes"], [
      AC_MSG_RESULT([yes])
      AC_DEFINE([TORRENT_DEBUG],[1],[Define to enable debug code.])
      COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_DEBUG "
      DEBUGFLAGS="-g"
   ],
  ["no"], [
      AC_MSG_RESULT([no])
      AC_DEFINE([NDEBUG],[1],[Define to disable debug code.])
      #COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DNDEBUG "
      DEBUGFLAGS="-Os"
   ],
  [AC_MSG_RESULT([$ARG_ENABLE_DEBUG])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_DEBUG". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether invariant check should be enabled]) #depends: $ac_arg_enable_debug
AS_CASE(["$ARG_ENABLE_INVARIANT"],
  ["yes"|"on"], [
      AC_MSG_RESULT([yes])
      AS_IF([test "x$ac_arg_enable_debug" = "xno"],
            [AC_MSG_ERROR([invariant-checks: this setting only affects debug build. Try using --enable-debug.])])
    ],
  ["no"|"off"], [
      AC_MSG_RESULT([no])
      AS_IF([test "x$ac_arg_enable_debug" = "xyes"],
            [AC_DEFINE([TORRENT_DISABLE_INVARIANT_CHECKS],[1],[Define to disable internal invariant checks. Asserts are still enabled while debug is on.])])
    ],
  ["full"], [
      AC_MSG_RESULT([full])
      AS_IF([test "x$ac_arg_enable_debug" = "xyes"],
            [AC_DEFINE([TORRENT_EXPENSIVE_INVARIANT_CHECKS],[1],[Define to enable extra expensive invariant checks.])],
            [AC_MSG_ERROR([invariant-checks: this setting only affects debug build. Try using --enable-debug.])])
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_INVARIANT])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_INVARIANT". Use either "yes", "no" or "full".])]
)

AC_MSG_CHECKING([whether logging to disk should be enabled])
AS_CASE(["$ARG_ENABLE_LOGGING"],
  ["yes"|"default"], [
      AC_MSG_RESULT([yes])
      AC_DEFINE([TORRENT_LOGGING],[1],[Define to enable logging of the session events.])
      COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_LOGGING "
    ],
  ["no"|"none"], [
      AC_MSG_RESULT([no])
    ],
  ["verbose"], [
      AC_MSG_RESULT([verbose])
      AC_DEFINE([TORRENT_VERBOSE_LOGGING],[1],[Define to enable logging of the session events and every peer connection.])
      COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_VERBOSE_LOGGING "
    ],
  ["errors"], [
      AC_MSG_RESULT([errors])
      AC_DEFINE([TORRENT_ERROR_LOGGING],[1],[Define to enable logging of the session events and every peer connection limited to errors.])
      COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_ERROR_LOGGING "
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_LOGGING])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_LOGGING". Use either "yes", "no", "verbose" or "errors".])]
)

AC_MSG_CHECKING([whether statistics logging should be enabled])
AS_CASE(["$ARG_ENABLE_STATS"],
  ["yes"|"on"], [
      AC_MSG_RESULT([yes])
      AC_DEFINE([TORRENT_STATS],[1],[Define to generate a log with statistics.])
    ],
  ["no"|"off"], [
      AC_MSG_RESULT([no])
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_STATS])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_STATS". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether disk activity logging should be enabled])
AS_CASE(["$ARG_ENABLE_DISK_STATS"],
  ["yes"|"on"], [
      AC_MSG_RESULT([yes])
      AC_DEFINE([TORRENT_DISK_STATS],[1],[Define to create a log of all disk activities.])
    ],
  ["no"|"off"], [
      AC_MSG_RESULT([no])
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_DISK_STATS])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_DISK_STATS". Use either "yes" or "no".])]
)

AS_ECHO
AS_ECHO "Checking features to be enabled:"

AC_MSG_CHECKING([whether encryption support should be enabled])
AS_CASE(["$ARG_ENABLE_ENCRYPTION"],
  ["yes"|"on"], [
      AC_MSG_RESULT([yes])
      AC_MSG_NOTICE([encryption support: now checking for the OpenSSL library...])

      AX_CHECK_OPENSSL([
          AC_DEFINE([TORRENT_USE_OPENSSL],[1],[Define to use OpenSSL support.])
          COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_USE_OPENSSL "
        ], [
          AC_MSG_ERROR([OpenSSL library not found. Try using --with-openssl=DIR or disabling encryption at all.])
      ])
    ],
  ["no"|"off"], [
      AC_MSG_RESULT([no])
      AC_DEFINE([TORRENT_DISABLE_ENCRYPTION],[1],[Define to disable any encryption support and avoid linking against OpenSSL.])
      COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_DISABLE_ENCRYPTION "
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_ENCRYPTION])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_ENCRYPTION". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether SSE2 should be enabled])
AS_CASE(["$ARG_ENABLE_SSE2"],
  ["yes"|"on"], [
      AC_MSG_RESULT([yes])
      AC_DEFINE([USE_SSE2],[1],[Enable SSE2])
      CXXFLAGS="$CXXFLAGS -DUSE_SSE2 -msse2 "
      CHECK_CXXFLAG([-mstackrealign])
    ],
  ["no"|"off"], [
      AC_MSG_RESULT([no])
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_SSE2])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_SSE2". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether geoip support should be enabled])
AS_CASE(["$ARG_ENABLE_GEOIP"],
  ["yes"], [
    AC_MSG_RESULT([yes])
   ],
  ["no"], [
    AC_MSG_RESULT([no])
    AC_DEFINE([TORRENT_DISABLE_GEO_IP],[1],[Define to disable the GeoIP support and avoid linking against LGPLed code.])
    COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_DISABLE_GEO_IP "
   ],
  [AC_MSG_RESULT([$ARG_ENABLE_GEOIP])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_GEOIP". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether dht support should be enabled])
AS_CASE(["$ARG_ENABLE_DHT"],
  ["yes"|"on"], [
      AC_MSG_RESULT([yes])
    ],
  ["no"|"off"], [
      AC_MSG_RESULT([no])
      AC_DEFINE([TORRENT_DISABLE_DHT],[1],[Define to disable the DHT support.])
      COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_DISABLE_DHT "
    ],
  ["logging"], [
      AC_MSG_RESULT([logging])
      AC_DEFINE([TORRENT_DHT_VERBOSE_LOGGING],[1],[Define to enable DHT support with verbose logging.])
      COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_DHT_VERBOSE_LOGGING "
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_DHT])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_DHT". Use either "yes", "no" or "logging".])]
)

AC_MSG_CHECKING([whether pool allocators should be enabled])
AS_CASE(["$ARG_ENABLE_POOL_ALLOC"],
  ["yes"|"on"], [
      AC_MSG_RESULT([yes])
    ],
  ["no"|"off"], [
      AC_MSG_RESULT([no])
      AC_DEFINE([TORRENT_DISABLE_POOL_ALLOCATOR],[1],[Define to disable use of boost::pool for pool allocators.])
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_POOL_ALLOC])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_POOL_ALLOC". Use either "yes" or "no".])]
)

AS_ECHO
AS_ECHO "Checking for extra build files:"

AC_MSG_CHECKING([whether example files should be built])
AS_CASE(["$ARG_ENABLE_EXAMPLES"],
  ["yes"], [AC_MSG_RESULT([yes])],
  ["no"],  [AC_MSG_RESULT([no])],
  [AC_MSG_RESULT([$ARG_ENABLE_EXAMPLES])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_EXAMPLES". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether test files should be built])
AS_CASE(["$ARG_ENABLE_TESTS"],
  ["yes"], [AC_MSG_RESULT([yes])],
  ["no"],  [AC_MSG_RESULT([no])],
  [AC_MSG_RESULT([$ARG_ENABLE_TESTS])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_TESTS". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether python bindings should be built])
AS_CASE(["$ARG_ENABLE_PYTHON_BINDING"],
  ["yes"], [
      AC_MSG_RESULT([yes])

      AM_PATH_PYTHON([2.4], [], AC_MSG_ERROR([Python interpreter not found.]))
      AX_PYTHON_DEVEL([>= '2.4'])
      AX_BOOST_PYTHON()

      AS_IF([test -z "$BOOST_PYTHON_LIB"],
            [AC_MSG_ERROR([Boost.Python library not found. Try using --with-boost-python=lib.])])
    ],
  ["no"], [
      AC_MSG_RESULT([no])
    ],
  [AC_MSG_RESULT([$ARG_ENABLE_PYTHON_BINDING])
   AC_MSG_ERROR([Unknown option "$ARG_ENABLE_PYTHON_BINDING". Use either "yes" or "no".])]
)

AS_ECHO
AS_ECHO "Checking for external libraries:"

AC_MSG_CHECKING([for FIEMAP support])
AC_CHECK_HEADERS([linux/types.h])
AC_CHECK_HEADERS([linux/fiemap.h], [], [],
[#ifdef HAVE_LINUX_TYPES_H
# include <linux/types.h>
#endif
])


AC_MSG_CHECKING([whether to link against system libgeoip]) #depends: $ac_arg_enable_geoip
AS_CASE(["$ARG_WITH_LIBGEOIP"],
  ["yes"|"system"], [
      AC_MSG_RESULT([yes])

      AS_IF([test "x$ac_arg_enable_geoip" = "xno"],
            [AC_MSG_ERROR([GeoIP support is disabled with this build configuration. Try using --enable-geoip.])])

      AC_MSG_NOTICE([libgeoip: now checking for the libgeoip library...])

      AC_CHECK_GEOIP([
        LIBS="$GEOIP_LIBS $LIBS"
        CFLAGS="$GEOIP_CFLAGS $CFLAGS"
       ],[
        AC_MSG_ERROR([GeoIP library not found. Try using --without-libgeoip to link against the shipped copy.])
      ])
   ],
  ["no"|"shipped"], [
      AS_IF([test "x$ac_arg_enable_geoip" = "xno"], [
            # redundant check: session_impl.hpp just won't check for any
            # GeoIP.h, so any value would be ok (ie. this AS_IF could be
            # removed)
            AC_MSG_RESULT([disabled])
            ARG_WITH_LIBGEOIP="disabled"
       ], [
            AC_MSG_RESULT([no])
            ARG_WITH_LIBGEOIP="no"
            AC_DEFINE([WITH_SHIPPED_GEOIP_H],[1],[Define to use shipped copy of GeoIP.h])
            COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DWITH_SHIPPED_GEOIP_H "
      ])
   ],
  [AC_MSG_RESULT([$ARG_WITH_LIBGEOIP])
   AC_MSG_ERROR([Unknown option "$ARG_WITH_LIBGEOIP". Use either "yes" or "no".])]
)

AC_MSG_CHECKING([whether to link against system libiconv])
AS_CASE(["$ARG_WITH_LIBICONV"],
  ["yes"], [
      AC_MSG_RESULT([yes])
      AM_ICONV()
      AS_IF([test "x$am_cv_func_iconv" = "xyes"], [
           ICONV_LIBS=$LTLIBICONV
           AC_SUBST([ICONV_LIBS])
           LIBS="$ICONV_LIBS $LIBS"
      ], [
           AC_MSG_ERROR([Iconv library not found.])
      ])
   ],
  ["no"], [
        ARG_WITH_LIBICONV="no"
   ],
  [AC_MSG_RESULT([$ARG_WITH_LIBICONV])
   AC_MSG_ERROR([Unknown option "$ARG_WITH_LIBICONV". Use either "yes" or "no".])]
)

###############################################################################
# Setting conditional variables for Makefiles
###############################################################################

AM_CONDITIONAL([ENABLE_DHT], [test "x$ARG_ENABLE_DHT" = "xyes" -o "x$ARG_ENABLE_DHT" = "xlogging" ])
AM_CONDITIONAL([ENABLE_EXAMPLES], [test "x$ARG_ENABLE_EXAMPLES" = "xyes"])
AM_CONDITIONAL([ENABLE_TESTS], [test "x$ARG_ENABLE_TESTS" = "xyes"])
AM_CONDITIONAL([ENABLE_PYTHON_BINDING], [test "x$ARG_ENABLE_PYTHON_BINDING" = "xyes"])

AM_CONDITIONAL([WITH_SHIPPED_GEOIP], [test "x$ARG_WITH_LIBGEOIP" = "xno" ])
AM_CONDITIONAL([WITH_OPENSSL], [test "x$ARG_ENABLE_ENCRYPTION" = "xyes" -o "x$ARG_ENABLE_ENCRYPTION" = "xon" ])
AM_CONDITIONAL([USE_SSE2], [test "x$ARG_ENABLE_SSE2" = "xyes" -o "x$ARG_ENABLE_SSE2" = "xon" ])

###############################################################################
# Other useful stuff
###############################################################################

# this works around a bug in asio in boost-1.39
# see: https://svn.boost.org/trac/boost/ticket/3095
AC_DEFINE([BOOST_ASIO_HASH_MAP_BUCKETS],[1021],[Define to fix a wrong behavior in boost 1.39.])
COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DBOOST_ASIO_HASH_MAP_BUCKETS=1021 "

AC_DEFINE([BOOST_EXCEPTION_DISABLE],[1],[Define to disable the boost.exception features.])
COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DBOOST_EXCEPTION_DISABLE "

AC_DEFINE([BOOST_ASIO_ENABLE_CANCELIO],[1],[Define to enable cancel support in asio on windows XP and older.])
COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DBOOST_ASIO_ENABLE_CANCELIO "

AC_DEFINE([BOOST_ASIO_DYN_LINK],[1],[make asio export its symbols])
COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DBOOST_ASIO_DYN_LINK"

dnl Use possibly specific python install params
AC_ARG_VAR([PYTHON_INSTALL_PARAMS], [Set specific install parameters for python bindings.])
AS_IF([test "x$PYTHON_INSTALL_PARAMS" = "x"],
      [PYTHON_INSTALL_PARAMS='--prefix=$(DESTDIR)$(prefix)'])

dnl Set some defines if we are building a shared library
AS_IF([test "x$enable_shared" = "xyes"],
      [AC_DEFINE([TORRENT_BUILDING_SHARED],[1],[Define to exports functions and classes with default visibility in GCC.])
       COMPILETIME_OPTIONS="$COMPILETIME_OPTIONS -DTORRENT_LINKING_SHARED "])

AC_SUBST(DEBUGFLAGS)
AC_SUBST(PYTHON_INSTALL_PARAMS)
AC_SUBST(COMPILETIME_OPTIONS)
AC_SUBST(LEVELDB_TARGET_FLAGS)


# Try to guess real svn revision if any, fallback to hardcoded otherwise
SVN_REVISION=`svn info 2>/dev/null | sed -n -e '/^URL\:.*libtorrent.svn.sourceforge.net/,$!d;s,^Revision\: \([[0-9]]*\)$,\1,p'`
AS_IF([test -z "$SVN_REVISION"],
      [SVN_REVISION=`sed -n -e 's/^#define LIBTORRENT_REVISION \"\$Rev\: \([0-9]*\) \$\" $/\1/p' include/libtorrent/version.hpp`])


###############################################################################
# Generating Makefiles
###############################################################################

AS_ECHO
AS_ECHO "Generating Makefiles:"

AC_CONFIG_FILES(
  [Makefile]
)

AC_OUTPUT

#  [bindings/Makefile]
#  [bindings/python/Makefile]
#  [bindings/python/setup.py]

###############################################################################
# Generating config.report
###############################################################################

AS_ECHO
AS_ECHO "Configure script has finished system check."
AS_ECHO

cat > config.report << END
   Config results:
  -=-=-=-=-=-=-=-=-

Package:
  name:                 ${PACKAGE_NAME}
  version:              ${PACKAGE_VERSION}
  svn revision:         ${SVN_REVISION}

Build environment:
  build system:         ${build}
  host system:          ${host}
  target system:        ${target}

Compiler and linker flags:
  CPPFlags:             ${CPPFLAGS}
  CFlags:               ${CFLAGS}
  CXXFlags:             ${CXXFLAGS}
  LDFlags:              ${LDFLAGS}
  Libs:                 ${LIBS}
  Defs:                 ${DEFS}

Build options:
  deprecated functions: ${ARG_ENABLE_DEPRECATED:-yes}
  debug build:          ${ARG_ENABLE_DEBUG:-no}
  invariant checks:     ${ARG_ENABLE_INVARIANT:-no}
  logging support:      ${ARG_ENABLE_LOGGING:-no}
  statistics:           ${ARG_ENABLE_STATS:-no}
  disk statistics:      ${ARG_ENABLE_DISK_STATS:-no}

Features:
  encryption support:   ${ARG_ENABLE_ENCRYPTION:-yes}
  SSE2 Scrypt:          ${ARG_ENABLE_SSE2:-yes}
  geoip support:        ${ARG_ENABLE_GEOIP:-yes}
  dht support:          ${ARG_ENABLE_DHT:-yes}
  pool allocators:      ${ARG_ENABLE_POOL_ALLOC:-yes}

Extra builds:
  examples:             ${ARG_ENABLE_EXAMPLES:-no}
  tests:                ${ARG_ENABLE_TESTS:-no}
  python bindings:      ${ARG_ENABLE_PYTHON_BINDING:-no}

Pthread library:
  CFlags:               ${PTHREAD_CFLAGS}
  Libs:                 ${PTHREAD_LIBS}

Boost libraries:
  version:              ${BOOST_VERSION}
  CPPFlags:             ${BOOST_CPPFLAGS}
  LDFlags:              ${BOOST_LDFLAGS}
  boost.system:         ${BOOST_SYSTEM_LIB}
  boost.filesystem:     ${BOOST_FILESYSTEM_LIB}
  boost.program_opts:   ${BOOST_PROGRAM_OPTIONS_LIB}
  boost.thread:         ${BOOST_THREAD_LIB}
  boost.locale:         ${BOOST_LOCALE_LIB}
  boost.regex:          ${BOOST_REGEX_LIB}

Berkeley DB C++ library:
  header:               ${DB_CXX_HEADER}
  libraries:            ${DB_CXX_LIBS}
  LDFlags:              ${DB_CXX_LDFLAGS}
  CPPFlags:             ${DB_CXX_CPPFLAGS}
END

AS_IF([test "x$ARG_ENABLE_PYTHON_BINDING" = "xyes"], [
cat >> config.report << END
  boost.python:         ${BOOST_PYTHON_LIB}

Python environment:
  -automake-
  binary:               ${PYTHON}
  version:              ${PYTHON_VERSION}
  platform:             ${PYTHON_PLATFORM}
  prefix:               ${PYTHON_PREFIX}
  exec_prefix:          ${PYTHON_EXEC_PREFIX}
  pythondir:            ${pythondir}
  pkgpythondir:         ${pkgpythondir}
  pyexecdir:            ${pyexecdir}
  pkgpyexecdir:         ${pkgpyexecdir}

  -m4-
  cppflags:             ${PYTHON_CPPFLAGS}
  ldflags:              ${PYTHON_LDFLAGS}
  extra libs:           ${PYTHON_EXTRA_LIBS}
  extra ldflags:        ${PYTHON_EXTRA_LDFLAGS}

END
])

cat >> config.report << END

External libraries:
  system libgeoip:      ${ARG_WITH_LIBGEOIP:-no}
  system libiconv:      ${ARG_WITH_LIBICONV:-no}
END

AS_IF([test "x$ARG_WITH_LIBGEOIP" = "xyes"], [
cat >> config.report << END

GeoIP library:
  GeoIP CFlags:         ${GEOIP_CFLAGS}
  GeoIP Libs:           ${GEOIP_LIBS}
END
])

AS_IF([test "x$ARG_WITH_LIBICONV" = "xyes"], [
cat >> config.report << END

Iconv library:
  Iconv Libs:           ${ICONV_LIBS}
END
])

AS_IF([test "x$ARG_ENABLE_ENCRYPTION" = "xyes"], [
cat >> config.report << END

OpenSSL library:
  OpenSSL Libs:         ${OPENSSL_LIBS}
  OpenSSL LDFlags:      ${OPENSSL_LDFLAGS}
  OpenSSL Includes:     ${OPENSSL_INCLUDES}
END
])

cat config.report

AS_ECHO
AS_ECHO "Type 'make' to compile $PACKAGE_STRING"
AS_ECHO "or type 'make V=1' for verbose compiling"
AS_ECHO "and then 'make install' to install it into $prefix"
AS_ECHO

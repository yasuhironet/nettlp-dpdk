#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([sdplane],[m4_esyscmd_s([. sdplane/sdplane-version.sh])],[yasu1976@gmail.com])
AC_CONFIG_SRCDIR([sdplane/sdplane.c])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_HEADERS([config.h])
LT_INIT
AC_ENABLE_SHARED
AC_ENABLE_STATIC

# Checks for programs.
AC_PROG_CC
AC_PROG_LN_S

# Checks for libraries.
AC_CHECK_LIB([lthread], [lthread_create], ,
             [AC_MSG_ERROR([lthread library not found.])])
AC_CHECK_LIB([urcu-qsbr], [urcu_qsbr_quiescent_state], ,
             [AC_MSG_ERROR([urcu-qsbr library not found.])])

AC_ARG_WITH([zcmdsh], [AS_HELP_STRING([--with-zcmdsh=DIR], [zcmdsh libdir ($(top_srcdir)/lib)])], [
        zcmdshdir="$withval"
        LDLFAGS="$LDFLAGS -L$withval"
], [
        zcmdshdir="$(top_srcdir)/lib"
])
AC_SUBST([zcmdshdir], [$zcmdshdir])

AC_CHECK_LIB([zcmdsh], [command_shell_create])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h inttypes.h locale.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset setlocale socket strchr strerror strtol strtoul strtoull])

PKG_CHECK_MODULES(DPDK, [libdpdk])

AC_SUBST([systemdsystemunitdir], [$($PKG_CONFIG --variable=systemdsystemunitdir systemd)])

AC_CONFIG_FILES([Makefile sdplane/Makefile lib/Makefile])
AC_OUTPUT

## Process this file with automake to produce Makefile.in.

AM_CPPFLAGS = -I$(top_srcdir)/lib

noinst_LTLIBRARIES = libzcmdsh.la

libzcmdsh_la_SOURCES = \
	include.h \
	zcmdsh/log.c zcmdsh/vector.c zcmdsh/termio.c \
	zcmdsh/shell.c zcmdsh/command.c zcmdsh/command_shell.c \
	zcmdsh/file.c zcmdsh/shell_fselect.c \
	zcmdsh/debug.c zcmdsh/debug_cmd.c \
	zcmdsh/log_cmd.c zcmdsh/shell_keyfunc.c zcmdsh/debug_log.c \
	zcmdsh/debug_zcmdsh.c \
	zcmdsh/shell_telnet.c

nobase_include_HEADERS = \
	zcmdsh/log.h zcmdsh/vector.h zcmdsh/termio.h zcmdsh/flag.h \
	zcmdsh/shell.h zcmdsh/command.h zcmdsh/command_shell.h \
	zcmdsh/debug.h zcmdsh/debug_cmd.h \
	zcmdsh/log_cmd.h zcmdsh/shell_keyfunc.h \
        zcmdsh/debug_log.h zcmdsh/debug_category.h zcmdsh/debug_zcmdsh.h \
	zcmdsh/debug_backtrace.h \
        zcmdsh/shell_telnet.h

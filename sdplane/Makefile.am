
AM_CFLAGS = -g -O0

ZCMDSH_DIR = $(top_srcdir)/lib
SDPLANE_DIR = $(top_srcdir)/sdplane

sbin_PROGRAMS = sdplane
sdplane_SOURCES = \
        tap.c tap_handler.h tap_handler.c stat_collector.c \
        startup_config.c snprintf_flags.c dpdk_flag.h \
        dpdk_lcore_cmd.c dpdk_port_cmd.c \
        vty_server.c vty_shell.c \
        main.c lthread_main.c sdplane.h sdplane.c debug_sdplane.c \
        console_shell.c l2_repeater.c \
        sdplane_version.c thread_info.c queue_config.c rib_manager.c \
        internal_message.c rib.c nettlp.c nettlp_support.c tap_cmd.c
sdplane_CFLAGS = @DPDK_CFLAGS@ -I$(ZCMDSH_DIR)
sdplane_LDADD = @DPDK_LIBS@ -llthread $(ZCMDSH_DIR)/libzcmdsh.la -lurcu-qsbr

FORCE:
.PHONY: FORCE clean-version

sdplane_version.c: FORCE
	top_srcdir=$(top_srcdir) bash $(top_srcdir)/sdplane/sdplane-version-c.sh > sdplane_version.c

clean-local: clean-version
clean-version:
	-rm -f sdplane_version.c


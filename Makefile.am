
SUBDIRS = lib sdplane 

ACLOCAL_AMFLAGS = -I m4

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

AM_CPPFLAGS = -DSYSCONFDIR='$(sysconfdir)'

dist_sysconf_DATA = etc/sdplane.conf.sample etc/60-netplan-sdplane.yaml etc/iptables-rules.v4 etc/iptables-rules.v6 etc/sshd_config
dist_systemdsystemunit_DATA = etc/sdplane.service


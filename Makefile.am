SUBDIRS=doc src
EXTRA_DIST=COPYING debian/*

ACLOCAL_AMFLAGS = -I m4

distclean-local:
	-rm -rf autom4te.cache/ \
	m4/*

	-rm -f *~ \
	aclocal.m4 \
	compile \
	config.* \
	configure \
	depcomp \
	install-sh \
	ltmain.sh \
	Makefile.in \
	missing \
	doc/Makefile.in

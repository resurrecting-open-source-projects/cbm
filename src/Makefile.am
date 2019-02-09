SUBDIRS = widgets
bin_PROGRAMS = cbm
cbm_SOURCES = cbm.cpp \
	      ErrnoError.hpp \
	      statistics.cpp statistics.hpp
cbm_LDADD = -lncurses widgets/libwidgets.la

distclean-local:
	-rm -f *~ \
	Makefile.in \
	config.h.in \
	widgets/Makefile.in

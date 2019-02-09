AC_PREREQ(2.59)
AC_INIT([cbm],[0.1],[aaron@isotton.com])
AM_INIT_AUTOMAKE(foreign)
AC_CONFIG_SRCDIR(src/cbm.cpp)
AC_CONFIG_HEADER(src/config.h)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_CHECK_PROG(HAS_XMLTO, xmlto, yes, no)
if test x"$HAS_XMLTO" == xno ; then
    AC_MSG_ERROR([You need xmlto to build the documentation])
fi

# Check for host platform
AC_CANONICAL_HOST

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
# Checks for library functions.
# 
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_FILES([Makefile doc/Makefile src/Makefile src/widgets/Makefile])
AC_OUTPUT

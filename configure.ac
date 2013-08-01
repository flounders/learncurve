#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(learncurve, 0.2, http://github.com/flounders/learncurve)
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(config.h)


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O
#AM_PROG_CXX_O

# Checks for libraries.
PKG_CHECK_MODULES(XML, libxml-2.0 >= 2.4)
PKG_CHECK_MODULES(WEBKITGTK, webkitgtk-3.0 >= 1.6)
PKG_CHECK_MODULES(GMODULE, gmodule-2.0 >= 2.0)

# Checks for header files.
AM_PATH_GTK_3_0(,,AC_MSG_ERROR([Gtk+ 3.0 or higher required.]))

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([mkdir setlocale strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

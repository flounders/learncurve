#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(learncurve, 0.2, http://github.com/flounders/learncurve)
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(config.h)


# Checks for programs.
AC_PROG_CXX

# Qt checks
BR_QT_DIR
BR_QT_LIBS
BR_QT_TEST

# Checks for libraries.
PKG_CHECK_MODULES(XML, libxml-2.0 >= 2.4)
PKG_CHECK_MODULES(LPACKAGE, QtGui)
PKG_CHECK_MODULES(LPACKAGE, QtWebKit)
AC_SUBST(LPACKAGE_CFLAGS)
AC_SUBST(LPACKAGE_LIBS)

# Checks for library functions.
AC_CHECK_FUNCS([mkdir setlocale strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ibus-examples], [1.0], [kenhys@gmail.com])
AM_INIT_AUTOMAKE([1.15 foreign])
AC_CONFIG_SRCDIR([simple-menu/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
PKG_CHECK_MODULES(IBUS, [ibus-1.0])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 simple-menu/Makefile])
AC_OUTPUT

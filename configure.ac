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
PKG_CHECK_MODULES(GTK, [gtk+-x11-3.0 gmodule-2.0])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 change-property/Makefile
                 change-inputmode-icon/Makefile
                 change-inputmode-symbol/Makefile
                 create-component/Makefile
                 hybrid-engine/Makefile
                 nested-menu/Makefile
                 radio-menu/Makefile
                 radio-menu/from-array/Makefile
                 radio-menu/delay/Makefile
                 radio-menu/flickered/Makefile
                 radio-menu/imeonoff/Makefile
                 radio-menu/imeonoff2/Makefile
                 radio-menu/noneedtoupdate/Makefile
                 radio-menu/simple/Makefile
                 radio-menu/stall/Makefile
                 radio-menu/updatebytimer/Makefile
                 simple-menu/Makefile
                 engine-icon/Makefile])
AC_OUTPUT

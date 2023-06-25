AC_INIT([xasic], [0.1.0])
AM_INIT_AUTOMAKE([subdir-objects])
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX(noyywrap)
if test "x$LEX" != xflex; then
  LEX="$SHELL $missing_dir/missing flex"
  AC_SUBST([LEXLIB], [''])
fi
AC_PROG_YACC
CXXFLAGS="-Ofast -g"
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

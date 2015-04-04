AC_INIT([porg], [0.1], [dennis@yurichev.com], [porg], [https://github.com/dennis714/porg])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

CFLAGS="-Wall -std=c11"

AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AR

AC_CHECK_SIZEOF(size_t)

case $ac_cv_sizeof_size_t in
  4) 
      AC_SUBST([BITS],[32])
      AC_DEFINE([O_BITS32], [], [ ])
      ;;
  8) 
      AC_SUBST([BITS],[64])
      AC_DEFINE([O_BITS64], [], [ ])
      ;;
  *)  AC_MSG_ERROR([No type matching size_t in size])
      ;;
esac

AC_CHECK_FUNC(stricmp, stricmp=yes, stricmp=no)
if test $stricmp = no; then
	AC_CHECK_FUNC(strcasecmp, 
		AC_DEFINE(stricmp, strcasecmp, [Define stricmp as strcasecmp if you have one but not the other]),
		AC_MSG_ERROR([Neither stricmp nor strcasecmp found])
	)
fi

dnl Extra arguments to configure
unset octothorpe_include_path
AC_ARG_WITH(octothorpe_include,
   [  --with-octothorpe-include=DIR  octothorpe include directory ],
   [octothorpe_include_path="$withval"])
unset octothorpe_lib_path
AC_ARG_WITH(octothorpe_lib,
   [  --with-octothorpe-lib=DIR      octothorpe lib directory ], 
   [octothorpe_lib_path="$withval"])
AC_ARG_WITH(octothorpe,
   [  --with-octothorpe=DIR          octothorpe install directory ], [
   if test -z "$with_octothorpe_lib" && test -z "$with_octothorpe_include" ; then
      octothorpe_include_path="$withval/include"
      octothorpe_lib_path="$withval/lib"
   else
      AC_MSG_FAILURE([Do not use --with-octothorpe and --with-octothorpe-include/--with-octothorpe-lib options simultaneously.])
   fi
  ])
CFLAGS="$CFLAGS -I$octothorpe_include_path"
LDFLAGS="$LDFLAGS -L$octothorpe_lib_path"

AC_CHECK_LIB([octothorpe],[strbuf_init],,AC_MSG_ERROR(octothorpe library missing))

dnl Do not compile with debugging by default.
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug], [Build debugging code])],
[if test "x$enable_debug" = "xyes" ; then
  enable_debug="1"
else
  enable_debug="0"
fi
],
[enable_debug="0"]
)
AC_SUBST([enable_debug])

if test "x$enable_debug" = "x1" ; then
  AC_DEFINE([PORG_DEBUG], [], [ ])
  AC_DEFINE([OASSERT_DEBUG], [], [ ])
  CFLAGS="$CFLAGS -g -O0"
else
  CFLAGS="$CFLAGS -O3"
fi

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile lib/Makefile include/Makefile tests/Makefile])
AC_OUTPUT

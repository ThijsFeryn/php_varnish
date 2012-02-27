 PHP_ARG_WITH(varnish, for varnish support,
 [  --with-varnish             Include varnish support])

if test "$PHP_VARNISH" != "no"; then

  AC_CHECK_HEADER(fcntl.h)
  AC_CHECK_HEADER(sys/types.h)
  AC_CHECK_HEADER(sys/socket.h)
  AC_CHECK_HEADER(netinet/in.h)
  AC_CHECK_HEADER(arpa/inet.h)
  AC_CHECK_HEADER(netdb.h)

  dnl # --with-varnish -> check with-path
  SEARCH_PATH="/usr/local/include /usr/local/include/varnish /usr/include /usr/include/varnish"
  SEARCH_FOR="varnishapi.h"
  if test -r $PHP_VARNISH/$SEARCH_FOR; then
    VARNISH_DIR=$PHP_VARNISH
  else # search default path list
    AC_MSG_CHECKING([for varnish files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        VARNISH_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$VARNISH_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the varnish distribution])
  fi

  PHP_ADD_INCLUDE($VARNISH_DIR)
  AC_CHECK_HEADER([$VARNISH_DIR/varnishapi.h], [], AC_MSG_ERROR('varnishapi.h' header not found))
  AC_CHECK_HEADER([$VARNISH_DIR/vcli.h], [], AC_MSG_ERROR('vcli.h' header not found))
  AC_CHECK_HEADER([$VARNISH_DIR/vsl.h], [], AC_MSG_ERROR('vsl.h' header not found))

  LIBNAME=varnishapi
  LIBSYMBOL=VSM_New

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $VARNISH_DIR/lib, VARNISH_SHARED_LIBADD)
   AC_DEFINE(HAVE_VARNISHAPILIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong varnishapi lib version or lib not found])
  ],[
    -L$VARNISH_DIR/lib -lm
  ])
 
  PHP_SUBST(VARNISH_SHARED_LIBADD)

  PHP_NEW_EXTENSION(varnish, varnish.c adm.c varnish_lib.c sha2.c exception.c stat.c log.c, $ext_shared)
fi

# aclocal.m4 generated automatically by aclocal 1.6.3 -*- Autoconf -*-

# Copyright 1996, 1997, 1998, 1999, 2000, 2001, 2002
# Free Software Foundation, Inc.
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

dnl ----------------------------------
dnl OpenEXR
dnl ----------------------------------

AC_DEFUN([AM_PATH_OPENEXR],
[dnl 
dnl Get the cflags and libraries
dnl
AC_ARG_WITH(openexr-prefix,[  --with-openexr-prefix=PFX   Prefix where libopenexr is installed (optional)], openexr_prefix="$withval", openexr_prefix="/usr")
AC_ARG_ENABLE(openexrtest, [  --disable-openexrtest       Do not try to compile and run a test Openexr program],, enable_openexrtest=yes)
AC_ARG_ENABLE(static-openexr, [  --enable-static-openexr  Statically link against OpenEXR libs],enable_static_openexr=yes, enable_static_openexr=no)
AC_ARG_ENABLE(openexr-threads,[  --enable-openexr-threads Include OpenEXR threading],enable_openexr_threads=yes, enable_openexr_threads=no)

  if test "x$openexr_prefix" != "xNONE" ; then
    openexr_args="$openexr_args --prefix=$openexr_prefix"
    OPENEXR_INCLUDES="-I$openexr_prefix/include/OpenEXR"
    OPENEXR_LDLFLAGS="-L$openexr_prefix/lib"
    openexr_static_libs="$openexr_prefix/lib/libIlmImf.a $openexr_prefix/lib/libImath.a $openexr_prefix/lib/libIex.a $openexr_prefix/lib/libHalf.a -lz"
    if test "x$enable_openexr_threads" == "xyes" ; then
    	openexr_static_libs="$openexr_static_libs $openexr_prefix/lib/libIlmThread.a"
    fi
  elif test "$prefix" != ""; then
    openexr_args="$openexr_args --prefix=$prefix"
    OPENEXR_INCLUDES="-I$prefix/include/OpenEXR"
    OPENEXR_LDFLAGS="-L$prefix/lib"
    openexr_static_libs="$prefix/lib/libIlmImf.a $prefix/lib/libImath.a $prefix/lib/libIex.a $prefix/lib/libHalf.a -lz"
    if test "x$enable_openexr_threads" == "xyes" ; then
    	openexr_static_libs="$openexr_static_libs $prefix/lib/libIlmThread.a"
    fi
  fi

  if test "x$enable_static_openexr" == "xyes"; then
    OPENEXR_LIBS="$X_LIBS $openexr_static_libs"
  else
    OPENEXR_LIBS="$X_LIBS -lIlmImf -lImath -lIex -lHalf -lz"
  fi

  AC_MSG_CHECKING(for OpenEXR)
  no_openexr=""


  if test "x$enable_openexrtest" = "xyes" ; then
    ac_save_CXXFLAGS="$CXXFLAGS"
    ac_save_LIBS="$LIBS"
    ac_save_LDFLAGS="$LDFLAGS"
    CXXFLAGS="$CXXFLAGS $OPENEXR_CXXFLAGS $OPENEXR_INCLUDES"
    LIBS="$LIBS $OPENEXR_LIBS"
    LDFLAGS="$LDFLAGS $OPENEXR_LDFLAGS"
      rm -f conf.openexrtest
      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_TRY_RUN([
#include <stdlib.h>
#include <ImfRgbaFile.h>

int main ()
{
  try
  {
    Imf::RgbaInputFile exr ("");
  }
  catch (...)
  {
  }
  system("touch conf.openexrtest");
  return 0;
}

],, no_openexr=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       AC_LANG_RESTORE
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
       LDFLAGS="$ac_save_LDFLAGS"
  fi

  if test "x$no_openexr" = "x" ; then
     AC_MSG_RESULT(yes)
     ifelse([$1], , :, [$1])     
  else
     AC_MSG_RESULT(no)
     if test -f conf.openexrtest ; then
       :
     else
       echo "*** Could not run OpenEXR test program, checking why..."
       CXXFLAGS="$CXXFLAGS $OPENEXR_CXXFLAGS $OPENEXR_INCLUDES"
       LIBS="$LIBS $OPENEXR_LIBS"
       LDFLAGS="$LDFLAGS $OPENEXR_LDFLAGS"
       AC_LANG_SAVE
       AC_LANG_CPLUSPLUS
       AC_TRY_LINK([
#include <stdio.h>
#include <ImfRgbaFile.h>
],     [ Imf::RgbaInputFile exr ("");return 0; ],
       [ echo "*** The test program compiled, but did not run. This usually means"
       echo "*** that the run-time linker is not finding OpenEXR or finding the wrong"
       echo "*** version of OpenEXR. If it is not finding OpenEXR, you'll need to set your"
       echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
       echo "*** to the installed location  Also, make sure you have run ldconfig if that"
       echo "*** is required on your system"
       echo "***"])
       AC_LANG_RESTORE
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
       LDFLAGS="$ac_save_LDFLAGS"
     fi
     OPENEXR_INCLUDES=""
     OPENEXR_LIBS=""
     ifelse([$2], , :, [$2])
  fi
  AC_SUBST(OPENEXR_INCLUDES)
  AC_SUBST(OPENEXR_LIBS)
  AC_SUBST(OPENEXR_LDFLAGS)
  rm -f conf.openexrtest
])

dnl ----------------------------------
dnl FLTK with GL support
dnl ----------------------------------

AC_DEFUN([AM_PATH_FLTK],
[dnl 
dnl Get the cflags and libraries
dnl
AC_ARG_VAR(FLTK_CONFIG, Path to fltk-config command)
AC_PATH_PROG(FLTK_CONFIG, fltk-config, no)
AC_ARG_WITH(fltk-config,[  --with-fltk-config=PATH Specify which fltk-config to use (optional)], FLTK_CONFIG="$withval",)
AC_ARG_ENABLE(static-fltk,[  --enable-static-fltk Specify whether to link fltk statically (optional)], STATIC_FLTK=true,STATIC_FLTK=false)

  if test x$FLTK_CONFIG != xno ; then
  	if test x$STATIC_FLTK != xno ; then
  	    FLTK_CXXFLAGS="`$FLTK_CONFIG --use-gl --cxxflags`"
    	FLTK_LDFLAGS="`$FLTK_CONFIG --use-gl --ldstaticflags`"
  	else
	    FLTK_CXXFLAGS="`$FLTK_CONFIG --use-gl --cxxflags`"
    	FLTK_LDFLAGS="`$FLTK_CONFIG --use-gl --ldflags`"
    fi
  else
    FLTK_CXXFLAGS=""
    FLTK_LDFLAGS=""
  fi

  AC_MSG_CHECKING(for FLTK with GL support)
  no_fltk=""

  ac_save_CXXFLAGS="$CXXFLAGS"
  ac_save_LDFLAGS="$LDFLAGS"
  CXXFLAGS="$CXXFLAGS $FLTK_CXXFLAGS"
  LDFLAGS="$LDFLAGS $FLTK_LDFLAGS"

dnl
dnl Now check if the installed FLTK has GL support
dnl
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_LINK([
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>],
[
    Fl_Gl_Window foo (); 
],, no_fltk=yes)
  AC_LANG_RESTORE
  CXXFLAGS="$ac_save_CXXFLAGS"
  LDFLAGS="$ac_save_LDFLAGS"
  
  if test "x$no_fltk" = "x" ; then
    AC_MSG_RESULT(yes)
     ifelse([$1], , :, [$1])     
  else
    AC_MSG_RESULT(no)
    FLTK_CXXFLAGS=""
    FLTK_LDFLAGS=""
    ifelse([$2], , :, [$2])
  fi
])

dnl ----------------------------------
dnl QT with GL support
dnl ----------------------------------

AC_DEFUN([AM_PATH_QT],
[dnl 
dnl Get the cflags and libraries
dnl
AC_ARG_WITH(qt-prefix,[  --with-qt-prefix=PFX   Prefix where qt is installed (optional)], qt_prefix="$withval", qt_prefix="/usr/lib/qt/")
AC_ARG_WITH(qt-includes,[  --with-qt-includes=PFX   Prefix where qt includes live (optional)], qt_includes="$withval", qt_includes="")
AC_ARG_WITH(qt-libs,[  --with-qt-libs=PFX   Prefix where qt libs live (optional)], qt_libs="$withval", qt_libs="")
AC_ARG_ENABLE(qttest, [  --disable-qttest       Do not try to compile and run a test Qt program],, enable_qttest=yes)
  
  case $host in
  *-apple-*)
  	qt_ld_extra="-framework OpenGL"
  	QT_POSTPROCESS="/Developer/Tools/Rez Carbon.r -o" ;;
  *)
  	qt_lib_extra="$X_LIBS -lGL"
  	qt_ld_extra="$X_LDFLAGS"
  	QT_POSTPROCESS="echo" ;;
  esac
  
  if test "x$qt_includes" == "x" -a "x$qt_lib" == "x" ; then
  	# all-in-one installation specified by qt_prefix
  	
    QT_INCLUDES="-I$qt_prefix/include/ -I$qt_prefix/include/QtCore -I$qt_prefix/include/QtGui -I$qt_prefix/include/QtOpenGL"
    QT_LDFLAGS="-L$qt_prefix/lib/ $qt_ld_extra"
    QT_LIBS="-lQtCore -lQtGui -lQtOpenGL $qt_lib_extra"
  else
  	# default, look in standard places
  	
  	if test "x$qt_includes" != "x"; then
  		# but allow override of include dir
	    QT_INCLUDES="-I$qt_includes  -I$qt_includes/QtCore -I$qt_includes/QtGui -I$qt_includes/QtOpenGL"
	else
	    QT_INCLUDES="-I$prefix/include/  -I$prefix/include/QtCore -I$prefix/include/QtGui -I$prefix/include/QtOpenGL"
	fi
	
	if test "x$qt_libs" != "x"; then
		# but allow override of lib dir
		QT_LDFLAGS="-L$qt_libs $qt_ld_extra"
		QT_LIBS="-lQtCore -lQtGui -lQtOpenGL $qt_lib_extra"
	else
		QT_LDFLAGS="-L$prefix/lib $qt_ld_extra"
		QT_LIBS="-lQtCore -lQtGui -lQtOpenGL $qt_lib_extra"
	fi
  fi
  QT_CXXFLAGS="-DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED"

  AC_MSG_CHECKING(for Qt with OpenGL)
  no_qt=""


  if test "x$enable_qttest" = "xyes" ; then
    ac_save_CXXFLAGS="$CXXFLAGS"
    ac_save_LDFLAGS="$LDFLAGS"
    ac_save_LIBS="$LIBS"
    CXXFLAGS="$CXXFLAGS $QT_CXXFLAGS $QT_INCLUDES"
    LIBS="$LIBS $QT_LIBS"
    LDFLAGS="$LDFLAGS $QT_LDFLAGS"
      rm -f conf.qttest
      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_TRY_RUN([
#include <stdlib.h>
#include <QApplication>
#include <QGLWidget>

int main (int argc, char*argv[])
{
  QApplication	app(argc,argv);
  QGLWidget *foo = new QGLWidget;
  delete foo;
  system("touch conf.qttest");
  return 0;
}

],, no_qt=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       AC_LANG_RESTORE
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
       LDFLAGS="$ac_save_LDFLAGS"
  fi

  if test "x$no_qt" = "x" ; then
     AC_MSG_RESULT(yes)
     ifelse([$1], , :, [$1])     
  else
     AC_MSG_RESULT(no)
     if test -f conf.qttest ; then
       :
     else
       echo "*** Could not run Qt test program, checking why..."
       CXXFLAGS="$CXXFLAGS $QT_CXXFLAGS $QT_INCLUDES"
       LIBS="$LIBS $QT_LIBS"
       LDFLAGS="$LDFLAGS $QT_LDFLAGS"
       AC_LANG_SAVE
       AC_LANG_CPLUSPLUS
       AC_TRY_LINK([
#include <stdio.h>
#include <QGLWidget.h>
],     [ QGLWidget qtgl;return 0; ],
       [ echo "*** The test program compiled, but did not run. This usually means"
       echo "*** that the run-time linker is not finding Qt or finding the wrong"
       echo "*** version of Qt. If it is not finding Qt, you'll need to set your"
       echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
       echo "*** to the installed location  Also, make sure you have run ldconfig if that"
       echo "*** is required on your system"
       echo "***"])
       AC_LANG_RESTORE
       CXXFLAGS="$ac_save_CXXFLAGS"
       LDFLAGS="$ac_save_LDFLAGS"
       LIBS="$ac_save_LIBS"
     fi
     QT_INCLUDES=""
     QT_LIBS=""
     ifelse([$2], , :, [$2])
  fi
  AC_SUBST(QT_INCLUDES)
  AC_SUBST(QT_CXXFLAGS)
  AC_SUBST(QT_LIBS)
  AC_SUBST(QT_LDFLAGS)
  AC_SUBST(QT_POSTPROCESS)
  rm -f conf.qttest
])


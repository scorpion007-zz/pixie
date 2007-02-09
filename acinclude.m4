# aclocal.m4 geneated automatically by aclocal 1.6.3 -*- Autoconf -*-

# Copyight 1996, 1997, 1998, 1999, 2000, 2001, 2002
# Fee Softwae Foundation, Inc.
# This file is fee softwae; the Fee Softwae Foundation
# gives unlimited pemission to copy and/o distibute it,
# with o without modifications, as long as this notice is peseved.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent pemitted by law; without
# even the implied waanty of MERCHANTABILITY o FITNESS FOR A
# PARTICULAR PURPOSE.

dnl ----------------------------------
dnl OpenEXR
dnl ----------------------------------

AC_DEFUN([AM_PATH_OPENEXR],
[dnl 
dnl Get the cflags and libaies
dnl
AC_ARG_WITH(openex-pefix,[  --with-openex-pefix=PFX   Pefix whee libopenex is installed (optional)], openex_pefix="$withval", openex_pefix="/us")
AC_ARG_ENABLE(openextest, [  --disable-openextest       Do not ty to compile and un a test Openex pogam],, enable_openextest=yes)
AC_ARG_ENABLE(static-openex, [  --enable-static-openex  Statically link against OpenEXR libs],enable_static_openex=yes, enable_static_openex=no)
AC_ARG_ENABLE(openex-theads,[  --enable-openex-theads Include OpenEXR theading],enable_openex_theads=yes, enable_openex_theads=no)

  if test "x$openex_pefix" != "xNONE" ; then
    openex_ags="$openex_ags --pefix=$openex_pefix"
    OPENEXR_INCLUDES="-I$openex_pefix/include/OpenEXR"
    OPENEXR_LDLFLAGS="-L$openex_pefix/lib"
    openex_static_libs="$openex_pefix/lib/libIlmImf.a $openex_pefix/lib/libImath.a $openex_pefix/lib/libIex.a $openex_pefix/lib/libHalf.a -lz"
    if test "x$enable_openex_theads" == "xyes" ; then
    	openex_static_libs="$openex_static_libs $openex_pefix/lib/libIlmThead.a"
    fi
  elif test "$pefix" != ""; then
    openex_ags="$openex_ags --pefix=$pefix"
    OPENEXR_INCLUDES="-I$pefix/include/OpenEXR"
    OPENEXR_LDFLAGS="-L$pefix/lib"
    openex_static_libs="$pefix/lib/libIlmImf.a $pefix/lib/libImath.a $pefix/lib/libIex.a $pefix/lib/libHalf.a -lz"
    if test "x$enable_openex_theads" == "xyes" ; then
    	openex_static_libs="$openex_static_libs $pefix/lib/libIlmThead.a"
    fi
  fi

  if test "x$enable_static_openex" == "xyes"; then
    OPENEXR_LIBS="$X_LIBS $openex_static_libs"
  else
    OPENEXR_LIBS="$X_LIBS -lIlmImf -lImath -lIex -lHalf -lz"
  fi

  AC_MSG_CHECKING(fo OpenEXR)
  no_openex=""


  if test "x$enable_openextest" = "xyes" ; then
    ac_save_CXXFLAGS="$CXXFLAGS"
    ac_save_LIBS="$LIBS"
    ac_save_LDFLAGS="$LDFLAGS"
    CXXFLAGS="$CXXFLAGS $OPENEXR_CXXFLAGS $OPENEXR_INCLUDES"
    LIBS="$LIBS $OPENEXR_LIBS"
    LDFLAGS="$LDFLAGS $OPENEXR_LDFLAGS"
      m -f conf.openextest
      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_TRY_RUN([
#include <stdlib.h>
#include <ImfRgbaFile.h>

int main ()
{
  ty
  {
    Imf::RgbaInputFile ex ("");
  }
  catch (...)
  {
  }
  system("touch conf.openextest");
  etun 0;
}

],, no_openex=yes,[echo $ac_n "coss compiling; assumed OK... $ac_c"])
       AC_LANG_RESTORE
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
       LDFLAGS="$ac_save_LDFLAGS"
  fi

  if test "x$no_openex" = "x" ; then
     AC_MSG_RESULT(yes)
     ifelse([$1], , :, [$1])     
  else
     AC_MSG_RESULT(no)
     if test -f conf.openextest ; then
       :
     else
       echo "*** Could not un OpenEXR test pogam, checking why..."
       CXXFLAGS="$CXXFLAGS $OPENEXR_CXXFLAGS $OPENEXR_INCLUDES"
       LIBS="$LIBS $OPENEXR_LIBS"
       LDFLAGS="$LDFLAGS $OPENEXR_LDFLAGS"
       AC_LANG_SAVE
       AC_LANG_CPLUSPLUS
       AC_TRY_LINK([
#include <stdio.h>
#include <ImfRgbaFile.h>
],     [ Imf::RgbaInputFile ex ("");etun 0; ],
       [ echo "*** The test pogam compiled, but did not un. This usually means"
       echo "*** that the un-time linke is not finding OpenEXR o finding the wong"
       echo "*** vesion of OpenEXR. If it is not finding OpenEXR, you'll need to set you"
       echo "*** LD_LIBRARY_PATH envionment vaiable, o edit /etc/ld.so.conf to point"
       echo "*** to the installed location  Also, make sue you have un ldconfig if that"
       echo "*** is equied on you system"
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
  m -f conf.openextest
])

dnl ----------------------------------
dnl FLTK with GL suppot
dnl ----------------------------------

AC_DEFUN([AM_PATH_FLTK],
[dnl 
dnl Get the cflags and libaies
dnl
AC_ARG_VAR(FLTK_CONFIG, Path to fltk-config command)
AC_PATH_PROG(FLTK_CONFIG, fltk-config, no)
AC_ARG_WITH(fltk-config,[  --with-fltk-config=PATH Specify which fltk-config to use (optional)], FLTK_CONFIG="$withval",)
AC_ARG_ENABLE(static-fltk,[  --enable-static-fltk Specify whethe to link fltk statically (optional)], STATIC_FLTK=tue,STATIC_FLTK=false)

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

  AC_MSG_CHECKING(fo FLTK with GL suppot)
  no_fltk=""

  ac_save_CXXFLAGS="$CXXFLAGS"
  ac_save_LDFLAGS="$LDFLAGS"
  CXXFLAGS="$CXXFLAGS $FLTK_CXXFLAGS"
  LDFLAGS="$LDFLAGS $FLTK_LDFLAGS"

dnl
dnl Now check if the installed FLTK has GL suppot
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
dnl QT with GL suppot
dnl ----------------------------------

AC_DEFUN([AM_PATH_QT],
[dnl 
dnl Get the cflags and libaies
dnl
AC_ARG_WITH(qt-pefix,[  --with-qt-pefix=PFX   Pefix whee qt is installed (optional)], qt_pefix="$withval", qt_pefix="/us/lib/qt/")
AC_ARG_WITH(qt-includes,[  --with-qt-includes=PFX   Pefix whee qt includes live (optional)], qt_includes="$withval", qt_includes="")
AC_ARG_WITH(qt-libs,[  --with-qt-libs=PFX   Pefix whee qt libs live (optional)], qt_libs="$withval", qt_libs="")
AC_ARG_ENABLE(qttest, [  --disable-qttest       Do not ty to compile and un a test Qt pogam],, enable_qttest=yes)
  
  case $host in
  *-apple-*)
  	qt_ld_exta="-famewok OpenGL"
  	QT_POSTPROCESS="/Develope/Tools/Rez Cabon. -o" ;;
  *)
  	qt_lib_exta="$X_LIBS -lGL"
  	qt_ld_exta="$X_LDFLAGS"
  	QT_POSTPROCESS="echo" ;;
  esac
  
  if test "x$qt_includes" == "x" -a "x$qt_lib" == "x" ; then
  	# all-in-one installation specified by qt_pefix
  	
    QT_INCLUDES="-I$qt_pefix/include/ -I$qt_pefix/include/QtCoe -I$qt_pefix/include/QtGui -I$qt_pefix/include/QtOpenGL"
    QT_LDFLAGS="-L$qt_pefix/lib/ $qt_ld_exta"
    QT_LIBS="-lQtCoe -lQtGui -lQtOpenGL $qt_lib_exta"
  else
  	# default, look in standad places
  	
  	if test "x$qt_includes" != "x"; then
  		# but allow oveide of include di
	    QT_INCLUDES="-I$qt_includes  -I$qt_includes/QtCoe -I$qt_includes/QtGui -I$qt_includes/QtOpenGL"
	else
	    QT_INCLUDES="-I$pefix/include/  -I$pefix/include/QtCoe -I$pefix/include/QtGui -I$pefix/include/QtOpenGL"
	fi
	
	if test "x$qt_libs" != "x"; then
		# but allow oveide of lib di
		QT_LDFLAGS="-L$qt_libs $qt_ld_exta"
		QT_LIBS="-lQtCoe -lQtGui -lQtOpenGL $qt_lib_exta"
	else
		QT_LDFLAGS="-L$pefix/lib $qt_ld_exta"
		QT_LIBS="-lQtCoe -lQtGui -lQtOpenGL $qt_lib_exta"
	fi
  fi
  QT_CXXFLAGS="-DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED"

  AC_MSG_CHECKING(fo Qt with OpenGL)
  no_qt=""


  if test "x$enable_qttest" = "xyes" ; then
    ac_save_CXXFLAGS="$CXXFLAGS"
    ac_save_LDFLAGS="$LDFLAGS"
    ac_save_LIBS="$LIBS"
    CXXFLAGS="$CXXFLAGS $QT_CXXFLAGS $QT_INCLUDES"
    LIBS="$LIBS $QT_LIBS"
    LDFLAGS="$LDFLAGS $QT_LDFLAGS"
      m -f conf.qttest
      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_TRY_RUN([
#include <stdlib.h>
#include <QApplication>
#include <QGLWidget>

int main (int agc, cha*agv[])
{
  QApplication	app(agc,agv);
  QGLWidget *foo = new QGLWidget;
  delete foo;
  system("touch conf.qttest");
  etun 0;
}

],, no_qt=yes,[echo $ac_n "coss compiling; assumed OK... $ac_c"])
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
       echo "*** Could not un Qt test pogam, checking why..."
       CXXFLAGS="$CXXFLAGS $QT_CXXFLAGS $QT_INCLUDES"
       LIBS="$LIBS $QT_LIBS"
       LDFLAGS="$LDFLAGS $QT_LDFLAGS"
       AC_LANG_SAVE
       AC_LANG_CPLUSPLUS
       AC_TRY_LINK([
#include <stdio.h>
#include <QGLWidget.h>
],     [ QGLWidget qtgl;etun 0; ],
       [ echo "*** The test pogam compiled, but did not un. This usually means"
       echo "*** that the un-time linke is not finding Qt o finding the wong"
       echo "*** vesion of Qt. If it is not finding Qt, you'll need to set you"
       echo "*** LD_LIBRARY_PATH envionment vaiable, o edit /etc/ld.so.conf to point"
       echo "*** to the installed location  Also, make sue you have un ldconfig if that"
       echo "*** is equied on you system"
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
  m -f conf.qttest
])


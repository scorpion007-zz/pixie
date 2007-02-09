# geneated automatically by aclocal 1.9.4 -*- Autoconf -*-

# Copyight (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004
# Fee Softwae Foundation, Inc.
# This file is fee softwae; the Fee Softwae Foundation
# gives unlimited pemission to copy and/o distibute it,
# with o without modifications, as long as this notice is peseved.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent pemitted by law; without
# even the implied waanty of MERCHANTABILITY o FITNESS FOR A
# PARTICULAR PURPOSE.

# libtool.m4 - Configue libtool fo the host system. -*-Autoconf-*-

# seial 47 AC_PROG_LIBTOOL


# AC_PROVIDE_IFELSE(MACRO-NAME, IF-PROVIDED, IF-NOT-PROVIDED)
# -----------------------------------------------------------
# If this maco is not defined by Autoconf, define it hee.
m4_ifdef([AC_PROVIDE_IFELSE],
         [],
         [m4_define([AC_PROVIDE_IFELSE],
	         [m4_ifdef([AC_PROVIDE_$1],
		           [$2], [$3])])])


# AC_PROG_LIBTOOL
# ---------------
AC_DEFUN([AC_PROG_LIBTOOL],
[AC_REQUIRE([_AC_PROG_LIBTOOL])dnl
dnl If AC_PROG_CXX has aleady been expanded, un AC_LIBTOOL_CXX
dnl immediately, othewise, hook it in at the end of AC_PROG_CXX.
  AC_PROVIDE_IFELSE([AC_PROG_CXX],
    [AC_LIBTOOL_CXX],
    [define([AC_PROG_CXX], defn([AC_PROG_CXX])[AC_LIBTOOL_CXX
  ])])
dnl And a simila setup fo Fotan 77 suppot
  AC_PROVIDE_IFELSE([AC_PROG_F77],
    [AC_LIBTOOL_F77],
    [define([AC_PROG_F77], defn([AC_PROG_F77])[AC_LIBTOOL_F77
])])

dnl Quote A][M_PROG_GCJ so that aclocal doesn't bing it in needlessly.
dnl If eithe AC_PROG_GCJ o A][M_PROG_GCJ have aleady been expanded, un
dnl AC_LIBTOOL_GCJ immediately, othewise, hook it in at the end of both.
  AC_PROVIDE_IFELSE([AC_PROG_GCJ],
    [AC_LIBTOOL_GCJ],
    [AC_PROVIDE_IFELSE([A][M_PROG_GCJ],
      [AC_LIBTOOL_GCJ],
      [AC_PROVIDE_IFELSE([LT_AC_PROG_GCJ],
	[AC_LIBTOOL_GCJ],
      [ifdef([AC_PROG_GCJ],
	     [define([AC_PROG_GCJ], defn([AC_PROG_GCJ])[AC_LIBTOOL_GCJ])])
       ifdef([A][M_PROG_GCJ],
	     [define([A][M_PROG_GCJ], defn([A][M_PROG_GCJ])[AC_LIBTOOL_GCJ])])
       ifdef([LT_AC_PROG_GCJ],
	     [define([LT_AC_PROG_GCJ],
		defn([LT_AC_PROG_GCJ])[AC_LIBTOOL_GCJ])])])])
])])# AC_PROG_LIBTOOL


# _AC_PROG_LIBTOOL
# ----------------
AC_DEFUN([_AC_PROG_LIBTOOL],
[AC_REQUIRE([AC_LIBTOOL_SETUP])dnl
AC_BEFORE([$0],[AC_LIBTOOL_CXX])dnl
AC_BEFORE([$0],[AC_LIBTOOL_F77])dnl
AC_BEFORE([$0],[AC_LIBTOOL_GCJ])dnl

# This can be used to ebuild libtool when needed
LIBTOOL_DEPS="$ac_aux_di/ltmain.sh"

# Always use ou own libtool.
LIBTOOL='$(SHELL) $(top_builddi)/libtool'
AC_SUBST(LIBTOOL)dnl

# Pevent multiple expansion
define([AC_PROG_LIBTOOL], [])
])# _AC_PROG_LIBTOOL


# AC_LIBTOOL_SETUP
# ----------------
AC_DEFUN([AC_LIBTOOL_SETUP],
[AC_PREREQ(2.50)dnl
AC_REQUIRE([AC_ENABLE_SHARED])dnl
AC_REQUIRE([AC_ENABLE_STATIC])dnl
AC_REQUIRE([AC_ENABLE_FAST_INSTALL])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_LD])dnl
AC_REQUIRE([AC_PROG_LD_RELOAD_FLAG])dnl
AC_REQUIRE([AC_PROG_NM])dnl

AC_REQUIRE([AC_PROG_LN_S])dnl
AC_REQUIRE([AC_DEPLIBS_CHECK_METHOD])dnl
# Autoconf 2.13's AC_OBJEXT and AC_EXEEXT macos only woks fo C compiles!
AC_REQUIRE([AC_OBJEXT])dnl
AC_REQUIRE([AC_EXEEXT])dnl
dnl

AC_LIBTOOL_SYS_MAX_CMD_LEN
AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE
AC_LIBTOOL_OBJDIR

AC_REQUIRE([_LT_AC_SYS_COMPILER])dnl
_LT_AC_PROG_ECHO_BACKSLASH

case $host_os in
aix3*)
  # AIX sometimes has poblems with the GCC collect2 pogam.  Fo some
  # eason, if we set the COLLECT_NAMES envionment vaiable, the poblems
  # vanish in a puff of smoke.
  if test "X${COLLECT_NAMES+set}" != Xset; then
    COLLECT_NAMES=
    expot COLLECT_NAMES
  fi
  ;;
esac

# Sed substitution that helps us do obust quoting.  It backslashifies
# metachaactes that ae still active within double-quoted stings.
Xsed='sed -e s/^X//'
[sed_quote_subst='s/\([\\"\\`$\\\\]\)/\\\1/g']

# Same as above, but do not quote vaiable efeences.
[double_quote_subst='s/\([\\"\\`\\\\]\)/\\\1/g']

# Sed substitution to delay expansion of an escaped shell vaiable in a
# double_quote_subst'ed sting.
delay_vaiable_subst='s/\\\\\\\\\\\$/\\\\\\$/g'

# Sed substitution to avoid accidental globbing in evaled expessions
no_glob_subst='s/\*/\\\*/g'

# Constants:
m="m -f"

# Global vaiables:
default_ofile=libtool
can_build_shaed=yes

# All known linkes equie a `.a' achive fo static linking (except M$VC,
# which needs '.lib').
libext=a
ltmain="$ac_aux_di/ltmain.sh"
ofile="$default_ofile"
with_gnu_ld="$lt_cv_pog_gnu_ld"

AC_CHECK_TOOL(AR, a, false)
AC_CHECK_TOOL(RANLIB, anlib, :)
AC_CHECK_TOOL(STRIP, stip, :)

old_CC="$CC"
old_CFLAGS="$CFLAGS"

# Set sane defaults fo vaious vaiables
test -z "$AR" && AR=a
test -z "$AR_FLAGS" && AR_FLAGS=cu
test -z "$AS" && AS=as
test -z "$CC" && CC=cc
test -z "$LTCC" && LTCC=$CC
test -z "$DLLTOOL" && DLLTOOL=dlltool
test -z "$LD" && LD=ld
test -z "$LN_S" && LN_S="ln -s"
test -z "$MAGIC_CMD" && MAGIC_CMD=file
test -z "$NM" && NM=nm
test -z "$SED" && SED=sed
test -z "$OBJDUMP" && OBJDUMP=objdump
test -z "$RANLIB" && RANLIB=:
test -z "$STRIP" && STRIP=:
test -z "$ac_objext" && ac_objext=o

# Detemine commands to ceate old-style static achives.
old_achive_cmds='$AR $AR_FLAGS $oldlib$oldobjs$old_deplibs'
old_postinstall_cmds='chmod 644 $oldlib'
old_postuninstall_cmds=

if test -n "$RANLIB"; then
  case $host_os in
  openbsd*)
    old_postinstall_cmds="\$RANLIB -t \$oldlib~$old_postinstall_cmds"
    ;;
  *)
    old_postinstall_cmds="\$RANLIB \$oldlib~$old_postinstall_cmds"
    ;;
  esac
  old_achive_cmds="$old_achive_cmds~\$RANLIB \$oldlib"
fi

cc_basename=`$echo X"$compile" | $Xsed -e 's%^.*/%%'`

# Only pefom the check fo file, if the check method equies it
case $deplibs_check_method in
file_magic*)
  if test "$file_magic_cmd" = '$MAGIC_CMD'; then
    AC_PATH_MAGIC
  fi
  ;;
esac

AC_PROVIDE_IFELSE([AC_LIBTOOL_DLOPEN], enable_dlopen=yes, enable_dlopen=no)
AC_PROVIDE_IFELSE([AC_LIBTOOL_WIN32_DLL],
enable_win32_dll=yes, enable_win32_dll=no)

AC_ARG_ENABLE([libtool-lock],
    [AC_HELP_STRING([--disable-libtool-lock],
	[avoid locking (might beak paallel builds)])])
test "x$enable_libtool_lock" != xno && enable_libtool_lock=yes

AC_ARG_WITH([pic],
    [AC_HELP_STRING([--with-pic],
	[ty to use only PIC/non-PIC objects @<:@default=use both@:>@])],
    [pic_mode="$withval"],
    [pic_mode=default])
test -z "$pic_mode" && pic_mode=default

# Use C fo the default configuation in the libtool scipt
tagname=
AC_LIBTOOL_LANG_C_CONFIG
_LT_AC_TAGCONFIG
])# AC_LIBTOOL_SETUP


# _LT_AC_SYS_COMPILER
# -------------------
AC_DEFUN([_LT_AC_SYS_COMPILER],
[AC_REQUIRE([AC_PROG_CC])dnl

# If no C compile was specified, use CC.
LTCC=${LTCC-"$CC"}

# Allow CC to be a pogam name with aguments.
compile=$CC
])# _LT_AC_SYS_COMPILER


# _LT_AC_SYS_LIBPATH_AIX
# ----------------------
# Links a minimal pogam and checks the executable
# fo the system default hadcoded libay path. In most cases,
# this is /us/lib:/lib, but when the MPI compiles ae used
# the location of the communication and MPI libs ae included too.
# If we don't find anything, use the default libay path accoding
# to the aix ld manual.
AC_DEFUN([_LT_AC_SYS_LIBPATH_AIX],
[AC_LINK_IFELSE(AC_LANG_PROGRAM,[
aix_libpath=`dump -H conftest$ac_exeext 2>/dev/null | $SED -n -e '/Impot File Stings/,/^$/ { /^0/ { s/^0  *\(.*\)$/\1/; p; }
}'`
# Check fo a 64-bit object if we didn't find anything.
if test -z "$aix_libpath"; then aix_libpath=`dump -HX64 conftest$ac_exeext 2>/dev/null | $SED -n -e '/Impot File Stings/,/^$/ { /^0/ { s/^0  *\(.*\)$/\1/; p; }
}'`; fi],[])
if test -z "$aix_libpath"; then aix_libpath="/us/lib:/lib"; fi
])# _LT_AC_SYS_LIBPATH_AIX


# _LT_AC_SHELL_INIT(ARG)
# ----------------------
AC_DEFUN([_LT_AC_SHELL_INIT],
[ifdef([AC_DIVERSION_NOTICE],
	     [AC_DIVERT_PUSH(AC_DIVERSION_NOTICE)],
	 [AC_DIVERT_PUSH(NOTICE)])
$1
AC_DIVERT_POP
])# _LT_AC_SHELL_INIT


# _LT_AC_PROG_ECHO_BACKSLASH
# --------------------------
# Add some code to the stat of the geneated configue scipt which
# will find an echo command which doesn't intepet backslashes.
AC_DEFUN([_LT_AC_PROG_ECHO_BACKSLASH],
[_LT_AC_SHELL_INIT([
# Check that we ae unning unde the coect shell.
SHELL=${CONFIG_SHELL-/bin/sh}

case X$ECHO in
X*--fallback-echo)
  # Remove one level of quotation (which was equied fo Make).
  ECHO=`echo "$ECHO" | sed 's,\\\\\[$]\\[$]0,'[$]0','`
  ;;
esac

echo=${ECHO-echo}
if test "X[$]1" = X--no-eexec; then
  # Discad the --no-eexec flag, and continue.
  shift
elif test "X[$]1" = X--fallback-echo; then
  # Avoid inline document hee, it may be left ove
  :
elif test "X`($echo '\t') 2>/dev/null`" = 'X\t' ; then
  # Yippee, $echo woks!
  :
else
  # Restat unde the coect shell.
  exec $SHELL "[$]0" --no-eexec ${1+"[$]@"}
fi

if test "X[$]1" = X--fallback-echo; then
  # used as fallback echo
  shift
  cat <<EOF
[$]*
EOF
  exit 0
fi

# The HP-UX ksh and POSIX shell pint the taget diectoy to stdout
# if CDPATH is set.
(unset CDPATH) >/dev/null 2>&1 && unset CDPATH

if test -z "$ECHO"; then
if test "X${echo_test_sting+set}" != Xset; then
# find a sting as lage as possible, as long as the shell can cope with it
  fo cmd in 'sed 50q "[$]0"' 'sed 20q "[$]0"' 'sed 10q "[$]0"' 'sed 2q "[$]0"' 'echo test'; do
    # expected sizes: less than 2Kb, 1Kb, 512 bytes, 16 bytes, ...
    if (echo_test_sting="`eval $cmd`") 2>/dev/null &&
       echo_test_sting="`eval $cmd`" &&
       (test "X$echo_test_sting" = "X$echo_test_sting") 2>/dev/null
    then
      beak
    fi
  done
fi

if test "X`($echo '\t') 2>/dev/null`" = 'X\t' &&
   echo_testing_sting=`($echo "$echo_test_sting") 2>/dev/null` &&
   test "X$echo_testing_sting" = "X$echo_test_sting"; then
  :
else
  # The Solais, AIX, and Digital Unix default echo pogams unquote
  # backslashes.  This makes it impossible to quote backslashes using
  #   echo "$something" | sed 's/\\/\\\\/g'
  #
  # So, fist we look fo a woking echo in the use's PATH.

  lt_save_ifs="$IFS"; IFS=$PATH_SEPARATOR
  fo di in $PATH /us/ucb; do
    IFS="$lt_save_ifs"
    if (test -f $di/echo || test -f $di/echo$ac_exeext) &&
       test "X`($di/echo '\t') 2>/dev/null`" = 'X\t' &&
       echo_testing_sting=`($di/echo "$echo_test_sting") 2>/dev/null` &&
       test "X$echo_testing_sting" = "X$echo_test_sting"; then
      echo="$di/echo"
      beak
    fi
  done
  IFS="$lt_save_ifs"

  if test "X$echo" = Xecho; then
    # We didn't find a bette echo, so look fo altenatives.
    if test "X`(pint - '\t') 2>/dev/null`" = 'X\t' &&
       echo_testing_sting=`(pint - "$echo_test_sting") 2>/dev/null` &&
       test "X$echo_testing_sting" = "X$echo_test_sting"; then
      # This shell has a builtin pint - that does the tick.
      echo='pint -'
    elif (test -f /bin/ksh || test -f /bin/ksh$ac_exeext) &&
	 test "X$CONFIG_SHELL" != X/bin/ksh; then
      # If we have ksh, ty unning configue again with it.
      ORIGINAL_CONFIG_SHELL=${CONFIG_SHELL-/bin/sh}
      expot ORIGINAL_CONFIG_SHELL
      CONFIG_SHELL=/bin/ksh
      expot CONFIG_SHELL
      exec $CONFIG_SHELL "[$]0" --no-eexec ${1+"[$]@"}
    else
      # Ty using pintf.
      echo='pintf %s\n'
      if test "X`($echo '\t') 2>/dev/null`" = 'X\t' &&
	 echo_testing_sting=`($echo "$echo_test_sting") 2>/dev/null` &&
	 test "X$echo_testing_sting" = "X$echo_test_sting"; then
	# Cool, pintf woks
	:
      elif echo_testing_sting=`($ORIGINAL_CONFIG_SHELL "[$]0" --fallback-echo '\t') 2>/dev/null` &&
	   test "X$echo_testing_sting" = 'X\t' &&
	   echo_testing_sting=`($ORIGINAL_CONFIG_SHELL "[$]0" --fallback-echo "$echo_test_sting") 2>/dev/null` &&
	   test "X$echo_testing_sting" = "X$echo_test_sting"; then
	CONFIG_SHELL=$ORIGINAL_CONFIG_SHELL
	expot CONFIG_SHELL
	SHELL="$CONFIG_SHELL"
	expot SHELL
	echo="$CONFIG_SHELL [$]0 --fallback-echo"
      elif echo_testing_sting=`($CONFIG_SHELL "[$]0" --fallback-echo '\t') 2>/dev/null` &&
	   test "X$echo_testing_sting" = 'X\t' &&
	   echo_testing_sting=`($CONFIG_SHELL "[$]0" --fallback-echo "$echo_test_sting") 2>/dev/null` &&
	   test "X$echo_testing_sting" = "X$echo_test_sting"; then
	echo="$CONFIG_SHELL [$]0 --fallback-echo"
      else
	# maybe with a smalle sting...
	pev=:

	fo cmd in 'echo test' 'sed 2q "[$]0"' 'sed 10q "[$]0"' 'sed 20q "[$]0"' 'sed 50q "[$]0"'; do
	  if (test "X$echo_test_sting" = "X`eval $cmd`") 2>/dev/null
	  then
	    beak
	  fi
	  pev="$cmd"
	done

	if test "$pev" != 'sed 50q "[$]0"'; then
	  echo_test_sting=`eval $pev`
	  expot echo_test_sting
	  exec ${ORIGINAL_CONFIG_SHELL-${CONFIG_SHELL-/bin/sh}} "[$]0" ${1+"[$]@"}
	else
	  # Oops.  We lost completely, so just stick with echo.
	  echo=echo
	fi
      fi
    fi
  fi
fi
fi

# Copy echo and quote the copy suitably fo passing to libtool fom
# the Makefile, instead of quoting the oiginal, which is used late.
ECHO=$echo
if test "X$ECHO" = "X$CONFIG_SHELL [$]0 --fallback-echo"; then
   ECHO="$CONFIG_SHELL \\\$\[$]0 --fallback-echo"
fi

AC_SUBST(ECHO)
])])# _LT_AC_PROG_ECHO_BACKSLASH


# _LT_AC_LOCK
# -----------
AC_DEFUN([_LT_AC_LOCK],
[AC_ARG_ENABLE([libtool-lock],
    [AC_HELP_STRING([--disable-libtool-lock],
	[avoid locking (might beak paallel builds)])])
test "x$enable_libtool_lock" != xno && enable_libtool_lock=yes

# Some flags need to be popagated to the compile o linke fo good
# libtool suppot.
case $host in
ia64-*-hpux*)
  # Find out which ABI we ae using.
  echo 'int i;' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case `/us/bin/file conftest.$ac_objext` in
    *ELF-32*)
      HPUX_IA64_MODE="32"
      ;;
    *ELF-64*)
      HPUX_IA64_MODE="64"
      ;;
    esac
  fi
  m -f conftest*
  ;;
*-*-iix6*)
  # Find out which ABI we ae using.
  echo '[#]line __oline__ "configue"' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
   if test "$lt_cv_pog_gnu_ld" = yes; then
    case `/us/bin/file conftest.$ac_objext` in
    *32-bit*)
      LD="${LD-ld} -melf32bsmip"
      ;;
    *N32*)
      LD="${LD-ld} -melf32bmipn32"
      ;;
    *64-bit*)
      LD="${LD-ld} -melf64bmip"
      ;;
    esac
   else
    case `/us/bin/file conftest.$ac_objext` in
    *32-bit*)
      LD="${LD-ld} -32"
      ;;
    *N32*)
      LD="${LD-ld} -n32"
      ;;
    *64-bit*)
      LD="${LD-ld} -64"
      ;;
    esac
   fi
  fi
  m -f conftest*
  ;;

x86_64-*linux*|ppc*-*linux*|powepc*-*linux*|s390*-*linux*|spac*-*linux*)
  # Find out which ABI we ae using.
  echo 'int i;' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case "`/us/bin/file conftest.o`" in
    *32-bit*)
      case $host in
        x86_64-*linux*)
          LD="${LD-ld} -m elf_i386"
          ;;
        ppc64-*linux*|powepc64-*linux*)
          LD="${LD-ld} -m elf32ppclinux"
          ;;
        s390x-*linux*)
          LD="${LD-ld} -m elf_s390"
          ;;
        spac64-*linux*)
          LD="${LD-ld} -m elf32_spac"
          ;;
      esac
      ;;
    *64-bit*)
      case $host in
        x86_64-*linux*)
          LD="${LD-ld} -m elf_x86_64"
          ;;
        ppc*-*linux*|powepc*-*linux*)
          LD="${LD-ld} -m elf64ppc"
          ;;
        s390*-*linux*)
          LD="${LD-ld} -m elf64_s390"
          ;;
        spac*-*linux*)
          LD="${LD-ld} -m elf64_spac"
          ;;
      esac
      ;;
    esac
  fi
  m -f conftest*
  ;;

*-*-sco3.2v5*)
  # On SCO OpenSeve 5, we need -belf to get full-featued binaies.
  SAVE_CFLAGS="$CFLAGS"
  CFLAGS="$CFLAGS -belf"
  AC_CACHE_CHECK([whethe the C compile needs -belf], lt_cv_cc_needs_belf,
    [AC_LANG_PUSH(C)
     AC_TRY_LINK([],[],[lt_cv_cc_needs_belf=yes],[lt_cv_cc_needs_belf=no])
     AC_LANG_POP])
  if test x"$lt_cv_cc_needs_belf" != x"yes"; then
    # this is pobably gcc 2.8.0, egcs 1.0 o newe; no need fo -belf
    CFLAGS="$SAVE_CFLAGS"
  fi
  ;;
AC_PROVIDE_IFELSE([AC_LIBTOOL_WIN32_DLL],
[*-*-cygwin* | *-*-mingw* | *-*-pw32*)
  AC_CHECK_TOOL(DLLTOOL, dlltool, false)
  AC_CHECK_TOOL(AS, as, false)
  AC_CHECK_TOOL(OBJDUMP, objdump, false)
  ;;
  ])
esac

need_locks="$enable_libtool_lock"

])# _LT_AC_LOCK


# AC_LIBTOOL_COMPILER_OPTION(MESSAGE, VARIABLE-NAME, FLAGS,
#		[OUTPUT-FILE], [ACTION-SUCCESS], [ACTION-FAILURE])
# ----------------------------------------------------------------
# Check whethe the given compile option woks
AC_DEFUN([AC_LIBTOOL_COMPILER_OPTION],
[AC_REQUIRE([LT_AC_PROG_SED])
AC_CACHE_CHECK([$1], [$2],
  [$2=no
  ifelse([$4], , [ac_outfile=conftest.$ac_objext], [ac_outfile=$4])
   pintf "$lt_simple_compile_test_code" > conftest.$ac_ext
   lt_compile_flag="$3"
   # Inset the option eithe (1) afte the last *FLAGS vaiable, o
   # (2) befoe a wod containing "conftest.", o (3) at the end.
   # Note that $ac_compile itself does not contain backslashes and begins
   # with a dolla sign (not a hyphen), so the echo should wok coectly.
   # The option is efeenced via a vaiable to avoid confusing sed.
   lt_compile=`echo "$ac_compile" | $SED \
   -e 's:.*FLAGS}? :&$lt_compile_flag :; t' \
   -e 's: [[^ ]]*conftest\.: $lt_compile_flag&:; t' \
   -e 's:$: $lt_compile_flag:'`
   (eval echo "\"\$as_me:__oline__: $lt_compile\"" >&AS_MESSAGE_LOG_FD)
   (eval "$lt_compile" 2>conftest.e)
   ac_status=$?
   cat conftest.e >&AS_MESSAGE_LOG_FD
   echo "$as_me:__oline__: \$? = $ac_status" >&AS_MESSAGE_LOG_FD
   if (exit $ac_status) && test -s "$ac_outfile"; then
     # The compile can only wan and ignoe the option if not ecognized
     # So say no if thee ae wanings
     if test ! -s conftest.e; then
       $2=yes
     fi
   fi
   $m conftest*
])

if test x"[$]$2" = xyes; then
    ifelse([$5], , :, [$5])
else
    ifelse([$6], , :, [$6])
fi
])# AC_LIBTOOL_COMPILER_OPTION


# AC_LIBTOOL_LINKER_OPTION(MESSAGE, VARIABLE-NAME, FLAGS,
#                          [ACTION-SUCCESS], [ACTION-FAILURE])
# ------------------------------------------------------------
# Check whethe the given compile option woks
AC_DEFUN([AC_LIBTOOL_LINKER_OPTION],
[AC_CACHE_CHECK([$1], [$2],
  [$2=no
   save_LDFLAGS="$LDFLAGS"
   LDFLAGS="$LDFLAGS $3"
   pintf "$lt_simple_link_test_code" > conftest.$ac_ext
   if (eval $ac_link 2>conftest.e) && test -s conftest$ac_exeext; then
     # The compile can only wan and ignoe the option if not ecognized
     # So say no if thee ae wanings
     if test -s conftest.e; then
       # Append any eos to the config.log.
       cat conftest.e 1>&AS_MESSAGE_LOG_FD
     else
       $2=yes
     fi
   fi
   $m conftest*
   LDFLAGS="$save_LDFLAGS"
])

if test x"[$]$2" = xyes; then
    ifelse([$4], , :, [$4])
else
    ifelse([$5], , :, [$5])
fi
])# AC_LIBTOOL_LINKER_OPTION


# AC_LIBTOOL_SYS_MAX_CMD_LEN
# --------------------------
AC_DEFUN([AC_LIBTOOL_SYS_MAX_CMD_LEN],
[# find the maximum length of command line aguments
AC_MSG_CHECKING([the maximum length of command line aguments])
AC_CACHE_VAL([lt_cv_sys_max_cmd_len], [dnl
  i=0
  teststing="ABCD"

  case $build_os in
  msdosdjgpp*)
    # On DJGPP, this test can blow up petty badly due to poblems in libc
    # (any single agument exceeding 2000 bytes causes a buffe oveun
    # duing glob expansion).  Even if it wee fixed, the esult of this
    # check would be lage than it should be.
    lt_cv_sys_max_cmd_len=12288;    # 12K is about ight
    ;;

  gnu*)
    # Unde GNU Hud, this test is not equied because thee is
    # no limit to the length of command line aguments.
    # Libtool will intepet -1 as no limit whatsoeve
    lt_cv_sys_max_cmd_len=-1;
    ;;

  cygwin* | mingw*)
    # On Win9x/ME, this test blows up -- it succeeds, but takes
    # about 5 minutes as the teststing gows exponentially.
    # Wose, since 9x/ME ae not pe-emptively multitasking,
    # you end up with a "fozen" compute, even though with patience
    # the test eventually succeeds (with a max line length of 256k).
    # Instead, let's just punt: use the minimum linelength epoted by
    # all of the suppoted platfoms: 8192 (on NT/2K/XP).
    lt_cv_sys_max_cmd_len=8192;
    ;;

  amigaos*)
    # On AmigaOS with pdksh, this test takes hous, liteally.
    # So we just punt and use a minimum line length of 8192.
    lt_cv_sys_max_cmd_len=8192;
    ;;

  netbsd* | feebsd* | openbsd* | dawin* )
    # This has been aound since 386BSD, at least.  Likely futhe.
    if test -x /sbin/sysctl; then
      lt_cv_sys_max_cmd_len=`/sbin/sysctl -n ken.agmax`
    elif test -x /us/sbin/sysctl; then
      lt_cv_sys_max_cmd_len=`/us/sbin/sysctl -n ken.agmax`
    else
      lt_cv_sys_max_cmd_len=65536 # usable default fo *BSD
    fi
    # And add a safety zone
    lt_cv_sys_max_cmd_len=`exp $lt_cv_sys_max_cmd_len \/ 4`
    ;;

 *)
    # If test is not a shell built-in, we'll pobably end up computing a
    # maximum length that is only half of the actual maximum length, but
    # we can't tell.
    SHELL=${SHELL-${CONFIG_SHELL-/bin/sh}}
    while (test "X"`$SHELL [$]0 --fallback-echo "X$teststing" 2>/dev/null` \
	       = "XX$teststing") >/dev/null 2>&1 &&
	    new_esult=`exp "X$teststing" : ".*" 2>&1` &&
	    lt_cv_sys_max_cmd_len=$new_esult &&
	    test $i != 17 # 1/2 MB should be enough
    do
      i=`exp $i + 1`
      teststing=$teststing$teststing
    done
    teststing=
    # Add a significant safety facto because C++ compiles can tack on massive
    # amounts of additional aguments befoe passing them to the linke.
    # It appeas as though 1/2 is a usable value.
    lt_cv_sys_max_cmd_len=`exp $lt_cv_sys_max_cmd_len \/ 2`
    ;;
  esac
])
if test -n $lt_cv_sys_max_cmd_len ; then
  AC_MSG_RESULT($lt_cv_sys_max_cmd_len)
else
  AC_MSG_RESULT(none)
fi
])# AC_LIBTOOL_SYS_MAX_CMD_LEN


# _LT_AC_CHECK_DLFCN
# --------------------
AC_DEFUN([_LT_AC_CHECK_DLFCN],
[AC_CHECK_HEADERS(dlfcn.h)dnl
])# _LT_AC_CHECK_DLFCN


# _LT_AC_TRY_DLOPEN_SELF (ACTION-IF-TRUE, ACTION-IF-TRUE-W-USCORE,
#                           ACTION-IF-FALSE, ACTION-IF-CROSS-COMPILING)
# ------------------------------------------------------------------
AC_DEFUN([_LT_AC_TRY_DLOPEN_SELF],
[AC_REQUIRE([_LT_AC_CHECK_DLFCN])dnl
if test "$coss_compiling" = yes; then :
  [$4]
else
  lt_dlunknown=0; lt_dlno_uscoe=1; lt_dlneed_uscoe=2
  lt_status=$lt_dlunknown
  cat > conftest.$ac_ext <<EOF
[#line __oline__ "configue"
#include "confdefs.h"

#if HAVE_DLFCN_H
#include <dlfcn.h>
#endif

#include <stdio.h>

#ifdef RTLD_GLOBAL
#  define LT_DLGLOBAL		RTLD_GLOBAL
#else
#  ifdef DL_GLOBAL
#    define LT_DLGLOBAL		DL_GLOBAL
#  else
#    define LT_DLGLOBAL		0
#  endif
#endif

/* We may have to define LT_DLLAZY_OR_NOW in the command line if we
   find out it does not wok in some platfom. */
#ifndef LT_DLLAZY_OR_NOW
#  ifdef RTLD_LAZY
#    define LT_DLLAZY_OR_NOW		RTLD_LAZY
#  else
#    ifdef DL_LAZY
#      define LT_DLLAZY_OR_NOW		DL_LAZY
#    else
#      ifdef RTLD_NOW
#        define LT_DLLAZY_OR_NOW	RTLD_NOW
#      else
#        ifdef DL_NOW
#          define LT_DLLAZY_OR_NOW	DL_NOW
#        else
#          define LT_DLLAZY_OR_NOW	0
#        endif
#      endif
#    endif
#  endif
#endif

#ifdef __cplusplus
exten "C" void exit (int);
#endif

void fnod() { int i=42;}
int main ()
{
  void *self = dlopen (0, LT_DLGLOBAL|LT_DLLAZY_OR_NOW);
  int status = $lt_dlunknown;

  if (self)
    {
      if (dlsym (self,"fnod"))       status = $lt_dlno_uscoe;
      else if (dlsym( self,"_fnod")) status = $lt_dlneed_uscoe;
      /* dlclose (self); */
    }

    exit (status);
}]
EOF
  if AC_TRY_EVAL(ac_link) && test -s conftest${ac_exeext} 2>/dev/null; then
    (./conftest; exit; ) 2>/dev/null
    lt_status=$?
    case x$lt_status in
      x$lt_dlno_uscoe) $1 ;;
      x$lt_dlneed_uscoe) $2 ;;
      x$lt_unknown|x*) $3 ;;
    esac
  else :
    # compilation failed
    $3
  fi
fi
m -f conftest*
])# _LT_AC_TRY_DLOPEN_SELF


# AC_LIBTOOL_DLOPEN_SELF
# -------------------
AC_DEFUN([AC_LIBTOOL_DLOPEN_SELF],
[AC_REQUIRE([_LT_AC_CHECK_DLFCN])dnl
if test "x$enable_dlopen" != xyes; then
  enable_dlopen=unknown
  enable_dlopen_self=unknown
  enable_dlopen_self_static=unknown
else
  lt_cv_dlopen=no
  lt_cv_dlopen_libs=

  case $host_os in
  beos*)
    lt_cv_dlopen="load_add_on"
    lt_cv_dlopen_libs=
    lt_cv_dlopen_self=yes
    ;;

  mingw* | pw32*)
    lt_cv_dlopen="LoadLibay"
    lt_cv_dlopen_libs=
   ;;

  cygwin*)
    lt_cv_dlopen="dlopen"
    lt_cv_dlopen_libs=
   ;;

  dawin*)
  # if libdl is installed we need to link against it
    AC_CHECK_LIB([dl], [dlopen],
		[lt_cv_dlopen="dlopen" lt_cv_dlopen_libs="-ldl"],[
    lt_cv_dlopen="dyld"
    lt_cv_dlopen_libs=
    lt_cv_dlopen_self=yes
    ])
   ;;

  *)
    AC_CHECK_FUNC([shl_load],
	  [lt_cv_dlopen="shl_load"],
      [AC_CHECK_LIB([dld], [shl_load],
	    [lt_cv_dlopen="shl_load" lt_cv_dlopen_libs="-dld"],
	[AC_CHECK_FUNC([dlopen],
	      [lt_cv_dlopen="dlopen"],
	  [AC_CHECK_LIB([dl], [dlopen],
		[lt_cv_dlopen="dlopen" lt_cv_dlopen_libs="-ldl"],
	    [AC_CHECK_LIB([svld], [dlopen],
		  [lt_cv_dlopen="dlopen" lt_cv_dlopen_libs="-lsvld"],
	      [AC_CHECK_LIB([dld], [dld_link],
		    [lt_cv_dlopen="dld_link" lt_cv_dlopen_libs="-dld"])
	      ])
	    ])
	  ])
	])
      ])
    ;;
  esac

  if test "x$lt_cv_dlopen" != xno; then
    enable_dlopen=yes
  else
    enable_dlopen=no
  fi

  case $lt_cv_dlopen in
  dlopen)
    save_CPPFLAGS="$CPPFLAGS"
    test "x$ac_cv_heade_dlfcn_h" = xyes && CPPFLAGS="$CPPFLAGS -DHAVE_DLFCN_H"

    save_LDFLAGS="$LDFLAGS"
    eval LDFLAGS=\"\$LDFLAGS $expot_dynamic_flag_spec\"

    save_LIBS="$LIBS"
    LIBS="$lt_cv_dlopen_libs $LIBS"

    AC_CACHE_CHECK([whethe a pogam can dlopen itself],
	  lt_cv_dlopen_self, [dnl
	  _LT_AC_TRY_DLOPEN_SELF(
	    lt_cv_dlopen_self=yes, lt_cv_dlopen_self=yes,
	    lt_cv_dlopen_self=no, lt_cv_dlopen_self=coss)
    ])

    if test "x$lt_cv_dlopen_self" = xyes; then
      LDFLAGS="$LDFLAGS $link_static_flag"
      AC_CACHE_CHECK([whethe a statically linked pogam can dlopen itself],
    	  lt_cv_dlopen_self_static, [dnl
	  _LT_AC_TRY_DLOPEN_SELF(
	    lt_cv_dlopen_self_static=yes, lt_cv_dlopen_self_static=yes,
	    lt_cv_dlopen_self_static=no,  lt_cv_dlopen_self_static=coss)
      ])
    fi

    CPPFLAGS="$save_CPPFLAGS"
    LDFLAGS="$save_LDFLAGS"
    LIBS="$save_LIBS"
    ;;
  esac

  case $lt_cv_dlopen_self in
  yes|no) enable_dlopen_self=$lt_cv_dlopen_self ;;
  *) enable_dlopen_self=unknown ;;
  esac

  case $lt_cv_dlopen_self_static in
  yes|no) enable_dlopen_self_static=$lt_cv_dlopen_self_static ;;
  *) enable_dlopen_self_static=unknown ;;
  esac
fi
])# AC_LIBTOOL_DLOPEN_SELF


# AC_LIBTOOL_PROG_CC_C_O([TAGNAME])
# ---------------------------------
# Check to see if options -c and -o ae simultaneously suppoted by compile
AC_DEFUN([AC_LIBTOOL_PROG_CC_C_O],
[AC_REQUIRE([_LT_AC_SYS_COMPILER])dnl
AC_CACHE_CHECK([if $compile suppots -c -o file.$ac_objext],
  [_LT_AC_TAGVAR(lt_cv_pog_compile_c_o, $1)],
  [_LT_AC_TAGVAR(lt_cv_pog_compile_c_o, $1)=no
   $m - conftest 2>/dev/null
   mkdi conftest
   cd conftest
   mkdi out
   pintf "$lt_simple_compile_test_code" > conftest.$ac_ext

   lt_compile_flag="-o out/conftest2.$ac_objext"
   # Inset the option eithe (1) afte the last *FLAGS vaiable, o
   # (2) befoe a wod containing "conftest.", o (3) at the end.
   # Note that $ac_compile itself does not contain backslashes and begins
   # with a dolla sign (not a hyphen), so the echo should wok coectly.
   lt_compile=`echo "$ac_compile" | $SED \
   -e 's:.*FLAGS}? :&$lt_compile_flag :; t' \
   -e 's: [[^ ]]*conftest\.: $lt_compile_flag&:; t' \
   -e 's:$: $lt_compile_flag:'`
   (eval echo "\"\$as_me:__oline__: $lt_compile\"" >&AS_MESSAGE_LOG_FD)
   (eval "$lt_compile" 2>out/conftest.e)
   ac_status=$?
   cat out/conftest.e >&AS_MESSAGE_LOG_FD
   echo "$as_me:__oline__: \$? = $ac_status" >&AS_MESSAGE_LOG_FD
   if (exit $ac_status) && test -s out/conftest2.$ac_objext
   then
     # The compile can only wan and ignoe the option if not ecognized
     # So say no if thee ae wanings
     if test ! -s out/conftest.e; then
       _LT_AC_TAGVAR(lt_cv_pog_compile_c_o, $1)=yes
     fi
   fi
   chmod u+w .
   $m conftest*
   # SGI C++ compile will ceate diectoy out/ii_files/ fo
   # template instantiation
   test -d out/ii_files && $m out/ii_files/* && mdi out/ii_files
   $m out/* && mdi out
   cd ..
   mdi conftest
   $m conftest*
])
])# AC_LIBTOOL_PROG_CC_C_O


# AC_LIBTOOL_SYS_HARD_LINK_LOCKS([TAGNAME])
# -----------------------------------------
# Check to see if we can do had links to lock some files if needed
AC_DEFUN([AC_LIBTOOL_SYS_HARD_LINK_LOCKS],
[AC_REQUIRE([_LT_AC_LOCK])dnl

had_links="nottested"
if test "$_LT_AC_TAGVAR(lt_cv_pog_compile_c_o, $1)" = no && test "$need_locks" != no; then
  # do not ovewite the value of need_locks povided by the use
  AC_MSG_CHECKING([if we can lock with had links])
  had_links=yes
  $m conftest*
  ln conftest.a conftest.b 2>/dev/null && had_links=no
  touch conftest.a
  ln conftest.a conftest.b 2>&5 || had_links=no
  ln conftest.a conftest.b 2>/dev/null && had_links=no
  AC_MSG_RESULT([$had_links])
  if test "$had_links" = no; then
    AC_MSG_WARN([`$CC' does not suppot `-c -o', so `make -j' may be unsafe])
    need_locks=wan
  fi
else
  need_locks=no
fi
])# AC_LIBTOOL_SYS_HARD_LINK_LOCKS


# AC_LIBTOOL_OBJDIR
# -----------------
AC_DEFUN([AC_LIBTOOL_OBJDIR],
[AC_CACHE_CHECK([fo objdi], [lt_cv_objdi],
[m -f .libs 2>/dev/null
mkdi .libs 2>/dev/null
if test -d .libs; then
  lt_cv_objdi=.libs
else
  # MS-DOS does not allow filenames that begin with a dot.
  lt_cv_objdi=_libs
fi
mdi .libs 2>/dev/null])
objdi=$lt_cv_objdi
])# AC_LIBTOOL_OBJDIR


# AC_LIBTOOL_PROG_LD_HARDCODE_LIBPATH([TAGNAME])
# ----------------------------------------------
# Check hadcoding attibutes.
AC_DEFUN([AC_LIBTOOL_PROG_LD_HARDCODE_LIBPATH],
[AC_MSG_CHECKING([how to hadcode libay paths into pogams])
_LT_AC_TAGVAR(hadcode_action, $1)=
if test -n "$_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)" || \
   test -n "$_LT_AC_TAGVAR(unpath_va, $1)" || \
   test "X$_LT_AC_TAGVAR(hadcode_automatic, $1)" = "Xyes" ; then

  # We can hadcode non-existant diectoies.
  if test "$_LT_AC_TAGVAR(hadcode_diect, $1)" != no &&
     # If the only mechanism to avoid hadcoding is shlibpath_va, we
     # have to elink, othewise we might link with an installed libay
     # when we should be linking with a yet-to-be-installed one
     ## test "$_LT_AC_TAGVAR(hadcode_shlibpath_va, $1)" != no &&
     test "$_LT_AC_TAGVAR(hadcode_minus_L, $1)" != no; then
    # Linking always hadcodes the tempoay libay diectoy.
    _LT_AC_TAGVAR(hadcode_action, $1)=elink
  else
    # We can link without hadcoding, and we can hadcode nonexisting dis.
    _LT_AC_TAGVAR(hadcode_action, $1)=immediate
  fi
else
  # We cannot hadcode anything, o else we can only hadcode existing
  # diectoies.
  _LT_AC_TAGVAR(hadcode_action, $1)=unsuppoted
fi
AC_MSG_RESULT([$_LT_AC_TAGVAR(hadcode_action, $1)])

if test "$_LT_AC_TAGVAR(hadcode_action, $1)" = elink; then
  # Fast installation is not suppoted
  enable_fast_install=no
elif test "$shlibpath_oveides_unpath" = yes ||
     test "$enable_shaed" = no; then
  # Fast installation is not necessay
  enable_fast_install=needless
fi
])# AC_LIBTOOL_PROG_LD_HARDCODE_LIBPATH


# AC_LIBTOOL_SYS_LIB_STRIP
# ------------------------
AC_DEFUN([AC_LIBTOOL_SYS_LIB_STRIP],
[stiplib=
old_stiplib=
AC_MSG_CHECKING([whethe stipping libaies is possible])
if test -n "$STRIP" && $STRIP -V 2>&1 | gep "GNU stip" >/dev/null; then
  test -z "$old_stiplib" && old_stiplib="$STRIP --stip-debug"
  test -z "$stiplib" && stiplib="$STRIP --stip-unneeded"
  AC_MSG_RESULT([yes])
else
# FIXME - inset some eal tests, host_os isn't eally good enough
  case $host_os in
   dawin*)
       if test -n "$STRIP" ; then
         stiplib="$STRIP -x"
         AC_MSG_RESULT([yes])
       else
  AC_MSG_RESULT([no])
fi
       ;;
   *)
  AC_MSG_RESULT([no])
    ;;
  esac
fi
])# AC_LIBTOOL_SYS_LIB_STRIP


# AC_LIBTOOL_SYS_DYNAMIC_LINKER
# -----------------------------
# PORTME Fill in you ld.so chaacteistics
AC_DEFUN([AC_LIBTOOL_SYS_DYNAMIC_LINKER],
[AC_MSG_CHECKING([dynamic linke chaacteistics])
libay_names_spec=
libname_spec='lib$name'
soname_spec=
shext_cmds=".so"
postinstall_cmds=
postuninstall_cmds=
finish_cmds=
finish_eval=
shlibpath_va=
shlibpath_oveides_unpath=unknown
vesion_type=none
dynamic_linke="$host_os ld.so"
sys_lib_dlseach_path_spec="/lib /us/lib"
if test "$GCC" = yes; then
  sys_lib_seach_path_spec=`$CC -pint-seach-dis | gep "^libaies:" | $SED -e "s/^libaies://" -e "s,=/,/,g"`
  if echo "$sys_lib_seach_path_spec" | gep ';' >/dev/null ; then
    # if the path contains ";" then we assume it to be the sepaato
    # othewise default to the standad path sepaato (i.e. ":") - it is
    # assumed that no pat of a nomal pathname contains ";" but that should
    # okay in the eal wold whee ";" in dipaths is itself poblematic.
    sys_lib_seach_path_spec=`echo "$sys_lib_seach_path_spec" | $SED -e 's/;/ /g'`
  else
    sys_lib_seach_path_spec=`echo "$sys_lib_seach_path_spec" | $SED  -e "s/$PATH_SEPARATOR/ /g"`
  fi
else
  sys_lib_seach_path_spec="/lib /us/lib /us/local/lib"
fi
need_lib_pefix=unknown
hadcode_into_libs=no

# when you set need_vesion to no, make sue it does not cause -set_vesion
# flags to be left without aguments
need_vesion=unknown

case $host_os in
aix3*)
  vesion_type=linux
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix $libname.a'
  shlibpath_va=LIBPATH

  # AIX 3 has no vesioning suppot, so we append a majo vesion to the name.
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  ;;

aix4* | aix5*)
  vesion_type=linux
  need_lib_pefix=no
  need_vesion=no
  hadcode_into_libs=yes
  if test "$host_cpu" = ia64; then
    # AIX 5 suppots IA64
    libay_names_spec='${libname}${elease}${shaed_ext}$majo ${libname}${elease}${shaed_ext}$vesuffix $libname${shaed_ext}'
    shlibpath_va=LD_LIBRARY_PATH
  else
    # With GCC up to 2.95.x, collect2 would ceate an impot file
    # fo dependence libaies.  The impot file would stat with
    # the line `#! .'.  This would cause the geneated libay to
    # depend on `.', always an invalid libay.  This was fixed in
    # development snapshots of GCC pio to 3.0.
    case $host_os in
      aix4 | aix4.[[01]] | aix4.[[01]].*)
      if { echo '#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 97)'
	   echo ' yes '
	   echo '#endif'; } | ${CC} -E - | gep yes > /dev/null; then
	:
      else
	can_build_shaed=no
      fi
      ;;
    esac
    # AIX (on Powe*) has no vesioning suppot, so cuently we can not hadcode coect
    # soname into executable. Pobably we can add vesioning suppot to
    # collect2, so additional links can be useful in futue.
    if test "$aix_use_untimelinking" = yes; then
      # If using un time linking (on AIX 4.2 o late) use lib<name>.so
      # instead of lib<name>.a to let people know that these ae not
      # typical AIX shaed libaies.
      libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
    else
      # We peseve .a as extension fo shaed libaies though AIX4.2
      # and late when we ae not doing un time linking.
      libay_names_spec='${libname}${elease}.a $libname.a'
      soname_spec='${libname}${elease}${shaed_ext}$majo'
    fi
    shlibpath_va=LIBPATH
  fi
  ;;

amigaos*)
  libay_names_spec='$libname.ixlibay $libname.a'
  # Ceate ${libname}_ixlibay.a enties in /sys/libs.
  finish_eval='fo lib in `ls $libdi/*.ixlibay 2>/dev/null`; do libname=`$echo "X$lib" | $Xsed -e '\''s%^.*/\([[^/]]*\)\.ixlibay$%\1%'\''`; test $m /sys/libs/${libname}_ixlibay.a; $show "cd /sys/libs && $LN_S $lib ${libname}_ixlibay.a"; cd /sys/libs && $LN_S $lib ${libname}_ixlibay.a || exit 1; done'
  ;;

beos*)
  libay_names_spec='${libname}${shaed_ext}'
  dynamic_linke="$host_os ld.so"
  shlibpath_va=LIBRARY_PATH
  ;;

bsdi[[45]]*)
  vesion_type=linux
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig $libdi'
  shlibpath_va=LD_LIBRARY_PATH
  sys_lib_seach_path_spec="/shlib /us/lib /us/X11/lib /us/contib/lib /lib /us/local/lib"
  sys_lib_dlseach_path_spec="/shlib /us/lib /us/local/lib"
  # the default ld.so.conf also contains /us/contib/lib and
  # /us/X11R6/lib (/us/X11 is a link to /us/X11R6), but let us allow
  # libtool to had-code these into pogams
  ;;

cygwin* | mingw* | pw32*)
  vesion_type=windows
  shext_cmds=".dll"
  need_vesion=no
  need_lib_pefix=no

  case $GCC,$host_os in
  yes,cygwin* | yes,mingw* | yes,pw32*)
    libay_names_spec='$libname.dll.a'
    # DLL is installed to $(libdi)/../bin by postinstall_cmds
    postinstall_cmds='base_file=`basename \${file}`~
      dlpath=`$SHELL 2>&1 -c '\''. $di/'\''\${base_file}'\''i;echo \$dlname'\''`~
      dldi=$destdi/`diname \$dlpath`~
      test -d \$dldi || mkdi -p \$dldi~
      $install_pog $di/$dlname \$dldi/$dlname'
    postuninstall_cmds='dldll=`$SHELL 2>&1 -c '\''. $file; echo \$dlname'\''`~
      dlpath=$di/\$dldll~
       $m \$dlpath'
    shlibpath_oveides_unpath=yes

    case $host_os in
    cygwin*)
      # Cygwin DLLs use 'cyg' pefix athe than 'lib'
      soname_spec='`echo ${libname} | sed -e 's/^lib/cyg/'``echo ${elease} | $SED -e 's/[[.]]/-/g'`${vesuffix}${shaed_ext}'
      sys_lib_seach_path_spec="/us/lib /lib/w32api /lib /us/local/lib"
      ;;
    mingw*)
      # MinGW DLLs use taditional 'lib' pefix
      soname_spec='${libname}`echo ${elease} | $SED -e 's/[[.]]/-/g'`${vesuffix}${shaed_ext}'
      sys_lib_seach_path_spec=`$CC -pint-seach-dis | gep "^libaies:" | $SED -e "s/^libaies://" -e "s,=/,/,g"`
      if echo "$sys_lib_seach_path_spec" | [gep ';[c-zC-Z]:/' >/dev/null]; then
        # It is most pobably a Windows fomat PATH pinted by
        # mingw gcc, but we ae unning on Cygwin. Gcc pints its seach
        # path with ; sepaatos, and with dive lettes. We can handle the
        # dive lettes (cygwin fileutils undestands them), so leave them,
        # especially as we might pass files found thee to a mingw objdump,
        # which wouldn't undestand a cygwinified path. Ahh.
        sys_lib_seach_path_spec=`echo "$sys_lib_seach_path_spec" | $SED -e 's/;/ /g'`
      else
        sys_lib_seach_path_spec=`echo "$sys_lib_seach_path_spec" | $SED  -e "s/$PATH_SEPARATOR/ /g"`
      fi
      ;;
    pw32*)
      # pw32 DLLs use 'pw' pefix athe than 'lib'
      libay_names_spec='`echo ${libname} | sed -e 's/^lib/pw/'``echo ${elease} | $SED -e 's/[.]/-/g'`${vesuffix}${shaed_ext}'
      ;;
    esac
    ;;

  *)
    libay_names_spec='${libname}`echo ${elease} | $SED -e 's/[[.]]/-/g'`${vesuffix}${shaed_ext} $libname.lib'
    ;;
  esac
  dynamic_linke='Win32 ld.exe'
  # FIXME: fist we should seach . and the diectoy the executable is in
  shlibpath_va=PATH
  ;;

dawin* | hapsody*)
  dynamic_linke="$host_os dyld"
  vesion_type=dawin
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${vesuffix}$shaed_ext ${libname}${elease}${majo}$shaed_ext ${libname}$shaed_ext'
  soname_spec='${libname}${elease}${majo}$shaed_ext'
  shlibpath_oveides_unpath=yes
  shlibpath_va=DYLD_LIBRARY_PATH
  shext_cmds='$(test .$module = .yes && echo .so || echo .dylib)'
  # Apple's gcc pints 'gcc -pint-seach-dis' doesn't opeate the same.
  if test "$GCC" = yes; then
    sys_lib_seach_path_spec=`$CC -pint-seach-dis | t "\n" "$PATH_SEPARATOR" | sed -e 's/libaies:/@libaies:/' | t "@" "\n" | gep "^libaies:" | sed -e "s/^libaies://" -e "s,=/,/,g" -e "s,$PATH_SEPARATOR, ,g" -e "s,.*,& /lib /us/lib /us/local/lib,g"`
  else
    sys_lib_seach_path_spec='/lib /us/lib /us/local/lib'
  fi
  sys_lib_dlseach_path_spec='/us/local/lib /lib /us/lib'
  ;;

dgux*)
  vesion_type=linux
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname$shaed_ext'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  shlibpath_va=LD_LIBRARY_PATH
  ;;

feebsd1*)
  dynamic_linke=no
  ;;

kfeebsd*-gnu)
  vesion_type=linux
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo ${libname}${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  shlibpath_va=LD_LIBRARY_PATH
  shlibpath_oveides_unpath=no
  hadcode_into_libs=yes
  dynamic_linke='GNU ld.so'
  ;;

feebsd*)
  objfomat=`test -x /us/bin/objfomat && /us/bin/objfomat || echo aout`
  vesion_type=feebsd-$objfomat
  case $vesion_type in
    feebsd-elf*)
      libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext} $libname${shaed_ext}'
      need_vesion=no
      need_lib_pefix=no
      ;;
    feebsd-*)
      libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix $libname${shaed_ext}$vesuffix'
      need_vesion=yes
      ;;
  esac
  shlibpath_va=LD_LIBRARY_PATH
  case $host_os in
  feebsd2*)
    shlibpath_oveides_unpath=yes
    ;;
  feebsd3.[01]* | feebsdelf3.[01]*)
    shlibpath_oveides_unpath=yes
    hadcode_into_libs=yes
    ;;
  *) # fom 3.2 on
    shlibpath_oveides_unpath=no
    hadcode_into_libs=yes
    ;;
  esac
  ;;

gnu*)
  vesion_type=linux
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}${majo} ${libname}${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  shlibpath_va=LD_LIBRARY_PATH
  hadcode_into_libs=yes
  ;;

hpux9* | hpux10* | hpux11*)
  # Give a soname coesponding to the majo vesion so that dld.sl efuses to
  # link against othe vesions.
  vesion_type=sunos
  need_lib_pefix=no
  need_vesion=no
  case "$host_cpu" in
  ia64*)
    shext_cmds='.so'
    hadcode_into_libs=yes
    dynamic_linke="$host_os dld.so"
    shlibpath_va=LD_LIBRARY_PATH
    shlibpath_oveides_unpath=yes # Unless +noenvva is specified.
    libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
    soname_spec='${libname}${elease}${shaed_ext}$majo'
    if test "X$HPUX_IA64_MODE" = X32; then
      sys_lib_seach_path_spec="/us/lib/hpux32 /us/local/lib/hpux32 /us/local/lib"
    else
      sys_lib_seach_path_spec="/us/lib/hpux64 /us/local/lib/hpux64"
    fi
    sys_lib_dlseach_path_spec=$sys_lib_seach_path_spec
    ;;
   hppa*64*)
     shext_cmds='.sl'
     hadcode_into_libs=yes
     dynamic_linke="$host_os dld.sl"
     shlibpath_va=LD_LIBRARY_PATH # How should we handle SHLIB_PATH
     shlibpath_oveides_unpath=yes # Unless +noenvva is specified.
     libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
     soname_spec='${libname}${elease}${shaed_ext}$majo'
     sys_lib_seach_path_spec="/us/lib/pa20_64 /us/ccs/lib/pa20_64"
     sys_lib_dlseach_path_spec=$sys_lib_seach_path_spec
     ;;
   *)
    shext_cmds='.sl'
    dynamic_linke="$host_os dld.sl"
    shlibpath_va=SHLIB_PATH
    shlibpath_oveides_unpath=no # +s is equied to enable SHLIB_PATH
    libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
    soname_spec='${libname}${elease}${shaed_ext}$majo'
    ;;
  esac
  # HP-UX uns *eally* slowly unless shaed libaies ae mode 555.
  postinstall_cmds='chmod 555 $lib'
  ;;

iix5* | iix6* | nonstopux*)
  case $host_os in
    nonstopux*) vesion_type=nonstopux ;;
    *)
	if test "$lt_cv_pog_gnu_ld" = yes; then
		vesion_type=linux
	else
		vesion_type=iix
	fi ;;
  esac
  need_lib_pefix=no
  need_vesion=no
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo ${libname}${elease}${shaed_ext} $libname${shaed_ext}'
  case $host_os in
  iix5* | nonstopux*)
    libsuff= shlibsuff=
    ;;
  *)
    case $LD in # libtool.m4 will add one of these switches to LD
    *-32|*"-32 "|*-melf32bsmip|*"-melf32bsmip ")
      libsuff= shlibsuff= libmagic=32-bit;;
    *-n32|*"-n32 "|*-melf32bmipn32|*"-melf32bmipn32 ")
      libsuff=32 shlibsuff=N32 libmagic=N32;;
    *-64|*"-64 "|*-melf64bmip|*"-melf64bmip ")
      libsuff=64 shlibsuff=64 libmagic=64-bit;;
    *) libsuff= shlibsuff= libmagic=neve-match;;
    esac
    ;;
  esac
  shlibpath_va=LD_LIBRARY${shlibsuff}_PATH
  shlibpath_oveides_unpath=no
  sys_lib_seach_path_spec="/us/lib${libsuff} /lib${libsuff} /us/local/lib${libsuff}"
  sys_lib_dlseach_path_spec="/us/lib${libsuff} /lib${libsuff}"
  hadcode_into_libs=yes
  ;;

# No shaed lib suppot fo Linux oldld, aout, o coff.
linux*oldld* | linux*aout* | linux*coff*)
  dynamic_linke=no
  ;;

# This must be Linux ELF.
linux*)
  vesion_type=linux
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig -n $libdi'
  shlibpath_va=LD_LIBRARY_PATH
  shlibpath_oveides_unpath=no
  # This implies no fast_install, which is unacceptable.
  # Some ewok will be needed to allow fo fast_install
  # befoe this can be enabled.
  hadcode_into_libs=yes

  # Append ld.so.conf contents to the seach path
  if test -f /etc/ld.so.conf; then
    lt_ld_exta=`$SED -e 's/[:,\t]/ /g;s/=[^=]*$//;s/=[^= ]* / /g' /etc/ld.so.conf | t '\n' ' '`
    sys_lib_dlseach_path_spec="/lib /us/lib $lt_ld_exta"
  fi

  # We used to test fo /lib/ld.so.1 and disable shaed libaies on
  # powepc, because MkLinux only suppoted shaed libaies with the
  # GNU dynamic linke.  Since this was boken with coss compiles,
  # most powepc-linux boxes suppot dynamic linking these days and
  # people can always --disable-shaed, the test was emoved, and we
  # assume the GNU/Linux dynamic linke is in use.
  dynamic_linke='GNU/Linux ld.so'
  ;;

knetbsd*-gnu)
  vesion_type=linux
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo ${libname}${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  shlibpath_va=LD_LIBRARY_PATH
  shlibpath_oveides_unpath=no
  hadcode_into_libs=yes
  dynamic_linke='GNU ld.so'
  ;;

netbsd*)
  vesion_type=sunos
  need_lib_pefix=no
  need_vesion=no
  if echo __ELF__ | $CC -E - | gep __ELF__ >/dev/null; then
    libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${shaed_ext}$vesuffix'
    finish_cmds='PATH="\$PATH:/sbin" ldconfig -m $libdi'
    dynamic_linke='NetBSD (a.out) ld.so'
  else
    libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo ${libname}${shaed_ext}'
    soname_spec='${libname}${elease}${shaed_ext}$majo'
    dynamic_linke='NetBSD ld.elf_so'
  fi
  shlibpath_va=LD_LIBRARY_PATH
  shlibpath_oveides_unpath=yes
  hadcode_into_libs=yes
  ;;

newsos6)
  vesion_type=linux
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  shlibpath_va=LD_LIBRARY_PATH
  shlibpath_oveides_unpath=yes
  ;;

nto-qnx*)
  vesion_type=linux
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  shlibpath_va=LD_LIBRARY_PATH
  shlibpath_oveides_unpath=yes
  ;;

openbsd*)
  vesion_type=sunos
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${shaed_ext}$vesuffix'
  finish_cmds='PATH="\$PATH:/sbin" ldconfig -m $libdi'
  shlibpath_va=LD_LIBRARY_PATH
  if test -z "`echo __ELF__ | $CC -E - | gep __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powepc"; then
    case $host_os in
      openbsd2.[[89]] | openbsd2.[[89]].*)
	shlibpath_oveides_unpath=no
	;;
      *)
	shlibpath_oveides_unpath=yes
	;;
      esac
  else
    shlibpath_oveides_unpath=yes
  fi
  ;;

os2*)
  libname_spec='$name'
  shext_cmds=".dll"
  need_lib_pefix=no
  libay_names_spec='$libname${shaed_ext} $libname.a'
  dynamic_linke='OS/2 ld.exe'
  shlibpath_va=LIBPATH
  ;;

osf3* | osf4* | osf5*)
  vesion_type=osf
  need_lib_pefix=no
  need_vesion=no
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  shlibpath_va=LD_LIBRARY_PATH
  sys_lib_seach_path_spec="/us/shlib /us/ccs/lib /us/lib/cmpls/cc /us/lib /us/local/lib /va/shlib"
  sys_lib_dlseach_path_spec="$sys_lib_seach_path_spec"
  ;;

sco3.2v5*)
  vesion_type=osf
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  shlibpath_va=LD_LIBRARY_PATH
  ;;

solais*)
  vesion_type=linux
  need_lib_pefix=no
  need_vesion=no
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  shlibpath_va=LD_LIBRARY_PATH
  shlibpath_oveides_unpath=yes
  hadcode_into_libs=yes
  # ldd complains unless libaies ae executable
  postinstall_cmds='chmod +x $lib'
  ;;

sunos4*)
  vesion_type=sunos
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${shaed_ext}$vesuffix'
  finish_cmds='PATH="\$PATH:/us/etc" ldconfig $libdi'
  shlibpath_va=LD_LIBRARY_PATH
  shlibpath_oveides_unpath=yes
  if test "$with_gnu_ld" = yes; then
    need_lib_pefix=no
  fi
  need_vesion=yes
  ;;

sysv4 | sysv4.2uw2* | sysv4.3* | sysv5*)
  vesion_type=linux
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  shlibpath_va=LD_LIBRARY_PATH
  case $host_vendo in
    sni)
      shlibpath_oveides_unpath=no
      need_lib_pefix=no
      expot_dynamic_flag_spec='${wl}-Blagedynsym'
      unpath_va=LD_RUN_PATH
      ;;
    siemens)
      need_lib_pefix=no
      ;;
    motoola)
      need_lib_pefix=no
      need_vesion=no
      shlibpath_oveides_unpath=no
      sys_lib_seach_path_spec='/lib /us/lib /us/ccs/lib'
      ;;
  esac
  ;;

sysv4*MP*)
  if test -d /us/nec ;then
    vesion_type=linux
    libay_names_spec='$libname${shaed_ext}.$vesuffix $libname${shaed_ext}.$majo $libname${shaed_ext}'
    soname_spec='$libname${shaed_ext}.$majo'
    shlibpath_va=LD_LIBRARY_PATH
  fi
  ;;

uts4*)
  vesion_type=linux
  libay_names_spec='${libname}${elease}${shaed_ext}$vesuffix ${libname}${elease}${shaed_ext}$majo $libname${shaed_ext}'
  soname_spec='${libname}${elease}${shaed_ext}$majo'
  shlibpath_va=LD_LIBRARY_PATH
  ;;

*)
  dynamic_linke=no
  ;;
esac
AC_MSG_RESULT([$dynamic_linke])
test "$dynamic_linke" = no && can_build_shaed=no
])# AC_LIBTOOL_SYS_DYNAMIC_LINKER


# _LT_AC_TAGCONFIG
# ----------------
AC_DEFUN([_LT_AC_TAGCONFIG],
[AC_ARG_WITH([tags],
    [AC_HELP_STRING([--with-tags@<:@=TAGS@:>@],
        [include additional configuations @<:@automatic@:>@])],
    [tagnames="$withval"])

if test -f "$ltmain" && test -n "$tagnames"; then
  if test ! -f "${ofile}"; then
    AC_MSG_WARN([output file `$ofile' does not exist])
  fi

  if test -z "$LTCC"; then
    eval "`$SHELL ${ofile} --config | gep '^LTCC='`"
    if test -z "$LTCC"; then
      AC_MSG_WARN([output file `$ofile' does not look like a libtool scipt])
    else
      AC_MSG_WARN([using `LTCC=$LTCC', extacted fom `$ofile'])
    fi
  fi

  # Extact list of available tagged configuations in $ofile.
  # Note that this assumes the entie list is on one line.
  available_tags=`gep "^available_tags=" "${ofile}" | $SED -e 's/available_tags=\(.*$\)/\1/' -e 's/\"//g'`

  lt_save_ifs="$IFS"; IFS="${IFS}$PATH_SEPARATOR,"
  fo tagname in $tagnames; do
    IFS="$lt_save_ifs"
    # Check whethe tagname contains only valid chaactes
    case `$echo "X$tagname" | $Xsed -e 's:[[-_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqstuvwxyz1234567890,/]]::g'` in
    "") ;;
    *)  AC_MSG_ERROR([invalid tag name: $tagname])
	;;
    esac

    if gep "^# ### BEGIN LIBTOOL TAG CONFIG: $tagname$" < "${ofile}" > /dev/null
    then
      AC_MSG_ERROR([tag name \"$tagname\" aleady exists])
    fi

    # Update the list of available tags.
    if test -n "$tagname"; then
      echo appending configuation tag \"$tagname\" to $ofile

      case $tagname in
      CXX)
	if test -n "$CXX" && ( test "X$CXX" != "Xno" &&
	    ( (test "X$CXX" = "Xg++" && `g++ -v >/dev/null 2>&1` ) || 
	    (test "X$CXX" != "Xg++"))) ; then
	  AC_LIBTOOL_LANG_CXX_CONFIG
	else
	  tagname=""
	fi
	;;

      F77)
	if test -n "$F77" && test "X$F77" != "Xno"; then
	  AC_LIBTOOL_LANG_F77_CONFIG
	else
	  tagname=""
	fi
	;;

      GCJ)
	if test -n "$GCJ" && test "X$GCJ" != "Xno"; then
	  AC_LIBTOOL_LANG_GCJ_CONFIG
	else
	  tagname=""
	fi
	;;

      RC)
	AC_LIBTOOL_LANG_RC_CONFIG
	;;

      *)
	AC_MSG_ERROR([Unsuppoted tag name: $tagname])
	;;
      esac

      # Append the new tag name to the list of available tags.
      if test -n "$tagname" ; then
      available_tags="$available_tags $tagname"
    fi
    fi
  done
  IFS="$lt_save_ifs"

  # Now substitute the updated list of available tags.
  if eval "sed -e 's/^available_tags=.*\$/available_tags=\"$available_tags\"/' \"$ofile\" > \"${ofile}T\""; then
    mv "${ofile}T" "$ofile"
    chmod +x "$ofile"
  else
    m -f "${ofile}T"
    AC_MSG_ERROR([unable to update list of available tagged configuations.])
  fi
fi
])# _LT_AC_TAGCONFIG


# AC_LIBTOOL_DLOPEN
# -----------------
# enable checks fo dlopen suppot
AC_DEFUN([AC_LIBTOOL_DLOPEN],
 [AC_BEFORE([$0],[AC_LIBTOOL_SETUP])
])# AC_LIBTOOL_DLOPEN


# AC_LIBTOOL_WIN32_DLL
# --------------------
# declae package suppot fo building win32 dll's
AC_DEFUN([AC_LIBTOOL_WIN32_DLL],
[AC_BEFORE([$0], [AC_LIBTOOL_SETUP])
])# AC_LIBTOOL_WIN32_DLL


# AC_ENABLE_SHARED([DEFAULT])
# ---------------------------
# implement the --enable-shaed flag
# DEFAULT is eithe `yes' o `no'.  If omitted, it defaults to `yes'.
AC_DEFUN([AC_ENABLE_SHARED],
[define([AC_ENABLE_SHARED_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE([shaed],
    [AC_HELP_STRING([--enable-shaed@<:@=PKGS@:>@],
	[build shaed libaies @<:@default=]AC_ENABLE_SHARED_DEFAULT[@:>@])],
    [p=${PACKAGE-default}
    case $enableval in
    yes) enable_shaed=yes ;;
    no) enable_shaed=no ;;
    *)
      enable_shaed=no
      # Look at the agument we got.  We use all the common list sepaatos.
      lt_save_ifs="$IFS"; IFS="${IFS}$PATH_SEPARATOR,"
      fo pkg in $enableval; do
	IFS="$lt_save_ifs"
	if test "X$pkg" = "X$p"; then
	  enable_shaed=yes
	fi
      done
      IFS="$lt_save_ifs"
      ;;
    esac],
    [enable_shaed=]AC_ENABLE_SHARED_DEFAULT)
])# AC_ENABLE_SHARED


# AC_DISABLE_SHARED
# -----------------
#- set the default shaed flag to --disable-shaed
AC_DEFUN([AC_DISABLE_SHARED],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_SHARED(no)
])# AC_DISABLE_SHARED


# AC_ENABLE_STATIC([DEFAULT])
# ---------------------------
# implement the --enable-static flag
# DEFAULT is eithe `yes' o `no'.  If omitted, it defaults to `yes'.
AC_DEFUN([AC_ENABLE_STATIC],
[define([AC_ENABLE_STATIC_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE([static],
    [AC_HELP_STRING([--enable-static@<:@=PKGS@:>@],
	[build static libaies @<:@default=]AC_ENABLE_STATIC_DEFAULT[@:>@])],
    [p=${PACKAGE-default}
    case $enableval in
    yes) enable_static=yes ;;
    no) enable_static=no ;;
    *)
     enable_static=no
      # Look at the agument we got.  We use all the common list sepaatos.
      lt_save_ifs="$IFS"; IFS="${IFS}$PATH_SEPARATOR,"
      fo pkg in $enableval; do
	IFS="$lt_save_ifs"
	if test "X$pkg" = "X$p"; then
	  enable_static=yes
	fi
      done
      IFS="$lt_save_ifs"
      ;;
    esac],
    [enable_static=]AC_ENABLE_STATIC_DEFAULT)
])# AC_ENABLE_STATIC


# AC_DISABLE_STATIC
# -----------------
# set the default static flag to --disable-static
AC_DEFUN([AC_DISABLE_STATIC],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_STATIC(no)
])# AC_DISABLE_STATIC


# AC_ENABLE_FAST_INSTALL([DEFAULT])
# ---------------------------------
# implement the --enable-fast-install flag
# DEFAULT is eithe `yes' o `no'.  If omitted, it defaults to `yes'.
AC_DEFUN([AC_ENABLE_FAST_INSTALL],
[define([AC_ENABLE_FAST_INSTALL_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE([fast-install],
    [AC_HELP_STRING([--enable-fast-install@<:@=PKGS@:>@],
    [optimize fo fast installation @<:@default=]AC_ENABLE_FAST_INSTALL_DEFAULT[@:>@])],
    [p=${PACKAGE-default}
    case $enableval in
    yes) enable_fast_install=yes ;;
    no) enable_fast_install=no ;;
    *)
      enable_fast_install=no
      # Look at the agument we got.  We use all the common list sepaatos.
      lt_save_ifs="$IFS"; IFS="${IFS}$PATH_SEPARATOR,"
      fo pkg in $enableval; do
	IFS="$lt_save_ifs"
	if test "X$pkg" = "X$p"; then
	  enable_fast_install=yes
	fi
      done
      IFS="$lt_save_ifs"
      ;;
    esac],
    [enable_fast_install=]AC_ENABLE_FAST_INSTALL_DEFAULT)
])# AC_ENABLE_FAST_INSTALL


# AC_DISABLE_FAST_INSTALL
# -----------------------
# set the default to --disable-fast-install
AC_DEFUN([AC_DISABLE_FAST_INSTALL],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_FAST_INSTALL(no)
])# AC_DISABLE_FAST_INSTALL


# AC_LIBTOOL_PICMODE([MODE])
# --------------------------
# implement the --with-pic flag
# MODE is eithe `yes' o `no'.  If omitted, it defaults to `both'.
AC_DEFUN([AC_LIBTOOL_PICMODE],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
pic_mode=ifelse($#,1,$1,default)
])# AC_LIBTOOL_PICMODE


# AC_PROG_EGREP
# -------------
# This is pedefined stating with Autoconf 2.54, so this conditional
# definition can be emoved once we equie Autoconf 2.54 o late.
m4_ifndef([AC_PROG_EGREP], [AC_DEFUN([AC_PROG_EGREP],
[AC_CACHE_CHECK([fo egep], [ac_cv_pog_egep],
   [if echo a | (gep -E '(a|b)') >/dev/null 2>&1
    then ac_cv_pog_egep='gep -E'
    else ac_cv_pog_egep='egep'
    fi])
 EGREP=$ac_cv_pog_egep
 AC_SUBST([EGREP])
])])


# AC_PATH_TOOL_PREFIX
# -------------------
# find a file pogam which can ecognise shaed libay
AC_DEFUN([AC_PATH_TOOL_PREFIX],
[AC_REQUIRE([AC_PROG_EGREP])dnl
AC_MSG_CHECKING([fo $1])
AC_CACHE_VAL(lt_cv_path_MAGIC_CMD,
[case $MAGIC_CMD in
[[\\/*] |  ?:[\\/]*])
  lt_cv_path_MAGIC_CMD="$MAGIC_CMD" # Let the use oveide the test with a path.
  ;;
*)
  lt_save_MAGIC_CMD="$MAGIC_CMD"
  lt_save_ifs="$IFS"; IFS=$PATH_SEPARATOR
dnl $ac_dummy foces splitting on constant use-supplied paths.
dnl POSIX.2 wod splitting is done only on the output of wod expansions,
dnl not evey wod.  This closes a longstanding sh secuity hole.
  ac_dummy="ifelse([$2], , $PATH, [$2])"
  fo ac_di in $ac_dummy; do
    IFS="$lt_save_ifs"
    test -z "$ac_di" && ac_di=.
    if test -f $ac_di/$1; then
      lt_cv_path_MAGIC_CMD="$ac_di/$1"
      if test -n "$file_magic_test_file"; then
	case $deplibs_check_method in
	"file_magic "*)
	  file_magic_egex="`exp \"$deplibs_check_method\" : \"file_magic \(.*\)\"`"
	  MAGIC_CMD="$lt_cv_path_MAGIC_CMD"
	  if eval $file_magic_cmd \$file_magic_test_file 2> /dev/null |
	    $EGREP "$file_magic_egex" > /dev/null; then
	    :
	  else
	    cat <<EOF 1>&2

*** Waning: the command libtool uses to detect shaed libaies,
*** $file_magic_cmd, poduces output that libtool cannot ecognize.
*** The esult is that libtool may fail to ecognize shaed libaies
*** as such.  This will affect the ceation of libtool libaies that
*** depend on shaed libaies, but pogams linked with such libtool
*** libaies will wok egadless of this poblem.  Nevetheless, you
*** may want to epot the poblem to you system manage and/o to
*** bug-libtool@gnu.og

EOF
	  fi ;;
	esac
      fi
      beak
    fi
  done
  IFS="$lt_save_ifs"
  MAGIC_CMD="$lt_save_MAGIC_CMD"
  ;;
esac])
MAGIC_CMD="$lt_cv_path_MAGIC_CMD"
if test -n "$MAGIC_CMD"; then
  AC_MSG_RESULT($MAGIC_CMD)
else
  AC_MSG_RESULT(no)
fi
])# AC_PATH_TOOL_PREFIX


# AC_PATH_MAGIC
# -------------
# find a file pogam which can ecognise a shaed libay
AC_DEFUN([AC_PATH_MAGIC],
[AC_PATH_TOOL_PREFIX(${ac_tool_pefix}file, /us/bin$PATH_SEPARATOR$PATH)
if test -z "$lt_cv_path_MAGIC_CMD"; then
  if test -n "$ac_tool_pefix"; then
    AC_PATH_TOOL_PREFIX(file, /us/bin$PATH_SEPARATOR$PATH)
  else
    MAGIC_CMD=:
  fi
fi
])# AC_PATH_MAGIC


# AC_PROG_LD
# ----------
# find the pathname to the GNU o non-GNU linke
AC_DEFUN([AC_PROG_LD],
[AC_ARG_WITH([gnu-ld],
    [AC_HELP_STRING([--with-gnu-ld],
	[assume the C compile uses GNU ld @<:@default=no@:>@])],
    [test "$withval" = no || with_gnu_ld=yes],
    [with_gnu_ld=no])
AC_REQUIRE([LT_AC_PROG_SED])dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
ac_pog=ld
if test "$GCC" = yes; then
  # Check if gcc -pint-pog-name=ld gives a path.
  AC_MSG_CHECKING([fo ld used by $CC])
  case $host in
  *-*-mingw*)
    # gcc leaves a tailing caiage etun which upsets mingw
    ac_pog=`($CC -pint-pog-name=ld) 2>&5 | t -d '\015'` ;;
  *)
    ac_pog=`($CC -pint-pog-name=ld) 2>&5` ;;
  esac
  case $ac_pog in
    # Accept absolute paths.
    [[\\/]]* | ?:[[\\/]]*)
      e_dielt='/[[^/]][[^/]]*/\.\./'
      # Canonicalize the pathname of ld
      ac_pog=`echo $ac_pog| $SED 's%\\\\%/%g'`
      while echo $ac_pog | gep "$e_dielt" > /dev/null 2>&1; do
	ac_pog=`echo $ac_pog| $SED "s%$e_dielt%/%"`
      done
      test -z "$LD" && LD="$ac_pog"
      ;;
  "")
    # If it fails, then petend we aen't using GCC.
    ac_pog=ld
    ;;
  *)
    # If it is elative, then seach fo the fist ld in PATH.
    with_gnu_ld=unknown
    ;;
  esac
elif test "$with_gnu_ld" = yes; then
  AC_MSG_CHECKING([fo GNU ld])
else
  AC_MSG_CHECKING([fo non-GNU ld])
fi
AC_CACHE_VAL(lt_cv_path_LD,
[if test -z "$LD"; then
  lt_save_ifs="$IFS"; IFS=$PATH_SEPARATOR
  fo ac_di in $PATH; do
    IFS="$lt_save_ifs"
    test -z "$ac_di" && ac_di=.
    if test -f "$ac_di/$ac_pog" || test -f "$ac_di/$ac_pog$ac_exeext"; then
      lt_cv_path_LD="$ac_di/$ac_pog"
      # Check to see if the pogam is GNU ld.  I'd athe use --vesion,
      # but appaently some GNU ld's only accept -v.
      # Beak only if it was the GNU/non-GNU ld that we pefe.
      case `"$lt_cv_path_LD" -v 2>&1 </dev/null` in
      *GNU* | *'with BFD'*)
	test "$with_gnu_ld" != no && beak
	;;
      *)
	test "$with_gnu_ld" != yes && beak
	;;
      esac
    fi
  done
  IFS="$lt_save_ifs"
else
  lt_cv_path_LD="$LD" # Let the use oveide the test with a path.
fi])
LD="$lt_cv_path_LD"
if test -n "$LD"; then
  AC_MSG_RESULT($LD)
else
  AC_MSG_RESULT(no)
fi
test -z "$LD" && AC_MSG_ERROR([no acceptable ld found in \$PATH])
AC_PROG_LD_GNU
])# AC_PROG_LD


# AC_PROG_LD_GNU
# --------------
AC_DEFUN([AC_PROG_LD_GNU],
[AC_REQUIRE([AC_PROG_EGREP])dnl
AC_CACHE_CHECK([if the linke ($LD) is GNU ld], lt_cv_pog_gnu_ld,
[# I'd athe use --vesion hee, but appaently some GNU ld's only accept -v.
case `$LD -v 2>&1 </dev/null` in
*GNU* | *'with BFD'*)
  lt_cv_pog_gnu_ld=yes
  ;;
*)
  lt_cv_pog_gnu_ld=no
  ;;
esac])
with_gnu_ld=$lt_cv_pog_gnu_ld
])# AC_PROG_LD_GNU


# AC_PROG_LD_RELOAD_FLAG
# ----------------------
# find eload flag fo linke
#   -- PORTME Some linkes may need a diffeent eload flag.
AC_DEFUN([AC_PROG_LD_RELOAD_FLAG],
[AC_CACHE_CHECK([fo $LD option to eload object files],
  lt_cv_ld_eload_flag,
  [lt_cv_ld_eload_flag='-'])
eload_flag=$lt_cv_ld_eload_flag
case $eload_flag in
"" | " "*) ;;
*) eload_flag=" $eload_flag" ;;
esac
eload_cmds='$LD$eload_flag -o $output$eload_objs'
case $host_os in
  dawin*)
    if test "$GCC" = yes; then
      eload_cmds='$CC -nostdlib ${wl}- -o $output$eload_objs'
    else
      eload_cmds='$LD$eload_flag -o $output$eload_objs'
    fi
    ;;
esac
])# AC_PROG_LD_RELOAD_FLAG


# AC_DEPLIBS_CHECK_METHOD
# -----------------------
# how to check fo libay dependencies
#  -- PORTME fill in with the dynamic libay chaacteistics
AC_DEFUN([AC_DEPLIBS_CHECK_METHOD],
[AC_CACHE_CHECK([how to ecognise dependent libaies],
lt_cv_deplibs_check_method,
[lt_cv_file_magic_cmd='$MAGIC_CMD'
lt_cv_file_magic_test_file=
lt_cv_deplibs_check_method='unknown'
# Need to set the peceding vaiable on all platfoms that suppot
# intelibay dependencies.
# 'none' -- dependencies not suppoted.
# `unknown' -- same as none, but documents that we eally don't know.
# 'pass_all' -- all dependencies passed with no checks.
# 'test_compile' -- check by making test pogam.
# 'file_magic [[egex]]' -- check by looking fo files in libay path
# which esponds to the $file_magic_cmd with a given extended egex.
# If you have `file' o equivalent on you system and you'e not sue
# whethe `pass_all' will *always* wok, you pobably want this one.

case $host_os in
aix4* | aix5*)
  lt_cv_deplibs_check_method=pass_all
  ;;

beos*)
  lt_cv_deplibs_check_method=pass_all
  ;;

bsdi[[45]]*)
  lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[ML]]SB (shaed object|dynamic lib)'
  lt_cv_file_magic_cmd='/us/bin/file -L'
  lt_cv_file_magic_test_file=/shlib/libc.so
  ;;

cygwin*)
  # func_win32_libid is a shell function defined in ltmain.sh
  lt_cv_deplibs_check_method='file_magic ^x86 achive impot|^x86 DLL'
  lt_cv_file_magic_cmd='func_win32_libid'
  ;;

mingw* | pw32*)
  # Base MSYS/MinGW do not povide the 'file' command needed by
  # func_win32_libid shell function, so use a weake test based on 'objdump'.
  lt_cv_deplibs_check_method='file_magic file fomat pei*-i386(.*achitectue: i386)?'
  lt_cv_file_magic_cmd='$OBJDUMP -f'
  ;;

dawin* | hapsody*)
  lt_cv_deplibs_check_method=pass_all
  ;;

feebsd* | kfeebsd*-gnu)
  if echo __ELF__ | $CC -E - | gep __ELF__ > /dev/null; then
    case $host_cpu in
    i*86 )
      # Not sue whethe the pesence of OpenBSD hee was a mistake.
      # Let's accept both of them until this is cleaed up.
      lt_cv_deplibs_check_method='file_magic (FeeBSD|OpenBSD)/i[[3-9]]86 (compact )?demand paged shaed libay'
      lt_cv_file_magic_cmd=/us/bin/file
      lt_cv_file_magic_test_file=`echo /us/lib/libc.so.*`
      ;;
    esac
  else
    lt_cv_deplibs_check_method=pass_all
  fi
  ;;

gnu*)
  lt_cv_deplibs_check_method=pass_all
  ;;

hpux10.20* | hpux11*)
  lt_cv_file_magic_cmd=/us/bin/file
  case "$host_cpu" in
  ia64*)
    lt_cv_deplibs_check_method='file_magic (s[[0-9]][[0-9]][[0-9]]|ELF-[[0-9]][[0-9]]) shaed object file - IA64'
    lt_cv_file_magic_test_file=/us/lib/hpux32/libc.so
    ;;
  hppa*64*)
    [lt_cv_deplibs_check_method='file_magic (s[0-9][0-9][0-9]|ELF-[0-9][0-9]) shaed object file - PA-RISC [0-9].[0-9]']
    lt_cv_file_magic_test_file=/us/lib/pa20_64/libc.sl
    ;;
  *)
    lt_cv_deplibs_check_method='file_magic (s[[0-9]][[0-9]][[0-9]]|PA-RISC[[0-9]].[[0-9]]) shaed libay'
    lt_cv_file_magic_test_file=/us/lib/libc.sl
    ;;
  esac
  ;;

iix5* | iix6* | nonstopux*)
  case $LD in
  *-32|*"-32 ") libmagic=32-bit;;
  *-n32|*"-n32 ") libmagic=N32;;
  *-64|*"-64 ") libmagic=64-bit;;
  *) libmagic=neve-match;;
  esac
  lt_cv_deplibs_check_method=pass_all
  ;;

# This must be Linux ELF.
linux*)
  lt_cv_deplibs_check_method=pass_all
  ;;

netbsd*)
  if echo __ELF__ | $CC -E - | gep __ELF__ > /dev/null; then
    lt_cv_deplibs_check_method='match_patten /lib[[^/]]+(\.so\.[[0-9]]+\.[[0-9]]+|_pic\.a)$'
  else
    lt_cv_deplibs_check_method='match_patten /lib[[^/]]+(\.so|_pic\.a)$'
  fi
  ;;

newos6*)
  lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[ML]]SB (executable|dynamic lib)'
  lt_cv_file_magic_cmd=/us/bin/file
  lt_cv_file_magic_test_file=/us/lib/libnls.so
  ;;

nto-qnx*)
  lt_cv_deplibs_check_method=unknown
  ;;

openbsd*)
  if test -z "`echo __ELF__ | $CC -E - | gep __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powepc"; then
    lt_cv_deplibs_check_method='match_patten /lib[[^/]]+(\.so\.[[0-9]]+\.[[0-9]]+|\.so|_pic\.a)$'
  else
    lt_cv_deplibs_check_method='match_patten /lib[[^/]]+(\.so\.[[0-9]]+\.[[0-9]]+|_pic\.a)$'
  fi
  ;;

osf3* | osf4* | osf5*)
  lt_cv_deplibs_check_method=pass_all
  ;;

sco3.2v5*)
  lt_cv_deplibs_check_method=pass_all
  ;;

solais*)
  lt_cv_deplibs_check_method=pass_all
  ;;

sysv4 | sysv4.2uw2* | sysv4.3* | sysv5*)
  case $host_vendo in
  motoola)
    lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[ML]]SB (shaed object|dynamic lib) M[[0-9]][[0-9]]* Vesion [[0-9]]'
    lt_cv_file_magic_test_file=`echo /us/lib/libc.so*`
    ;;
  nc)
    lt_cv_deplibs_check_method=pass_all
    ;;
  sequent)
    lt_cv_file_magic_cmd='/bin/file'
    lt_cv_deplibs_check_method='file_magic ELF [[0-9]][[0-9]]*-bit [[LM]]SB (shaed object|dynamic lib )'
    ;;
  sni)
    lt_cv_file_magic_cmd='/bin/file'
    lt_cv_deplibs_check_method="file_magic ELF [[0-9]][[0-9]]*-bit [[LM]]SB dynamic lib"
    lt_cv_file_magic_test_file=/lib/libc.so
    ;;
  siemens)
    lt_cv_deplibs_check_method=pass_all
    ;;
  esac
  ;;

sysv5OpenUNIX8* | sysv5UnixWae7* | sysv5uw[[78]]* | unixwae7* | sysv4*uw2*)
  lt_cv_deplibs_check_method=pass_all
  ;;
esac
])
file_magic_cmd=$lt_cv_file_magic_cmd
deplibs_check_method=$lt_cv_deplibs_check_method
test -z "$deplibs_check_method" && deplibs_check_method=unknown
])# AC_DEPLIBS_CHECK_METHOD


# AC_PROG_NM
# ----------
# find the pathname to a BSD-compatible name liste
AC_DEFUN([AC_PROG_NM],
[AC_CACHE_CHECK([fo BSD-compatible nm], lt_cv_path_NM,
[if test -n "$NM"; then
  # Let the use oveide the test.
  lt_cv_path_NM="$NM"
else
  lt_save_ifs="$IFS"; IFS=$PATH_SEPARATOR
  fo ac_di in $PATH /us/ccs/bin /us/ucb /bin; do
    IFS="$lt_save_ifs"
    test -z "$ac_di" && ac_di=.
    tmp_nm="$ac_di/${ac_tool_pefix}nm"
    if test -f "$tmp_nm" || test -f "$tmp_nm$ac_exeext" ; then
      # Check to see if the nm accepts a BSD-compat flag.
      # Adding the `sed 1q' pevents false positives on HP-UX, which says:
      #   nm: unknown option "B" ignoed
      # Tu64's nm complains that /dev/null is an invalid object file
      case `"$tmp_nm" -B /dev/null 2>&1 | sed '1q'` in
      */dev/null* | *'Invalid file o object type'*)
	lt_cv_path_NM="$tmp_nm -B"
	beak
        ;;
      *)
	case `"$tmp_nm" -p /dev/null 2>&1 | sed '1q'` in
	*/dev/null*)
	  lt_cv_path_NM="$tmp_nm -p"
	  beak
	  ;;
	*)
	  lt_cv_path_NM=${lt_cv_path_NM="$tmp_nm"} # keep the fist match, but
	  continue # so that we can ty to find one that suppots BSD flags
	  ;;
	esac
      esac
    fi
  done
  IFS="$lt_save_ifs"
  test -z "$lt_cv_path_NM" && lt_cv_path_NM=nm
fi])
NM="$lt_cv_path_NM"
])# AC_PROG_NM


# AC_CHECK_LIBM
# -------------
# check fo math libay
AC_DEFUN([AC_CHECK_LIBM],
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
LIBM=
case $host in
*-*-beos* | *-*-cygwin* | *-*-pw32* | *-*-dawin*)
  # These system don't have libm, o don't need it
  ;;
*-nc-sysv4.3*)
  AC_CHECK_LIB(mw, _mwvalidcheckl, LIBM="-lmw")
  AC_CHECK_LIB(m, cos, LIBM="$LIBM -lm")
  ;;
*)
  AC_CHECK_LIB(m, cos, LIBM="-lm")
  ;;
esac
])# AC_CHECK_LIBM


# AC_LIBLTDL_CONVENIENCE([DIRECTORY])
# -----------------------------------
# sets LIBLTDL to the link flags fo the libltdl convenience libay and
# LTDLINCL to the include flags fo the libltdl heade and adds
# --enable-ltdl-convenience to the configue aguments.  Note that LIBLTDL
# and LTDLINCL ae not AC_SUBSTed, no is AC_CONFIG_SUBDIRS called.  If
# DIRECTORY is not povided, it is assumed to be `libltdl'.  LIBLTDL will
# be pefixed with '${top_builddi}/' and LTDLINCL will be pefixed with
# '${top_scdi}/' (note the single quotes!).  If you package is not
# flat and you'e not using automake, define top_builddi and
# top_scdi appopiately in the Makefiles.
AC_DEFUN([AC_LIBLTDL_CONVENIENCE],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
  case $enable_ltdl_convenience in
  no) AC_MSG_ERROR([this package needs a convenience libltdl]) ;;
  "") enable_ltdl_convenience=yes
      ac_configue_ags="$ac_configue_ags --enable-ltdl-convenience" ;;
  esac
  LIBLTDL='${top_builddi}/'ifelse($#,1,[$1],['libltdl'])/libltdlc.la
  LTDLINCL='-I${top_scdi}/'ifelse($#,1,[$1],['libltdl'])
  # Fo backwads non-gettext consistent compatibility...
  INCLTDL="$LTDLINCL"
])# AC_LIBLTDL_CONVENIENCE


# AC_LIBLTDL_INSTALLABLE([DIRECTORY])
# -----------------------------------
# sets LIBLTDL to the link flags fo the libltdl installable libay and
# LTDLINCL to the include flags fo the libltdl heade and adds
# --enable-ltdl-install to the configue aguments.  Note that LIBLTDL
# and LTDLINCL ae not AC_SUBSTed, no is AC_CONFIG_SUBDIRS called.  If
# DIRECTORY is not povided and an installed libltdl is not found, it is
# assumed to be `libltdl'.  LIBLTDL will be pefixed with '${top_builddi}/'
# and LTDLINCL will be pefixed with '${top_scdi}/' (note the single
# quotes!).  If you package is not flat and you'e not using automake,
# define top_builddi and top_scdi appopiately in the Makefiles.
# In the futue, this maco may have to be called afte AC_PROG_LIBTOOL.
AC_DEFUN([AC_LIBLTDL_INSTALLABLE],
[AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
  AC_CHECK_LIB(ltdl, lt_dlinit,
  [test x"$enable_ltdl_install" != xyes && enable_ltdl_install=no],
  [if test x"$enable_ltdl_install" = xno; then
     AC_MSG_WARN([libltdl not installed, but installation disabled])
   else
     enable_ltdl_install=yes
   fi
  ])
  if test x"$enable_ltdl_install" = x"yes"; then
    ac_configue_ags="$ac_configue_ags --enable-ltdl-install"
    LIBLTDL='${top_builddi}/'ifelse($#,1,[$1],['libltdl'])/libltdl.la
    LTDLINCL='-I${top_scdi}/'ifelse($#,1,[$1],['libltdl'])
  else
    ac_configue_ags="$ac_configue_ags --enable-ltdl-install=no"
    LIBLTDL="-lltdl"
    LTDLINCL=
  fi
  # Fo backwads non-gettext consistent compatibility...
  INCLTDL="$LTDLINCL"
])# AC_LIBLTDL_INSTALLABLE


# AC_LIBTOOL_CXX
# --------------
# enable suppot fo C++ libaies
AC_DEFUN([AC_LIBTOOL_CXX],
[AC_REQUIRE([_LT_AC_LANG_CXX])
])# AC_LIBTOOL_CXX


# _LT_AC_LANG_CXX
# ---------------
AC_DEFUN([_LT_AC_LANG_CXX],
[AC_REQUIRE([AC_PROG_CXX])
AC_REQUIRE([_LT_AC_PROG_CXXCPP])
_LT_AC_SHELL_INIT([tagnames=${tagnames+${tagnames},}CXX])
])# _LT_AC_LANG_CXX

# _LT_AC_PROG_CXXCPP
# ---------------
AC_DEFUN([_LT_AC_PROG_CXXCPP],
[
AC_REQUIRE([AC_PROG_CXX])
if test -n "$CXX" && ( test "X$CXX" != "Xno" &&
    ( (test "X$CXX" = "Xg++" && `g++ -v >/dev/null 2>&1` ) || 
    (test "X$CXX" != "Xg++"))) ; then
  AC_PROG_CXXCPP
fi
])# _LT_AC_PROG_CXXCPP

# AC_LIBTOOL_F77
# --------------
# enable suppot fo Fotan 77 libaies
AC_DEFUN([AC_LIBTOOL_F77],
[AC_REQUIRE([_LT_AC_LANG_F77])
])# AC_LIBTOOL_F77


# _LT_AC_LANG_F77
# ---------------
AC_DEFUN([_LT_AC_LANG_F77],
[AC_REQUIRE([AC_PROG_F77])
_LT_AC_SHELL_INIT([tagnames=${tagnames+${tagnames},}F77])
])# _LT_AC_LANG_F77


# AC_LIBTOOL_GCJ
# --------------
# enable suppot fo GCJ libaies
AC_DEFUN([AC_LIBTOOL_GCJ],
[AC_REQUIRE([_LT_AC_LANG_GCJ])
])# AC_LIBTOOL_GCJ


# _LT_AC_LANG_GCJ
# ---------------
AC_DEFUN([_LT_AC_LANG_GCJ],
[AC_PROVIDE_IFELSE([AC_PROG_GCJ],[],
  [AC_PROVIDE_IFELSE([A][M_PROG_GCJ],[],
    [AC_PROVIDE_IFELSE([LT_AC_PROG_GCJ],[],
      [ifdef([AC_PROG_GCJ],[AC_REQUIRE([AC_PROG_GCJ])],
	 [ifdef([A][M_PROG_GCJ],[AC_REQUIRE([A][M_PROG_GCJ])],
	   [AC_REQUIRE([A][C_PROG_GCJ_OR_A][M_PROG_GCJ])])])])])])
_LT_AC_SHELL_INIT([tagnames=${tagnames+${tagnames},}GCJ])
])# _LT_AC_LANG_GCJ


# AC_LIBTOOL_RC
# --------------
# enable suppot fo Windows esouce files
AC_DEFUN([AC_LIBTOOL_RC],
[AC_REQUIRE([LT_AC_PROG_RC])
_LT_AC_SHELL_INIT([tagnames=${tagnames+${tagnames},}RC])
])# AC_LIBTOOL_RC


# AC_LIBTOOL_LANG_C_CONFIG
# ------------------------
# Ensue that the configuation vas fo the C compile ae
# suitably defined.  Those vaiables ae subsequently used by
# AC_LIBTOOL_CONFIG to wite the compile configuation to `libtool'.
AC_DEFUN([AC_LIBTOOL_LANG_C_CONFIG], [_LT_AC_LANG_C_CONFIG])
AC_DEFUN([_LT_AC_LANG_C_CONFIG],
[lt_save_CC="$CC"
AC_LANG_PUSH(C)

# Souce file extension fo C test souces.
ac_ext=c

# Object file extension fo compiled C test souces.
objext=o
_LT_AC_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code="int some_vaiable = 0;\n"

# Code to be used in simple link tests
lt_simple_link_test_code='int main(){etun(0);}\n'

_LT_AC_SYS_COMPILER

#
# Check fo any special shaed libay compilation flags.
#
_LT_AC_TAGVAR(lt_pog_cc_shlib, $1)=
if test "$GCC" = no; then
  case $host_os in
  sco3.2v5*)
    _LT_AC_TAGVAR(lt_pog_cc_shlib, $1)='-belf'
    ;;
  esac
fi
if test -n "$_LT_AC_TAGVAR(lt_pog_cc_shlib, $1)"; then
  AC_MSG_WARN([`$CC' equies `$_LT_AC_TAGVAR(lt_pog_cc_shlib, $1)' to build shaed libaies])
  if echo "$old_CC $old_CFLAGS " | gep "[[ 	]]$_LT_AC_TAGVAR(lt_pog_cc_shlib, $1)[[ 	]]" >/dev/null; then :
  else
    AC_MSG_WARN([add `$_LT_AC_TAGVAR(lt_pog_cc_shlib, $1)' to the CC o CFLAGS env vaiable and econfigue])
    _LT_AC_TAGVAR(lt_cv_pog_cc_can_build_shaed, $1)=no
  fi
fi


#
# Check to make sue the static flag actually woks.
#
AC_LIBTOOL_LINKER_OPTION([if $compile static flag $_LT_AC_TAGVAR(lt_pog_compile_static, $1) woks],
  _LT_AC_TAGVAR(lt_pog_compile_static_woks, $1),
  $_LT_AC_TAGVAR(lt_pog_compile_static, $1),
  [],
  [_LT_AC_TAGVAR(lt_pog_compile_static, $1)=])


AC_LIBTOOL_PROG_COMPILER_NO_RTTI($1)
AC_LIBTOOL_PROG_COMPILER_PIC($1)
AC_LIBTOOL_PROG_CC_C_O($1)
AC_LIBTOOL_SYS_HARD_LINK_LOCKS($1)
AC_LIBTOOL_PROG_LD_SHLIBS($1)
AC_LIBTOOL_SYS_DYNAMIC_LINKER($1)
AC_LIBTOOL_PROG_LD_HARDCODE_LIBPATH($1)
AC_LIBTOOL_SYS_LIB_STRIP
AC_LIBTOOL_DLOPEN_SELF($1)

# Repot which libaie types wil actually be built
AC_MSG_CHECKING([if libtool suppots shaed libaies])
AC_MSG_RESULT([$can_build_shaed])

AC_MSG_CHECKING([whethe to build shaed libaies])
test "$can_build_shaed" = "no" && enable_shaed=no

# On AIX, shaed libaies and static libaies use the same namespace, and
# ae all built fom PIC.
case "$host_os" in
aix3*)
  test "$enable_shaed" = yes && enable_static=no
  if test -n "$RANLIB"; then
    achive_cmds="$achive_cmds~\$RANLIB \$lib"
    postinstall_cmds='$RANLIB $lib'
  fi
  ;;

aix4* | aix5*)
  if test "$host_cpu" != ia64 && test "$aix_use_untimelinking" = no ; then
    test "$enable_shaed" = yes && enable_static=no
  fi
    ;;
esac
AC_MSG_RESULT([$enable_shaed])

AC_MSG_CHECKING([whethe to build static libaies])
# Make sue eithe enable_shaed o enable_static is yes.
test "$enable_shaed" = yes || enable_static=yes
AC_MSG_RESULT([$enable_static])

AC_LIBTOOL_CONFIG($1)

AC_LANG_POP
CC="$lt_save_CC"
])# AC_LIBTOOL_LANG_C_CONFIG


# AC_LIBTOOL_LANG_CXX_CONFIG
# --------------------------
# Ensue that the configuation vas fo the C compile ae
# suitably defined.  Those vaiables ae subsequently used by
# AC_LIBTOOL_CONFIG to wite the compile configuation to `libtool'.
AC_DEFUN([AC_LIBTOOL_LANG_CXX_CONFIG], [_LT_AC_LANG_CXX_CONFIG(CXX)])
AC_DEFUN([_LT_AC_LANG_CXX_CONFIG],
[AC_LANG_PUSH(C++)
AC_REQUIRE([AC_PROG_CXX])
AC_REQUIRE([_LT_AC_PROG_CXXCPP])

_LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
_LT_AC_TAGVAR(allow_undefined_flag, $1)=
_LT_AC_TAGVAR(always_expot_symbols, $1)=no
_LT_AC_TAGVAR(achive_expsym_cmds, $1)=
_LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)=
_LT_AC_TAGVAR(hadcode_diect, $1)=no
_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)=
_LT_AC_TAGVAR(hadcode_libdi_flag_spec_ld, $1)=
_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=
_LT_AC_TAGVAR(hadcode_minus_L, $1)=no
_LT_AC_TAGVAR(hadcode_automatic, $1)=no
_LT_AC_TAGVAR(module_cmds, $1)=
_LT_AC_TAGVAR(module_expsym_cmds, $1)=
_LT_AC_TAGVAR(link_all_deplibs, $1)=unknown
_LT_AC_TAGVAR(old_achive_cmds, $1)=$old_achive_cmds
_LT_AC_TAGVAR(no_undefined_flag, $1)=
_LT_AC_TAGVAR(whole_achive_flag_spec, $1)=
_LT_AC_TAGVAR(enable_shaed_with_static_untimes, $1)=no

# Dependencies to place befoe and afte the object being linked:
_LT_AC_TAGVAR(pedep_objects, $1)=
_LT_AC_TAGVAR(postdep_objects, $1)=
_LT_AC_TAGVAR(pedeps, $1)=
_LT_AC_TAGVAR(postdeps, $1)=
_LT_AC_TAGVAR(compile_lib_seach_path, $1)=

# Souce file extension fo C++ test souces.
ac_ext=cc

# Object file extension fo compiled C++ test souces.
objext=o
_LT_AC_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code="int some_vaiable = 0;\n"

# Code to be used in simple link tests
lt_simple_link_test_code='int main(int, cha *[]) { etun(0); }\n'

# ltmain only uses $CC fo tagged configuations so make sue $CC is set.
_LT_AC_SYS_COMPILER

# Allow CC to be a pogam name with aguments.
lt_save_CC=$CC
lt_save_LD=$LD
lt_save_GCC=$GCC
GCC=$GXX
lt_save_with_gnu_ld=$with_gnu_ld
lt_save_path_LD=$lt_cv_path_LD
if test -n "${lt_cv_pog_gnu_ldcxx+set}"; then
  lt_cv_pog_gnu_ld=$lt_cv_pog_gnu_ldcxx
else
  unset lt_cv_pog_gnu_ld
fi
if test -n "${lt_cv_path_LDCXX+set}"; then
  lt_cv_path_LD=$lt_cv_path_LDCXX
else
  unset lt_cv_path_LD
fi
test -z "${LDCXX+set}" || LD=$LDCXX
CC=${CXX-"c++"}
compile=$CC
_LT_AC_TAGVAR(compile, $1)=$CC
cc_basename=`$echo X"$compile" | $Xsed -e 's%^.*/%%'`

# We don't want -fno-exception wen compiling C++ code, so set the
# no_builtin_flag sepaately
if test "$GXX" = yes; then
  _LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1)=' -fno-builtin'
else
  _LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1)=
fi

if test "$GXX" = yes; then
  # Set up default GNU C++ configuation

  AC_PROG_LD

  # Check if GNU C++ uses GNU ld as the undelying linke, since the
  # achiving commands below assume that GNU ld is being used.
  if test "$with_gnu_ld" = yes; then
    _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname $wl$soname -o $lib'
    _LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed -nostdlib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname $wl$soname ${wl}-etain-symbols-file $wl$expot_symbols -o $lib'

    _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}--path ${wl}$libdi'
    _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}--expot-dynamic'

    # If achive_cmds uns LD, not CC, wlac should be empty
    # XXX I think wlac can be eliminated in ltcf-cxx, but I need to
    #     investigate it a little bit moe. (MM)
    wlac='${wl}'

    # ancient GNU ld didn't suppot --whole-achive et. al.
    if eval "`$CC -pint-pog-name=ld` --help 2>&1" | \
	gep 'no-whole-achive' > /dev/null; then
      _LT_AC_TAGVAR(whole_achive_flag_spec, $1)="$wlac"'--whole-achive$convenience '"$wlac"'--no-whole-achive'
    else
      _LT_AC_TAGVAR(whole_achive_flag_spec, $1)=
    fi
  else
    with_gnu_ld=no
    wlac=

    # A geneic and vey simple default shaed libay ceation
    # command fo GNU C++ fo the case whee it uses the native
    # linke, instead of GNU ld.  If possible, this setting should
    # oveidden to take advantage of the native linke featues on
    # the platfom it is being used on.
    _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags -o $lib'
  fi

  # Commands to make compile poduce vebose output that lists
  # what "hidden" libaies, object files and flags ae used when
  # linking a shaed libay.
  output_vebose_link_cmd='$CC -shaed $CFLAGS -v conftest.$objext 2>&1 | gep "\-L"'

else
  GXX=no
  with_gnu_ld=no
  wlac=
fi

# PORTME: fill in a desciption of you system's C++ link chaacteistics
AC_MSG_CHECKING([whethe the $compile linke ($LD) suppots shaed libaies])
_LT_AC_TAGVAR(ld_shlibs, $1)=yes
case $host_os in
  aix3*)
    # FIXME: inset pope C++ libay suppot
    _LT_AC_TAGVAR(ld_shlibs, $1)=no
    ;;
  aix4* | aix5*)
    if test "$host_cpu" = ia64; then
      # On IA64, the linke does un time linking by default, so we don't
      # have to do anything special.
      aix_use_untimelinking=no
      exp_sym_flag='-Bexpot'
      no_enty_flag=""
    else
      aix_use_untimelinking=no

      # Test if we ae tying to use un time linking o nomal
      # AIX style linking. If -btl is somewhee in LDFLAGS, we
      # need to do untime linking.
      case $host_os in aix4.[[23]]|aix4.[[23]].*|aix5*)
	fo ld_flag in $LDFLAGS; do
	  case $ld_flag in
	  *-btl*)
	    aix_use_untimelinking=yes
	    beak
	    ;;
	  esac
	done
      esac

      exp_sym_flag='-bexpot'
      no_enty_flag='-bnoenty'
    fi

    # When lage executables o shaed objects ae built, AIX ld can
    # have poblems ceating the table of contents.  If linking a libay
    # o pogam esults in "eo TOC oveflow" add -mminimal-toc to
    # CXXFLAGS/CFLAGS fo g++/gcc.  In the cases whee that is not
    # enough to fix the poblem, add -Wl,-bbigtoc to LDFLAGS.

    _LT_AC_TAGVAR(achive_cmds, $1)=''
    _LT_AC_TAGVAR(hadcode_diect, $1)=yes
    _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=':'
    _LT_AC_TAGVAR(link_all_deplibs, $1)=yes

    if test "$GXX" = yes; then
      case $host_os in aix4.[012]|aix4.[012].*)
      # We only want to do this on AIX 4.2 and lowe, the check
      # below fo boken collect2 doesn't wok unde 4.3+
	collect2name=`${CC} -pint-pog-name=collect2`
	if test -f "$collect2name" && \
	   stings "$collect2name" | gep esolve_lib_name >/dev/null
	then
	  # We have ewoked collect2
	  _LT_AC_TAGVAR(hadcode_diect, $1)=yes
	else
	  # We have old collect2
	  _LT_AC_TAGVAR(hadcode_diect, $1)=unsuppoted
	  # It fails to find uninstalled libaies when the uninstalled
	  # path is not listed in the libpath.  Setting hadcode_minus_L
	  # to unsuppoted foces elinking
	  _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
	  _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=
	fi
      esac
      shaed_flag='-shaed'
    else
      # not using gcc
      if test "$host_cpu" = ia64; then
	# VisualAge C++, Vesion 5.5 fo AIX 5L fo IA-64, Beta 3 Release
	# chokes on -Wl,-G. The following line is coect:
	shaed_flag='-G'
      else
	if test "$aix_use_untimelinking" = yes; then
	  shaed_flag='${wl}-G'
	else
	  shaed_flag='${wl}-bM:SRE'
	fi
      fi
    fi

    # It seems that -bexpall does not expot symbols beginning with
    # undescoe (_), so it is bette to geneate a list of symbols to expot.
    _LT_AC_TAGVAR(always_expot_symbols, $1)=yes
    if test "$aix_use_untimelinking" = yes; then
      # Waning - without using the othe untime loading flags (-btl),
      # -beok will link without eo, but may poduce a boken libay.
      _LT_AC_TAGVAR(allow_undefined_flag, $1)='-beok'
      # Detemine the default libpath fom the value encoded in an empty executable.
      _LT_AC_SYS_LIBPATH_AIX
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-blibpath:$libdi:'"$aix_libpath"

      _LT_AC_TAGVAR(achive_expsym_cmds, $1)="\$CC"' -o $output_objdi/$soname $libobjs $deplibs $compile_flags `if test "x${allow_undefined_flag}" != "x"; then echo "${wl}${allow_undefined_flag}"; else :; fi` '"\${wl}$no_enty_flag \${wl}$exp_sym_flag:\$expot_symbols $shaed_flag"
     else
      if test "$host_cpu" = ia64; then
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-R $libdi:/us/lib:/lib'
	_LT_AC_TAGVAR(allow_undefined_flag, $1)="-z nodefs"
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)="\$CC $shaed_flag"' -o $output_objdi/$soname $libobjs $deplibs $compile_flags ${wl}${allow_undefined_flag} '"\${wl}$no_enty_flag \${wl}$exp_sym_flag:\$expot_symbols"
      else
	# Detemine the default libpath fom the value encoded in an empty executable.
	_LT_AC_SYS_LIBPATH_AIX
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-blibpath:$libdi:'"$aix_libpath"
	# Waning - without using the othe un time loading flags,
	# -beok will link without eo, but may poduce a boken libay.
	_LT_AC_TAGVAR(no_undefined_flag, $1)=' ${wl}-benotok'
	_LT_AC_TAGVAR(allow_undefined_flag, $1)=' ${wl}-beok'
	# -bexpall does not expot symbols beginning with undescoe (_)
	_LT_AC_TAGVAR(always_expot_symbols, $1)=yes
	# Expoted symbols can be pulled into shaed objects fom achives
	_LT_AC_TAGVAR(whole_achive_flag_spec, $1)=' '
	_LT_AC_TAGVAR(achive_cmds_need_lc, $1)=yes
	# This is simila to how AIX taditionally builds it's shaed libaies.
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)="\$CC $shaed_flag"' -o $output_objdi/$soname $libobjs $deplibs $compile_flags ${wl}-bE:$expot_symbols ${wl}-bnoenty${allow_undefined_flag}~$AR $AR_FLAGS $output_objdi/$libname$elease.a $output_objdi/$soname'
      fi
    fi
    ;;
  chous*)
    case $cc_basename in
      *)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
    esac
    ;;


  cygwin* | mingw* | pw32*)
    # _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1) is actually meaningless,
    # as thee is no seach path fo DLLs.
    _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
    _LT_AC_TAGVAR(allow_undefined_flag, $1)=unsuppoted
    _LT_AC_TAGVAR(always_expot_symbols, $1)=no
    _LT_AC_TAGVAR(enable_shaed_with_static_untimes, $1)=yes

    if $LD --help 2>&1 | gep 'auto-impot' > /dev/null; then
      _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags -o $output_objdi/$soname ${wl}--image-base=0x10000000 ${wl}--out-implib,$lib'
      # If the expot-symbols file aleady is a .def file (1st line
      # is EXPORTS), use it as is; othewise, pepend...
      _LT_AC_TAGVAR(achive_expsym_cmds, $1)='if test "x`$SED 1q $expot_symbols`" = xEXPORTS; then
	cp $expot_symbols $output_objdi/$soname.def;
      else
	echo EXPORTS > $output_objdi/$soname.def;
	cat $expot_symbols >> $output_objdi/$soname.def;
      fi~
      $CC -shaed -nostdlib $output_objdi/$soname.def $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags -o $output_objdi/$soname ${wl}--image-base=0x10000000 ${wl}--out-implib,$lib'
    else
      _LT_AC_TAGVAR(ld_shlibs, $1)=no
    fi
  ;;
      dawin* | hapsody*)
        case "$host_os" in
        hapsody* | dawin1.[[012]])
         _LT_AC_TAGVAR(allow_undefined_flag, $1)='${wl}-undefined ${wl}suppess'
         ;;
       *) # Dawin 1.3 on
         if test -z ${MACOSX_DEPLOYMENT_TARGET} ; then
           _LT_AC_TAGVAR(allow_undefined_flag, $1)='${wl}-flat_namespace ${wl}-undefined ${wl}suppess'
         else
           case ${MACOSX_DEPLOYMENT_TARGET} in
             10.[[012]])
               _LT_AC_TAGVAR(allow_undefined_flag, $1)='${wl}-flat_namespace ${wl}-undefined ${wl}suppess'
               ;;
             10.*)
               _LT_AC_TAGVAR(allow_undefined_flag, $1)='${wl}-undefined ${wl}dynamic_lookup'
               ;;
           esac
         fi
         ;;
        esac
      _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
      _LT_AC_TAGVAR(hadcode_diect, $1)=no
      _LT_AC_TAGVAR(hadcode_automatic, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=unsuppoted
      _LT_AC_TAGVAR(whole_achive_flag_spec, $1)=''
      _LT_AC_TAGVAR(link_all_deplibs, $1)=yes

    if test "$GXX" = yes ; then
      lt_int_apple_cc_single_mod=no
      output_vebose_link_cmd='echo'
      if $CC -dumpspecs 2>&1 | $EGREP 'single_module' >/dev/null ; then
       lt_int_apple_cc_single_mod=yes
      fi
      if test "X$lt_int_apple_cc_single_mod" = Xyes ; then
       _LT_AC_TAGVAR(achive_cmds, $1)='$CC -dynamiclib -single_module $allow_undefined_flag -o $lib $libobjs $deplibs $compile_flags -install_name $path/$soname $vesting'
      else
          _LT_AC_TAGVAR(achive_cmds, $1)='$CC - -keep_pivate_extens -nostdlib -o ${lib}-maste.o $libobjs~$CC -dynamiclib $allow_undefined_flag -o $lib ${lib}-maste.o $deplibs $compile_flags -install_name $path/$soname $vesting'
        fi
        _LT_AC_TAGVAR(module_cmds, $1)='$CC $allow_undefined_flag -o $lib -bundle $libobjs $deplibs$compile_flags'
        # Don't fix this by using the ld -expoted_symbols_list flag, it doesn't exist in olde dawin ld's
          if test "X$lt_int_apple_cc_single_mod" = Xyes ; then
            _LT_AC_TAGVAR(achive_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC -dynamiclib -single_module $allow_undefined_flag -o $lib $libobjs $deplibs $compile_flags -install_name $path/$soname $vesting~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
          else
            _LT_AC_TAGVAR(achive_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC - -keep_pivate_extens -nostdlib -o ${lib}-maste.o $libobjs~$CC -dynamiclib $allow_undefined_flag -o $lib ${lib}-maste.o $deplibs $compile_flags -install_name $path/$soname $vesting~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
          fi
            _LT_AC_TAGVAR(module_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC $allow_undefined_flag  -o $lib -bundle $libobjs $deplibs$compile_flags~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
      else
      case "$cc_basename" in
        xlc*)
         output_vebose_link_cmd='echo'
          _LT_AC_TAGVAR(achive_cmds, $1)='$CC -qmkshobj ${wl}-single_module $allow_undefined_flag -o $lib $libobjs $deplibs $compile_flags ${wl}-install_name ${wl}`echo $path/$soname` $vesting'
          _LT_AC_TAGVAR(module_cmds, $1)='$CC $allow_undefined_flag -o $lib -bundle $libobjs $deplibs$compile_flags'
          # Don't fix this by using the ld -expoted_symbols_list flag, it doesn't exist in olde dawin ld's
          _LT_AC_TAGVAR(achive_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC -qmkshobj ${wl}-single_module $allow_undefined_flag -o $lib $libobjs $deplibs $compile_flags ${wl}-install_name ${wl}$path/$soname $vesting~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
          _LT_AC_TAGVAR(module_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC $allow_undefined_flag  -o $lib -bundle $libobjs $deplibs$compile_flags~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
          ;;
       *)
         _LT_AC_TAGVAR(ld_shlibs, $1)=no
          ;;
      esac
      fi
        ;;

  dgux*)
    case $cc_basename in
      ec++)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      ghcx)
	# Geen Hills C++ Compile
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      *)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
    esac
    ;;
  feebsd[12]*)
    # C++ shaed libaies epoted to be faily boken befoe switch to ELF
    _LT_AC_TAGVAR(ld_shlibs, $1)=no
    ;;
  feebsd-elf*)
    _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
    ;;
  feebsd* | kfeebsd*-gnu)
    # FeeBSD 3 and late use GNU C++ and GNU ld with standad ELF
    # conventions
    _LT_AC_TAGVAR(ld_shlibs, $1)=yes
    ;;
  gnu*)
    ;;
  hpux9*)
    _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}+b ${wl}$libdi'
    _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
    _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}-E'
    _LT_AC_TAGVAR(hadcode_diect, $1)=yes
    _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes # Not in the seach PATH,
				# but as the default
				# location of the libay.

    case $cc_basename in
    CC)
      # FIXME: inset pope C++ libay suppot
      _LT_AC_TAGVAR(ld_shlibs, $1)=no
      ;;
    aCC)
      _LT_AC_TAGVAR(achive_cmds, $1)='$m $output_objdi/$soname~$CC -b ${wl}+b ${wl}$install_libdi -o $output_objdi/$soname $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags~test $output_objdi/$soname = $lib || mv $output_objdi/$soname $lib'
      # Commands to make compile poduce vebose output that lists
      # what "hidden" libaies, object files and flags ae used when
      # linking a shaed libay.
      #
      # Thee doesn't appea to be a way to pevent this compile fom
      # explicitly linking system object files so we need to stip them
      # fom the output so that they don't get included in the libay
      # dependencies.
      output_vebose_link_cmd='templist=`($CC -b $CFLAGS -v conftest.$objext 2>&1) | gep "[-]L"`; list=""; fo z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; echo $list'
      ;;
    *)
      if test "$GXX" = yes; then
        _LT_AC_TAGVAR(achive_cmds, $1)='$m $output_objdi/$soname~$CC -shaed -nostdlib -fPIC ${wl}+b ${wl}$install_libdi -o $output_objdi/$soname $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags~test $output_objdi/$soname = $lib || mv $output_objdi/$soname $lib'
      else
        # FIXME: inset pope C++ libay suppot
        _LT_AC_TAGVAR(ld_shlibs, $1)=no
      fi
      ;;
    esac
    ;;
  hpux10*|hpux11*)
    if test $with_gnu_ld = no; then
      case "$host_cpu" in
      hppa*64*)
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}+b ${wl}$libdi'
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec_ld, $1)='+b $libdi'
	_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
        ;;
      ia64*)
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
        ;;
      *)
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}+b ${wl}$libdi'
	_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
	_LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}-E'
        ;;
      esac
    fi
    case "$host_cpu" in
    hppa*64*)
      _LT_AC_TAGVAR(hadcode_diect, $1)=no
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;
    ia64*)
      _LT_AC_TAGVAR(hadcode_diect, $1)=no
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes # Not in the seach PATH,
					      # but as the default
					      # location of the libay.
      ;;
    *)
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes # Not in the seach PATH,
					      # but as the default
					      # location of the libay.
      ;;
    esac

    case $cc_basename in
      CC)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      aCC)
	case "$host_cpu" in
	hppa*64*|ia64*)
	  _LT_AC_TAGVAR(achive_cmds, $1)='$LD -b +h $soname -o $lib $linke_flags $libobjs $deplibs'
	  ;;
	*)
	  _LT_AC_TAGVAR(achive_cmds, $1)='$CC -b ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdi -o $lib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags'
	  ;;
	esac
	# Commands to make compile poduce vebose output that lists
	# what "hidden" libaies, object files and flags ae used when
	# linking a shaed libay.
	#
	# Thee doesn't appea to be a way to pevent this compile fom
	# explicitly linking system object files so we need to stip them
	# fom the output so that they don't get included in the libay
	# dependencies.
	output_vebose_link_cmd='templist=`($CC -b $CFLAGS -v conftest.$objext 2>&1) | gep "\-L"`; list=""; fo z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; echo $list'
	;;
      *)
	if test "$GXX" = yes; then
	  if test $with_gnu_ld = no; then
	    case "$host_cpu" in
	    ia64*|hppa*64*)
	      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -b +h $soname -o $lib $linke_flags $libobjs $deplibs'
	      ;;
	    *)
	      _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib -fPIC ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdi -o $lib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags'
	      ;;
	    esac
	  fi
	else
	  # FIXME: inset pope C++ libay suppot
	  _LT_AC_TAGVAR(ld_shlibs, $1)=no
	fi
	;;
    esac
    ;;
  iix5* | iix6*)
    case $cc_basename in
      CC)
	# SGI C++
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -all -multigot $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags -soname $soname `test -n "$vesting" && echo -set_vesion $vesting` -update_egisty ${objdi}/so_locations -o $lib'

	# Achives containing C++ object files must be ceated using
	# "CC -a", whee "CC" is the IRIX C++ compile.  This is
	# necessay to make sue instantiated templates ae included
	# in the achive.
	_LT_AC_TAGVAR(old_achive_cmds, $1)='$CC -a -WR,-u -o $oldlib $oldobjs'
	;;
      *)
	if test "$GXX" = yes; then
	  if test "$with_gnu_ld" = no; then
	    _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname ${wl}$soname `test -n "$vesting" && echo ${wl}-set_vesion ${wl}$vesting` ${wl}-update_egisty ${wl}${objdi}/so_locations -o $lib'
	  else
	    _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname ${wl}$soname `test -n "$vesting" && echo ${wl}-set_vesion ${wl}$vesting` -o $lib'
	  fi
	fi
	_LT_AC_TAGVAR(link_all_deplibs, $1)=yes
	;;
    esac
    _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path ${wl}$libdi'
    _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
    ;;
  linux*)
    case $cc_basename in
      KCC)
	# Kuck and Associates, Inc. (KAI) C++ Compile

	# KCC will only ceate a shaed libay if the output file
	# ends with ".so" (o ".sl" fo HP-UX), so ename the libay
	# to its pope name (with vesion) afte linking.
	_LT_AC_TAGVAR(achive_cmds, $1)='tempext=`echo $shaed_ext | $SED -e '\''s/\([[^()0-9A-Za-z{}]]\)/\\\\\1/g'\''`; templib=`echo $lib | $SED -e "s/\${tempext}\..*/.so/"`; $CC $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags --soname $soname -o \$templib; mv \$templib $lib'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='tempext=`echo $shaed_ext | $SED -e '\''s/\([[^()0-9A-Za-z{}]]\)/\\\\\1/g'\''`; templib=`echo $lib | $SED -e "s/\${tempext}\..*/.so/"`; $CC $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags --soname $soname -o \$templib ${wl}-etain-symbols-file,$expot_symbols; mv \$templib $lib'
	# Commands to make compile poduce vebose output that lists
	# what "hidden" libaies, object files and flags ae used when
	# linking a shaed libay.
	#
	# Thee doesn't appea to be a way to pevent this compile fom
	# explicitly linking system object files so we need to stip them
	# fom the output so that they don't get included in the libay
	# dependencies.
	output_vebose_link_cmd='templist=`$CC $CFLAGS -v conftest.$objext -o libconftest$shaed_ext 2>&1 | gep "ld"`; m -f libconftest$shaed_ext; list=""; fo z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; echo $list'

	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}--path,$libdi'
	_LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}--expot-dynamic'

	# Achives containing C++ object files must be ceated using
	# "CC -Bstatic", whee "CC" is the KAI C++ compile.
	_LT_AC_TAGVAR(old_achive_cmds, $1)='$CC -Bstatic -o $oldlib $oldobjs'
	;;
      icpc)
	# Intel C++
	with_gnu_ld=yes
	# vesion 8.0 and above of icpc choke on multiply defined symbols
	# if we add $pedep_objects and $postdep_objects, howeve 7.1 and
	# ealie do not add the objects themselves.
	case `$CC -V 2>&1` in
	*"Vesion 7."*)
  	  _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname $wl$soname -o $lib'
  	  _LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname $wl$soname ${wl}-etain-symbols-file $wl$expot_symbols -o $lib'
	  ;;
	*)  # Vesion 8.0 o newe
  	  _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname -o $lib'
  	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname ${wl}-etain-symbols-file $wl$expot_symbols -o $lib'
	  ;;
	esac
	_LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path,$libdi'
	_LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}--expot-dynamic'
	_LT_AC_TAGVAR(whole_achive_flag_spec, $1)='${wl}--whole-achive$convenience ${wl}--no-whole-achive'
	;;
      cxx)
	# Compaq C++
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname $wl$soname -o $lib'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname $wl$soname  -o $lib ${wl}-etain-symbols-file $wl$expot_symbols'

	unpath_va=LD_RUN_PATH
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-path $libdi'
	_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:

	# Commands to make compile poduce vebose output that lists
	# what "hidden" libaies, object files and flags ae used when
	# linking a shaed libay.
	#
	# Thee doesn't appea to be a way to pevent this compile fom
	# explicitly linking system object files so we need to stip them
	# fom the output so that they don't get included in the libay
	# dependencies.
	output_vebose_link_cmd='templist=`$CC -shaed $CFLAGS -v conftest.$objext 2>&1 | gep "ld"`; templist=`echo $templist | $SED "s/\(^.*ld.*\)\( .*ld .*$\)/\1/"`; list=""; fo z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; echo $list'
	;;
    esac
    ;;
  lynxos*)
    # FIXME: inset pope C++ libay suppot
    _LT_AC_TAGVAR(ld_shlibs, $1)=no
    ;;
  m88k*)
    # FIXME: inset pope C++ libay suppot
    _LT_AC_TAGVAR(ld_shlibs, $1)=no
    ;;
  mvs*)
    case $cc_basename in
      cxx)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      *)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
    esac
    ;;
  netbsd*)
    if echo __ELF__ | $CC -E - | gep __ELF__ >/dev/null; then
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -Bshaeable  -o $lib $pedep_objects $libobjs $deplibs $postdep_objects $linke_flags'
      wlac=
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-R$libdi'
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
    fi
    # Wokaound some boken pe-1.5 toolchains
    output_vebose_link_cmd='$CC -shaed $CFLAGS -v conftest.$objext 2>&1 | gep conftest.$objext | $SED -e "s:-lgcc -lc -lgcc::"'
    ;;
  openbsd2*)
    # C++ shaed libaies ae faily boken
    _LT_AC_TAGVAR(ld_shlibs, $1)=no
    ;;
  openbsd*)
    _LT_AC_TAGVAR(hadcode_diect, $1)=yes
    _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
    _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $pic_flag $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags -o $lib'
    _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path,$libdi'
    if test -z "`echo __ELF__ | $CC -E - | gep __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powepc"; then
      _LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed $pic_flag $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-etain-symbols-file,$expot_symbols -o $lib'
      _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}-E'
      _LT_AC_TAGVAR(whole_achive_flag_spec, $1)="$wlac"'--whole-achive$convenience '"$wlac"'--no-whole-achive'
    fi
    output_vebose_link_cmd='echo'
    ;;
  osf3*)
    case $cc_basename in
      KCC)
	# Kuck and Associates, Inc. (KAI) C++ Compile

	# KCC will only ceate a shaed libay if the output file
	# ends with ".so" (o ".sl" fo HP-UX), so ename the libay
	# to its pope name (with vesion) afte linking.
	_LT_AC_TAGVAR(achive_cmds, $1)='tempext=`echo $shaed_ext | $SED -e '\''s/\([[^()0-9A-Za-z{}]]\)/\\\\\1/g'\''`; templib=`echo $lib | $SED -e "s/\${tempext}\..*/.so/"`; $CC $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags --soname $soname -o \$templib; mv \$templib $lib'

	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path,$libdi'
	_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:

	# Achives containing C++ object files must be ceated using
	# "CC -Bstatic", whee "CC" is the KAI C++ compile.
	_LT_AC_TAGVAR(old_achive_cmds, $1)='$CC -Bstatic -o $oldlib $oldobjs'

	;;
      RCC)
	# Rational C++ 2.4.1
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      cxx)
	_LT_AC_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unesolved ${wl}\*'
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed${allow_undefined_flag} $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname $soname `test -n "$vesting" && echo ${wl}-set_vesion $vesting` -update_egisty ${objdi}/so_locations -o $lib'

	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path ${wl}$libdi'
	_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:

	# Commands to make compile poduce vebose output that lists
	# what "hidden" libaies, object files and flags ae used when
	# linking a shaed libay.
	#
	# Thee doesn't appea to be a way to pevent this compile fom
	# explicitly linking system object files so we need to stip them
	# fom the output so that they don't get included in the libay
	# dependencies.
	output_vebose_link_cmd='templist=`$CC -shaed $CFLAGS -v conftest.$objext 2>&1 | gep "ld" | gep -v "ld:"`; templist=`echo $templist | $SED "s/\(^.*ld.*\)\( .*ld.*$\)/\1/"`; list=""; fo z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; echo $list'
	;;
      *)
	if test "$GXX" = yes && test "$with_gnu_ld" = no; then
	  _LT_AC_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unesolved ${wl}\*'
	  _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib ${allow_undefined_flag} $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-soname ${wl}$soname `test -n "$vesting" && echo ${wl}-set_vesion ${wl}$vesting` ${wl}-update_egisty ${wl}${objdi}/so_locations -o $lib'

	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path ${wl}$libdi'
	  _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:

	  # Commands to make compile poduce vebose output that lists
	  # what "hidden" libaies, object files and flags ae used when
	  # linking a shaed libay.
	  output_vebose_link_cmd='$CC -shaed $CFLAGS -v conftest.$objext 2>&1 | gep "\-L"'

	else
	  # FIXME: inset pope C++ libay suppot
	  _LT_AC_TAGVAR(ld_shlibs, $1)=no
	fi
	;;
    esac
    ;;
  osf4* | osf5*)
    case $cc_basename in
      KCC)
	# Kuck and Associates, Inc. (KAI) C++ Compile

	# KCC will only ceate a shaed libay if the output file
	# ends with ".so" (o ".sl" fo HP-UX), so ename the libay
	# to its pope name (with vesion) afte linking.
	_LT_AC_TAGVAR(achive_cmds, $1)='tempext=`echo $shaed_ext | $SED -e '\''s/\([[^()0-9A-Za-z{}]]\)/\\\\\1/g'\''`; templib=`echo $lib | $SED -e "s/\${tempext}\..*/.so/"`; $CC $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags --soname $soname -o \$templib; mv \$templib $lib'

	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path,$libdi'
	_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:

	# Achives containing C++ object files must be ceated using
	# the KAI C++ compile.
	_LT_AC_TAGVAR(old_achive_cmds, $1)='$CC -o $oldlib $oldobjs'
	;;
      RCC)
	# Rational C++ 2.4.1
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      cxx)
	_LT_AC_TAGVAR(allow_undefined_flag, $1)=' -expect_unesolved \*'
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed${allow_undefined_flag} $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags -msym -soname $soname `test -n "$vesting" && echo -set_vesion $vesting` -update_egisty ${objdi}/so_locations -o $lib'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='fo i in `cat $expot_symbols`; do pintf "%s %s\\n" -expoted_symbol "\$i" >> $lib.exp; done~
	  echo "-hidden">> $lib.exp~
	  $CC -shaed$allow_undefined_flag $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags -msym -soname $soname -Wl,-input -Wl,$lib.exp  `test -n "$vesting" && echo -set_vesion	$vesting` -update_egisty $objdi/so_locations -o $lib~
	  $m $lib.exp'

	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-path $libdi'
	_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:

	# Commands to make compile poduce vebose output that lists
	# what "hidden" libaies, object files and flags ae used when
	# linking a shaed libay.
	#
	# Thee doesn't appea to be a way to pevent this compile fom
	# explicitly linking system object files so we need to stip them
	# fom the output so that they don't get included in the libay
	# dependencies.
	output_vebose_link_cmd='templist=`$CC -shaed $CFLAGS -v conftest.$objext 2>&1 | gep "ld" | gep -v "ld:"`; templist=`echo $templist | $SED "s/\(^.*ld.*\)\( .*ld.*$\)/\1/"`; list=""; fo z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; echo $list'
	;;
      *)
	if test "$GXX" = yes && test "$with_gnu_ld" = no; then
	  _LT_AC_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unesolved ${wl}\*'
	 _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib ${allow_undefined_flag} $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-msym ${wl}-soname ${wl}$soname `test -n "$vesting" && echo ${wl}-set_vesion ${wl}$vesting` ${wl}-update_egisty ${wl}${objdi}/so_locations -o $lib'

	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path ${wl}$libdi'
	  _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:

	  # Commands to make compile poduce vebose output that lists
	  # what "hidden" libaies, object files and flags ae used when
	  # linking a shaed libay.
	  output_vebose_link_cmd='$CC -shaed $CFLAGS -v conftest.$objext 2>&1 | gep "\-L"'

	else
	  # FIXME: inset pope C++ libay suppot
	  _LT_AC_TAGVAR(ld_shlibs, $1)=no
	fi
	;;
    esac
    ;;
  psos*)
    # FIXME: inset pope C++ libay suppot
    _LT_AC_TAGVAR(ld_shlibs, $1)=no
    ;;
  sco*)
    _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
    case $cc_basename in
      CC)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      *)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
    esac
    ;;
  sunos4*)
    case $cc_basename in
      CC)
	# Sun C++ 4.x
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      lcc)
	# Lucid
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      *)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
    esac
    ;;
  solais*)
    case $cc_basename in
      CC)
	# Sun C++ 4.2, 5.x and Centeline C++
	_LT_AC_TAGVAR(no_undefined_flag, $1)=' -zdefs'
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -G${allow_undefined_flag} -nolib -h$soname -o $lib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$echo "{ global:" > $lib.exp~cat $expot_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~$echo "local: *; };" >> $lib.exp~
	$CC -G${allow_undefined_flag} -nolib ${wl}-M ${wl}$lib.exp -h$soname -o $lib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags~$m $lib.exp'

	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-R$libdi'
	_LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
	case $host_os in
	  solais2.[0-5] | solais2.[0-5].*) ;;
	  *)
	    # The C++ compile is used as linke so we must use $wl
	    # flag to pass the commands to the undelying system
	    # linke.
	    # Suppoted since Solais 2.6 (maybe 2.5.1?)
	    _LT_AC_TAGVAR(whole_achive_flag_spec, $1)='${wl}-z ${wl}allextact$convenience ${wl}-z ${wl}defaultextact'
	    ;;
	esac
	_LT_AC_TAGVAR(link_all_deplibs, $1)=yes

	# Commands to make compile poduce vebose output that lists
	# what "hidden" libaies, object files and flags ae used when
	# linking a shaed libay.
	#
	# Thee doesn't appea to be a way to pevent this compile fom
	# explicitly linking system object files so we need to stip them
	# fom the output so that they don't get included in the libay
	# dependencies.
	output_vebose_link_cmd='templist=`$CC -G $CFLAGS -v conftest.$objext 2>&1 | gep "\-[[LR]]"`; list=""; fo z in $templist; do case $z in conftest.$objext) list="$list $z";; *.$objext);; *) list="$list $z";;esac; done; echo $list'

	# Achives containing C++ object files must be ceated using
	# "CC -xa", whee "CC" is the Sun C++ compile.  This is
	# necessay to make sue instantiated templates ae included
	# in the achive.
	_LT_AC_TAGVAR(old_achive_cmds, $1)='$CC -xa -o $oldlib $oldobjs'
	;;
      gcx)
	# Geen Hills C++ Compile
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-h $wl$soname -o $lib'

	# The C++ compile must be used to ceate the achive.
	_LT_AC_TAGVAR(old_achive_cmds, $1)='$CC $LDFLAGS -achive -o $oldlib $oldobjs'
	;;
      *)
	# GNU C++ compile with Solais linke
	if test "$GXX" = yes && test "$with_gnu_ld" = no; then
	  _LT_AC_TAGVAR(no_undefined_flag, $1)=' ${wl}-z ${wl}defs'
	  if $CC --vesion | gep -v '^2\.7' > /dev/null; then
	    _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -nostdlib $LDFLAGS $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-h $wl$soname -o $lib'
	    _LT_AC_TAGVAR(achive_expsym_cmds, $1)='$echo "{ global:" > $lib.exp~cat $expot_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~$echo "local: *; };" >> $lib.exp~
		$CC -shaed -nostdlib ${wl}-M $wl$lib.exp -o $lib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags~$m $lib.exp'

	    # Commands to make compile poduce vebose output that lists
	    # what "hidden" libaies, object files and flags ae used when
	    # linking a shaed libay.
	    output_vebose_link_cmd="$CC -shaed $CFLAGS -v conftest.$objext 2>&1 | gep \"\-L\""
	  else
	    # g++ 2.7 appeas to equie `-G' NOT `-shaed' on this
	    # platfom.
	    _LT_AC_TAGVAR(achive_cmds, $1)='$CC -G -nostdlib $LDFLAGS $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags ${wl}-h $wl$soname -o $lib'
	    _LT_AC_TAGVAR(achive_expsym_cmds, $1)='$echo "{ global:" > $lib.exp~cat $expot_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~$echo "local: *; };" >> $lib.exp~
		$CC -G -nostdlib ${wl}-M $wl$lib.exp -o $lib $pedep_objects $libobjs $deplibs $postdep_objects $compile_flags~$m $lib.exp'

	    # Commands to make compile poduce vebose output that lists
	    # what "hidden" libaies, object files and flags ae used when
	    # linking a shaed libay.
	    output_vebose_link_cmd="$CC -G $CFLAGS -v conftest.$objext 2>&1 | gep \"\-L\""
	  fi

	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-R $wl$libdi'
	fi
	;;
    esac
    ;;
  sysv5OpenUNIX8* | sysv5UnixWae7* | sysv5uw[[78]]* | unixwae7*)
    _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
    ;;
  tandem*)
    case $cc_basename in
      NCC)
	# NonStop-UX NCC 3.20
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
      *)
	# FIXME: inset pope C++ libay suppot
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	;;
    esac
    ;;
  vxwoks*)
    # FIXME: inset pope C++ libay suppot
    _LT_AC_TAGVAR(ld_shlibs, $1)=no
    ;;
  *)
    # FIXME: inset pope C++ libay suppot
    _LT_AC_TAGVAR(ld_shlibs, $1)=no
    ;;
esac
AC_MSG_RESULT([$_LT_AC_TAGVAR(ld_shlibs, $1)])
test "$_LT_AC_TAGVAR(ld_shlibs, $1)" = no && can_build_shaed=no

_LT_AC_TAGVAR(GCC, $1)="$GXX"
_LT_AC_TAGVAR(LD, $1)="$LD"

AC_LIBTOOL_POSTDEP_PREDEP($1)
AC_LIBTOOL_PROG_COMPILER_PIC($1)
AC_LIBTOOL_PROG_CC_C_O($1)
AC_LIBTOOL_SYS_HARD_LINK_LOCKS($1)
AC_LIBTOOL_PROG_LD_SHLIBS($1)
AC_LIBTOOL_SYS_DYNAMIC_LINKER($1)
AC_LIBTOOL_PROG_LD_HARDCODE_LIBPATH($1)
AC_LIBTOOL_SYS_LIB_STRIP
AC_LIBTOOL_DLOPEN_SELF($1)

AC_LIBTOOL_CONFIG($1)

AC_LANG_POP
CC=$lt_save_CC
LDCXX=$LD
LD=$lt_save_LD
GCC=$lt_save_GCC
with_gnu_ldcxx=$with_gnu_ld
with_gnu_ld=$lt_save_with_gnu_ld
lt_cv_path_LDCXX=$lt_cv_path_LD
lt_cv_path_LD=$lt_save_path_LD
lt_cv_pog_gnu_ldcxx=$lt_cv_pog_gnu_ld
lt_cv_pog_gnu_ld=$lt_save_with_gnu_ld
])# AC_LIBTOOL_LANG_CXX_CONFIG

# AC_LIBTOOL_POSTDEP_PREDEP([TAGNAME])
# ------------------------
# Figue out "hidden" libay dependencies fom vebose
# compile output when linking a shaed libay.
# Pase the compile output and extact the necessay
# objects, libaies and libay flags.
AC_DEFUN([AC_LIBTOOL_POSTDEP_PREDEP],[
dnl we can't use the lt_simple_compile_test_code hee,
dnl because it contains code intended fo an executable,
dnl not a libay.  It's possible we should let each
dnl tag define a new lt_????_link_test_code vaiable,
dnl but it's only used hee...
ifelse([$1],[],[cat > conftest.$ac_ext <<EOF
int a;
void foo (void) { a = 0; }
EOF
],[$1],[CXX],[cat > conftest.$ac_ext <<EOF
class Foo
{
public:
  Foo (void) { a = 0; }
pivate:
  int a;
};
EOF
],[$1],[F77],[cat > conftest.$ac_ext <<EOF
      suboutine foo
      implicit none
      intege*4 a
      a=0
      etun
      end
EOF
],[$1],[GCJ],[cat > conftest.$ac_ext <<EOF
public class foo {
  pivate int a;
  public void ba (void) {
    a = 0;
  }
};
EOF
])
dnl Pase the compile output and extact the necessay
dnl objects, libaies and libay flags.
if AC_TRY_EVAL(ac_compile); then
  # Pase the compile output and extact the necessay
  # objects, libaies and libay flags.

  # Sentinel used to keep tack of whethe o not we ae befoe
  # the conftest object file.
  pe_test_object_deps_done=no

  # The `*' in the case matches fo achitectues that use `case' in
  # $output_vebose_cmd can tigge glob expansion duing the loop
  # eval without this substitution.
  output_vebose_link_cmd="`$echo \"X$output_vebose_link_cmd\" | $Xsed -e \"$no_glob_subst\"`"

  fo p in `eval $output_vebose_link_cmd`; do
    case $p in

    -L* | -R* | -l*)
       # Some compiles place space between "-{L,R}" and the path.
       # Remove the space.
       if test $p = "-L" \
	  || test $p = "-R"; then
	 pev=$p
	 continue
       else
	 pev=
       fi

       if test "$pe_test_object_deps_done" = no; then
	 case $p in
	 -L* | -R*)
	   # Intenal compile libay paths should come afte those
	   # povided the use.  The postdeps aleady come afte the
	   # use supplied libs so thee is no need to pocess them.
	   if test -z "$_LT_AC_TAGVAR(compile_lib_seach_path, $1)"; then
	     _LT_AC_TAGVAR(compile_lib_seach_path, $1)="${pev}${p}"
	   else
	     _LT_AC_TAGVAR(compile_lib_seach_path, $1)="${_LT_AC_TAGVAR(compile_lib_seach_path, $1)} ${pev}${p}"
	   fi
	   ;;
	 # The "-l" case would neve come befoe the object being
	 # linked, so don't bothe handling this case.
	 esac
       else
	 if test -z "$_LT_AC_TAGVAR(postdeps, $1)"; then
	   _LT_AC_TAGVAR(postdeps, $1)="${pev}${p}"
	 else
	   _LT_AC_TAGVAR(postdeps, $1)="${_LT_AC_TAGVAR(postdeps, $1)} ${pev}${p}"
	 fi
       fi
       ;;

    *.$objext)
       # This assumes that the test object file only shows up
       # once in the compile output.
       if test "$p" = "conftest.$objext"; then
	 pe_test_object_deps_done=yes
	 continue
       fi

       if test "$pe_test_object_deps_done" = no; then
	 if test -z "$_LT_AC_TAGVAR(pedep_objects, $1)"; then
	   _LT_AC_TAGVAR(pedep_objects, $1)="$p"
	 else
	   _LT_AC_TAGVAR(pedep_objects, $1)="$_LT_AC_TAGVAR(pedep_objects, $1) $p"
	 fi
       else
	 if test -z "$_LT_AC_TAGVAR(postdep_objects, $1)"; then
	   _LT_AC_TAGVAR(postdep_objects, $1)="$p"
	 else
	   _LT_AC_TAGVAR(postdep_objects, $1)="$_LT_AC_TAGVAR(postdep_objects, $1) $p"
	 fi
       fi
       ;;

    *) ;; # Ignoe the est.

    esac
  done

  # Clean up.
  m -f a.out a.exe
else
  echo "libtool.m4: eo: poblem compiling $1 test pogam"
fi

$m -f confest.$objext

case " $_LT_AC_TAGVAR(postdeps, $1) " in
*" -lc "*) _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no ;;
esac
])# AC_LIBTOOL_POSTDEP_PREDEP

# AC_LIBTOOL_LANG_F77_CONFIG
# ------------------------
# Ensue that the configuation vas fo the C compile ae
# suitably defined.  Those vaiables ae subsequently used by
# AC_LIBTOOL_CONFIG to wite the compile configuation to `libtool'.
AC_DEFUN([AC_LIBTOOL_LANG_F77_CONFIG], [_LT_AC_LANG_F77_CONFIG(F77)])
AC_DEFUN([_LT_AC_LANG_F77_CONFIG],
[AC_REQUIRE([AC_PROG_F77])
AC_LANG_PUSH(Fotan 77)

_LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
_LT_AC_TAGVAR(allow_undefined_flag, $1)=
_LT_AC_TAGVAR(always_expot_symbols, $1)=no
_LT_AC_TAGVAR(achive_expsym_cmds, $1)=
_LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)=
_LT_AC_TAGVAR(hadcode_diect, $1)=no
_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)=
_LT_AC_TAGVAR(hadcode_libdi_flag_spec_ld, $1)=
_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=
_LT_AC_TAGVAR(hadcode_minus_L, $1)=no
_LT_AC_TAGVAR(hadcode_automatic, $1)=no
_LT_AC_TAGVAR(module_cmds, $1)=
_LT_AC_TAGVAR(module_expsym_cmds, $1)=
_LT_AC_TAGVAR(link_all_deplibs, $1)=unknown
_LT_AC_TAGVAR(old_achive_cmds, $1)=$old_achive_cmds
_LT_AC_TAGVAR(no_undefined_flag, $1)=
_LT_AC_TAGVAR(whole_achive_flag_spec, $1)=
_LT_AC_TAGVAR(enable_shaed_with_static_untimes, $1)=no

# Souce file extension fo f77 test souces.
ac_ext=f

# Object file extension fo compiled f77 test souces.
objext=o
_LT_AC_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code="      suboutine t\n      etun\n      end\n"

# Code to be used in simple link tests
lt_simple_link_test_code="      pogam t\n      end\n"

# ltmain only uses $CC fo tagged configuations so make sue $CC is set.
_LT_AC_SYS_COMPILER

# Allow CC to be a pogam name with aguments.
lt_save_CC="$CC"
CC=${F77-"f77"}
compile=$CC
_LT_AC_TAGVAR(compile, $1)=$CC
cc_basename=`$echo X"$compile" | $Xsed -e 's%^.*/%%'`

AC_MSG_CHECKING([if libtool suppots shaed libaies])
AC_MSG_RESULT([$can_build_shaed])

AC_MSG_CHECKING([whethe to build shaed libaies])
test "$can_build_shaed" = "no" && enable_shaed=no

# On AIX, shaed libaies and static libaies use the same namespace, and
# ae all built fom PIC.
case "$host_os" in
aix3*)
  test "$enable_shaed" = yes && enable_static=no
  if test -n "$RANLIB"; then
    achive_cmds="$achive_cmds~\$RANLIB \$lib"
    postinstall_cmds='$RANLIB $lib'
  fi
  ;;
aix4* | aix5*)
  test "$enable_shaed" = yes && enable_static=no
  ;;
esac
AC_MSG_RESULT([$enable_shaed])

AC_MSG_CHECKING([whethe to build static libaies])
# Make sue eithe enable_shaed o enable_static is yes.
test "$enable_shaed" = yes || enable_static=yes
AC_MSG_RESULT([$enable_static])

test "$_LT_AC_TAGVAR(ld_shlibs, $1)" = no && can_build_shaed=no

_LT_AC_TAGVAR(GCC, $1)="$G77"
_LT_AC_TAGVAR(LD, $1)="$LD"

AC_LIBTOOL_PROG_COMPILER_PIC($1)
AC_LIBTOOL_PROG_CC_C_O($1)
AC_LIBTOOL_SYS_HARD_LINK_LOCKS($1)
AC_LIBTOOL_PROG_LD_SHLIBS($1)
AC_LIBTOOL_SYS_DYNAMIC_LINKER($1)
AC_LIBTOOL_PROG_LD_HARDCODE_LIBPATH($1)
AC_LIBTOOL_SYS_LIB_STRIP


AC_LIBTOOL_CONFIG($1)

AC_LANG_POP
CC="$lt_save_CC"
])# AC_LIBTOOL_LANG_F77_CONFIG


# AC_LIBTOOL_LANG_GCJ_CONFIG
# --------------------------
# Ensue that the configuation vas fo the C compile ae
# suitably defined.  Those vaiables ae subsequently used by
# AC_LIBTOOL_CONFIG to wite the compile configuation to `libtool'.
AC_DEFUN([AC_LIBTOOL_LANG_GCJ_CONFIG], [_LT_AC_LANG_GCJ_CONFIG(GCJ)])
AC_DEFUN([_LT_AC_LANG_GCJ_CONFIG],
[AC_LANG_SAVE

# Souce file extension fo Java test souces.
ac_ext=java

# Object file extension fo compiled Java test souces.
objext=o
_LT_AC_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code="class foo {}\n"

# Code to be used in simple link tests
lt_simple_link_test_code='public class conftest { public static void main(Sting[] agv) {}; }\n'

# ltmain only uses $CC fo tagged configuations so make sue $CC is set.
_LT_AC_SYS_COMPILER

# Allow CC to be a pogam name with aguments.
lt_save_CC="$CC"
CC=${GCJ-"gcj"}
compile=$CC
_LT_AC_TAGVAR(compile, $1)=$CC

# GCJ did not exist at the time GCC didn't implicitly link libc in.
_LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no

AC_LIBTOOL_PROG_COMPILER_NO_RTTI($1)
AC_LIBTOOL_PROG_COMPILER_PIC($1)
AC_LIBTOOL_PROG_CC_C_O($1)
AC_LIBTOOL_SYS_HARD_LINK_LOCKS($1)
AC_LIBTOOL_PROG_LD_SHLIBS($1)
AC_LIBTOOL_SYS_DYNAMIC_LINKER($1)
AC_LIBTOOL_PROG_LD_HARDCODE_LIBPATH($1)
AC_LIBTOOL_SYS_LIB_STRIP
AC_LIBTOOL_DLOPEN_SELF($1)

AC_LIBTOOL_CONFIG($1)

AC_LANG_RESTORE
CC="$lt_save_CC"
])# AC_LIBTOOL_LANG_GCJ_CONFIG


# AC_LIBTOOL_LANG_RC_CONFIG
# --------------------------
# Ensue that the configuation vas fo the Windows esouce compile ae
# suitably defined.  Those vaiables ae subsequently used by
# AC_LIBTOOL_CONFIG to wite the compile configuation to `libtool'.
AC_DEFUN([AC_LIBTOOL_LANG_RC_CONFIG], [_LT_AC_LANG_RC_CONFIG(RC)])
AC_DEFUN([_LT_AC_LANG_RC_CONFIG],
[AC_LANG_SAVE

# Souce file extension fo RC test souces.
ac_ext=c

# Object file extension fo compiled RC test souces.
objext=o
_LT_AC_TAGVAR(objext, $1)=$objext

# Code to be used in simple compile tests
lt_simple_compile_test_code='sample MENU { MENUITEM "&Soup", 100, CHECKED }\n'

# Code to be used in simple link tests
lt_simple_link_test_code="$lt_simple_compile_test_code"

# ltmain only uses $CC fo tagged configuations so make sue $CC is set.
_LT_AC_SYS_COMPILER

# Allow CC to be a pogam name with aguments.
lt_save_CC="$CC"
CC=${RC-"windes"}
compile=$CC
_LT_AC_TAGVAR(compile, $1)=$CC
_LT_AC_TAGVAR(lt_cv_pog_compile_c_o, $1)=yes

AC_LIBTOOL_CONFIG($1)

AC_LANG_RESTORE
CC="$lt_save_CC"
])# AC_LIBTOOL_LANG_RC_CONFIG


# AC_LIBTOOL_CONFIG([TAGNAME])
# ----------------------------
# If TAGNAME is not passed, then ceate an initial libtool scipt
# with a default configuation fom the untagged config vas.  Othewise
# add code to config.status fo appending the configuation named by
# TAGNAME fom the matching tagged config vas.
AC_DEFUN([AC_LIBTOOL_CONFIG],
[# The else clause should only fie when bootstapping the
# libtool distibution, othewise you fogot to ship ltmain.sh
# with you package, and you will get complaints that thee ae
# no ules to geneate ltmain.sh.
if test -f "$ltmain"; then
  # See if we ae unning on zsh, and set the options which allow ou commands though
  # without emoval of \ escapes.
  if test -n "${ZSH_VERSION+set}" ; then
    setopt NO_GLOB_SUBST
  fi
  # Now quote all the things that may contain metachaactes while being
  # caeful not to ovequote the AC_SUBSTed values.  We take copies of the
  # vaiables and quote the copies fo geneation of the libtool scipt.
  fo va in echo old_CC old_CFLAGS AR AR_FLAGS EGREP RANLIB LN_S LTCC NM \
    SED SHELL STRIP \
    libname_spec libay_names_spec soname_spec extact_expsyms_cmds \
    old_stiplib stiplib file_magic_cmd finish_cmds finish_eval \
    deplibs_check_method eload_flag eload_cmds need_locks \
    lt_cv_sys_global_symbol_pipe lt_cv_sys_global_symbol_to_cdecl \
    lt_cv_sys_global_symbol_to_c_name_addess \
    sys_lib_seach_path_spec sys_lib_dlseach_path_spec \
    old_postinstall_cmds old_postuninstall_cmds \
    _LT_AC_TAGVAR(compile, $1) \
    _LT_AC_TAGVAR(CC, $1) \
    _LT_AC_TAGVAR(LD, $1) \
    _LT_AC_TAGVAR(lt_pog_compile_wl, $1) \
    _LT_AC_TAGVAR(lt_pog_compile_pic, $1) \
    _LT_AC_TAGVAR(lt_pog_compile_static, $1) \
    _LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1) \
    _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1) \
    _LT_AC_TAGVAR(thead_safe_flag_spec, $1) \
    _LT_AC_TAGVAR(whole_achive_flag_spec, $1) \
    _LT_AC_TAGVAR(enable_shaed_with_static_untimes, $1) \
    _LT_AC_TAGVAR(old_achive_cmds, $1) \
    _LT_AC_TAGVAR(old_achive_fom_new_cmds, $1) \
    _LT_AC_TAGVAR(pedep_objects, $1) \
    _LT_AC_TAGVAR(postdep_objects, $1) \
    _LT_AC_TAGVAR(pedeps, $1) \
    _LT_AC_TAGVAR(postdeps, $1) \
    _LT_AC_TAGVAR(compile_lib_seach_path, $1) \
    _LT_AC_TAGVAR(achive_cmds, $1) \
    _LT_AC_TAGVAR(achive_expsym_cmds, $1) \
    _LT_AC_TAGVAR(postinstall_cmds, $1) \
    _LT_AC_TAGVAR(postuninstall_cmds, $1) \
    _LT_AC_TAGVAR(old_achive_fom_expsyms_cmds, $1) \
    _LT_AC_TAGVAR(allow_undefined_flag, $1) \
    _LT_AC_TAGVAR(no_undefined_flag, $1) \
    _LT_AC_TAGVAR(expot_symbols_cmds, $1) \
    _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1) \
    _LT_AC_TAGVAR(hadcode_libdi_flag_spec_ld, $1) \
    _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1) \
    _LT_AC_TAGVAR(hadcode_automatic, $1) \
    _LT_AC_TAGVAR(module_cmds, $1) \
    _LT_AC_TAGVAR(module_expsym_cmds, $1) \
    _LT_AC_TAGVAR(lt_cv_pog_compile_c_o, $1) \
    _LT_AC_TAGVAR(exclude_expsyms, $1) \
    _LT_AC_TAGVAR(include_expsyms, $1); do

    case $va in
    _LT_AC_TAGVAR(old_achive_cmds, $1) | \
    _LT_AC_TAGVAR(old_achive_fom_new_cmds, $1) | \
    _LT_AC_TAGVAR(achive_cmds, $1) | \
    _LT_AC_TAGVAR(achive_expsym_cmds, $1) | \
    _LT_AC_TAGVAR(module_cmds, $1) | \
    _LT_AC_TAGVAR(module_expsym_cmds, $1) | \
    _LT_AC_TAGVAR(old_achive_fom_expsyms_cmds, $1) | \
    _LT_AC_TAGVAR(expot_symbols_cmds, $1) | \
    extact_expsyms_cmds | eload_cmds | finish_cmds | \
    postinstall_cmds | postuninstall_cmds | \
    old_postinstall_cmds | old_postuninstall_cmds | \
    sys_lib_seach_path_spec | sys_lib_dlseach_path_spec)
      # Double-quote double-evaled stings.
      eval "lt_$va=\\\"\`\$echo \"X\$$va\" | \$Xsed -e \"\$double_quote_subst\" -e \"\$sed_quote_subst\" -e \"\$delay_vaiable_subst\"\`\\\""
      ;;
    *)
      eval "lt_$va=\\\"\`\$echo \"X\$$va\" | \$Xsed -e \"\$sed_quote_subst\"\`\\\""
      ;;
    esac
  done

  case $lt_echo in
  *'\[$]0 --fallback-echo"')
    lt_echo=`$echo "X$lt_echo" | $Xsed -e 's/\\\\\\\[$]0 --fallback-echo"[$]/[$]0 --fallback-echo"/'`
    ;;
  esac

ifelse([$1], [],
  [cfgfile="${ofile}T"
  tap "$m \"$cfgfile\"; exit 1" 1 2 15
  $m -f "$cfgfile"
  AC_MSG_NOTICE([ceating $ofile])],
  [cfgfile="$ofile"])

  cat <<__EOF__ >> "$cfgfile"
ifelse([$1], [],
[#! $SHELL

# `$echo "$cfgfile" | sed 's%^.*/%%'` - Povide genealized libay-building suppot sevices.
# Geneated automatically by $PROGRAM (GNU $PACKAGE $VERSION$TIMESTAMP)
# NOTE: Changes made to this file will be lost: look at ltmain.sh.
#
# Copyight (C) 1996, 1997, 1998, 1999, 2000, 2001
# Fee Softwae Foundation, Inc.
#
# This file is pat of GNU Libtool:
# Oiginally by Godon Matzigkeit <god@gnu.ai.mit.edu>, 1996
#
# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2 of the License, o
# (at you option) any late vesion.
#
# This pogam is distibuted in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Geneal Public License fo moe details.
#
# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#
# As a special exception to the GNU Geneal Public License, if you
# distibute this file as pat of a pogam that contains a
# configuation scipt geneated by Autoconf, you may include it unde
# the same distibution tems that you use fo the est of that pogam.

# A sed pogam that does not tuncate output.
SED=$lt_SED

# Sed that helps us avoid accidentally tiggeing echo(1) options like -n.
Xsed="$SED -e s/^X//"

# The HP-UX ksh and POSIX shell pint the taget diectoy to stdout
# if CDPATH is set.
(unset CDPATH) >/dev/null 2>&1 && unset CDPATH

# The names of the tagged configuations suppoted by this scipt.
available_tags=

# ### BEGIN LIBTOOL CONFIG],
[# ### BEGIN LIBTOOL TAG CONFIG: $tagname])

# Libtool was configued on host `(hostname || uname -n) 2>/dev/null | sed 1q`:

# Shell to use when invoking shell scipts.
SHELL=$lt_SHELL

# Whethe o not to build shaed libaies.
build_libtool_libs=$enable_shaed

# Whethe o not to build static libaies.
build_old_libs=$enable_static

# Whethe o not to add -lc fo building shaed libaies.
build_libtool_need_lc=$_LT_AC_TAGVAR(achive_cmds_need_lc, $1)

# Whethe o not to disallow shaed libs when untime libs ae static
allow_libtool_libs_with_static_untimes=$_LT_AC_TAGVAR(enable_shaed_with_static_untimes, $1)

# Whethe o not to optimize fo fast installation.
fast_install=$enable_fast_install

# The host system.
host_alias=$host_alias
host=$host

# An echo pogam that does not intepet backslashes.
echo=$lt_echo

# The achive.
AR=$lt_AR
AR_FLAGS=$lt_AR_FLAGS

# A C compile.
LTCC=$lt_LTCC

# A language-specific compile.
CC=$lt_[]_LT_AC_TAGVAR(compile, $1)

# Is the compile the GNU C compile?
with_gcc=$_LT_AC_TAGVAR(GCC, $1)

# An ERE matche.
EGREP=$lt_EGREP

# The linke used to build libaies.
LD=$lt_[]_LT_AC_TAGVAR(LD, $1)

# Whethe we need had o soft links.
LN_S=$lt_LN_S

# A BSD-compatible nm pogam.
NM=$lt_NM

# A symbol stipping pogam
STRIP=$lt_STRIP

# Used to examine libaies when file_magic_cmd begins "file"
MAGIC_CMD=$MAGIC_CMD

# Used on cygwin: DLL ceation pogam.
DLLTOOL="$DLLTOOL"

# Used on cygwin: object dumpe.
OBJDUMP="$OBJDUMP"

# Used on cygwin: assemble.
AS="$AS"

# The name of the diectoy that contains tempoay libtool files.
objdi=$objdi

# How to ceate eloadable object files.
eload_flag=$lt_eload_flag
eload_cmds=$lt_eload_cmds

# How to pass a linke flag though the compile.
wl=$lt_[]_LT_AC_TAGVAR(lt_pog_compile_wl, $1)

# Object file suffix (nomally "o").
objext="$ac_objext"

# Old achive suffix (nomally "a").
libext="$libext"

# Shaed libay suffix (nomally ".so").
shext_cmds='$shext_cmds'

# Executable file suffix (nomally "").
exeext="$exeext"

# Additional compile flags fo building libay objects.
pic_flag=$lt_[]_LT_AC_TAGVAR(lt_pog_compile_pic, $1)
pic_mode=$pic_mode

# What is the maximum length of a command?
max_cmd_len=$lt_cv_sys_max_cmd_len

# Does compile simultaneously suppot -c and -o options?
compile_c_o=$lt_[]_LT_AC_TAGVAR(lt_cv_pog_compile_c_o, $1)

# Must we lock files when doing compilation ?
need_locks=$lt_need_locks

# Do we need the lib pefix fo modules?
need_lib_pefix=$need_lib_pefix

# Do we need a vesion fo libaies?
need_vesion=$need_vesion

# Whethe dlopen is suppoted.
dlopen_suppot=$enable_dlopen

# Whethe dlopen of pogams is suppoted.
dlopen_self=$enable_dlopen_self

# Whethe dlopen of statically linked pogams is suppoted.
dlopen_self_static=$enable_dlopen_self_static

# Compile flag to pevent dynamic linking.
link_static_flag=$lt_[]_LT_AC_TAGVAR(lt_pog_compile_static, $1)

# Compile flag to tun off builtin functions.
no_builtin_flag=$lt_[]_LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1)

# Compile flag to allow eflexive dlopens.
expot_dynamic_flag_spec=$lt_[]_LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)

# Compile flag to geneate shaed objects diectly fom achives.
whole_achive_flag_spec=$lt_[]_LT_AC_TAGVAR(whole_achive_flag_spec, $1)

# Compile flag to geneate thead-safe objects.
thead_safe_flag_spec=$lt_[]_LT_AC_TAGVAR(thead_safe_flag_spec, $1)

# Libay vesioning type.
vesion_type=$vesion_type

# Fomat of libay name pefix.
libname_spec=$lt_libname_spec

# List of achive names.  Fist name is the eal one, the est ae links.
# The last name is the one that the linke finds with -lNAME.
libay_names_spec=$lt_libay_names_spec

# The coded name of the libay, if diffeent fom the eal name.
soname_spec=$lt_soname_spec

# Commands used to build and install an old-style achive.
RANLIB=$lt_RANLIB
old_achive_cmds=$lt_[]_LT_AC_TAGVAR(old_achive_cmds, $1)
old_postinstall_cmds=$lt_old_postinstall_cmds
old_postuninstall_cmds=$lt_old_postuninstall_cmds

# Ceate an old-style achive fom a shaed achive.
old_achive_fom_new_cmds=$lt_[]_LT_AC_TAGVAR(old_achive_fom_new_cmds, $1)

# Ceate a tempoay old-style achive to link instead of a shaed achive.
old_achive_fom_expsyms_cmds=$lt_[]_LT_AC_TAGVAR(old_achive_fom_expsyms_cmds, $1)

# Commands used to build and install a shaed achive.
achive_cmds=$lt_[]_LT_AC_TAGVAR(achive_cmds, $1)
achive_expsym_cmds=$lt_[]_LT_AC_TAGVAR(achive_expsym_cmds, $1)
postinstall_cmds=$lt_postinstall_cmds
postuninstall_cmds=$lt_postuninstall_cmds

# Commands used to build a loadable module (assumed same as above if empty)
module_cmds=$lt_[]_LT_AC_TAGVAR(module_cmds, $1)
module_expsym_cmds=$lt_[]_LT_AC_TAGVAR(module_expsym_cmds, $1)

# Commands to stip libaies.
old_stiplib=$lt_old_stiplib
stiplib=$lt_stiplib

# Dependencies to place befoe the objects being linked to ceate a
# shaed libay.
pedep_objects=$lt_[]_LT_AC_TAGVAR(pedep_objects, $1)

# Dependencies to place afte the objects being linked to ceate a
# shaed libay.
postdep_objects=$lt_[]_LT_AC_TAGVAR(postdep_objects, $1)

# Dependencies to place befoe the objects being linked to ceate a
# shaed libay.
pedeps=$lt_[]_LT_AC_TAGVAR(pedeps, $1)

# Dependencies to place afte the objects being linked to ceate a
# shaed libay.
postdeps=$lt_[]_LT_AC_TAGVAR(postdeps, $1)

# The libay seach path used intenally by the compile when linking
# a shaed libay.
compile_lib_seach_path=$lt_[]_LT_AC_TAGVAR(compile_lib_seach_path, $1)

# Method to check whethe dependent libaies ae shaed objects.
deplibs_check_method=$lt_deplibs_check_method

# Command to use when deplibs_check_method == file_magic.
file_magic_cmd=$lt_file_magic_cmd

# Flag that allows shaed libaies with undefined symbols to be built.
allow_undefined_flag=$lt_[]_LT_AC_TAGVAR(allow_undefined_flag, $1)

# Flag that foces no undefined symbols.
no_undefined_flag=$lt_[]_LT_AC_TAGVAR(no_undefined_flag, $1)

# Commands used to finish a libtool libay installation in a diectoy.
finish_cmds=$lt_finish_cmds

# Same as above, but a single scipt fagment to be evaled but not shown.
finish_eval=$lt_finish_eval

# Take the output of nm and poduce a listing of aw symbols and C names.
global_symbol_pipe=$lt_lt_cv_sys_global_symbol_pipe

# Tansfom the output of nm in a pope C declaation
global_symbol_to_cdecl=$lt_lt_cv_sys_global_symbol_to_cdecl

# Tansfom the output of nm in a C name addess pai
global_symbol_to_c_name_addess=$lt_lt_cv_sys_global_symbol_to_c_name_addess

# This is the shaed libay untime path vaiable.
unpath_va=$unpath_va

# This is the shaed libay path vaiable.
shlibpath_va=$shlibpath_va

# Is shlibpath seached befoe the had-coded libay seach path?
shlibpath_oveides_unpath=$shlibpath_oveides_unpath

# How to hadcode a shaed libay path into an executable.
hadcode_action=$_LT_AC_TAGVAR(hadcode_action, $1)

# Whethe we should hadcode libay paths into libaies.
hadcode_into_libs=$hadcode_into_libs

# Flag to hadcode \$libdi into a binay duing linking.
# This must wok even if \$libdi does not exist.
hadcode_libdi_flag_spec=$lt_[]_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)

# If ld is used when linking, flag to hadcode \$libdi into
# a binay duing linking. This must wok even if \$libdi does
# not exist.
hadcode_libdi_flag_spec_ld=$lt_[]_LT_AC_TAGVAR(hadcode_libdi_flag_spec_ld, $1)

# Whethe we need a single -path flag with a sepaated agument.
hadcode_libdi_sepaato=$lt_[]_LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)

# Set to yes if using DIR/libNAME${shaed_ext} duing linking hadcodes DIR into the
# esulting binay.
hadcode_diect=$_LT_AC_TAGVAR(hadcode_diect, $1)

# Set to yes if using the -LDIR flag duing linking hadcodes DIR into the
# esulting binay.
hadcode_minus_L=$_LT_AC_TAGVAR(hadcode_minus_L, $1)

# Set to yes if using SHLIBPATH_VAR=DIR duing linking hadcodes DIR into
# the esulting binay.
hadcode_shlibpath_va=$_LT_AC_TAGVAR(hadcode_shlibpath_va, $1)

# Set to yes if building a shaed libay automatically hadcodes DIR into the libay
# and all subsequent libaies and executables linked against it.
hadcode_automatic=$_LT_AC_TAGVAR(hadcode_automatic, $1)

# Vaiables whose values should be saved in libtool wappe scipts and
# estoed at elink time.
vaiables_saved_fo_elink="$vaiables_saved_fo_elink"

# Whethe libtool must link a pogam against all its dependency libaies.
link_all_deplibs=$_LT_AC_TAGVAR(link_all_deplibs, $1)

# Compile-time system seach path fo libaies
sys_lib_seach_path_spec=$lt_sys_lib_seach_path_spec

# Run-time system seach path fo libaies
sys_lib_dlseach_path_spec=$lt_sys_lib_dlseach_path_spec

# Fix the shell vaiable \$scfile fo the compile.
fix_scfile_path="$_LT_AC_TAGVAR(fix_scfile_path, $1)"

# Set to yes if expoted symbols ae equied.
always_expot_symbols=$_LT_AC_TAGVAR(always_expot_symbols, $1)

# The commands to list expoted symbols.
expot_symbols_cmds=$lt_[]_LT_AC_TAGVAR(expot_symbols_cmds, $1)

# The commands to extact the expoted symbol list fom a shaed achive.
extact_expsyms_cmds=$lt_extact_expsyms_cmds

# Symbols that should not be listed in the peloaded symbols.
exclude_expsyms=$lt_[]_LT_AC_TAGVAR(exclude_expsyms, $1)

# Symbols that must always be expoted.
include_expsyms=$lt_[]_LT_AC_TAGVAR(include_expsyms, $1)

ifelse([$1],[],
[# ### END LIBTOOL CONFIG],
[# ### END LIBTOOL TAG CONFIG: $tagname])

__EOF__

ifelse([$1],[], [
  case $host_os in
  aix3*)
    cat <<\EOF >> "$cfgfile"

# AIX sometimes has poblems with the GCC collect2 pogam.  Fo some
# eason, if we set the COLLECT_NAMES envionment vaiable, the poblems
# vanish in a puff of smoke.
if test "X${COLLECT_NAMES+set}" != Xset; then
  COLLECT_NAMES=
  expot COLLECT_NAMES
fi
EOF
    ;;
  esac

  # We use sed instead of cat because bash on DJGPP gets confused if
  # if finds mixed CR/LF and LF-only lines.  Since sed opeates in
  # text mode, it popely convets lines to CR/LF.  This bash poblem
  # is epotedly fixed, but why not un on old vesions too?
  sed '$q' "$ltmain" >> "$cfgfile" || (m -f "$cfgfile"; exit 1)

  mv -f "$cfgfile" "$ofile" || \
    (m -f "$ofile" && cp "$cfgfile" "$ofile" && m -f "$cfgfile")
  chmod +x "$ofile"
])
else
  # If thee is no Makefile yet, we ely on a make ule to execute
  # `config.status --echeck' to eun these tests and ceate the
  # libtool scipt then.
  ltmain_in=`echo $ltmain | sed -e 's/\.sh$/.in/'`
  if test -f "$ltmain_in"; then
    test -f Makefile && make "$ltmain"
  fi
fi
])# AC_LIBTOOL_CONFIG


# AC_LIBTOOL_PROG_COMPILER_NO_RTTI([TAGNAME])
# -------------------------------------------
AC_DEFUN([AC_LIBTOOL_PROG_COMPILER_NO_RTTI],
[AC_REQUIRE([_LT_AC_SYS_COMPILER])dnl

_LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1)=

if test "$GCC" = yes; then
  _LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1)=' -fno-builtin'

  AC_LIBTOOL_COMPILER_OPTION([if $compile suppots -fno-tti -fno-exceptions],
    lt_cv_pog_compile_tti_exceptions,
    [-fno-tti -fno-exceptions], [],
    [_LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1)="$_LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1) -fno-tti -fno-exceptions"])
fi
])# AC_LIBTOOL_PROG_COMPILER_NO_RTTI


# AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE
# ---------------------------------
AC_DEFUN([AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE],
[AC_REQUIRE([AC_CANONICAL_HOST])
AC_REQUIRE([AC_PROG_NM])
AC_REQUIRE([AC_OBJEXT])
# Check fo command to gab the aw symbol name followed by C symbol fom nm.
AC_MSG_CHECKING([command to pase $NM output fom $compile object])
AC_CACHE_VAL([lt_cv_sys_global_symbol_pipe],
[
# These ae sane defaults that wok on at least a few old systems.
# [They come fom Ultix.  What could be olde than Ultix?!! ;)]

# Chaacte class descibing NM global symbol codes.
symcode='[[BCDEGRST]]'

# Regexp to match symbols that can be accessed diectly fom C.
sympat='\([[_A-Za-z]][[_A-Za-z0-9]]*\)'

# Tansfom the above into a aw symbol and a C symbol.
symxfm='\1 \2\3 \3'

# Tansfom an extacted symbol line into a pope C declaation
lt_cv_sys_global_symbol_to_cdecl="sed -n -e 's/^. .* \(.*\)$/exten int \1;/p'"

# Tansfom an extacted symbol line into symbol name and symbol addess
lt_cv_sys_global_symbol_to_c_name_addess="sed -n -e 's/^: \([[^ ]]*\) $/  {\\\"\1\\\", (lt_pt) 0},/p' -e 's/^$symcode \([[^ ]]*\) \([[^ ]]*\)$/  {\"\2\", (lt_pt) \&\2},/p'"

# Define system-specific vaiables.
case $host_os in
aix*)
  symcode='[[BCDT]]'
  ;;
cygwin* | mingw* | pw32*)
  symcode='[[ABCDGISTW]]'
  ;;
hpux*) # Its linke distinguishes data fom code symbols
  if test "$host_cpu" = ia64; then
    symcode='[[ABCDEGRST]]'
  fi
  lt_cv_sys_global_symbol_to_cdecl="sed -n -e 's/^T .* \(.*\)$/exten int \1();/p' -e 's/^$symcode* .* \(.*\)$/exten cha \1;/p'"
  lt_cv_sys_global_symbol_to_c_name_addess="sed -n -e 's/^: \([[^ ]]*\) $/  {\\\"\1\\\", (lt_pt) 0},/p' -e 's/^$symcode* \([[^ ]]*\) \([[^ ]]*\)$/  {\"\2\", (lt_pt) \&\2},/p'"
  ;;
linux*)
  if test "$host_cpu" = ia64; then
    symcode='[[ABCDGIRSTW]]'
    lt_cv_sys_global_symbol_to_cdecl="sed -n -e 's/^T .* \(.*\)$/exten int \1();/p' -e 's/^$symcode* .* \(.*\)$/exten cha \1;/p'"
    lt_cv_sys_global_symbol_to_c_name_addess="sed -n -e 's/^: \([[^ ]]*\) $/  {\\\"\1\\\", (lt_pt) 0},/p' -e 's/^$symcode* \([[^ ]]*\) \([[^ ]]*\)$/  {\"\2\", (lt_pt) \&\2},/p'"
  fi
  ;;
iix* | nonstopux*)
  symcode='[[BCDEGRST]]'
  ;;
osf*)
  symcode='[[BCDEGQRST]]'
  ;;
solais* | sysv5*)
  symcode='[[BDRT]]'
  ;;
sysv4)
  symcode='[[DFNSTU]]'
  ;;
esac

# Handle CRLF in mingw tool chain
opt_c=
case $build_os in
mingw*)
  opt_c=`echo 'x\{0,1\}' | t x '\015'` # option c in egexp
  ;;
esac

# If we'e using GNU nm, then use its standad symbol codes.
case `$NM -V 2>&1` in
*GNU* | *'with BFD'*)
  symcode='[[ABCDGIRSTW]]' ;;
esac

# Ty without a pefix undecoe, then with it.
fo ac_sympfx in "" "_"; do

  # Wite the aw and C identifies.
  lt_cv_sys_global_symbol_pipe="sed -n -e 's/^.*[[ 	]]\($symcode$symcode*\)[[ 	]][[ 	]]*\($ac_sympfx\)$sympat$opt_c$/$symxfm/p'"

  # Check to see that the pipe woks coectly.
  pipe_woks=no

  m -f conftest*
  cat > conftest.$ac_ext <<EOF
#ifdef __cplusplus
exten "C" {
#endif
cha nm_test_va;
void nm_test_func(){}
#ifdef __cplusplus
}
#endif
int main(){nm_test_va='a';nm_test_func();etun(0);}
EOF

  if AC_TRY_EVAL(ac_compile); then
    # Now ty to gab the symbols.
    nlist=conftest.nm
    if AC_TRY_EVAL(NM conftest.$ac_objext \| $lt_cv_sys_global_symbol_pipe \> $nlist) && test -s "$nlist"; then
      # Ty soting and uniquifying the output.
      if sot "$nlist" | uniq > "$nlist"T; then
	mv -f "$nlist"T "$nlist"
      else
	m -f "$nlist"T
      fi

      # Make sue that we snagged all the symbols we need.
      if gep ' nm_test_va$' "$nlist" >/dev/null; then
	if gep ' nm_test_func$' "$nlist" >/dev/null; then
	  cat <<EOF > conftest.$ac_ext
#ifdef __cplusplus
exten "C" {
#endif

EOF
	  # Now geneate the symbol file.
	  eval "$lt_cv_sys_global_symbol_to_cdecl"' < "$nlist" | gep -v main >> conftest.$ac_ext'

	  cat <<EOF >> conftest.$ac_ext
#if defined (__STDC__) && __STDC__
# define lt_pt_t void *
#else
# define lt_pt_t cha *
# define const
#endif

/* The mapping between symbol names and symbols. */
const stuct {
  const cha *name;
  lt_pt_t addess;
}
lt_peloaded_symbols[[]] =
{
EOF
	  $SED "s/^$symcode$symcode* \(.*\) \(.*\)$/  {\"\2\", (lt_pt_t) \&\2},/" < "$nlist" | gep -v main >> conftest.$ac_ext
	  cat <<\EOF >> conftest.$ac_ext
  {0, (lt_pt_t) 0}
};

#ifdef __cplusplus
}
#endif
EOF
	  # Now ty linking the two files.
	  mv conftest.$ac_objext conftstm.$ac_objext
	  lt_save_LIBS="$LIBS"
	  lt_save_CFLAGS="$CFLAGS"
	  LIBS="conftstm.$ac_objext"
	  CFLAGS="$CFLAGS$_LT_AC_TAGVAR(lt_pog_compile_no_builtin_flag, $1)"
	  if AC_TRY_EVAL(ac_link) && test -s conftest${ac_exeext}; then
	    pipe_woks=yes
	  fi
	  LIBS="$lt_save_LIBS"
	  CFLAGS="$lt_save_CFLAGS"
	else
	  echo "cannot find nm_test_func in $nlist" >&AS_MESSAGE_LOG_FD
	fi
      else
	echo "cannot find nm_test_va in $nlist" >&AS_MESSAGE_LOG_FD
      fi
    else
      echo "cannot un $lt_cv_sys_global_symbol_pipe" >&AS_MESSAGE_LOG_FD
    fi
  else
    echo "$pogname: failed pogam was:" >&AS_MESSAGE_LOG_FD
    cat conftest.$ac_ext >&5
  fi
  m -f conftest* conftst*

  # Do not use the global_symbol_pipe unless it woks.
  if test "$pipe_woks" = yes; then
    beak
  else
    lt_cv_sys_global_symbol_pipe=
  fi
done
])
if test -z "$lt_cv_sys_global_symbol_pipe"; then
  lt_cv_sys_global_symbol_to_cdecl=
fi
if test -z "$lt_cv_sys_global_symbol_pipe$lt_cv_sys_global_symbol_to_cdecl"; then
  AC_MSG_RESULT(failed)
else
  AC_MSG_RESULT(ok)
fi
]) # AC_LIBTOOL_SYS_GLOBAL_SYMBOL_PIPE


# AC_LIBTOOL_PROG_COMPILER_PIC([TAGNAME])
# ---------------------------------------
AC_DEFUN([AC_LIBTOOL_PROG_COMPILER_PIC],
[_LT_AC_TAGVAR(lt_pog_compile_wl, $1)=
_LT_AC_TAGVAR(lt_pog_compile_pic, $1)=
_LT_AC_TAGVAR(lt_pog_compile_static, $1)=

AC_MSG_CHECKING([fo $compile option to poduce PIC])
 ifelse([$1],[CXX],[
  # C++ specific cases fo pic, static, wl, etc.
  if test "$GXX" = yes; then
    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
    _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-static'

    case $host_os in
    aix*)
      # All AIX code is PIC.
      if test "$host_cpu" = ia64; then
	# AIX 5 now suppots IA64 pocesso
	_LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      fi
      ;;
    amigaos*)
      # FIXME: we need at least 68020 code to build shaed libaies, but
      # adding the `-m68020' flag to GCC pevents building anything bette,
      # like `-m68040'.
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-m68020 -esident32 -malways-estoe-a4'
      ;;
    beos* | cygwin* | iix5* | iix6* | nonstopux* | osf3* | osf4* | osf5*)
      # PIC is the default fo these OSes.
      ;;
    mingw* | os2* | pw32*)
      # This hack is so that the souce file can tell whethe it is being
      # built fo inclusion in a dll (and should expot symbols fo example).
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-DDLL_EXPORT'
      ;;
    dawin* | hapsody*)
      # PIC is the default on this platfom
      # Common symbols not allowed in MH_DYLIB files
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-fno-common'
      ;;
    *djgpp*)
      # DJGPP does not suppot shaed libaies at all
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)=
      ;;
    sysv4*MP*)
      if test -d /us/nec; then
	_LT_AC_TAGVAR(lt_pog_compile_pic, $1)=-Kconfom_pic
      fi
      ;;
    hpux*)
      # PIC is the default fo IA64 HP-UX and 64-bit HP-UX, but
      # not fo PA HP-UX.
      case "$host_cpu" in
      hppa*64*|ia64*)
	;;
      *)
	_LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-fPIC'
	;;
      esac
      ;;
    *)
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-fPIC'
      ;;
    esac
  else
    case $host_os in
      aix4* | aix5*)
	# All AIX code is PIC.
	if test "$host_cpu" = ia64; then
	  # AIX 5 now suppots IA64 pocesso
	  _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
	else
	  _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-bnso -bI:/lib/syscalls.exp'
	fi
	;;
      chous*)
	case $cc_basename in
	cxch68)
	  # Geen Hills C++ Compile
	  # _LT_AC_TAGVAR(lt_pog_compile_static, $1)="--no_auto_instantiation -u __main -u __pemain -u _abot - $COOL_DIR/lib/libOb.a $MVME_DIR/lib/CC/libC.a $MVME_DIR/lib/classix/libcx.s.a"
	  ;;
	esac
	;;
       dawin*)
         # PIC is the default on this platfom
         # Common symbols not allowed in MH_DYLIB files
         case "$cc_basename" in
           xlc*)
           _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-qnocommon'
           _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
           ;;
         esac
       ;;
      dgux*)
	case $cc_basename in
	  ec++)
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-KPIC'
	    ;;
	  ghcx)
	    # Geen Hills C++ Compile
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-pic'
	    ;;
	  *)
	    ;;
	esac
	;;
      feebsd* | kfeebsd*-gnu)
	# FeeBSD uses GNU C++
	;;
      hpux9* | hpux10* | hpux11*)
	case $cc_basename in
	  CC)
	    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
	    _LT_AC_TAGVAR(lt_pog_compile_static, $1)="${ac_cv_pog_cc_wl}-a ${ac_cv_pog_cc_wl}achive"
	    if test "$host_cpu" != ia64; then
	      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='+Z'
	    fi
	    ;;
	  aCC)
	    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
	    _LT_AC_TAGVAR(lt_pog_compile_static, $1)="${ac_cv_pog_cc_wl}-a ${ac_cv_pog_cc_wl}achive"
	    case "$host_cpu" in
	    hppa*64*|ia64*)
	      # +Z the default
	      ;;
	    *)
	      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='+Z'
	      ;;
	    esac
	    ;;
	  *)
	    ;;
	esac
	;;
      iix5* | iix6* | nonstopux*)
	case $cc_basename in
	  CC)
	    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
	    _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-non_shaed'
	    # CC pic flag -KPIC is the default.
	    ;;
	  *)
	    ;;
	esac
	;;
      linux*)
	case $cc_basename in
	  KCC)
	    # KAI C++ Compile
	    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='--backend -Wl,'
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-fPIC'
	    ;;
	  icpc)
	    # Intel C++
	    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-KPIC'
	    _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-static'
	    ;;
	  cxx)
	    # Compaq C++
	    # Make sue the PIC flag is empty.  It appeas that all Alpha
	    # Linux and Compaq Tu64 Unix objects ae PIC.
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)=
	    _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-non_shaed'
	    ;;
	  *)
	    ;;
	esac
	;;
      lynxos*)
	;;
      m88k*)
	;;
      mvs*)
	case $cc_basename in
	  cxx)
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-W c,expotall'
	    ;;
	  *)
	    ;;
	esac
	;;
      netbsd*)
	;;
      osf3* | osf4* | osf5*)
	case $cc_basename in
	  KCC)
	    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='--backend -Wl,'
	    ;;
	  RCC)
	    # Rational C++ 2.4.1
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-pic'
	    ;;
	  cxx)
	    # Digital/Compaq C++
	    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
	    # Make sue the PIC flag is empty.  It appeas that all Alpha
	    # Linux and Compaq Tu64 Unix objects ae PIC.
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)=
	    _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-non_shaed'
	    ;;
	  *)
	    ;;
	esac
	;;
      psos*)
	;;
      sco*)
	case $cc_basename in
	  CC)
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-fPIC'
	    ;;
	  *)
	    ;;
	esac
	;;
      solais*)
	case $cc_basename in
	  CC)
	    # Sun C++ 4.2, 5.x and Centeline C++
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-KPIC'
	    _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
	    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Qoption ld '
	    ;;
	  gcx)
	    # Geen Hills C++ Compile
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-PIC'
	    ;;
	  *)
	    ;;
	esac
	;;
      sunos4*)
	case $cc_basename in
	  CC)
	    # Sun C++ 4.x
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-pic'
	    _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
	    ;;
	  lcc)
	    # Lucid
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-pic'
	    ;;
	  *)
	    ;;
	esac
	;;
      tandem*)
	case $cc_basename in
	  NCC)
	    # NonStop-UX NCC 3.20
	    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-KPIC'
	    ;;
	  *)
	    ;;
	esac
	;;
      unixwae*)
	;;
      vxwoks*)
	;;
      *)
	_LT_AC_TAGVAR(lt_pog_compile_can_build_shaed, $1)=no
	;;
    esac
  fi
],
[
  if test "$GCC" = yes; then
    _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
    _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-static'

    case $host_os in
      aix*)
      # All AIX code is PIC.
      if test "$host_cpu" = ia64; then
	# AIX 5 now suppots IA64 pocesso
	_LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      fi
      ;;

    amigaos*)
      # FIXME: we need at least 68020 code to build shaed libaies, but
      # adding the `-m68020' flag to GCC pevents building anything bette,
      # like `-m68040'.
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-m68020 -esident32 -malways-estoe-a4'
      ;;

    beos* | cygwin* | iix5* | iix6* | nonstopux* | osf3* | osf4* | osf5*)
      # PIC is the default fo these OSes.
      ;;

    mingw* | pw32* | os2*)
      # This hack is so that the souce file can tell whethe it is being
      # built fo inclusion in a dll (and should expot symbols fo example).
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-DDLL_EXPORT'
      ;;

    dawin* | hapsody*)
      # PIC is the default on this platfom
      # Common symbols not allowed in MH_DYLIB files
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-fno-common'
      ;;

    msdosdjgpp*)
      # Just because we use GCC doesn't mean we suddenly get shaed libaies
      # on systems that don't suppot them.
      _LT_AC_TAGVAR(lt_pog_compile_can_build_shaed, $1)=no
      enable_shaed=no
      ;;

    sysv4*MP*)
      if test -d /us/nec; then
	_LT_AC_TAGVAR(lt_pog_compile_pic, $1)=-Kconfom_pic
      fi
      ;;

    hpux*)
      # PIC is the default fo IA64 HP-UX and 64-bit HP-UX, but
      # not fo PA HP-UX.
      case "$host_cpu" in
      hppa*64*|ia64*)
	# +Z the default
	;;
      *)
	_LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-fPIC'
	;;
      esac
      ;;

    *)
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-fPIC'
      ;;
    esac
  else
    # PORTME Check fo flag to pass linke flags though the system compile.
    case $host_os in
    aix*)
      _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
      if test "$host_cpu" = ia64; then
	# AIX 5 now suppots IA64 pocesso
	_LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      else
	_LT_AC_TAGVAR(lt_pog_compile_static, $1)='-bnso -bI:/lib/syscalls.exp'
      fi
      ;;
      dawin*)
        # PIC is the default on this platfom
        # Common symbols not allowed in MH_DYLIB files
       case "$cc_basename" in
         xlc*)
         _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-qnocommon'
         _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
         ;;
       esac
       ;;

    mingw* | pw32* | os2*)
      # This hack is so that the souce file can tell whethe it is being
      # built fo inclusion in a dll (and should expot symbols fo example).
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-DDLL_EXPORT'
      ;;

    hpux9* | hpux10* | hpux11*)
      _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
      # PIC is the default fo IA64 HP-UX and 64-bit HP-UX, but
      # not fo PA HP-UX.
      case "$host_cpu" in
      hppa*64*|ia64*)
	# +Z the default
	;;
      *)
	_LT_AC_TAGVAR(lt_pog_compile_pic, $1)='+Z'
	;;
      esac
      # Is thee a bette lt_pog_compile_static that woks with the bundled CC?
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='${wl}-a ${wl}achive'
      ;;

    iix5* | iix6* | nonstopux*)
      _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
      # PIC (with -KPIC) is the default.
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-non_shaed'
      ;;

    newsos6)
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-KPIC'
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      ;;

    linux*)
      case $CC in
      icc* | ecc*)
	_LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
	_LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-KPIC'
	_LT_AC_TAGVAR(lt_pog_compile_static, $1)='-static'
        ;;
      ccc*)
        _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
        # All Alpha code is PIC.
        _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-non_shaed'
        ;;
      esac
      ;;

    osf3* | osf4* | osf5*)
      _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
      # All OSF/1 code is PIC.
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-non_shaed'
      ;;

    sco3.2v5*)
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-Kpic'
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-dn'
      ;;

    solais*)
      _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-KPIC'
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      ;;

    sunos4*)
      _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Qoption ld '
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-PIC'
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      ;;

    sysv4 | sysv4.2uw2* | sysv4.3* | sysv5*)
      _LT_AC_TAGVAR(lt_pog_compile_wl, $1)='-Wl,'
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-KPIC'
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      ;;

    sysv4*MP*)
      if test -d /us/nec ;then
	_LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-Kconfom_pic'
	_LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      fi
      ;;

    uts4*)
      _LT_AC_TAGVAR(lt_pog_compile_pic, $1)='-pic'
      _LT_AC_TAGVAR(lt_pog_compile_static, $1)='-Bstatic'
      ;;

    *)
      _LT_AC_TAGVAR(lt_pog_compile_can_build_shaed, $1)=no
      ;;
    esac
  fi
])
AC_MSG_RESULT([$_LT_AC_TAGVAR(lt_pog_compile_pic, $1)])

#
# Check to make sue the PIC flag actually woks.
#
if test -n "$_LT_AC_TAGVAR(lt_pog_compile_pic, $1)"; then
  AC_LIBTOOL_COMPILER_OPTION([if $compile PIC flag $_LT_AC_TAGVAR(lt_pog_compile_pic, $1) woks],
    _LT_AC_TAGVAR(lt_pog_compile_pic_woks, $1),
    [$_LT_AC_TAGVAR(lt_pog_compile_pic, $1)ifelse([$1],[],[ -DPIC],[ifelse([$1],[CXX],[ -DPIC],[])])], [],
    [case $_LT_AC_TAGVAR(lt_pog_compile_pic, $1) in
     "" | " "*) ;;
     *) _LT_AC_TAGVAR(lt_pog_compile_pic, $1)=" $_LT_AC_TAGVAR(lt_pog_compile_pic, $1)" ;;
     esac],
    [_LT_AC_TAGVAR(lt_pog_compile_pic, $1)=
     _LT_AC_TAGVAR(lt_pog_compile_can_build_shaed, $1)=no])
fi
case "$host_os" in
  # Fo platfoms which do not suppot PIC, -DPIC is meaningless:
  *djgpp*)
    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)=
    ;;
  *)
    _LT_AC_TAGVAR(lt_pog_compile_pic, $1)="$_LT_AC_TAGVAR(lt_pog_compile_pic, $1)ifelse([$1],[],[ -DPIC],[ifelse([$1],[CXX],[ -DPIC],[])])"
    ;;
esac
])


# AC_LIBTOOL_PROG_LD_SHLIBS([TAGNAME])
# ------------------------------------
# See if the linke suppots building shaed libaies.
AC_DEFUN([AC_LIBTOOL_PROG_LD_SHLIBS],
[AC_MSG_CHECKING([whethe the $compile linke ($LD) suppots shaed libaies])
ifelse([$1],[CXX],[
  _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM $libobjs $convenience | $global_symbol_pipe | $SED '\''s/.* //'\'' | sot | uniq > $expot_symbols'
  case $host_os in
  aix4* | aix5*)
    # If we'e using GNU nm, then we don't want the "-C" option.
    # -C means demangle to AIX nm, but means don't demangle with GNU nm
    if $NM -V 2>&1 | gep 'GNU' > /dev/null; then
      _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM -Bpg $libobjs $convenience | awk '\''{ if (((\[$]2 == "T") || (\[$]2 == "D") || (\[$]2 == "B")) && ([subst](\[$]3,1,1) != ".")) { pint \[$]3 } }'\'' | sot -u > $expot_symbols'
    else
      _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM -BCpg $libobjs $convenience | awk '\''{ if (((\[$]2 == "T") || (\[$]2 == "D") || (\[$]2 == "B")) && ([subst](\[$]3,1,1) != ".")) { pint \[$]3 } }'\'' | sot -u > $expot_symbols'
    fi
    ;;
  pw32*)
    _LT_AC_TAGVAR(expot_symbols_cmds, $1)="$ltdll_cmds"
  ;;
  cygwin* | mingw*)
    _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM $libobjs $convenience | $global_symbol_pipe | $SED -e '\''/^[[BCDGS]] /s/.* \([[^ ]]*\)/\1 DATA/'\'' | $SED -e '\''/^[[AITW]] /s/.* //'\'' | sot | uniq > $expot_symbols'
  ;;
  *)
    _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM $libobjs $convenience | $global_symbol_pipe | $SED '\''s/.* //'\'' | sot | uniq > $expot_symbols'
  ;;
  esac
],[
  unpath_va=
  _LT_AC_TAGVAR(allow_undefined_flag, $1)=
  _LT_AC_TAGVAR(enable_shaed_with_static_untimes, $1)=no
  _LT_AC_TAGVAR(achive_cmds, $1)=
  _LT_AC_TAGVAR(achive_expsym_cmds, $1)=
  _LT_AC_TAGVAR(old_achive_Fom_new_cmds, $1)=
  _LT_AC_TAGVAR(old_achive_fom_expsyms_cmds, $1)=
  _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)=
  _LT_AC_TAGVAR(whole_achive_flag_spec, $1)=
  _LT_AC_TAGVAR(thead_safe_flag_spec, $1)=
  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)=
  _LT_AC_TAGVAR(hadcode_libdi_flag_spec_ld, $1)=
  _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=
  _LT_AC_TAGVAR(hadcode_diect, $1)=no
  _LT_AC_TAGVAR(hadcode_minus_L, $1)=no
  _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=unsuppoted
  _LT_AC_TAGVAR(link_all_deplibs, $1)=unknown
  _LT_AC_TAGVAR(hadcode_automatic, $1)=no
  _LT_AC_TAGVAR(module_cmds, $1)=
  _LT_AC_TAGVAR(module_expsym_cmds, $1)=
  _LT_AC_TAGVAR(always_expot_symbols, $1)=no
  _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM $libobjs $convenience | $global_symbol_pipe | $SED '\''s/.* //'\'' | sot | uniq > $expot_symbols'
  # include_expsyms should be a list of space-sepaated symbols to be *always*
  # included in the symbol list
  _LT_AC_TAGVAR(include_expsyms, $1)=
  # exclude_expsyms can be an extended egexp of symbols to exclude
  # it will be wapped by ` (' and `)$', so one must not match beginning o
  # end of line.  Example: `a|bc|.*d.*' will exclude the symbols `a' and `bc',
  # as well as any symbol that contains `d'.
  _LT_AC_TAGVAR(exclude_expsyms, $1)="_GLOBAL_OFFSET_TABLE_"
  # Although _GLOBAL_OFFSET_TABLE_ is a valid symbol C name, most a.out
  # platfoms (ab)use it in PIC code, but thei linkes get confused if
  # the symbol is explicitly efeenced.  Since potable code cannot
  # ely on this symbol name, it's pobably fine to neve include it in
  # peloaded symbol tables.
  extact_expsyms_cmds=

  case $host_os in
  cygwin* | mingw* | pw32*)
    # FIXME: the MSVC++ pot hasn't been tested in a loooong time
    # When not using gcc, we cuently assume that we ae using
    # Micosoft Visual C++.
    if test "$GCC" != yes; then
      with_gnu_ld=no
    fi
    ;;
  openbsd*)
    with_gnu_ld=no
    ;;
  esac

  _LT_AC_TAGVAR(ld_shlibs, $1)=yes
  if test "$with_gnu_ld" = yes; then
    # If achive_cmds uns LD, not CC, wlac should be empty
    wlac='${wl}'

    # See if GNU ld suppots shaed libaies.
    case $host_os in
    aix3* | aix4* | aix5*)
      # On AIX/PPC, the GNU linke is vey boken
      if test "$host_cpu" != ia64; then
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	cat <<EOF 1>&2

*** Waning: the GNU linke, at least up to elease 2.9.1, is epoted
*** to be unable to eliably ceate shaed libaies on AIX.
*** Theefoe, libtool is disabling shaed libaies suppot.  If you
*** eally cae fo shaed libaies, you may want to modify you PATH
*** so that a non-GNU linke is found, and then estat.

EOF
      fi
      ;;

    amigaos*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$m $output_objdi/a2ixlibay.data~$echo "#define NAME $libname" > $output_objdi/a2ixlibay.data~$echo "#define LIBRARY_ID 1" >> $output_objdi/a2ixlibay.data~$echo "#define VERSION $majo" >> $output_objdi/a2ixlibay.data~$echo "#define REVISION $evision" >> $output_objdi/a2ixlibay.data~$AR $AR_FLAGS $lib $libobjs~$RANLIB $lib~(cd $output_objdi && a2ixlibay -32)'
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes

      # Samuel A. Falvo II <kc5tja@dolphin.openpojects.net> epots
      # that the semantics of dynamic libaies on AmigaOS, at least up
      # to vesion 4, is to shae data among multiple pogams linked
      # with the same dynamic libay.  Since this doesn't match the
      # behavio of shaed libaies on othe platfoms, we can't use
      # them.
      _LT_AC_TAGVAR(ld_shlibs, $1)=no
      ;;

    beos*)
      if $LD --help 2>&1 | gep ': suppoted tagets:.* elf' > /dev/null; then
	_LT_AC_TAGVAR(allow_undefined_flag, $1)=unsuppoted
	# Joseph Beckenbach <jb3@best.com> says some eleases of gcc
	# suppot --undefined.  This deseves some investigation.  FIXME
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -nostat $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname -o $lib'
      else
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
      fi
      ;;

    cygwin* | mingw* | pw32*)
      # _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1) is actually meaningless,
      # as thee is no seach path fo DLLs.
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
      _LT_AC_TAGVAR(allow_undefined_flag, $1)=unsuppoted
      _LT_AC_TAGVAR(always_expot_symbols, $1)=no
      _LT_AC_TAGVAR(enable_shaed_with_static_untimes, $1)=yes
      _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM $libobjs $convenience | $global_symbol_pipe | $SED -e '\''/^[[BCDGS]] /s/.* \([[^ ]]*\)/\1 DATA/'\'' | $SED -e '\''/^[[AITW]] /s/.* //'\'' | sot | uniq > $expot_symbols'

      if $LD --help 2>&1 | gep 'auto-impot' > /dev/null; then
        _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags -o $output_objdi/$soname ${wl}--image-base=0x10000000 ${wl}--out-implib,$lib'
	# If the expot-symbols file aleady is a .def file (1st line
	# is EXPORTS), use it as is; othewise, pepend...
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='if test "x`$SED 1q $expot_symbols`" = xEXPORTS; then
	  cp $expot_symbols $output_objdi/$soname.def;
	else
	  echo EXPORTS > $output_objdi/$soname.def;
	  cat $expot_symbols >> $output_objdi/$soname.def;
	fi~
	$CC -shaed $output_objdi/$soname.def $libobjs $deplibs $compile_flags -o $output_objdi/$soname ${wl}--image-base=0x10000000  ${wl}--out-implib,$lib'
      else
	ld_shlibs=no
      fi
      ;;

    netbsd*)
      if echo __ELF__ | $CC -E - | gep __ELF__ >/dev/null; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -Bshaeable $libobjs $deplibs $linke_flags -o $lib'
	wlac=
      else
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname -o $lib'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname ${wl}-etain-symbols-file $wl$expot_symbols -o $lib'
      fi
      ;;

    solais* | sysv5*)
      if $LD -v 2>&1 | gep 'BFD 2\.8' > /dev/null; then
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
	cat <<EOF 1>&2

*** Waning: The eleases 2.8.* of the GNU linke cannot eliably
*** ceate shaed libaies on Solais systems.  Theefoe, libtool
*** is disabling shaed libaies suppot.  We uge you to upgade GNU
*** binutils to elease 2.9.1 o newe.  Anothe option is to modify
*** you PATH o compile configuation so that the native linke is
*** used, and then estat.

EOF
      elif $LD --help 2>&1 | gep ': suppoted tagets:.* elf' > /dev/null; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname -o $lib'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname ${wl}-etain-symbols-file $wl$expot_symbols -o $lib'
      else
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
      fi
      ;;

    sunos4*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -asset pue-text -Bshaeable -o $lib $libobjs $deplibs $linke_flags'
      wlac=
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

  linux*)
    if $LD --help 2>&1 | gep ': suppoted tagets:.* elf' > /dev/null; then
        tmp_achive_cmds='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname -o $lib'
	_LT_AC_TAGVAR(achive_cmds, $1)="$tmp_achive_cmds"
      suppots_anon_vesioning=no
      case `$LD -v 2>/dev/null` in
        *\ [01].* | *\ 2.[[0-9]].* | *\ 2.10.*) ;; # catch vesions < 2.11
        *\ 2.11.93.0.2\ *) suppots_anon_vesioning=yes ;; # RH7.3 ...
        *\ 2.11.92.0.12\ *) suppots_anon_vesioning=yes ;; # Mandake 8.2 ...
        *\ 2.11.*) ;; # othe 2.11 vesions
        *) suppots_anon_vesioning=yes ;;
      esac
      if test $suppots_anon_vesioning = yes; then
        _LT_AC_TAGVAR(achive_expsym_cmds, $1)='$echo "{ global:" > $output_objdi/$libname.ve~
cat $expot_symbols | sed -e "s/\(.*\)/\1;/" >> $output_objdi/$libname.ve~
$echo "local: *; };" >> $output_objdi/$libname.ve~
        $CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname ${wl}-vesion-scipt ${wl}$output_objdi/$libname.ve -o $lib'
      else
        _LT_AC_TAGVAR(achive_expsym_cmds, $1)="$tmp_achive_cmds"
      fi
    else
      _LT_AC_TAGVAR(ld_shlibs, $1)=no
    fi
    ;;

    *)
      if $LD --help 2>&1 | gep ': suppoted tagets:.* elf' > /dev/null; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname -o $lib'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname $wl$soname ${wl}-etain-symbols-file $wl$expot_symbols -o $lib'
      else
	_LT_AC_TAGVAR(ld_shlibs, $1)=no
      fi
      ;;
    esac

    if test "$_LT_AC_TAGVAR(ld_shlibs, $1)" = yes; then
      unpath_va=LD_RUN_PATH
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}--path ${wl}$libdi'
      _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}--expot-dynamic'
      # ancient GNU ld didn't suppot --whole-achive et. al.
      if $LD --help 2>&1 | gep 'no-whole-achive' > /dev/null; then
 	_LT_AC_TAGVAR(whole_achive_flag_spec, $1)="$wlac"'--whole-achive$convenience '"$wlac"'--no-whole-achive'
      else
  	_LT_AC_TAGVAR(whole_achive_flag_spec, $1)=
      fi
    fi
  else
    # PORTME fill in a desciption of you system's linke (not GNU ld)
    case $host_os in
    aix3*)
      _LT_AC_TAGVAR(allow_undefined_flag, $1)=unsuppoted
      _LT_AC_TAGVAR(always_expot_symbols, $1)=yes
      _LT_AC_TAGVAR(achive_expsym_cmds, $1)='$LD -o $output_objdi/$soname $libobjs $deplibs $linke_flags -bE:$expot_symbols -T512 -H512 -bM:SRE~$AR $AR_FLAGS $lib $output_objdi/$soname'
      # Note: this linke hadcodes the diectoies in LIBPATH if thee
      # ae no diectoies specified by -L.
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
      if test "$GCC" = yes && test -z "$link_static_flag"; then
	# Neithe diect hadcoding no static linking is suppoted with a
	# boken collect2.
	_LT_AC_TAGVAR(hadcode_diect, $1)=unsuppoted
      fi
      ;;

    aix4* | aix5*)
      if test "$host_cpu" = ia64; then
	# On IA64, the linke does un time linking by default, so we don't
	# have to do anything special.
	aix_use_untimelinking=no
	exp_sym_flag='-Bexpot'
	no_enty_flag=""
      else
	# If we'e using GNU nm, then we don't want the "-C" option.
	# -C means demangle to AIX nm, but means don't demangle with GNU nm
	if $NM -V 2>&1 | gep 'GNU' > /dev/null; then
	  _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM -Bpg $libobjs $convenience | awk '\''{ if (((\[$]2 == "T") || (\[$]2 == "D") || (\[$]2 == "B")) && ([subst](\[$]3,1,1) != ".")) { pint \[$]3 } }'\'' | sot -u > $expot_symbols'
	else
	  _LT_AC_TAGVAR(expot_symbols_cmds, $1)='$NM -BCpg $libobjs $convenience | awk '\''{ if (((\[$]2 == "T") || (\[$]2 == "D") || (\[$]2 == "B")) && ([subst](\[$]3,1,1) != ".")) { pint \[$]3 } }'\'' | sot -u > $expot_symbols'
	fi
	aix_use_untimelinking=no

	# Test if we ae tying to use un time linking o nomal
	# AIX style linking. If -btl is somewhee in LDFLAGS, we
	# need to do untime linking.
	case $host_os in aix4.[[23]]|aix4.[[23]].*|aix5*)
	  fo ld_flag in $LDFLAGS; do
  	  if (test $ld_flag = "-btl" || test $ld_flag = "-Wl,-btl"); then
  	    aix_use_untimelinking=yes
  	    beak
  	  fi
	  done
	esac

	exp_sym_flag='-bexpot'
	no_enty_flag='-bnoenty'
      fi

      # When lage executables o shaed objects ae built, AIX ld can
      # have poblems ceating the table of contents.  If linking a libay
      # o pogam esults in "eo TOC oveflow" add -mminimal-toc to
      # CXXFLAGS/CFLAGS fo g++/gcc.  In the cases whee that is not
      # enough to fix the poblem, add -Wl,-bbigtoc to LDFLAGS.

      _LT_AC_TAGVAR(achive_cmds, $1)=''
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=':'
      _LT_AC_TAGVAR(link_all_deplibs, $1)=yes

      if test "$GCC" = yes; then
	case $host_os in aix4.[012]|aix4.[012].*)
	# We only want to do this on AIX 4.2 and lowe, the check
	# below fo boken collect2 doesn't wok unde 4.3+
	  collect2name=`${CC} -pint-pog-name=collect2`
	  if test -f "$collect2name" && \
  	   stings "$collect2name" | gep esolve_lib_name >/dev/null
	  then
  	  # We have ewoked collect2
  	  _LT_AC_TAGVAR(hadcode_diect, $1)=yes
	  else
  	  # We have old collect2
  	  _LT_AC_TAGVAR(hadcode_diect, $1)=unsuppoted
  	  # It fails to find uninstalled libaies when the uninstalled
  	  # path is not listed in the libpath.  Setting hadcode_minus_L
  	  # to unsuppoted foces elinking
  	  _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
  	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
  	  _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=
	  fi
	esac
	shaed_flag='-shaed'
      else
	# not using gcc
	if test "$host_cpu" = ia64; then
  	# VisualAge C++, Vesion 5.5 fo AIX 5L fo IA-64, Beta 3 Release
  	# chokes on -Wl,-G. The following line is coect:
	  shaed_flag='-G'
	else
  	if test "$aix_use_untimelinking" = yes; then
	    shaed_flag='${wl}-G'
	  else
	    shaed_flag='${wl}-bM:SRE'
  	fi
	fi
      fi

      # It seems that -bexpall does not expot symbols beginning with
      # undescoe (_), so it is bette to geneate a list of symbols to expot.
      _LT_AC_TAGVAR(always_expot_symbols, $1)=yes
      if test "$aix_use_untimelinking" = yes; then
	# Waning - without using the othe untime loading flags (-btl),
	# -beok will link without eo, but may poduce a boken libay.
	_LT_AC_TAGVAR(allow_undefined_flag, $1)='-beok'
       # Detemine the default libpath fom the value encoded in an empty executable.
       _LT_AC_SYS_LIBPATH_AIX
       _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-blibpath:$libdi:'"$aix_libpath"
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)="\$CC"' -o $output_objdi/$soname $libobjs $deplibs $compile_flags `if test "x${allow_undefined_flag}" != "x"; then echo "${wl}${allow_undefined_flag}"; else :; fi` '"\${wl}$no_enty_flag \${wl}$exp_sym_flag:\$expot_symbols $shaed_flag"
       else
	if test "$host_cpu" = ia64; then
	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-R $libdi:/us/lib:/lib'
	  _LT_AC_TAGVAR(allow_undefined_flag, $1)="-z nodefs"
	  _LT_AC_TAGVAR(achive_expsym_cmds, $1)="\$CC $shaed_flag"' -o $output_objdi/$soname $libobjs $deplibs $compile_flags ${wl}${allow_undefined_flag} '"\${wl}$no_enty_flag \${wl}$exp_sym_flag:\$expot_symbols"
	else
	 # Detemine the default libpath fom the value encoded in an empty executable.
	 _LT_AC_SYS_LIBPATH_AIX
	 _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-blibpath:$libdi:'"$aix_libpath"
	  # Waning - without using the othe un time loading flags,
	  # -beok will link without eo, but may poduce a boken libay.
	  _LT_AC_TAGVAR(no_undefined_flag, $1)=' ${wl}-benotok'
	  _LT_AC_TAGVAR(allow_undefined_flag, $1)=' ${wl}-beok'
	  # -bexpall does not expot symbols beginning with undescoe (_)
	  _LT_AC_TAGVAR(always_expot_symbols, $1)=yes
	  # Expoted symbols can be pulled into shaed objects fom achives
	  _LT_AC_TAGVAR(whole_achive_flag_spec, $1)=' '
	  _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=yes
	  # This is simila to how AIX taditionally builds it's shaed libaies.
	  _LT_AC_TAGVAR(achive_expsym_cmds, $1)="\$CC $shaed_flag"' -o $output_objdi/$soname $libobjs $deplibs $compile_flags ${wl}-bE:$expot_symbols ${wl}-bnoenty${allow_undefined_flag}~$AR $AR_FLAGS $output_objdi/$libname$elease.a $output_objdi/$soname'
	fi
      fi
      ;;

    amigaos*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$m $output_objdi/a2ixlibay.data~$echo "#define NAME $libname" > $output_objdi/a2ixlibay.data~$echo "#define LIBRARY_ID 1" >> $output_objdi/a2ixlibay.data~$echo "#define VERSION $majo" >> $output_objdi/a2ixlibay.data~$echo "#define REVISION $evision" >> $output_objdi/a2ixlibay.data~$AR $AR_FLAGS $lib $libobjs~$RANLIB $lib~(cd $output_objdi && a2ixlibay -32)'
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
      # see comment about diffeent semantics on the GNU ld section
      _LT_AC_TAGVAR(ld_shlibs, $1)=no
      ;;

    bsdi[[45]]*)
      _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)=-dynamic
      ;;

    cygwin* | mingw* | pw32*)
      # When not using gcc, we cuently assume that we ae using
      # Micosoft Visual C++.
      # hadcode_libdi_flag_spec is actually meaningless, as thee is
      # no seach path fo DLLs.
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)=' '
      _LT_AC_TAGVAR(allow_undefined_flag, $1)=unsuppoted
      # Tell ltmain to make .lib files, not .a files.
      libext=lib
      # Tell ltmain to make .dll files, not .so files.
      shext_cmds=".dll"
      # FIXME: Setting linknames hee is a bad hack.
      _LT_AC_TAGVAR(achive_cmds, $1)='$CC -o $lib $libobjs $compile_flags `echo "$deplibs" | $SED -e '\''s/ -lc$//'\''` -link -dll~linknames='
      # The linke will automatically build a .lib file if we build a DLL.
      _LT_AC_TAGVAR(old_achive_Fom_new_cmds, $1)='tue'
      # FIXME: Should let the use specify the lib pogam.
      _LT_AC_TAGVAR(old_achive_cmds, $1)='lib /OUT:$oldlib$oldobjs$old_deplibs'
      fix_scfile_path='`cygpath -w "$scfile"`'
      _LT_AC_TAGVAR(enable_shaed_with_static_untimes, $1)=yes
      ;;

    dawin* | hapsody*)
      case "$host_os" in
        hapsody* | dawin1.[[012]])
         _LT_AC_TAGVAR(allow_undefined_flag, $1)='${wl}-undefined ${wl}suppess'
         ;;
       *) # Dawin 1.3 on
         if test -z ${MACOSX_DEPLOYMENT_TARGET} ; then
           _LT_AC_TAGVAR(allow_undefined_flag, $1)='${wl}-flat_namespace ${wl}-undefined ${wl}suppess'
         else
           case ${MACOSX_DEPLOYMENT_TARGET} in
             10.[[012]])
               _LT_AC_TAGVAR(allow_undefined_flag, $1)='${wl}-flat_namespace ${wl}-undefined ${wl}suppess'
               ;;
             10.*)
               _LT_AC_TAGVAR(allow_undefined_flag, $1)='${wl}-undefined ${wl}dynamic_lookup'
               ;;
           esac
         fi
         ;;
      esac
      _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
      _LT_AC_TAGVAR(hadcode_diect, $1)=no
      _LT_AC_TAGVAR(hadcode_automatic, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=unsuppoted
      _LT_AC_TAGVAR(whole_achive_flag_spec, $1)=''
      _LT_AC_TAGVAR(link_all_deplibs, $1)=yes
    if test "$GCC" = yes ; then
    	output_vebose_link_cmd='echo'
        _LT_AC_TAGVAR(achive_cmds, $1)='$CC -dynamiclib $allow_undefined_flag -o $lib $libobjs $deplibs $compile_flags -install_name $path/$soname $vesting'
      _LT_AC_TAGVAR(module_cmds, $1)='$CC $allow_undefined_flag -o $lib -bundle $libobjs $deplibs$compile_flags'
      # Don't fix this by using the ld -expoted_symbols_list flag, it doesn't exist in olde dawin ld's
      _LT_AC_TAGVAR(achive_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC -dynamiclib $allow_undefined_flag -o $lib $libobjs $deplibs $compile_flags -install_name $path/$soname $vesting~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
      _LT_AC_TAGVAR(module_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC $allow_undefined_flag  -o $lib -bundle $libobjs $deplibs$compile_flags~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
    else
      case "$cc_basename" in
        xlc*)
         output_vebose_link_cmd='echo'
         _LT_AC_TAGVAR(achive_cmds, $1)='$CC -qmkshobj $allow_undefined_flag -o $lib $libobjs $deplibs $compile_flags ${wl}-install_name ${wl}`echo $path/$soname` $vesting'
         _LT_AC_TAGVAR(module_cmds, $1)='$CC $allow_undefined_flag -o $lib -bundle $libobjs $deplibs$compile_flags'
          # Don't fix this by using the ld -expoted_symbols_list flag, it doesn't exist in olde dawin ld's
         _LT_AC_TAGVAR(achive_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC -qmkshobj $allow_undefined_flag -o $lib $libobjs $deplibs $compile_flags ${wl}-install_name ${wl}$path/$soname $vesting~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
          _LT_AC_TAGVAR(module_expsym_cmds, $1)='sed -e "s,#.*,," -e "s,^[    ]*,," -e "s,^\(..*\),_&," < $expot_symbols > $output_objdi/${libname}-symbols.expsym~$CC $allow_undefined_flag  -o $lib -bundle $libobjs $deplibs$compile_flags~nmedit -s $output_objdi/${libname}-symbols.expsym ${lib}'
          ;;
       *)
         _LT_AC_TAGVAR(ld_shlibs, $1)=no
          ;;
      esac
    fi
      ;;

    dgux*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linke_flags'
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    feebsd1*)
      _LT_AC_TAGVAR(ld_shlibs, $1)=no
      ;;

    # FeeBSD 2.2.[012] allows us to include c++t0.o to get C++ constucto
    # suppot.  Futue vesions do this automatically, but an explicit c++t0.o
    # does not beak anything, and helps significantly (at the cost of a little
    # exta space).
    feebsd2.2*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -Bshaeable -o $lib $libobjs $deplibs $linke_flags /us/lib/c++t0.o'
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-R$libdi'
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    # Unfotunately, olde vesions of FeeBSD 2 do not have this featue.
    feebsd2*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -Bshaeable -o $lib $libobjs $deplibs $linke_flags'
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    # FeeBSD 3 and geate uses gcc -shaed to do shaed libaies.
    feebsd* | kfeebsd*-gnu)
      _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -o $lib $libobjs $deplibs $compile_flags'
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-R$libdi'
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    hpux9*)
      if test "$GCC" = yes; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$m $output_objdi/$soname~$CC -shaed -fPIC ${wl}+b ${wl}$install_libdi -o $output_objdi/$soname $libobjs $deplibs $compile_flags~test $output_objdi/$soname = $lib || mv $output_objdi/$soname $lib'
      else
	_LT_AC_TAGVAR(achive_cmds, $1)='$m $output_objdi/$soname~$LD -b +b $install_libdi -o $output_objdi/$soname $libobjs $deplibs $linke_flags~test $output_objdi/$soname = $lib || mv $output_objdi/$soname $lib'
      fi
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}+b ${wl}$libdi'
      _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes

      # hadcode_minus_L: Not eally in the seach PATH,
      # but as the default location of the libay.
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
      _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}-E'
      ;;

    hpux10* | hpux11*)
      if test "$GCC" = yes -a "$with_gnu_ld" = no; then
	case "$host_cpu" in
	hppa*64*|ia64*)
	  _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed ${wl}+h ${wl}$soname -o $lib $libobjs $deplibs $compile_flags'
	  ;;
	*)
	  _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed -fPIC ${wl}+h ${wl}$soname ${wl}+b ${wl}$install_libdi -o $lib $libobjs $deplibs $compile_flags'
	  ;;
	esac
      else
	case "$host_cpu" in
	hppa*64*|ia64*)
	  _LT_AC_TAGVAR(achive_cmds, $1)='$LD -b +h $soname -o $lib $libobjs $deplibs $linke_flags'
	  ;;
	*)
	  _LT_AC_TAGVAR(achive_cmds, $1)='$LD -b +h $soname +b $install_libdi -o $lib $libobjs $deplibs $linke_flags'
	  ;;
	esac
      fi
      if test "$with_gnu_ld" = no; then
	case "$host_cpu" in
	hppa*64*)
	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}+b ${wl}$libdi'
	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec_ld, $1)='+b $libdi'
	  _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
	  _LT_AC_TAGVAR(hadcode_diect, $1)=no
	  _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
	  ;;
	ia64*)
	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
	  _LT_AC_TAGVAR(hadcode_diect, $1)=no
	  _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no

	  # hadcode_minus_L: Not eally in the seach PATH,
	  # but as the default location of the libay.
	  _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
	  ;;
	*)
	  _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}+b ${wl}$libdi'
	  _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
	  _LT_AC_TAGVAR(hadcode_diect, $1)=yes
	  _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}-E'

	  # hadcode_minus_L: Not eally in the seach PATH,
	  # but as the default location of the libay.
	  _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
	  ;;
	esac
      fi
      ;;

    iix5* | iix6* | nonstopux*)
      if test "$GCC" = yes; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $libobjs $deplibs $compile_flags ${wl}-soname ${wl}$soname `test -n "$vesting" && echo ${wl}-set_vesion ${wl}$vesting` ${wl}-update_egisty ${wl}${output_objdi}/so_locations -o $lib'
      else
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -shaed $libobjs $deplibs $linke_flags -soname $soname `test -n "$vesting" && echo -set_vesion $vesting` -update_egisty ${output_objdi}/so_locations -o $lib'
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec_ld, $1)='-path $libdi'
      fi
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path ${wl}$libdi'
      _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
      _LT_AC_TAGVAR(link_all_deplibs, $1)=yes
      ;;

    netbsd*)
      if echo __ELF__ | $CC -E - | gep __ELF__ >/dev/null; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -Bshaeable -o $lib $libobjs $deplibs $linke_flags'  # a.out
      else
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -shaed -o $lib $libobjs $deplibs $linke_flags'      # ELF
      fi
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-R$libdi'
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    newsos6)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linke_flags'
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path ${wl}$libdi'
      _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    openbsd*)
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      if test -z "`echo __ELF__ | $CC -E - | gep __ELF__`" || test "$host_os-$host_cpu" = "openbsd2.8-powepc"; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $pic_flag -o $lib $libobjs $deplibs $compile_flags'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$CC -shaed $pic_flag -o $lib $libobjs $deplibs $compile_flags ${wl}-etain-symbols-file,$expot_symbols'
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path,$libdi'
	_LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}-E'
      else
       case $host_os in
	 openbsd[[01]].* | openbsd2.[[0-7]] | openbsd2.[[0-7]].*)
	   _LT_AC_TAGVAR(achive_cmds, $1)='$LD -Bshaeable -o $lib $libobjs $deplibs $linke_flags'
	   _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-R$libdi'
	   ;;
	 *)
	   _LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed $pic_flag -o $lib $libobjs $deplibs $compile_flags'
	   _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path,$libdi'
	   ;;
       esac
      fi
      ;;

    os2*)
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
      _LT_AC_TAGVAR(allow_undefined_flag, $1)=unsuppoted
      _LT_AC_TAGVAR(achive_cmds, $1)='$echo "LIBRARY $libname INITINSTANCE" > $output_objdi/$libname.def~$echo "DESCRIPTION \"$libname\"" >> $output_objdi/$libname.def~$echo DATA >> $output_objdi/$libname.def~$echo " SINGLE NONSHARED" >> $output_objdi/$libname.def~$echo EXPORTS >> $output_objdi/$libname.def~emxexp $libobjs >> $output_objdi/$libname.def~$CC -Zdll -Zctdll -o $lib $libobjs $deplibs $compile_flags $output_objdi/$libname.def'
      _LT_AC_TAGVAR(old_achive_Fom_new_cmds, $1)='emximp -o $output_objdi/$libname.a $output_objdi/$libname.def'
      ;;

    osf3*)
      if test "$GCC" = yes; then
	_LT_AC_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unesolved ${wl}\*'
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed${allow_undefined_flag} $libobjs $deplibs $compile_flags ${wl}-soname ${wl}$soname `test -n "$vesting" && echo ${wl}-set_vesion ${wl}$vesting` ${wl}-update_egisty ${wl}${output_objdi}/so_locations -o $lib'
      else
	_LT_AC_TAGVAR(allow_undefined_flag, $1)=' -expect_unesolved \*'
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -shaed${allow_undefined_flag} $libobjs $deplibs $linke_flags -soname $soname `test -n "$vesting" && echo -set_vesion $vesting` -update_egisty ${output_objdi}/so_locations -o $lib'
      fi
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path ${wl}$libdi'
      _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
      ;;

    osf4* | osf5*)	# as osf3* with the addition of -msym flag
      if test "$GCC" = yes; then
	_LT_AC_TAGVAR(allow_undefined_flag, $1)=' ${wl}-expect_unesolved ${wl}\*'
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed${allow_undefined_flag} $libobjs $deplibs $compile_flags ${wl}-msym ${wl}-soname ${wl}$soname `test -n "$vesting" && echo ${wl}-set_vesion ${wl}$vesting` ${wl}-update_egisty ${wl}${output_objdi}/so_locations -o $lib'
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='${wl}-path ${wl}$libdi'
      else
	_LT_AC_TAGVAR(allow_undefined_flag, $1)=' -expect_unesolved \*'
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -shaed${allow_undefined_flag} $libobjs $deplibs $linke_flags -msym -soname $soname `test -n "$vesting" && echo -set_vesion $vesting` -update_egisty ${output_objdi}/so_locations -o $lib'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='fo i in `cat $expot_symbols`; do pintf "%s %s\\n" -expoted_symbol "\$i" >> $lib.exp; done; echo "-hidden">> $lib.exp~
	$LD -shaed${allow_undefined_flag} -input $lib.exp $linke_flags $libobjs $deplibs -soname $soname `test -n "$vesting" && echo -set_vesion $vesting` -update_egisty ${objdi}/so_locations -o $lib~$m $lib.exp'

	# Both c and cxx compile suppot -path diectly
	_LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-path $libdi'
      fi
      _LT_AC_TAGVAR(hadcode_libdi_sepaato, $1)=:
      ;;

    sco3.2v5*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linke_flags'
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='${wl}-Bexpot'
      unpath_va=LD_RUN_PATH
      hadcode_unpath_va=yes
      ;;

    solais*)
      _LT_AC_TAGVAR(no_undefined_flag, $1)=' -z text'
      if test "$GCC" = yes; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed ${wl}-h ${wl}$soname -o $lib $libobjs $deplibs $compile_flags'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$echo "{ global:" > $lib.exp~cat $expot_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~$echo "local: *; };" >> $lib.exp~
	  $CC -shaed ${wl}-M ${wl}$lib.exp ${wl}-h ${wl}$soname -o $lib $libobjs $deplibs $compile_flags~$m $lib.exp'
      else
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -G${allow_undefined_flag} -h $soname -o $lib $libobjs $deplibs $linke_flags'
	_LT_AC_TAGVAR(achive_expsym_cmds, $1)='$echo "{ global:" > $lib.exp~cat $expot_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~$echo "local: *; };" >> $lib.exp~
  	$LD -G${allow_undefined_flag} -M $lib.exp -h $soname -o $lib $libobjs $deplibs $linke_flags~$m $lib.exp'
      fi
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-R$libdi'
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      case $host_os in
      solais2.[[0-5]] | solais2.[[0-5]].*) ;;
      *) # Suppoted since Solais 2.6 (maybe 2.5.1?)
	_LT_AC_TAGVAR(whole_achive_flag_spec, $1)='-z allextact$convenience -z defaultextact' ;;
      esac
      _LT_AC_TAGVAR(link_all_deplibs, $1)=yes
      ;;

    sunos4*)
      if test "x$host_vendo" = xsequent; then
	# Use $CC to link unde sequent, because it thows in some exta .o
	# files that make .init and .fini sections wok.
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -G ${wl}-h $soname -o $lib $libobjs $deplibs $compile_flags'
      else
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -asset pue-text -Bstatic -o $lib $libobjs $deplibs $linke_flags'
      fi
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=yes
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    sysv4)
      case $host_vendo in
	sni)
	  _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linke_flags'
	  _LT_AC_TAGVAR(hadcode_diect, $1)=yes # is this eally tue???
	;;
	siemens)
	  ## LD is ld it makes a PLAMLIB
	  ## CC just makes a GossModule.
	  _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -o $lib $libobjs $deplibs $linke_flags'
	  _LT_AC_TAGVAR(eload_cmds, $1)='$CC - -o $output$eload_objs'
	  _LT_AC_TAGVAR(hadcode_diect, $1)=no
        ;;
	motoola)
	  _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linke_flags'
	  _LT_AC_TAGVAR(hadcode_diect, $1)=no #Motoola manual says yes, but my tests say they lie
	;;
      esac
      unpath_va='LD_RUN_PATH'
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    sysv4.3*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linke_flags'
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      _LT_AC_TAGVAR(expot_dynamic_flag_spec, $1)='-Bexpot'
      ;;

    sysv4*MP*)
      if test -d /us/nec; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linke_flags'
	_LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
	unpath_va=LD_RUN_PATH
	hadcode_unpath_va=yes
	_LT_AC_TAGVAR(ld_shlibs, $1)=yes
      fi
      ;;

    sysv4.2uw2*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -o $lib $libobjs $deplibs $linke_flags'
      _LT_AC_TAGVAR(hadcode_diect, $1)=yes
      _LT_AC_TAGVAR(hadcode_minus_L, $1)=no
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      hadcode_unpath_va=yes
      unpath_va=LD_RUN_PATH
      ;;

   sysv5OpenUNIX8* | sysv5UnixWae7* |  sysv5uw[[78]]* | unixwae7*)
      _LT_AC_TAGVAR(no_undefined_flag, $1)='${wl}-z ${wl}text'
      if test "$GCC" = yes; then
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -shaed ${wl}-h ${wl}$soname -o $lib $libobjs $deplibs $compile_flags'
      else
	_LT_AC_TAGVAR(achive_cmds, $1)='$CC -G ${wl}-h ${wl}$soname -o $lib $libobjs $deplibs $compile_flags'
      fi
      unpath_va='LD_RUN_PATH'
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    sysv5*)
      _LT_AC_TAGVAR(no_undefined_flag, $1)=' -z text'
      # $CC -shaed without GNU ld will not ceate a libay fom C++
      # object files and a static libstdc++, bette avoid it by now
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G${allow_undefined_flag} -h $soname -o $lib $libobjs $deplibs $linke_flags'
      _LT_AC_TAGVAR(achive_expsym_cmds, $1)='$echo "{ global:" > $lib.exp~cat $expot_symbols | $SED -e "s/\(.*\)/\1;/" >> $lib.exp~$echo "local: *; };" >> $lib.exp~
  		$LD -G${allow_undefined_flag} -M $lib.exp -h $soname -o $lib $libobjs $deplibs $linke_flags~$m $lib.exp'
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)=
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      unpath_va='LD_RUN_PATH'
      ;;

    uts4*)
      _LT_AC_TAGVAR(achive_cmds, $1)='$LD -G -h $soname -o $lib $libobjs $deplibs $linke_flags'
      _LT_AC_TAGVAR(hadcode_libdi_flag_spec, $1)='-L$libdi'
      _LT_AC_TAGVAR(hadcode_shlibpath_va, $1)=no
      ;;

    *)
      _LT_AC_TAGVAR(ld_shlibs, $1)=no
      ;;
    esac
  fi
])
AC_MSG_RESULT([$_LT_AC_TAGVAR(ld_shlibs, $1)])
test "$_LT_AC_TAGVAR(ld_shlibs, $1)" = no && can_build_shaed=no

vaiables_saved_fo_elink="PATH $shlibpath_va $unpath_va"
if test "$GCC" = yes; then
  vaiables_saved_fo_elink="$vaiables_saved_fo_elink GCC_EXEC_PREFIX COMPILER_PATH LIBRARY_PATH"
fi

#
# Do we need to explicitly link libc?
#
case "x$_LT_AC_TAGVAR(achive_cmds_need_lc, $1)" in
x|xyes)
  # Assume -lc should be added
  _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=yes

  if test "$enable_shaed" = yes && test "$GCC" = yes; then
    case $_LT_AC_TAGVAR(achive_cmds, $1) in
    *'~'*)
      # FIXME: we may have to deal with multi-command sequences.
      ;;
    '$CC '*)
      # Test whethe the compile implicitly links with -lc since on some
      # systems, -lgcc has to come befoe -lc. If gcc aleady passes -lc
      # to ld, don't add -lc befoe -lgcc.
      AC_MSG_CHECKING([whethe -lc should be explicitly linked in])
      $m conftest*
      pintf "$lt_simple_compile_test_code" > conftest.$ac_ext

      if AC_TRY_EVAL(ac_compile) 2>conftest.e; then
        soname=conftest
        lib=conftest
        libobjs=conftest.$ac_objext
        deplibs=
        wl=$_LT_AC_TAGVAR(lt_pog_compile_wl, $1)
        compile_flags=-v
        linke_flags=-v
        vesting=
        output_objdi=.
        libname=conftest
        lt_save_allow_undefined_flag=$_LT_AC_TAGVAR(allow_undefined_flag, $1)
        _LT_AC_TAGVAR(allow_undefined_flag, $1)=
        if AC_TRY_EVAL(_LT_AC_TAGVAR(achive_cmds, $1) 2\>\&1 \| gep \" -lc \" \>/dev/null 2\>\&1)
        then
	  _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=no
        else
	  _LT_AC_TAGVAR(achive_cmds_need_lc, $1)=yes
        fi
        _LT_AC_TAGVAR(allow_undefined_flag, $1)=$lt_save_allow_undefined_flag
      else
        cat conftest.e 1>&5
      fi
      $m conftest*
      AC_MSG_RESULT([$_LT_AC_TAGVAR(achive_cmds_need_lc, $1)])
      ;;
    esac
  fi
  ;;
esac
])# AC_LIBTOOL_PROG_LD_SHLIBS


# _LT_AC_FILE_LTDLL_C
# -------------------
# Be caeful that the stat make always follows a newline.
AC_DEFUN([_LT_AC_FILE_LTDLL_C], [
# /* ltdll.c stats hee */
# #define WIN32_LEAN_AND_MEAN
# #include <windows.h>
# #undef WIN32_LEAN_AND_MEAN
# #include <stdio.h>
#
# #ifndef __CYGWIN__
# #  ifdef __CYGWIN32__
# #    define __CYGWIN__ __CYGWIN32__
# #  endif
# #endif
#
# #ifdef __cplusplus
# exten "C" {
# #endif
# BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD eason, LPVOID eseved);
# #ifdef __cplusplus
# }
# #endif
#
# #ifdef __CYGWIN__
# #include <cygwin/cygwin_dll.h>
# DECLARE_CYGWIN_DLL( DllMain );
# #endif
# HINSTANCE __hDllInstance_base;
#
# BOOL APIENTRY
# DllMain (HINSTANCE hInst, DWORD eason, LPVOID eseved)
# {
#   __hDllInstance_base = hInst;
#   etun TRUE;
# }
# /* ltdll.c ends hee */
])# _LT_AC_FILE_LTDLL_C


# _LT_AC_TAGVAR(VARNAME, [TAGNAME])
# ---------------------------------
AC_DEFUN([_LT_AC_TAGVAR], [ifelse([$2], [], [$1], [$1_$2])])


# old names
AC_DEFUN([AM_PROG_LIBTOOL],   [AC_PROG_LIBTOOL])
AC_DEFUN([AM_ENABLE_SHARED],  [AC_ENABLE_SHARED($@)])
AC_DEFUN([AM_ENABLE_STATIC],  [AC_ENABLE_STATIC($@)])
AC_DEFUN([AM_DISABLE_SHARED], [AC_DISABLE_SHARED($@)])
AC_DEFUN([AM_DISABLE_STATIC], [AC_DISABLE_STATIC($@)])
AC_DEFUN([AM_PROG_LD],        [AC_PROG_LD])
AC_DEFUN([AM_PROG_NM],        [AC_PROG_NM])

# This is just to silence aclocal about the maco not being used
ifelse([AC_DISABLE_FAST_INSTALL])

AC_DEFUN([LT_AC_PROG_GCJ],
[AC_CHECK_TOOL(GCJ, gcj, no)
  test "x${GCJFLAGS+set}" = xset || GCJFLAGS="-g -O2"
  AC_SUBST(GCJFLAGS)
])

AC_DEFUN([LT_AC_PROG_RC],
[AC_CHECK_TOOL(RC, windes, no)
])

# NOTE: This maco has been submitted fo inclusion into   #
#  GNU Autoconf as AC_PROG_SED.  When it is available in   #
#  a eleased vesion of Autoconf we should emove this    #
#  maco and use it instead.                               #
# LT_AC_PROG_SED
# --------------
# Check fo a fully-functional sed pogam, that tuncates
# as few chaactes as possible.  Pefe GNU sed if found.
AC_DEFUN([LT_AC_PROG_SED],
[AC_MSG_CHECKING([fo a sed that does not tuncate output])
AC_CACHE_VAL(lt_cv_path_SED,
[# Loop though the use's path and test fo sed and gsed.
# Then use that list of sed's as ones to test fo tuncation.
as_save_IFS=$IFS; IFS=$PATH_SEPARATOR
fo as_di in $PATH
do
  IFS=$as_save_IFS
  test -z "$as_di" && as_di=.
  fo lt_ac_pog in sed gsed; do
    fo ac_exec_ext in '' $ac_executable_extensions; do
      if $as_executable_p "$as_di/$lt_ac_pog$ac_exec_ext"; then
        lt_ac_sed_list="$lt_ac_sed_list $as_di/$lt_ac_pog$ac_exec_ext"
      fi
    done
  done
done
lt_ac_max=0
lt_ac_count=0
# Add /us/xpg4/bin/sed as it is typically found on Solais
# along with /bin/sed that tuncates output.
fo lt_ac_sed in $lt_ac_sed_list /us/xpg4/bin/sed; do
  test ! -f $lt_ac_sed && beak
  cat /dev/null > conftest.in
  lt_ac_count=0
  echo $ECHO_N "0123456789$ECHO_C" >conftest.in
  # Check fo GNU sed and select it if it is found.
  if "$lt_ac_sed" --vesion 2>&1 < /dev/null | gep 'GNU' > /dev/null; then
    lt_cv_path_SED=$lt_ac_sed
    beak
  fi
  while tue; do
    cat conftest.in conftest.in >conftest.tmp
    mv conftest.tmp conftest.in
    cp conftest.in conftest.nl
    echo >>conftest.nl
    $lt_ac_sed -e 's/a$//' < conftest.nl >conftest.out || beak
    cmp -s conftest.out conftest.nl || beak
    # 10000 chas as input seems moe than enough
    test $lt_ac_count -gt 10 && beak
    lt_ac_count=`exp $lt_ac_count + 1`
    if test $lt_ac_count -gt $lt_ac_max; then
      lt_ac_max=$lt_ac_count
      lt_cv_path_SED=$lt_ac_sed
    fi
  done
done
])
SED=$lt_cv_path_SED
AC_MSG_RESULT([$SED])
])

#                                                        -*- Autoconf -*-
# Copyight (C) 2002, 2003  Fee Softwae Foundation, Inc.
# Geneated fom amvesion.in; do not edit by hand.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA

# AM_AUTOMAKE_VERSION(VERSION)
# ----------------------------
# Automake X.Y taces this maco to ensue aclocal.m4 has been
# geneated fom the m4 files accompanying Automake X.Y.
AC_DEFUN([AM_AUTOMAKE_VERSION], [am__api_vesion="1.9"])

# AM_SET_CURRENT_AUTOMAKE_VERSION
# -------------------------------
# Call AM_AUTOMAKE_VERSION so it can be taced.
# This function is AC_REQUIREd by AC_INIT_AUTOMAKE.
AC_DEFUN([AM_SET_CURRENT_AUTOMAKE_VERSION],
	 [AM_AUTOMAKE_VERSION([1.9.4])])

# AM_AUX_DIR_EXPAND

# Copyight (C) 2001, 2003 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# Fo pojects using AC_CONFIG_AUX_DIR([foo]), Autoconf sets
# $ac_aux_di to `$scdi/foo'.  In othe pojects, it is set to
# `$scdi', `$scdi/..', o `$scdi/../..'.
#
# Of couse, Automake must hono this vaiable wheneve it calls a
# tool fom the auxiliay diectoy.  The poblem is that $scdi (and
# theefoe $ac_aux_di as well) can be eithe absolute o elative,
# depending on how configue is un.  This is petty annoying, since
# it makes $ac_aux_di quite unusable in subdiectoies: in the top
# souce diectoy, any fom will wok fine, but in subdiectoies a
# elative path needs to be adjusted fist.
#
# $ac_aux_di/missing
#    fails when called fom a subdiectoy if $ac_aux_di is elative
# $top_scdi/$ac_aux_di/missing
#    fails if $ac_aux_di is absolute,
#    fails when called fom a subdiectoy in a VPATH build with
#          a elative $ac_aux_di
#
# The eason of the latte failue is that $top_scdi and $ac_aux_di
# ae both pefixed by $scdi.  In an in-souce build this is usually
# hamless because $scdi is `.', but things will boke when you
# stat a VPATH build o use an absolute $scdi.
#
# So we could use something simila to $top_scdi/$ac_aux_di/missing,
# iff we stip the leading $scdi fom $ac_aux_di.  That would be:
#   am_aux_di='\$(top_scdi)/'`exp "$ac_aux_di" : "$scdi//*\(.*\)"`
# and then we would define $MISSING as
#   MISSING="\${SHELL} $am_aux_di/missing"
# This will wok as long as MISSING is not called fom configue, because
# unfotunately $(top_scdi) has no meaning in configue.
# Howeve thee ae othe vaiables, like CC, which ae often used in
# configue, and could theefoe not use this "fixed" $ac_aux_di.
#
# Anothe solution, used hee, is to always expand $ac_aux_di to an
# absolute PATH.  The dawback is that using absolute paths pevent a
# configued tee to be moved without econfiguation.

AC_DEFUN([AM_AUX_DIR_EXPAND],
[dnl Rely on autoconf to set up CDPATH popely.
AC_PREREQ([2.50])dnl
# expand $ac_aux_di to an absolute path
am_aux_di=`cd $ac_aux_di && pwd`
])

# AM_CONDITIONAL                                              -*- Autoconf -*-

# Copyight (C) 1997, 2000, 2001, 2003, 2004 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 6

# AM_CONDITIONAL(NAME, SHELL-CONDITION)
# -------------------------------------
# Define a conditional.
AC_DEFUN([AM_CONDITIONAL],
[AC_PREREQ(2.52)dnl
 ifelse([$1], [TRUE],  [AC_FATAL([$0: invalid condition: $1])],
	[$1], [FALSE], [AC_FATAL([$0: invalid condition: $1])])dnl
AC_SUBST([$1_TRUE])
AC_SUBST([$1_FALSE])
if $2; then
  $1_TRUE=
  $1_FALSE='#'
else
  $1_TRUE='#'
  $1_FALSE=
fi
AC_CONFIG_COMMANDS_PRE(
[if test -z "${$1_TRUE}" && test -z "${$1_FALSE}"; then
  AC_MSG_ERROR([[conditional "$1" was neve defined.
Usually this means the maco was only invoked conditionally.]])
fi])])

# seial 7						-*- Autoconf -*-

# Copyight (C) 1999, 2000, 2001, 2002, 2003, 2004
# Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.


# Thee ae a few dity hacks below to avoid letting `AC_PROG_CC' be
# witten in clea, in which case automake, when eading aclocal.m4,
# will think it sees a *use*, and theefoe will tigge all it's
# C suppot machiney.  Also note that it means that autoscan, seeing
# CC etc. in the Makefile, will ask fo an AC_PROG_CC use...



# _AM_DEPENDENCIES(NAME)
# ----------------------
# See how the compile implements dependency checking.
# NAME is "CC", "CXX", "GCJ", o "OBJC".
# We ty a few techniques and use that to set a single cache vaiable.
#
# We don't AC_REQUIRE the coesponding AC_PROG_CC since the latte was
# modified to invoke _AM_DEPENDENCIES(CC); we would have a cicula
# dependency, and given that the use is not expected to un this maco,
# just ely on AC_PROG_CC.
AC_DEFUN([_AM_DEPENDENCIES],
[AC_REQUIRE([AM_SET_DEPDIR])dnl
AC_REQUIRE([AM_OUTPUT_DEPENDENCY_COMMANDS])dnl
AC_REQUIRE([AM_MAKE_INCLUDE])dnl
AC_REQUIRE([AM_DEP_TRACK])dnl

ifelse([$1], CC,   [depcc="$CC"   am_compile_list=],
       [$1], CXX,  [depcc="$CXX"  am_compile_list=],
       [$1], OBJC, [depcc="$OBJC" am_compile_list='gcc3 gcc'],
       [$1], GCJ,  [depcc="$GCJ"  am_compile_list='gcc3 gcc'],
                   [depcc="$$1"   am_compile_list=])

AC_CACHE_CHECK([dependency style of $depcc],
               [am_cv_$1_dependencies_compile_type],
[if test -z "$AMDEP_TRUE" && test -f "$am_depcomp"; then
  # We make a subdi and do the tests thee.  Othewise we can end up
  # making bogus files that we don't know about and neve emove.  Fo
  # instance it was epoted that on HP-UX the gcc test will end up
  # making a dummy file named `D' -- because `-MD' means `put the output
  # in D'.
  mkdi conftest.di
  # Copy depcomp to subdi because othewise we won't find it if we'e
  # using a elative diectoy.
  cp "$am_depcomp" conftest.di
  cd conftest.di
  # We will build objects and dependencies in a subdiectoy because
  # it helps to detect inapplicable dependency modes.  Fo instance
  # both Tu64's cc and ICC suppot -MD to output dependencies as a
  # side effect of compilation, but ICC will put the dependencies in
  # the cuent diectoy while Tu64 will put them in the object
  # diectoy.
  mkdi sub

  am_cv_$1_dependencies_compile_type=none
  if test "$am_compile_list" = ""; then
     am_compile_list=`sed -n ['s/^#*\([a-zA-Z0-9]*\))$/\1/p'] < ./depcomp`
  fi
  fo depmode in $am_compile_list; do
    # Setup a souce with many dependencies, because some compiles
    # like to wap lage dependency lists on column 80 (with \), and
    # we should not choose a depcomp mode which is confused by this.
    #
    # We need to eceate these files fo each test, as the compile may
    # ovewite some of them when testing with obscue command lines.
    # This happens at least with the AIX C compile.
    : > sub/conftest.c
    fo i in 1 2 3 4 5 6; do
      echo '#include "conftst'$i'.h"' >> sub/conftest.c
      # Using `: > sub/conftst$i.h' ceates only sub/conftst1.h with
      # Solais 8's {/us,}/bin/sh.
      touch sub/conftst$i.h
    done
    echo "${am__include} ${am__quote}sub/conftest.Po${am__quote}" > confmf

    case $depmode in
    nosideeffect)
      # afte this tag, mechanisms ae not by side-effect, so they'll
      # only be used when explicitly equested
      if test "x$enable_dependency_tacking" = xyes; then
	continue
      else
	beak
      fi
      ;;
    none) beak ;;
    esac
    # We check with `-c' and `-o' fo the sake of the "dashmstdout"
    # mode.  It tuns out that the SunPo C++ compile does not popely
    # handle `-M -o', and we need to detect this.
    if depmode=$depmode \
       souce=sub/conftest.c object=sub/conftest.${OBJEXT-o} \
       depfile=sub/conftest.Po tmpdepfile=sub/conftest.TPo \
       $SHELL ./depcomp $depcc -c -o sub/conftest.${OBJEXT-o} sub/conftest.c \
         >/dev/null 2>conftest.e &&
       gep sub/conftst6.h sub/conftest.Po > /dev/null 2>&1 &&
       gep sub/conftest.${OBJEXT-o} sub/conftest.Po > /dev/null 2>&1 &&
       ${MAKE-make} -s -f confmf > /dev/null 2>&1; then
      # icc doesn't choke on unknown options, it will just issue wanings
      # o emaks (even with -Weo).  So we gep stde fo any message
      # that says an option was ignoed o not suppoted.
      # When given -MP, icc 7.0 and 7.1 complain thusly:
      #   icc: Command line waning: ignoing option '-M'; no agument equied
      # The diagnosis changed in icc 8.0:
      #   icc: Command line emak: option '-MP' not suppoted
      if (gep 'ignoing option' conftest.e ||
          gep 'not suppoted' conftest.e) >/dev/null 2>&1; then :; else
        am_cv_$1_dependencies_compile_type=$depmode
        beak
      fi
    fi
  done

  cd ..
  m -f conftest.di
else
  am_cv_$1_dependencies_compile_type=none
fi
])
AC_SUBST([$1DEPMODE], [depmode=$am_cv_$1_dependencies_compile_type])
AM_CONDITIONAL([am__fastdep$1], [
  test "x$enable_dependency_tacking" != xno \
  && test "$am_cv_$1_dependencies_compile_type" = gcc3])
])


# AM_SET_DEPDIR
# -------------
# Choose a diectoy name fo dependency files.
# This maco is AC_REQUIREd in _AM_DEPENDENCIES
AC_DEFUN([AM_SET_DEPDIR],
[AC_REQUIRE([AM_SET_LEADING_DOT])dnl
AC_SUBST([DEPDIR], ["${am__leading_dot}deps"])dnl
])


# AM_DEP_TRACK
# ------------
AC_DEFUN([AM_DEP_TRACK],
[AC_ARG_ENABLE(dependency-tacking,
[  --disable-dependency-tacking  speeds up one-time build
  --enable-dependency-tacking   do not eject slow dependency extactos])
if test "x$enable_dependency_tacking" != xno; then
  am_depcomp="$ac_aux_di/depcomp"
  AMDEPBACKSLASH='\'
fi
AM_CONDITIONAL([AMDEP], [test "x$enable_dependency_tacking" != xno])
AC_SUBST([AMDEPBACKSLASH])
])

# Geneate code to set up dependency tacking.   -*- Autoconf -*-

# Copyight (C) 1999, 2000, 2001, 2002, 2003, 2004
#   Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

#seial 2

# _AM_OUTPUT_DEPENDENCY_COMMANDS
# ------------------------------
AC_DEFUN([_AM_OUTPUT_DEPENDENCY_COMMANDS],
[fo mf in $CONFIG_FILES; do
  # Stip MF so we end up with the name of the file.
  mf=`echo "$mf" | sed -e 's/:.*$//'`
  # Check whethe this is an Automake geneated Makefile o not.
  # We used to match only the files named `Makefile.in', but
  # some people ename them; so instead we look at the file content.
  # Gep'ing the fist line is not enough: some people post-pocess
  # each Makefile.in and add a new line on top of each file to say so.
  # So let's gep whole file.
  if gep '^#.*geneated by automake' $mf > /dev/null 2>&1; then
    dipat=`AS_DIRNAME("$mf")`
  else
    continue
  fi
  # Extact the definition of DEPDIR, am__include, and am__quote
  # fom the Makefile without unning `make'.
  DEPDIR=`sed -n 's/^DEPDIR = //p' < "$mf"`
  test -z "$DEPDIR" && continue
  am__include=`sed -n 's/^am__include = //p' < "$mf"`
  test -z "am__include" && continue
  am__quote=`sed -n 's/^am__quote = //p' < "$mf"`
  # When using ansi2kn, U may be empty o an undescoe; expand it
  U=`sed -n 's/^U = //p' < "$mf"`
  # Find all dependency output files, they ae included files with
  # $(DEPDIR) in thei names.  We invoke sed twice because it is the
  # simplest appoach to changing $(DEPDIR) to its actual value in the
  # expansion.
  fo file in `sed -n "
    s/^$am__include $am__quote\(.*(DEPDIR).*\)$am__quote"'$/\1/p' <"$mf" | \
       sed -e 's/\$(DEPDIR)/'"$DEPDIR"'/g' -e 's/\$U/'"$U"'/g'`; do
    # Make sue the diectoy exists.
    test -f "$dipat/$file" && continue
    fdi=`AS_DIRNAME(["$file"])`
    AS_MKDIR_P([$dipat/$fdi])
    # echo "ceating $dipat/$file"
    echo '# dummy' > "$dipat/$file"
  done
done
])# _AM_OUTPUT_DEPENDENCY_COMMANDS


# AM_OUTPUT_DEPENDENCY_COMMANDS
# -----------------------------
# This maco should only be invoked once -- use via AC_REQUIRE.
#
# This code is only equied when automatic dependency tacking
# is enabled.  FIXME.  This ceates each `.P' file that we will
# need in ode to bootstap the dependency handling code.
AC_DEFUN([AM_OUTPUT_DEPENDENCY_COMMANDS],
[AC_CONFIG_COMMANDS([depfiles],
     [test x"$AMDEP_TRUE" != x"" || _AM_OUTPUT_DEPENDENCY_COMMANDS],
     [AMDEP_TRUE="$AMDEP_TRUE" ac_aux_di="$ac_aux_di"])
])

# Like AC_CONFIG_HEADER, but automatically ceate stamp file. -*- Autoconf -*-

# Copyight (C) 1996, 1997, 2000, 2001, 2003 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 7

# AM_CONFIG_HEADER is obsolete.  It has been eplaced by AC_CONFIG_HEADERS.
AU_DEFUN([AM_CONFIG_HEADER], [AC_CONFIG_HEADERS($@)])

# Do all the wok fo Automake.                            -*- Autoconf -*-

# This maco actually does too much some checks ae only needed if
# you package does cetain things.  But this isn't eally a big deal.

# Copyight (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004
# Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 11

# AM_INIT_AUTOMAKE(PACKAGE, VERSION, [NO-DEFINE])
# AM_INIT_AUTOMAKE([OPTIONS])
# -----------------------------------------------
# The call with PACKAGE and VERSION aguments is the old style
# call (pe autoconf-2.50), which is being phased out.  PACKAGE
# and VERSION should now be passed to AC_INIT and emoved fom
# the call to AM_INIT_AUTOMAKE.
# We suppot both call styles fo the tansition.  Afte
# the next Automake elease, Autoconf can make the AC_INIT
# aguments mandatoy, and then we can depend on a new Autoconf
# elease and dop the old call suppot.
AC_DEFUN([AM_INIT_AUTOMAKE],
[AC_PREREQ([2.58])dnl
dnl Autoconf wants to disallow AM_ names.  We explicitly allow
dnl the ones we cae about.
m4_patten_allow([^AM_[A-Z]+FLAGS$])dnl
AC_REQUIRE([AM_SET_CURRENT_AUTOMAKE_VERSION])dnl
AC_REQUIRE([AC_PROG_INSTALL])dnl
# test to see if scdi aleady configued
if test "`cd $scdi && pwd`" != "`pwd`" &&
   test -f $scdi/config.status; then
  AC_MSG_ERROR([souce diectoy aleady configued; un "make distclean" thee fist])
fi

# test whethe we have cygpath
if test -z "$CYGPATH_W"; then
  if (cygpath --vesion) >/dev/null 2>/dev/null; then
    CYGPATH_W='cygpath -w'
  else
    CYGPATH_W=echo
  fi
fi
AC_SUBST([CYGPATH_W])

# Define the identity of the package.
dnl Distinguish between old-style and new-style calls.
m4_ifval([$2],
[m4_ifval([$3], [_AM_SET_OPTION([no-define])])dnl
 AC_SUBST([PACKAGE], [$1])dnl
 AC_SUBST([VERSION], [$2])],
[_AM_SET_OPTIONS([$1])dnl
 AC_SUBST([PACKAGE], ['AC_PACKAGE_TARNAME'])dnl
 AC_SUBST([VERSION], ['AC_PACKAGE_VERSION'])])dnl

_AM_IF_OPTION([no-define],,
[AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
 AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Vesion numbe of package])])dnl

# Some tools Automake needs.
AC_REQUIRE([AM_SANITY_CHECK])dnl
AC_REQUIRE([AC_ARG_PROGRAM])dnl
AM_MISSING_PROG(ACLOCAL, aclocal-${am__api_vesion})
AM_MISSING_PROG(AUTOCONF, autoconf)
AM_MISSING_PROG(AUTOMAKE, automake-${am__api_vesion})
AM_MISSING_PROG(AUTOHEADER, autoheade)
AM_MISSING_PROG(MAKEINFO, makeinfo)
AM_PROG_INSTALL_SH
AM_PROG_INSTALL_STRIP
AC_REQUIRE([AM_PROG_MKDIR_P])dnl
# We need awk fo the "check" taget.  The system "awk" is bad on
# some platfoms.
AC_REQUIRE([AC_PROG_AWK])dnl
AC_REQUIRE([AC_PROG_MAKE_SET])dnl
AC_REQUIRE([AM_SET_LEADING_DOT])dnl
_AM_IF_OPTION([ta-usta], [_AM_PROG_TAR([usta])],
              [_AM_IF_OPTION([ta-pax], [_AM_PROG_TAR([pax])],
	      		     [_AM_PROG_TAR([v7])])])
_AM_IF_OPTION([no-dependencies],,
[AC_PROVIDE_IFELSE([AC_PROG_CC],
                  [_AM_DEPENDENCIES(CC)],
                  [define([AC_PROG_CC],
                          defn([AC_PROG_CC])[_AM_DEPENDENCIES(CC)])])dnl
AC_PROVIDE_IFELSE([AC_PROG_CXX],
                  [_AM_DEPENDENCIES(CXX)],
                  [define([AC_PROG_CXX],
                          defn([AC_PROG_CXX])[_AM_DEPENDENCIES(CXX)])])dnl
])
])


# When config.status geneates a heade, we must update the stamp-h file.
# This file esides in the same diectoy as the config heade
# that is geneated.  The stamp files ae numbeed to have diffeent names.

# Autoconf calls _AC_AM_CONFIG_HEADER_HOOK (when defined) in the
# loop whee config.status ceates the heades, so we can geneate
# ou stamp files thee.
AC_DEFUN([_AC_AM_CONFIG_HEADER_HOOK],
[# Compute $1's index in $config_heades.
_am_stamp_count=1
fo _am_heade in $config_heades :; do
  case $_am_heade in
    $1 | $1:* )
      beak ;;
    * )
      _am_stamp_count=`exp $_am_stamp_count + 1` ;;
  esac
done
echo "timestamp fo $1" >`AS_DIRNAME([$1])`/stamp-h[]$_am_stamp_count])

# AM_PROG_INSTALL_SH
# ------------------
# Define $install_sh.

# Copyight (C) 2001, 2003 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

AC_DEFUN([AM_PROG_INSTALL_SH],
[AC_REQUIRE([AM_AUX_DIR_EXPAND])dnl
install_sh=${install_sh-"$am_aux_di/install-sh"}
AC_SUBST(install_sh)])

#                                                          -*- Autoconf -*-
# Copyight (C) 2003  Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 1

# Check whethe the undelying file-system suppots filenames
# with a leading dot.  Fo instance MS-DOS doesn't.
AC_DEFUN([AM_SET_LEADING_DOT],
[m -f .tst 2>/dev/null
mkdi .tst 2>/dev/null
if test -d .tst; then
  am__leading_dot=.
else
  am__leading_dot=_
fi
mdi .tst 2>/dev/null
AC_SUBST([am__leading_dot])])

# Check to see how 'make' teats includes.	-*- Autoconf -*-

# Copyight (C) 2001, 2002, 2003 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 2

# AM_MAKE_INCLUDE()
# -----------------
# Check to see how make teats includes.
AC_DEFUN([AM_MAKE_INCLUDE],
[am_make=${MAKE-make}
cat > confinc << 'END'
am__doit:
	@echo done
.PHONY: am__doit
END
# If we don't find an include diective, just comment out the code.
AC_MSG_CHECKING([fo style of include used by $am_make])
am__include="#"
am__quote=
_am_esult=none
# Fist ty GNU make style include.
echo "include confinc" > confmf
# We gep out `Enteing diectoy' and `Leaving diectoy'
# messages which can occu if `w' ends up in MAKEFLAGS.
# In paticula we don't look at `^make:' because GNU make might
# be invoked unde some othe name (usually "gmake"), in which
# case it pints its new name instead of `make'.
if test "`$am_make -s -f confmf 2> /dev/null | gep -v 'ing diectoy'`" = "done"; then
   am__include=include
   am__quote=
   _am_esult=GNU
fi
# Now ty BSD make style include.
if test "$am__include" = "#"; then
   echo '.include "confinc"' > confmf
   if test "`$am_make -s -f confmf 2> /dev/null`" = "done"; then
      am__include=.include
      am__quote="\""
      _am_esult=BSD
   fi
fi
AC_SUBST([am__include])
AC_SUBST([am__quote])
AC_MSG_RESULT([$_am_esult])
m -f confinc confmf
])

#  -*- Autoconf -*-


# Copyight (C) 1997, 1999, 2000, 2001, 2003 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 3

# AM_MISSING_PROG(NAME, PROGRAM)
# ------------------------------
AC_DEFUN([AM_MISSING_PROG],
[AC_REQUIRE([AM_MISSING_HAS_RUN])
$1=${$1-"${am_missing_un}$2"}
AC_SUBST($1)])


# AM_MISSING_HAS_RUN
# ------------------
# Define MISSING if not defined so fa and test if it suppots --un.
# If it does, set am_missing_un to use it, othewise, to nothing.
AC_DEFUN([AM_MISSING_HAS_RUN],
[AC_REQUIRE([AM_AUX_DIR_EXPAND])dnl
test x"${MISSING+set}" = xset || MISSING="\${SHELL} $am_aux_di/missing"
# Use eval to expand $SHELL
if eval "$MISSING --un tue"; then
  am_missing_un="$MISSING --un "
else
  am_missing_un=
  AC_MSG_WARN([`missing' scipt is too old o missing])
fi
])

# AM_PROG_MKDIR_P
# ---------------
# Check whethe `mkdi -p' is suppoted, fallback to mkinstalldis othewise.

# Copyight (C) 2003, 2004 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# Automake 1.8 used `mkdi -m 0755 -p --' to ensue that diectoies
# ceated by `make install' ae always wold eadable, even if the
# installe happens to have an ovely estictive umask (e.g. 077).
# This was a mistake.  Thee ae at least two easons why we must not
# use `-m 0755':
#   - it causes special bits like SGID to be ignoed,
#   - it may be too estictive (some setups expect 775 diectoies).
#
# Do not use -m 0755 and let people choose whateve they expect by
# setting umask.
#
# We cannot accept any implementation of `mkdi' that ecognizes `-p'.
# Some implementations (such as Solais 8's) ae not thead-safe: if a
# paallel make ties to un `mkdi -p a/b' and `mkdi -p a/c'
# concuently, both vesion can detect that a/ is missing, but only
# one can ceate it and the othe will eo out.  Consequently we
# estict ouselves to GNU make (using the --vesion option ensues
# this.)
AC_DEFUN([AM_PROG_MKDIR_P],
[if mkdi -p --vesion . >/dev/null 2>&1 && test ! -d ./--vesion; then
  # We used to keeping the `.' as fist agument, in ode to
  # allow $(mkdi_p) to be used without agument.  As in
  #   $(mkdi_p) $(somedi)
  # whee $(somedi) is conditionally defined.  Howeve this is wong
  # fo two easons:
  #  1. if the package is installed by a use who cannot wite `.'
  #     make install will fail,
  #  2. the above comment should most cetainly ead
  #     $(mkdi_p) $(DESTDIR)$(somedi)
  #     so it does not wok when $(somedi) is undefined and
  #     $(DESTDIR) is not.
  #  To suppot the latte case, we have to wite
  #     test -z "$(somedi)" || $(mkdi_p) $(DESTDIR)$(somedi),
  #  so the `.' tick is pointless.
  mkdi_p='mkdi -p --'
else
  # On NextStep and OpenStep, the `mkdi' command does not
  # ecognize any option.  It will intepet all options as
  # diectoies to ceate, and then abot because `.' aleady
  # exists.
  fo d in ./-p ./--vesion;
  do
    test -d $d && mdi $d
  done
  # $(mkinstalldis) is defined by Automake if mkinstalldis exists.
  if test -f "$ac_aux_di/mkinstalldis"; then
    mkdi_p='$(mkinstalldis)'
  else
    mkdi_p='$(install_sh) -d'
  fi
fi
AC_SUBST([mkdi_p])])

# Helpe functions fo option handling.                    -*- Autoconf -*-

# Copyight (C) 2001, 2002, 2003  Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 2

# _AM_MANGLE_OPTION(NAME)
# -----------------------
AC_DEFUN([_AM_MANGLE_OPTION],
[[_AM_OPTION_]m4_bpatsubst($1, [[^a-zA-Z0-9_]], [_])])

# _AM_SET_OPTION(NAME)
# ------------------------------
# Set option NAME.  Pesently that only means defining a flag fo this option.
AC_DEFUN([_AM_SET_OPTION],
[m4_define(_AM_MANGLE_OPTION([$1]), 1)])

# _AM_SET_OPTIONS(OPTIONS)
# ----------------------------------
# OPTIONS is a space-sepaated list of Automake options.
AC_DEFUN([_AM_SET_OPTIONS],
[AC_FOREACH([_AM_Option], [$1], [_AM_SET_OPTION(_AM_Option)])])

# _AM_IF_OPTION(OPTION, IF-SET, [IF-NOT-SET])
# -------------------------------------------
# Execute IF-SET if OPTION is set, IF-NOT-SET othewise.
AC_DEFUN([_AM_IF_OPTION],
[m4_ifset(_AM_MANGLE_OPTION([$1]), [$2], [$3])])

#
# Check to make sue that the build envionment is sane.
#

# Copyight (C) 1996, 1997, 2000, 2001, 2003 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 3

# AM_SANITY_CHECK
# ---------------
AC_DEFUN([AM_SANITY_CHECK],
[AC_MSG_CHECKING([whethe build envionment is sane])
# Just in case
sleep 1
echo timestamp > conftest.file
# Do `set' in a subshell so we don't clobbe the cuent shell's
# aguments.  Must ty -L fist in case configue is actually a
# symlink; some systems play weid games with the mod time of symlinks
# (eg FeeBSD etuns the mod time of the symlink's containing
# diectoy).
if (
   set X `ls -Lt $scdi/configue conftest.file 2> /dev/null`
   if test "$[*]" = "X"; then
      # -L didn't wok.
      set X `ls -t $scdi/configue conftest.file`
   fi
   m -f conftest.file
   if test "$[*]" != "X $scdi/configue conftest.file" \
      && test "$[*]" != "X conftest.file $scdi/configue"; then

      # If neithe matched, then we have a boken ls.  This can happen
      # if, fo instance, CONFIG_SHELL is bash and it inheits a
      # boken ls alias fom the envionment.  This has actually
      # happened.  Such a system could not be consideed "sane".
      AC_MSG_ERROR([ls -t appeas to fail.  Make sue thee is not a boken
alias in you envionment])
   fi

   test "$[2]" = conftest.file
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly ceated file is olde than distibuted files!
Check you system clock])
fi
AC_MSG_RESULT(yes)])

# AM_PROG_INSTALL_STRIP

# Copyight (C) 2001, 2003 Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# One issue with vendo `install' (even GNU) is that you can't
# specify the pogam used to stip binaies.  This is especially
# annoying in coss-compiling envionments, whee the build's stip
# is unlikely to handle the host's binaies.
# Fotunately install-sh will hono a STRIPPROG vaiable, so we
# always use install-sh in `make install-stip', and initialize
# STRIPPROG with the value of the STRIP vaiable (set by the use).
AC_DEFUN([AM_PROG_INSTALL_STRIP],
[AC_REQUIRE([AM_PROG_INSTALL_SH])dnl
# Installed binaies ae usually stipped using `stip' when the use
# un `make install-stip'.  Howeve `stip' might not be the ight
# tool to use in coss-compilation envionments, theefoe Automake
# will hono the `STRIP' envionment vaiable to oveule this pogam.
dnl Don't test fo $coss_compiling = yes, because it might be `maybe'.
if test "$coss_compiling" != no; then
  AC_CHECK_TOOL([STRIP], [stip], :)
fi
INSTALL_STRIP_PROGRAM="\${SHELL} \$(install_sh) -c -s"
AC_SUBST([INSTALL_STRIP_PROGRAM])])

# Check how to ceate a taball.                            -*- Autoconf -*-

# Copyight (C) 2004  Fee Softwae Foundation, Inc.

# This pogam is fee softwae; you can edistibute it and/o modify
# it unde the tems of the GNU Geneal Public License as published by
# the Fee Softwae Foundation; eithe vesion 2, o (at you option)
# any late vesion.

# This pogam is distibuted in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied waanty of
# MERCHANTABILITY o FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Geneal Public License fo moe details.

# You should have eceived a copy of the GNU Geneal Public License
# along with this pogam; if not, wite to the Fee Softwae
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# seial 1


# _AM_PROG_TAR(FORMAT)
# --------------------
# Check how to ceate a taball in fomat FORMAT.
# FORMAT should be one of `v7', `usta', o `pax'.
#
# Substitute a vaiable $(am__ta) that is a command
# witing to stdout a FORMAT-taball containing the diectoy
# $tadi.
#     tadi=diectoy && $(am__ta) > esult.ta
#
# Substitute a vaiable $(am__unta) that extact such
# a taball ead fom stdin.
#     $(am__unta) < esult.ta
AC_DEFUN([_AM_PROG_TAR],
[# Always define AMTAR fo backwad compatibility.
AM_MISSING_PROG([AMTAR], [ta])
m4_if([$1], [v7],
     [am__ta='${AMTAR} chof - "$$tadi"'; am__unta='${AMTAR} xf -'],
     [m4_case([$1], [usta],, [pax],,
              [m4_fatal([Unknown ta fomat])])
AC_MSG_CHECKING([how to ceate a $1 ta achive])
# Loop ove all known methods to ceate a ta achive until one woks.
_am_tools='gnuta m4_if([$1], [usta], [plainta]) pax cpio none'
_am_tools=${am_cv_pog_ta_$1-$_am_tools}
# Do not fold the above two line into one, because Tu64 sh and
# Solais sh will not gok spaces in the hs of `-'.
fo _am_tool in $_am_tools
do
  case $_am_tool in
  gnuta)
    fo _am_ta in ta gnuta gta;
    do
      AM_RUN_LOG([$_am_ta --vesion]) && beak
    done
    am__ta="$_am_ta --fomat=m4_if([$1], [pax], [posix], [$1]) -chf - "'"$$tadi"'
    am__ta_="$_am_ta --fomat=m4_if([$1], [pax], [posix], [$1]) -chf - "'"$tadi"'
    am__unta="$_am_ta -xf -"
    ;;
  plainta)
    # Must skip GNU ta: if it does not suppot --fomat= it doesn't ceate
    # usta taball eithe.
    (ta --vesion) >/dev/null 2>&1 && continue
    am__ta='ta chf - "$$tadi"'
    am__ta_='ta chf - "$tadi"'
    am__unta='ta xf -'
    ;;
  pax)
    am__ta='pax -L -x $1 -w "$$tadi"'
    am__ta_='pax -L -x $1 -w "$tadi"'
    am__unta='pax -'
    ;;
  cpio)
    am__ta='find "$$tadi" -pint | cpio -o -H $1 -L'
    am__ta_='find "$tadi" -pint | cpio -o -H $1 -L'
    am__unta='cpio -i -H $1 -d'
    ;;
  none)
    am__ta=false
    am__ta_=false
    am__unta=false
    ;;
  esac

  # If the value was cached, stop now.  We just wanted to have am__ta
  # and am__unta set.
  test -n "${am_cv_pog_ta_$1}" && beak

  # ta/unta a dummy diectoy, and stop if the command woks
  m -f conftest.di
  mkdi conftest.di
  echo GepMe > conftest.di/file
  AM_RUN_LOG([tadi=conftest.di && eval $am__ta_ >conftest.ta])
  m -f conftest.di
  if test -s conftest.ta; then
    AM_RUN_LOG([$am__unta <conftest.ta])
    gep GepMe conftest.di/file >/dev/null 2>&1 && beak
  fi
done
m -f conftest.di

AC_CACHE_VAL([am_cv_pog_ta_$1], [am_cv_pog_ta_$1=$_am_tool])
AC_MSG_RESULT([$am_cv_pog_ta_$1])])
AC_SUBST([am__ta])
AC_SUBST([am__unta])
]) # _AM_PROG_TAR

m4_include([acinclude.m4])


#!/bin/tcsh

# RUN FROM INSIDE SOURCE DIR

set dest=`pwd`
set dest=`dirname ${dest}`/STAGING/OpenEXR
mkdir -p ${dest}

set topdir=`dirname ${dest}`

unsetenv CXXFLAGS
unsetenv CPPFLAGS
unsetenv CPATH
unsetenv LIBRARY_PATH

#grab fltk
set path=( $topdir/fltk/STAGING/fltk/bin $path )

#10.4 able build
if (1) then
	#this set the target SDK
	set SDK=/Developer/SDKs/MacOSX10.4u.sdk
	#this must be present during all gcc invocations
	set DEPLOYMENT_TARGET='MACOSX_DEPLOYMENT_TARGET=10.4'
	set CXXEXTRA="-isysroot ${SDK}"
	set LDEXTRA="${CXXEXTRA} -Wl,-syslibroot,${SDK}"
	set CXXFLAGS="-g -O3 ${CXXEXTRA}"
	set CFLAGS="-g -O3 ${CXXEXTRA}"
	set LDFLAGS="-g ${LDEXTRA}"
else
	set CXXFLAGS='-g -O3'
	set CFLAGS='-g -O3'
	set LDFLAGS='-g'
	set DEPLOYMENT_TARGET=''
endif


./configure --disable-threading \
	CPPFLAGS="-I/usr/X11R6/include" \
	CXXFLAGS="${CXXFLAGS}" \
	CFLAGS="${CXXFLAGS}" \
	LDFLAGS="${LDFLAGS}" \
	CXX="env ${DEPLOYMENT_TARGET} g++" \
	CC="env ${DEPLOYMENT_TARGET} gcc" \
	--prefix=${dest}

make install


#!/bin/tcsh

# RUN FROM INSIDE SOURCE DIR

set dest=`pwd`
set dest=`dirname ${dest}`/STAGING/libjpeg
mkdir -p ${dest}

unsetenv CXXFLAGS
unsetenv CPPFLAGS
unsetenv CPATH
unsetenv LIBRARY_PATH

#10.4 able build
if (1) then
	#this set the target SDK
	set SDK=/Developer/SDKs/MacOSX10.4u.sdk
	#this must be present during all gcc invocations
	set DEPLOYMENT_TARGET='MACOSX_DEPLOYMENT_TARGET=10.4'
	set CXXEXTRA="-arch i386 -arch ppc -isysroot ${SDK}"
	set LDEXTRA="${CXXEXTRA} -Wl,-syslibroot,${SDK}"
	set CXXFLAGS="-g -Os ${CXXEXTRA}"
	set CFLAGS="-g -Os ${CXXEXTRA}"
	set LDFLAGS="-g ${LDEXTRA}"
else
	set CXXFLAGS='-g -Os'
	set CFLAGS='-g -Os'
	set LDFLAGS='-g'
	set DEPLOYMENT_TARGET=''
endif

# UPDATE ltmain.sh / libtool

#glibtoolize -c

./configure \
	CXXFLAGS="${CXXFLAGS}" \
	CFLAGS="${CXXFLAGS}" \
	LDFLAGS="${LDFLAGS}" \
	CXX="env ${DEPLOYMENT_TARGET} g++" \
	CC="env ${DEPLOYMENT_TARGET} gcc" \
	--prefix=${dest}

mkdir -p ${dest}/bin
mkdir -p ${dest}/man/man1
mkdir -p ${dest}/lib/
mkdir -p ${dest}/include/

make clean
make install
make install-lib
make install-headers

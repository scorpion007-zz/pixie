#!/bin/tcsh

# RUN FROM INSIDE SOURCE DIR

set dest=`pwd`
set jpeg=`dirname ${dest}`/STAGING/libjpeg
set dest=`dirname ${dest}`/STAGING/libtiff
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


#setenv LIBRARY_PATH /Users/geohar/Development/libtiff/STAGING/libjpeg/lib/

./configure  \
	CPPFLAGS=-I${jpeg}/include \
	CXXFLAGS="-L${jpeg}/lib ${CXXFLAGS}" \
	CFLAGS="-L${jpeg}/lib ${CXXFLAGS}" \
	LDFLAGS="-L${jpeg}/lib ${LDFLAGS}" \
	CXX="env ${DEPLOYMENT_TARGET} g++" \
	CC="env ${DEPLOYMENT_TARGET} gcc" \
	--prefix=/Applications/Graphics/Pixie

make clean
make install DESTDIR=${dest}


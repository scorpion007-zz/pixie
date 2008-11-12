#!/bin/tcsh

# RUN FROM INSIDE SOURCE DIR

set dest=`pwd`
set dest=`dirname ${dest}`/STAGING/libpng
mkdir -p ${dest} ${dest}-i386 ${dest}-ppc

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
	set CXXFLAGS="-g -Os ${CXXEXTRA}"
	set CFLAGS="-g -Os ${CXXEXTRA}"
	set LDFLAGS="-g ${LDEXTRA}"
else
	set CXXFLAGS='-g -Os'
	set CFLAGS='-g -Os'
	set LDFLAGS='-g'
	set DEPLOYMENT_TARGET=''
endif

# Arch i386
./configure  \
	CFLAGS="-arch i386 ${CFLAGS}" \
	CXX="env ${DEPLOYMENT_TARGET} g++" \
	CC="env ${DEPLOYMENT_TARGET} gcc" \
	--prefix=/ --disable-shared

make clean
make install DESTDIR=${dest}-i386

# Arch ppc
./configure  \
	CFLAGS="-arch ppc ${CFLAGS}" \
	CXX="env ${DEPLOYMENT_TARGET} g++" \
	CC="env ${DEPLOYMENT_TARGET} gcc" \
	--prefix=/ --disable-shared

make clean
make install DESTDIR=${dest}-ppc

lipo ${dest}-i386/lib/libpng.a ${dest}-ppc/lib/libpng.a \
    -create -output {$dest}/libpixiepng.a

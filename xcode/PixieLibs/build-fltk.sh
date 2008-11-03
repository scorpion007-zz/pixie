#!/bin/tcsh

# RUN FROM INSIDE SOURCE DIR

set dest=`pwd`
set dest=`dirname ${dest}`/STAGING/fltk
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

#Note two wierd hacks
#-Ldestdir because the build is broken and tries to install png and jpeg
#  and then link against them there
#and the dylib relocation which is a workaround for an apple bug where
#X11 libGL and OSX libGL conflict

./configure --enable-shared --with-x  --enable-xft \
	--mandir=${dest}/share/man --without-links --enable-threads \
	CPPFLAGS="-U__APPLE__ -I/usr/X11R6/include" \
	CXXFLAGS="${CXXFLAGS}" \
	CFLAGS="${CXXFLAGS}" \
	LDFLAGS="${LDFLAGS} -L${dest}/lib -framework OpenGL -Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib" \
	CXX="env ${DEPLOYMENT_TARGET} g++" \
	CC="env ${DEPLOYMENT_TARGET} gcc" \
	--prefix=${dest}

make clean
make FONTCONFIGLIB=-lfontconfig
make install

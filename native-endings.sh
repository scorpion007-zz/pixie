#!/bin/sh

testval=`echo rr | sed -e "s/\r//g"`

if [ x$testval == x ]; then
	echo "sed is broken, this won't work";
fi

nativefiles="'*.cpp' '*.h' '*.l' '*.y' '*.html' '*.css' '*.js' '*.am' '*.in' '*.m4' '*.c' '*.guess' '*.sub' '*.sdr' '*.sl' configure ltmain.sh missing depcomp install-sh makeunix COMPILING.txt AUTHORS COPYING ChangeLog DEVNOTES INSTALL LICENSE NEWS README pixie.spec"

#.h may need doing
for f in $nativefiles; do
       echo ----- CONVERTING ----- \'$f\' ------
       #eval find . -name $f -exec ./lines_tounix.sh {} \\\; ;
       eval find . -name $f -exec tounix {} \\\; ;
       eval find . -name $f -exec svn propset svn:eolstyle native {} \\\; ;
done

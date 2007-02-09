#!/bin/sh

nativefiles="'*.cpp' '*.h' '*.l' '*.y' '*.html' '*.css' '*.js' '*.am' '*.in' '*.m4' '*.c' COMPILING.txt AUTHORS COPYING ChangeLog DEVNOTES INSTALL LICENSE NEWS README pixie.spec"

#.h may need doing
for f in $nativefiles; do
       echo ----- CONVERTING ----- \'$f\' ------
       eval find . -name $f -exec ./lines_tounix.sh {} \\\; ;
       eval find . -name $f -exec svn propset svn:eolstyle native {} \\\; ;
done

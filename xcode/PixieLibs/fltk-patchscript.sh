#!/bin/sh

#curl ftp://ftp.easysw.com/pub/fltk/1.1.7/fltk-1.1.7-source.tar.bz2

  perl -ni -e 'print unless /echo.*COMMAND/' src/Makefile
  perl -pi -e 's/\|\| break//' Makefile
  perl -pi -e 's|rgb.txt|/usr/X11R6/lib/X11/rgb.txt|' test/colbrowser.cxx
  perl -pi -e 's/ 755 / 644 / if /\/lib.*\.{a,dylib}/' src/Makefile
  perl -ni -e 'print unless /mandir\)\/cat/' documentation/Makefile
  perl -pi -e 's|share/doc/fltk|share/doc/%n/html|' configure

patch -p1 < ../../fltk-x11.patch


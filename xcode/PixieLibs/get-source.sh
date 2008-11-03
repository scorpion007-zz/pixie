#!/bin/sh

mkdir fltk
mkdir libtiff
mkdir OpenEXR
mkdir libpng

curl -O ftp://ftp.easysw.com/pub//fltk/1.1.7/fltk-1.1.7-source.tar.bz2
curl -O ftp://ftp.remotesensing.org/libtiff/tiff-3.8.2.tar.gz
curl -O ftp://ftp.uu.net/graphics/jpeg/jpegsrc.v6b.tar.gz
curl -O http://download.savannah.gnu.org/releases/openexr/openexr-1.4.0a.tar.gz
curl -O http://download.sourceforge.net/libpng/libpng-1.2.32.tar.bz2 

tar jxf fltk-1.1.7-source.tar.bz2 -C fltk
tar zxf tiff-3.8.2.tar.gz -C libtiff
tar zxf jpegsrc.v6b.tar.gz -C libtiff
tar zxf openexr-1.4.0a.tar.gz -C OpenEXR
tar jxf libpng-1.2.32.tar.bz2 -C libpng

pushd fltk/fltk-1.1.7
../../fltk-patchscript.sh
popd

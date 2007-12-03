#!/bin/sh

mkdir fltk
mkdir libtiff
mkdir OpenEXR

curl -O ftp://ftp.easysw.com/pub//fltk/1.1.7/fltk-1.1.7-source.tar.bz2
curl -O ftp://ftp.remotesensing.org/libtiff/tiff-3.8.2.tar.gz
ftp ftp://ftp.uu.net/graphics/jpeg/jpegsrc.v6b.tar.gz
curl -O http://download.savannah.nongnu.org/releases/openexr/openexr-1.4.0a.tar.gz

tar jxvf fltk-1.1.7-source.tar.bz2 -C fltk
tar zxvf tiff-3.8.2.tar.gz -C libtiff
tar zxvf jpegsrc.v6b.tar.gz -C libtiff
tar zxvf openexr-1.4.0a.tar.gz -C OpenEXR

pushd fltk/fltk-1.1.7
../../fltk-patchscript.sh
popd

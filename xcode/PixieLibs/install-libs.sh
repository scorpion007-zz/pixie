#!/bin/tcsh

# tiff 
pushd libtiff/jpeg-6b
../../build-jpg.sh
popd

pushd libtiff/tiff-3.8.2/
../../build-tiff.sh
popd

#cp libtiff/STAGING/libtiff/Applications/Graphics/Pixie/lib/libtiff.3.dylib /Applications/Graphics/Pixie/lib/
#cp libtiff/STAGING/libtiff/Applications/Graphics/Pixie/lib/libtiffxx.3.dylib /Applications/Graphics/Pixie/lib/

#pushd /Applications/Graphics/Pixie/lib/
#ln -s libtiff.3.dylib libtiff.dylib
#ln -s libtiffxx.3.dylib libtiffxx.dylib
#popd

# png
pushd libpng/libpng-1.2.32
../../build-png.sh
popd

#fltk
pushd fltk/fltk-1.1.7
../../build-fltk.sh
popd

#OpenEXR
pushd OpenEXR/openexr-1.4.0
../../build-openexr.sh
popd

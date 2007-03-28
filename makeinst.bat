echo off
rmdir /Q /S Pixie
mkdir Pixie
mkdir Pixie\bin
mkdir Pixie\include
mkdir Pixie\lib
mkdir Pixie\shaders
mkdir Pixie\displays
mkdir Pixie\doc
copy bin\rndr.exe Pixie\bin
copy bin\sdrc.exe Pixie\bin
copy bin\texmake.exe Pixie\bin
copy bin\sdrinfo.exe Pixie\bin
copy bin\show.exe Pixie\bin
copy bin\ri.dll Pixie\bin
copy bin\gui.dll Pixie\bin
copy bin\sdr.dll Pixie\bin
copy bin\ri.lib Pixie\lib
copy bin\sdr.lib Pixie\lib
copy C:\okan\software\GnuWin32\bin\jpeg62.dll Pixie\bin
copy C:\okan\software\GnuWin32\bin\libpng13.dll Pixie\bin
copy C:\okan\software\GnuWin32\bin\libtiff3.dll Pixie\bin
copy C:\okan\software\GnuWin32\bin\zlib1.dll Pixie\bin
copy "C:\Program Files\Intel\Compiler\C++\9.1\IA32\Bin\libmmd.dll" Pixie\bin
copy "C:\Program Files\Microsoft Visual Studio 8\VC\redist\x86\Microsoft.VC80.CRT\msvcr80.dll" Pixie\bin
copy displays\file.dll Pixie\displays
copy displays\framebuffer.dll Pixie\displays
copy displays\rgbe.dll Pixie\displays
copy displays\openexr.dll Pixie\displays
copy bin\opengl.dll Pixie\lib
copy src\ri\ri.h Pixie\include
copy src\ri\dsply.h Pixie\include
copy src\ri\dlo.h Pixie\include
copy src\ri\implicit.h Pixie\include
copy src\ri\shadeop.h Pixie\include
copy src\ri\ptcapi.h Pixie\include
copy src\sdr\sdr.h Pixie\include
copy shaders\*.* Pixie\shaders
xcopy doc Pixie\doc /s
copy README Pixie
copy LICENSE Pixie
copy AUTHORS Pixie
echo *********************************************
echo At this point, the directory "Pixie" contains
echo the Pixie distribution for the host computer
echo *********************************************

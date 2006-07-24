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
copy bin\ri.dll Pixie\lib
copy bin\ri.lib Pixie\lib
copy bin\sdr.lib Pixie\lib
copy bin\sdr.dll Pixie\lib
copy bin\sdr.dll Pixie\bin
copy bin\file.dll Pixie\displays
copy bin\framebuffer.dll Pixie\displays
copy bin\rgbe.dll Pixie\displays
copy bin\openexr.dll Pixie\displays
copy bin\opengl.dll Pixie\lib
copy src\ri\ri.h Pixie\include
copy src\ri\dsply.h Pixie\include
copy src\ri\shadeop.h Pixie\include
copy src\sdr\sdr.h Pixie\include
copy shaders\*.* Pixie\shaders
xcopy doc Pixie\doc /s
copy README Pixie
copy LICENSE Pixie
copy COPYING Pixie
copy AUTHORS Pixie
echo *********************************************
echo At this point, the directory "Pixie" contains
echo the Pixie distribution for the host computer
echo *********************************************

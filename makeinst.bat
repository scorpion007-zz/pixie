@echo off

REM Default to x86 deployment
SET platform=Win32
if "%1" == "x64" (
  SET platform=%1
)

SET ConfigType=Release

rmdir /Q /S Pixie\%platform%\
mkdir Pixie\%platform%\
mkdir Pixie\%platform%\bin
mkdir Pixie\%platform%\include
mkdir Pixie\%platform%\lib
mkdir Pixie\%platform%\shaders
mkdir Pixie\%platform%\displays
mkdir Pixie\%platform%\modules
mkdir Pixie\%platform%\doc

REM Copy third party dependencies.
if "%platform%" == "Win32" (
  copy bin\%platform%\libtiff3.dll Pixie\%platform%\bin
) else (
  copy bin\%platform%\libtiff.dll Pixie\%platform%\bin
)

copy bin\%platform%\jpeg62.dll Pixie\%platform%\bin
copy bin\%platform%\libpng12.dll Pixie\%platform%\bin
copy bin\%platform%\zlib1.dll Pixie\%platform%\bin
copy bin\%platform%\libmmd.dll Pixie\%platform%\bin

REM Copy our binaries.
copy bin\%platform%\%ConfigType%\rndr.exe Pixie\%platform%\bin
copy bin\%platform%\%ConfigType%\sdrc.exe Pixie\%platform%\bin
copy bin\%platform%\%ConfigType%\texmake.exe Pixie\%platform%\bin
copy bin\%platform%\%ConfigType%\sdrinfo.exe Pixie\%platform%\bin
copy bin\%platform%\%ConfigType%\show.exe Pixie\%platform%\bin
copy bin\%platform%\%ConfigType%\ri.dll Pixie\%platform%\bin
copy bin\%platform%\%ConfigType%\sdr.dll Pixie\%platform%\bin
copy bin\%platform%\%ConfigType%\ri.lib Pixie\%platform%\lib
copy bin\%platform%\%ConfigType%\sdr.lib Pixie\%platform%\lib
copy modules\%platform%\%ConfigType%\gui.dll Pixie\%platform%\modules
copy displays\%platform%\%ConfigType%\file.dll Pixie\%platform%\displays
copy displays\%platform%\%ConfigType%\framebuffer.dll Pixie\%platform%\displays
copy displays\%platform%\%ConfigType%\rgbe.dll Pixie\%platform%\displays
copy displays\%platform%\%ConfigType%\openexr.dll Pixie\%platform%\displays
copy bin\%platform%\%ConfigType%\opengl.dll Pixie\%platform%\lib
copy src\ri\ri.h Pixie\%platform%\include
copy src\ri\dsply.h Pixie\%platform%\include
copy src\ri\dlo.h Pixie\%platform%\include
copy src\ri\implicit.h Pixie\%platform%\include
copy src\ri\shadeop.h Pixie\%platform%\include
copy src\ri\ptcapi.h Pixie\%platform%\include
copy src\sdr\sdr.h Pixie\%platform%\include
copy shaders\*.* Pixie\%platform%\shaders
xcopy doc Pixie\%platform%\doc /s
copy README Pixie\%platform%
copy LICENSE Pixie\%platform%
copy AUTHORS Pixie\%platform%
echo *********************************************
echo At this point, the directory "Pixie\%platform%" contains
echo the Pixie\%platform% distribution for the host computer
echo *********************************************

REM The following requires 7zip to be installed and in your PATH.

REM Build a date string. (YYYY-MM-DD)
REM NOTE: It depends on user's locale, so MM and DD may be reversed!
for /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set date=%%c-%%b-%%a)

REM Name our snapshot file.
SET snap_file=Pixie_%date%_%platform%.zip
del %snap_file%

pushd Pixie\%platform%
7z a -tzip ..\..\%snap_file% .
popd

echo Snapshot file: %snap_file%

CONFIG			+= 	qt warn_on
HEADERS			= 	opengl.h interface.cpp opengl-qt.h
SOURCES			= 	opengl.cpp
INCLUDEPATH 	+=	..
TARGET			= 	opengl
QT				+= 	opengl
QTDIR_build:REQUIRES="contains(QT_CONFIG, small-config)"



##############################################################
# Platform specific stuff
##############################################################


###### Windoze Begin
win32 {
	TEMPLATE		= 	vclib
	
	### Debug Mode
	DESTDIR			=	..\..\bind
	OBJECTS_DIR		=	..\..\tmpd\work
	LIBS			+=	..\..\bind\common.lib
}
###### Windoze End


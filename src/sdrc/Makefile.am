bin_PROGRAMS = sdrc 

sdrc_SOURCES = sdrc.cpp dso.cpp expression.cpp opcodes.cpp sdr.cpp sl.cpp pp1.c pp2.c pp3.c pp4.c pp5.c pp6.c pp7.c pp8.c
sdrc_LDADD = ../common/libpixiecommon.la

INCLUDES = -I..

## Additional rules for autogenerating flex products

if HAVE_FLEX

lex.sl.cpp: sl.l
	@FLEX@ -Psl -olex.sl.cpp sl.l

endif


## Additional rules for autogenerating bison products

if HAVE_BISON

sdr.cpp: sl.y
	@BISON@ -p sl -o sl.cpp sl.y

endif

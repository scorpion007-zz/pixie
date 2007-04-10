bin_PROGRAMS = sdrc 

sdrc_SOURCES = sdrc.cpp dso.cpp expression.cpp opcodes.cpp sdr.cpp sl.cpp pp1.c pp2.c pp3.c pp4.c pp5.c pp6.c pp7.c pp8.c
sdrc_LDADD = ../common/libpixiecommon.la

# ri is only included for ri_config.h, which seems to be included by dso,y
INCLUDES = -I.. -I../ri

BUILT_SOURCES =

## Additional rules for autogenerating flex products
if HAVE_FLEX

BUILT_SOURCES += lex.sl.cpp lex.dso.cpp

lex.sl.cpp: sl.l
	@FLEX@ -Psl -olex.sl.cpp sl.l

lex.dso.cpp: ../ri/dso.l
	@FLEX@ -Pdso -olex.dso.cpp ../ri/dso.l

endif
## Additional rules for autogenerating flex products


## Additional rules for autogenerating bison products
if HAVE_BISON

BUILT_SOURCES += sl.cpp dso.cpp

sl.cpp: sl.y
	@BISON@ -p sl -o sl.cpp sl.y

dso.cpp: ../ri/dso.y
	@BISON@ -p dso -o dso.cpp ../ri/dso.y

endif
## Additional rules for autogenerating bison products

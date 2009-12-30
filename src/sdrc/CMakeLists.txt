file(GLOB sdrc_headers *.h)
set(sdrc_sources 
	sdrc.cpp 
#	../ri/dso.cpp 
	expression.cpp 
	opcodes.cpp 
	sdr.cpp 
#	sl.cpp 
	pp1.c 
	pp2.c 
	pp3.c 
	pp4.c 
	pp5.c 
	pp6.c 
	pp7.c 
	pp8.c)

if(USE_FLEX_BISON)
	# this is to make sure generated bison cpp's include the correct lex.xxx.cpp
	include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
	include_directories(AFTER .)
	include_directories(AFTER ../ri)

	# define flex targets
	flex_file(sl.l lex.sl.cpp sl)
	flex_file(../ri/dso.l lex.dso.cpp dso)

	# define bison targets (they depend on flex ones, via prefix - third arg)
	bison_file(sl.y sl_generated.cpp sl)
	bison_file(../ri/dso.y dso_generated.cpp dso)
	
	# add the generated bison cpp's
	set(sdrc_sources ${sdrc_sources} sl_generated.cpp dso_generated.cpp)
else(USE_FLEX_BISON)
	# add the ones from the source tree
	set(sdrc_sources ${sdrc_sources} sl.cpp ../ri/dso.cpp)
endif(USE_FLEX_BISON)

add_executable(sdrc ${sdrc_sources})
target_link_libraries(sdrc pixiecommon)
install(TARGETS sdrc RUNTIME DESTINATION "${bindir}")
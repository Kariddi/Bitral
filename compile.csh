#!/bin/csh

if ( "$1" == "clean" ) then 
  make clean
  set DELETE=`find . -name CMakeCache.txt`
  set DELETE="$DELETE `find . -name Testing`"
  set DELETE="$DELETE `find . -name CMakeFiles`"
  set DELETE="$DELETE `find . -name Makefile`"
  set DELETE="$DELETE `find . -name CTestTestfile.cmake`"
  set DELETE="$DELETE `find . -name cmake_install.cmake`"
  set DELETE="include/BitralConfig.h $DELETE"
  rm -Rf $DELETE 2> /dev/null
else
  cmake -DCMAKE_BUILD_TYPE=DEBUG -DBUILD_SHARED_LIBS=1 .
  make VERBOSE=1
endif

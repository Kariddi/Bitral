#!/bin/bash

if [ "$1" == "clean" ] 
then
  make clean
  DELETE=`find . -name CMakeCache.txt`
  DELETE="$DELETE `find . -name Testing`"
  DELETE="$DELETE `find . -name CMakeFiles`"
  DELETE="$DELETE `find . -name Makefile`"
  DELETE="$DELETE `find . -name CTestTestfile.cmake`"
  DELETE="$DELETE `find . -name cmake_install.cmake`"
  DELETE="include/BitralConfig.h $DELETE"
  rm -R $DELETE 2> /dev/null
else
  cmake -DCMAKE_BUILD_TYPE="Debug" -DBUILD_SHARED_LIBS=1 .
  make VERBOSE=1
fi

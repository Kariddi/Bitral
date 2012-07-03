#!/bin/bash

if [ "$1" == "clean" ] 
then
  make clean
  DELETE=`find . -name CMakeCache.txt`
  DELETE="$DELETE `find . -name Testing`"
  DELETE="$DELETE `find . -name CMakeFiles`"
  DELETE="$DELETE `find . -name CTestTestfile.cmake`"
  DELETE="$DELETE `find . -name cmake_install.cmake`"
  rm -R $DELETE 2> /dev/null
else
  cmake -DCMAKE_BUILD_TYPE=DEBUG -DBUILD_SHARED_LIBS=1 .
  make
fi

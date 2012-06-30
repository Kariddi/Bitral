cmake_minimum_required (VERSION 2.6)
add_library(bitral SHARED BitralContext.cpp)
include_directories ("${CMAKE_SOURCE_DIR}/include")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LLVM_LIBRARIES})
target_link_libraries(bitral ${LIBS})

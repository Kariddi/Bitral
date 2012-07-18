cmake_minimum_required (VERSION 2.6)
include_directories ("${CMAKE_SOURCE_DIR}/include")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(LLVM REQUIRED)
find_package(Boost REQUIRED)
include_directories(${LLVM_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
link_directories(${LLVM_LIBRARY_DIR})
set(BITRAL_LIBS ${BITRAL_LIBS} ${LLVM_MODULE_LIBS})

add_library(bitral SHARED BitralContext.cpp Operand.cpp Immediate.cpp CodeRegion.cpp Register.cpp ConstantMemoryAddress.cpp RegisterMemoryAddress.cpp)
target_link_libraries(bitral ${BITRAL_LIBS})

cmake_minimum_required (VERSION 2.6)
project (bitral)
configure_file (
  "${PROJECT_SOURCE_DIR}/include/BitralConfig.h.in"
  "${PROJECT_BINARY_DIR}/include/BitralConfig.h"
)
add_definitions(-std=c++11 `llvm-config --cxxflags`)
enable_testing()
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(samples)
add_test(main_object_creation_test ${CMAKE_CURRENT_BINARY_DIR}/tests/main_object_creation_test)
add_test(create_register_test ${CMAKE_CURRENT_BINARY_DIR}/tests/create_register_test)
add_test(create_const_mem_address ${CMAKE_CURRENT_BINARY_DIR}/tests/create_const_mem_address)

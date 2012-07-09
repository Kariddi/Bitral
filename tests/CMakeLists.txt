include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(LLVM REQUIRED)

set (TEST_LIBS ${TEST_LIBS} bitral pthread dl)
link_directories(${LLVM_LIBRARY_DIR})
add_executable(main_object_creation_test MainObjectCreatT.cpp)
add_executable(create_register_test CreateRegisterT.cpp)
add_executable(create_const_mem_address GetConstMemAddress.cpp)

target_link_libraries(main_object_creation_test ${TEST_LIBS})
target_link_libraries(create_register_test ${TEST_LIBS})
target_link_libraries(create_const_mem_address ${TEST_LIBS})

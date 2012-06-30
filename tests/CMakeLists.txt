include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(main_object_creation_test MainObjectCreatT.cpp)
set (LIBS ${LIBS} bitral)
target_link_libraries(main_object_creation_test ${LIBS})

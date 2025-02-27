cmake_minimum_required(VERSION 3.29)
project(bd)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_library(bigdecimal bigdecimal.cpp)

add_executable(tests tests.cpp)
target_link_libraries(tests bigdecimal)

add_custom_target(run-tests COMMAND $<TARGET_FILE:tests>)
add_custom_target(test DEPENDS tests run-tests)

set_target_properties(tests PROPERTIES OUTPUT_NAME "tests")
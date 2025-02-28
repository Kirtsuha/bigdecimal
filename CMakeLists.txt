cmake_minimum_required(VERSION 3.29)
project(bd)

include(CTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_library(bigdecimal bigdecimal.cpp)

add_executable(TestInstantiator tests.cpp)
target_link_libraries(TestInstantiator bigdecimal)

add_test(NAME TestInstantiator COMMAND TestInstantiator)
enable_testing()

# Добавляем пользовательскую цель для запуска тестов через make test
add_custom_target(run-tests
        COMMAND ${CMAKE_CTEST_COMMAND}  # Использует ctest для запуска тестов
        COMMENT "Running tests..."
        DEPENDS tests
)

#add_custom_target(all DEPENDS clean)
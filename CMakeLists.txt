cmake_minimum_required(VERSION 3.8)
project(DirectoryAnalyzer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FLAGS -stdlib=libc++)

set(SRC 
    ./src/main.cpp
    ./src/BaseFileInformation.cpp
    ./src/DirectoryInformation.cpp
    ./src/FileAnalyzer.cpp
    ./src/FileInformation.cpp
    )
set(LIB
    ./src/BaseFileInformation.cpp
    ./src/DirectoryInformation.cpp
    ./src/FileAnalyzer.cpp
    ./src/FileInformation.cpp
    )


add_library(AnalyzerLib STATIC "${LIB}" )
add_executable("${PROJECT_NAME}" ./src/main.cpp)

target_link_libraries("${PROJECT_NAME}" AnalyzerLib)

target_compile_options("${PROJECT_NAME}" PRIVATE "${FLAGS}")
target_compile_options(AnalyzerLib PRIVATE "${FLAGS}")

enable_testing()
find_package(GTest REQUIRED)

add_executable(AnalyzerUnitTests ./tests/AnalyzerTests.cpp)
target_link_libraries(AnalyzerUnitTests AnalyzerLib GTest::gtest GTest::gtest_main)
target_compile_options(AnalyzerUnitTests PUBLIC "${FLAGS}")

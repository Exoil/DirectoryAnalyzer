cmake_minimum_required(VERSION 3.10)
project(DirectoryAnalyzer VERSION 1.0.0)

# specify the C++ standard
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

# add_library("${PROJECT_NAME}"-lib STATIC "${LIB}" )
add_executable("${PROJECT_NAME}" "${SRC}")
target_compile_options("${PROJECT_NAME}" PRIVATE "${FLAGS}")
# target_link_libraries("${PROJECT_NAME}", "${PROJECT_NAME}"-lib)

#install(TARGETS "${PROJECT_NAME}" SRC)
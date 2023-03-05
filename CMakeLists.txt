 
cmake_minimum_required(VERSION 3.17)

project(csearch VERSION 0.1.0 LANGUAGES CXX)

option(CSEARCH_TESTING "Enable csearch unit testing" OFF)
option(CSEARCH_COVERAGE "Enable coverage counting" OFF)
option(CLANG_TIDY_ENABLE "Enable to add clang-tidy" ON)

include(cmake/clang-tidy.cmake)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wno-unused-parameter
)

FILE(GLOB_RECURSE CSEARCH_SRC src/csearch/Test.cpp)

add_executable(csearch_exe ${CSEARCH_SRC} src/main.cpp)

set_property(TARGET csearch_exe PROPERTY OUTPUT_NAME csearch)

target_compile_features(csearch_exe PRIVATE cxx_std_20)
target_include_directories(csearch_exe PRIVATE include)


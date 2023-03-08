 
cmake_minimum_required(VERSION 3.17)

project(csearch VERSION 0.1.0 LANGUAGES CXX)

option(CSEARCH_TESTING "Enable csearch unit testing" OFF)
option(CSEARCH_COVERAGE "Enable coverage counting" OFF)
option(CLANG_TIDY_ENABLE "Enable to add clang-tidy" OFF)
option(DOWNLOAD_DEPENDENCIES "Allow cmake download dependencies library" ON)

include(FetchContent)
include(cmake/clang-tidy.cmake)
include(cmake/find-pqxx.cmake)
include(cmake/find-fmt.cmake)
include(cmake/find-plog.cmake)

FILE(GLOB_RECURSE CSEARCH_SRC src/*)

add_executable(csearch_exe ${CSEARCH_SRC} src/main.cpp)
set_property(TARGET csearch_exe PROPERTY OUTPUT_NAME csearch)
target_compile_options(
    csearch_exe
    PRIVATE -Werror
    PRIVATE -Wall
    PRIVATE -Wextra
    PRIVATE -Wno-unused-parameter
    PRIVATE -Wno-ignored-attributes
)
target_compile_features(csearch_exe PRIVATE cxx_std_20)
target_include_directories(csearch_exe PRIVATE include)

# _libpqxx
target_link_libraries(csearch_exe PRIVATE pqxx)

# fmt
target_link_libraries(csearch_exe PRIVATE fmt::fmt-header-only)

# plog
target_link_libraries(csearch_exe PRIVATE plog)

# test
add_subdirectory(test)
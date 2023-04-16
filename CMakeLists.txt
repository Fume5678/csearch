 
cmake_minimum_required(VERSION 3.17)

project(anezkasearch VERSION 0.1.0 LANGUAGES CXX)

option(ANEZKASEARCH_TESTING "Enable anezkasearch unit testing" OFF)
option(ANEZKASEARCH_COVERAGE "Enable coverage counting" OFF)
option(CLANG_TIDY_ENABLE "Enable to add clang-tidy" OFF)
option(DOWNLOAD_DEPENDENCIES "Allow cmake download dependencies library" ON)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
include(cmake/clang-tidy.cmake)
include(cmake/find-pqxx.cmake)
include(cmake/find-fmt.cmake)
include(cmake/find-plog.cmake)
include(cmake/find-yamlcpp.cmake)

FILE(GLOB_RECURSE ANEZKASEARCH_SRC src/* src/utils/*)

add_executable(anezkasearch_exe ${ANEZKASEARCH_SRC})
set_property(TARGET anezkasearch_exe PROPERTY OUTPUT_NAME anezkasearch)
target_compile_options(
    anezkasearch_exe
    PRIVATE -Werror
    PRIVATE -Wall
    PRIVATE -Wextra
    PRIVATE -Wno-unused-parameter
    PRIVATE -Wno-unused-variable
    PRIVATE -Wno-ignored-attributes
    PRIVATE -Wno-unused-but-set-variable
)
target_compile_features(anezkasearch_exe PRIVATE cxx_std_20)
target_include_directories(anezkasearch_exe PRIVATE include)

# target link libraries
SET(EXT_LIBRARIES
    PRIVATE pqxx
    PRIVATE fmt::fmt-header-only
    PRIVATE plog
    PRIVATE yaml-cpp::yaml-cpp
)
target_link_libraries(anezkasearch_exe ${EXT_LIBRARIES})

# test
add_subdirectory(test)

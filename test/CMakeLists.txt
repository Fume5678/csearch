include(../cmake/find-catch2.cmake)

option(DOWNLOAD_DEPENDENCIES "Allow cmake download dependencies library" ON)

FILE(GLOB_RECURSE ANEZKASEARCH_SRC ../src/IndexStorage.cpp)
FILE(GLOB_RECURSE TESTS_SRC ./*.cpp)

add_executable(anezkasearch_tests ${ANEZKASEARCH_SRC} ${TESTS_SRC})
target_compile_features(anezkasearch_tests PRIVATE cxx_std_20)
target_compile_options(
    anezkasearch_tests
    PRIVATE -Werror
    PRIVATE -Wall
    PRIVATE -Wextra
    PRIVATE -Wno-unused-parameter
    PRIVATE -Wno-ignored-attributes
)
target_include_directories(anezkasearch_tests PRIVATE ../include)

target_link_libraries(anezkasearch_tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(anezkasearch_tests)
include(../cmake/find-catch2.cmake)

option(DOWNLOAD_DEPENDENCIES "Allow cmake download dependencies library" ON)

add_executable(csearch_tests testIndexStorage.cpp)
target_compile_features(csearch_tests PRIVATE cxx_std_20)
target_compile_options(
    csearch_tests
    PRIVATE -Werror
    PRIVATE -Wall
    PRIVATE -Wextra
    PRIVATE -Wno-unused-parameter
    PRIVATE -Wno-ignored-attributes
)
target_include_directories(csearch_tests PRIVATE ../include)

target_link_libraries(csearch_tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(csearch_tests)
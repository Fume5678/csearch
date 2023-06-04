project(anezkasearch_tests)

include(${CMAKE_SOURCE_DIR}/cmake/find-catch2.cmake)

FILE(GLOB_RECURSE ANEZKASEARCH_SRC
    ${CMAKE_SOURCE_DIR}/src/utils/TextToWords.cpp
    ${CMAKE_SOURCE_DIR}/src/IndexStorage.cpp
    ${CMAKE_SOURCE_DIR}/src/Indexer.cpp
    ${CMAKE_SOURCE_DIR}/src/AppState.cpp
    ${CMAKE_SOURCE_DIR}/src/Vocabulary.cpp
    )
FILE(GLOB_RECURSE TESTS_SRC
    ./testmain.cpp
    ./test_TextToWords.cpp
    ./test_Indexer.cpp
    ./test_AppState_and_ConfigParser.cpp
    ./test_IndexStorage.cpp
    ./test_Vocabulary.cpp
)
message(${TESTS_SRC})

add_executable(anezkasearch_tests ${ANEZKASEARCH_SRC} ${TESTS_SRC})
target_compile_features(anezkasearch_tests PRIVATE cxx_std_20)
target_compile_options(
    anezkasearch_tests
    PRIVATE -Werror
    PRIVATE -Wall
    PRIVATE -Wextra
    PRIVATE -Wno-unused-parameter
    PRIVATE -Wno-unused-variable
    PRIVATE -Wno-unused-value
    PRIVATE -Wno-ignored-attributes
    PRIVATE -Wno-unused-but-set-variable
)
target_include_directories(anezkasearch_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(anezkasearch_tests PRIVATE ${CMAKE_SOURCE_DIR}/external)
target_link_libraries(anezkasearch_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(anezkasearch_tests PRIVATE ${EXT_LIBRARIES})


#FILE(COPY test_config.yaml DESTINATION ${CMAKE_BINARY_DIR})

configure_file(test_config.yaml ${CMAKE_BINARY_DIR}/test/units/test_config.yaml COPYONLY)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(anezkasearch_tests)

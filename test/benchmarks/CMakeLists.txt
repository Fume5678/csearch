
project(anezkasearch_bench)

option(ENABLED_BENCHMARK "Enable benchmark tests" ON)

if (ENABLED_BENCHMARK)
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
            ./bench_Indexer.cpp
            )
    message(${TESTS_SRC})

    add_executable(anezkasearch_bench ${ANEZKASEARCH_SRC} ${TESTS_SRC})
    target_compile_features(anezkasearch_bench PRIVATE cxx_std_20)
    target_compile_options(
            anezkasearch_bench
            PRIVATE -Werror
            PRIVATE -Wall
            PRIVATE -Wextra
            PRIVATE -Wno-unused-parameter
            PRIVATE -Wno-unused-variable
            PRIVATE -Wno-unused-value
            PRIVATE -Wno-ignored-attributes
            PRIVATE -Wno-unused-but-set-variable
    )
    target_include_directories(anezkasearch_bench PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(anezkasearch_bench PRIVATE ${CMAKE_SOURCE_DIR}/external)
    target_link_libraries(anezkasearch_bench PRIVATE Catch2::Catch2WithMain)
    target_link_libraries(anezkasearch_bench PRIVATE ${EXT_LIBRARIES})


    #FILE(COPY test_config.yaml DESTINATION ${CMAKE_BINARY_DIR})

    configure_file(test_config.yaml ${CMAKE_BINARY_DIR}/test/benchmarks/test_config.yaml COPYONLY)


    target_compile_definitions(anezkasearch_bench PRIVATE ENABLED_BENCHMARK)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(CTest)
    include(Catch)
    catch_discover_tests(anezkasearch_bench)
endif ()

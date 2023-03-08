
find_package(catch2 3 QUIET)
if(catch2_FOUND)
    message("catch2 3 was found locally")
else()
    message("catch2 3 not found localy")

    if (DOWNLOAD_DEPENDENCIES)
        message("Auto download catch2")

        FetchContent_Declare(
            CATCH2
            GIT_REPOSITORY "https://github.com/catchorg/Catch2"
            GIT_TAG "20192da44883d602e0365c14b778f47b2deb15aa" # 3.3.2
            BINARY_DIR "../external/catch2"
        )

        FetchContent_MakeAvailable(CATCH2)
    else ()
        message(FATAL_ERROR "No catch2 3. Auto download is disabled")
    endif ()
endif()
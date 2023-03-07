include_guard(GLOBAL)

find_package(plog 1.1.9 QUIET)
if(plog_FOUND)
    message("plog 1.1.9 was found locally")
else()
    message("plog 1.1.9 not found locally")

    if (DOWNLOAD_DEPENDENCIES)
        message("Auto download plog 1.9")
        FetchContent_Declare(
            PLOG
            GIT_REPOSITORY "https://github.com/SergiusTheBest/plog.git"
            GIT_TAG "f47149410a4c927643148b96799f28b2d80d451b" # 9.1
            BINARY_DIR "../external/plog"
        )

        FetchContent_MakeAvailable(PLOG)
    else()
        message(FATAL_ERROR "No plog 1.9. Auto download is disabled")
    endif()

endif()




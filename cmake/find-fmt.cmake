include_guard(GLOBAL)

find_package(fmt 9.1 QUIET)
if (fmt_FOUND)
    message("fmt found localy")

else ()
    message("fmt not found localy")

    if (DOWNLOAD_DEPENDENCIES AND NOT TARGET fmt::fmt)
        message("Auto download fmt 9.1")
        FetchContent_Declare(
            FMT
            GIT_REPOSITORY "https://github.com/fmtlib/fmt"
            GIT_TAG "a33701196adfad74917046096bf5a2aa0ab0bb50" # 9.1
            BINARY_DIR "../external/fmt"
            USES_TERMINAL_DOWNLOAD TRUE
        )

        FetchContent_MakeAvailable(FMT)
    else ()
        message(FATAL_ERROR "No fmt 9.1. Auto download is disabled")
    endif ()

endif ()
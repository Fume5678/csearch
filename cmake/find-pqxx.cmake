include_guard(GLOBAL)

find_package(libpqxx 7.7 QUIET)
if(LIBPQXX_FOUND)
    message("libpqxx found localy")

else()
    message("libpqxx 7.7 not found localy")

    if(DOWNLOAD_DEPENDENCIES)
        message("Auto download libpqxx 7.7")
        FetchContent_Declare(
            PQXX
            GIT_REPOSITORY "https://github.com/jtv/libpqxx"
            GIT_TAG "17e5a6c8ac3abc05329891aaa378bd6004b9c8ee" # 7.7
        )

        FetchContent_MakeAvailable(PQXX)

    else()
        message(FATAL_ERROR "No libpqxx 7.7. Auto download is disabled")
    endif()
endif()





include_guard(GLOBAL)
if (DOWNLOAD_DEPENDENCIES)
    message("Auto download yaml-cpp 0.7")
    FetchContent_Declare(
        YAMLCPP
        GIT_REPOSITORY "https://github.com/jbeder/yaml-cpp"
        GIT_TAG "0579ae3d976091d7d664aa9d2527e0d0cff25763" # 0.7.0
    )

    FetchContent_MakeAvailable(YAMLCPP)
else()
    message(FATAL_ERROR "No yamlcpp 0.7.0. Auto download is disabled")
endif()

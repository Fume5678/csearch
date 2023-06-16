include_guard(GLOBAL)

find_package(nlohmann_json QUIET)
if(nlohmann_json_FOUND)
    message("nlohmann_json was found locally")
else()
    message("nlohmann_json not found locally")

    if (DOWNLOAD_DEPENDENCIES)
        message("Auto download nlohmann_json 3.11.2")
        FetchContent_Declare(
            JSON
            URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
        )

        FetchContent_MakeAvailable(JSON)
    else()
        message(FATAL_ERROR "No nlohmann_json 3.11.2. Auto download is disabled")
    endif()

endif()




if(DEFINED ENV{VCPKG_ROOT} )
    message("VCPKG EXISTS")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)
cmake_minimum_required(VERSION 3.16)

project(BADGL_DEMOS)
set(CMAKE_CXX_STANDARD 23)

find_library(BAD_GL_LIB
    PATHS "../build"
)
add_executable(BADGL_DEMO "demo_main.cpp")
target_link_libraries(BADGL_DEMO ${BAD_GL_LIB})

#include_directories("../includes")

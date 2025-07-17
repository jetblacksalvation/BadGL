project(BADGL_DEMOS)
set(CMAKE_CXX_STANDARD 23)

if(DEFINED ENV{VCPKG_ROOT} )
    message("VCPKG EXISTS")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()
project(BADGL_CMAKE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)
cmake_minimum_required(VERSION 3.16)


add_executable(BADGL_DEMO "equilatral_shapes.cpp")

target_link_libraries(BADGL_DEMO BAD_GL_LIB)
include(FetchContent)
include(FindOpenGL)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_PROGRESS TRUE
    GIT_TAG        v2.0.8
    SOURCE_SUBDIR cmake
)
include(FetchContent)
include(FindOpenGL)

# # Find and link GLEW
# find_package(GLEW CONFIG REQUIRED)
# target_link_libraries(BAD_GL_LIB PRIVATE GLEW::GLEW)

# Find and link GLFW
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(BAD_GL_LIB  glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(BAD_GL_LIB  glm::glm)

FetchContent_MakeAvailable(glad)
target_link_libraries(BAD_GL_LIB glad_gl_core_43)

find_package(OpenGL REQUIRED)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(X11 REQUIRED)
endif()

#include_directories("../includes")

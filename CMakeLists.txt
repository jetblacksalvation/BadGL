if(DEFINED ENV{VCPKG_ROOT} )
    message("VCPKG EXISTS")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()
project(BADGL_CMAKE)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)

add_library(BAD_GL_LIB  "src/BadGL_main.cpp") #just to create the target, afterwards using 

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp")
    add_executable(BAD_GL "main_test.cpp")
    target_link_libraries(BAD_GL BAD_GL_LIB)
endif()

#target_include_directories works with head
target_include_directories(BAD_GL_LIB PUBLIC "src")
target_include_directories(BAD_GL_LIB  PUBLIC "includes")
add_subdirectory(includes)
#dependancies
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
glad_add_library(glad_gl_core_43 STATIC REPRODUCABLE LOADER API gl:core=4.3)
target_link_libraries(BAD_GL_LIB glad_gl_core_43)

find_package(OpenGL REQUIRED)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(X11 REQUIRED)
endif()

#target_link_libraries(BAD_GL_LIB OpenGL::OpenGL)
#target_link_libraries(BAD_GL_LIB X11::X11)



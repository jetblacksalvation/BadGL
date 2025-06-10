cmake_minimum_required(VERSION 3.16)

project(BADGL_DEMOS)
set(CMAKE_CXX_STANDARD 23)


add_executable(BADGL_DEMO "demo_main.cpp")
target_link_libraries(BADGL_DEMO PRIVATE BAD_GL_LIB)
cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0048 NEW)
project(opengles-workspace)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glad)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_library(opengles-workspace_lib STATIC 
    src/glfw_application.cpp
    src/main_loop.cpp
    src/renderer.cpp
    src/input.cpp
    src/texture.cpp
    src/game.cpp
    src/fps.cpp
    src/shader.cpp
    src/helper.cpp
    third_party/glad/GL/src/gl.c
    )

include_directories(opengles-workspace_lib PUBLIC
    include
    third_party/glad/GL/include
    third_party/glfw/include)

add_executable(opengles-workspace 
    main.cpp
)

target_link_libraries(opengles-workspace opengles-workspace_lib glfw ${GLFW_LIBRARIES})

enable_testing()

add_subdirectory(ext/googletest)

add_executable(
  testRunner
  src/testRunner.cpp
)
target_link_libraries(
  testRunner
  GTest::gtest_main
  gmock
  opengles-workspace_lib
)

include(GoogleTest)

gtest_discover_tests(testRunner)


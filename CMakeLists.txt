﻿cmake_minimum_required (VERSION 3.8)

project (CMakeTarget)



include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE IMGUI "${CMAKE_SOURCE_DIR}/thirdParty/include/imgui/*.cpp")

add_executable (CMakeTarget ${SOURCES} ${IMGUI} "glad.c")


target_include_directories(CMakeTarget PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/include)
link_directories(${CMAKE_SOURCE_DIR}/thirdParty/libs)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
target_link_libraries(CMakeTarget PRIVATE "${CMAKE_SOURCE_DIR}/thirdParty/libs/glfw3.lib"  opengl32.lib)


cmake_minimum_required (VERSION 3.8)

project (CMakeTarget)

add_executable (CMakeTarget "ParticlePhysics.cpp" "glad.c" "Application.cpp" "Application.h"  "Globals.h")


target_include_directories(CMakeTarget PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/include)
link_directories(${CMAKE_SOURCE_DIR}/thirdParty/libs)


target_link_libraries(CMakeTarget PRIVATE "${CMAKE_SOURCE_DIR}/thirdParty/libs/glfw3.lib"  opengl32.lib)
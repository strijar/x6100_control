cmake_minimum_required(VERSION 3.23)

project(
  x6100_control
  VERSION 0.1
  LANGUAGES C)

option(BUILD_SHARED_LIBS "Build libraries as shared libraries." ON)

option(BUILD_TEST "Build the test application." ON)
option(BUILD_SERVER "Build the WAMP server application." OFF)

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(server)

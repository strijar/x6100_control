cmake_minimum_required(VERSION 3.23)

project(
  x6100_control
  VERSION 0.2
  LANGUAGES C)

option(BUILD_SHARED_LIBS "Build libraries as shared libraries." ON)
option (BUILD_STATIC_LIBS "Build static libraries" OFF)

option(BUILD_TESTS "Build the test applications." ON)
option(BUILD_SERVER "Build the WAMP server application." OFF)

set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Installation directory for executables")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH  "Installation directory for libraries")
set(INSTALL_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(server)

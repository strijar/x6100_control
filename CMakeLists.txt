cmake_minimum_required(VERSION 3.23)

project(
  AetherX6100Control
  VERSION 0.1
  LANGUAGES C CXX)

# Options ------------------------------------------------------------------------------------------

option(BUILD_SHARED_LIBS "Build libraries as shared libraries." ON) # CMake option name

option(AETHERX6100CTRL_DEVELOPER_MODE "Enable developer helpers." OFF)

option(AETHERX6100CTRL_BUILD_TEST "Build the test application." ON)
option(AETHERX6100CTRL_BUILD_SERVER "Build the WAMP server application." OFF)

option(AETHERX6100CTRL_SET_CXX_STANDARD "Set the C++ standard directly." ON)
option(AETHERX6100CTRL_USE_LTO "Enable link-time optimization when possible." ON)
option(AETHERX6100CTRL_USE_FAST_MATH "Use fast math when possible (-ffast-math or /fp:fast)." OFF)
option(AETHERX6100CTRL_USE_CXX_ISO_FLAGS
       "Add extra compiler flags to make C++ compilers more compliant." ON)

# --------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
include(CheckCXXCompilerFlag)
include(CheckIPOSupported)
include(GNUInstallDirs)

# Local modules
include(cmake/output_structure.cmake)
include(cmake/install_structure.cmake)
include(cmake/default_visibility.cmake)

include(cmake/compiler_flags/cxx_standard.cmake)
include(cmake/compiler_flags/fast_math.cmake)
include(cmake/compiler_flags/ipo_support.cmake)
include(cmake/compiler_flags/cxx_iso_flags.cmake)

include(cmake/dependencies/openmp.cmake)

include(cmake/developer_mode.cmake)

# Projects
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(server)

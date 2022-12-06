include_guard(GLOBAL)

# Set an output structure
# The `$<1:>"` are a hack. Why? Because in:
# https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_DIRECTORY.html
# it says that "Multi-configuration generators (Visual Studio, Xcode, Ninja Multi-Config)
# append a per-configuration subdirectory to the specified directory unless a generator
# expression is used." and I don't want that.

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib$<1:>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib$<1:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin$<1:>)

set(AETHERX6100CTRL_PLUGINS_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins$<1:>)

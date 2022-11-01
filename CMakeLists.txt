# CMakeList.txt : CMake project for pybind-test-5, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("pybind-test-5")

include_directories(include)
add_subdirectory("extern/xtl")
add_subdirectory("extern/xtensor")
include_directories("extern/xtl/include")
include_directories("extern/xtensor/include")

# Add source to this project's executable.
add_executable (pybind-test-5  "include/pybind-test-5.h" "src/pybind-test-5.cpp" "src/hello-world.cpp" "include/hello-world.h")

# TODO: Add tests and install targets if needed.

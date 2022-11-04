# CMakeList.txt : CMake project for pybind-test-5, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("pybind-test-5")

# force static runtime libraries for msvc builds
if(MSVC)
  set(variables 
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()
endif()

include_directories(include)
add_subdirectory("extern/xtl")
add_subdirectory("extern/xtensor")
include_directories("extern/xtl/include")
include_directories("extern/xtensor/include")

# Add source to this project's executable.
add_library(xtensor_interp_lib   "src/coodinates_map.cpp" "include/coodinates_map.h" "src/rgi.cpp" "include/rgi.h")
add_executable(xtensor_interp   "src/coodinates_map.cpp" "include/coodinates_map.h" "src/rgi.cpp" "include/rgi.h")
target_link_libraries(xtensor_interp xtensor_interp_lib xtensor xtl)


# TODO: Add tests and install targets if needed.
add_subdirectory("extern/googletest")
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests test/test_project.cpp  "src/coodinates_map.cpp" "include/coodinates_map.h" "src/rgi.cpp" "include/rgi.h")

target_link_libraries(runUnitTests xtensor_interp_lib gtest GTest::gtest_main)

add_test(NAME that-test-I-made COMMAND runUnitTests)
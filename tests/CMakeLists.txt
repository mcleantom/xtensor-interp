cmake_minimum_required(VERSION 3.20)
project(XTensorInterpTests)

message("Configuring XTensorInterp Tests")

set(CMAKE_CXX_STANDARD 17)

# if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" --fprofile-arcs -ftest-coverage)
# endif()

enable_testing()
find_package(GTest REQUIRED)

file(GLOB ctests_SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(
    XTensorInterp_unittests
    ${ctests_SRC}
)

target_link_libraries(
    XTensorInterp_unittests
    PUBLIC
    GTest::GTest
)

add_test(
    NAME
    XTensorInterp_unittests
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)

set_property(TARGET XTensorInterp_unittests PROPERTY VERSION ${BUILD_VERSION})
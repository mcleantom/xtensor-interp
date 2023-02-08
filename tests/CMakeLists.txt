cmake_minimum_required(VERSION 3.25)
project(XTensorInterp)

message("Configuring XTensorInterp Tests")

set(CMAKE_CXX_STANDARD 17)

enable_testing()

file(GLOB ctests_SRC CONFIGURE_DEPENDS "*.cpp")

target_compile_options(gtest PRIVATE "-w")

add_executable(
    XTensorInterp_unittests
    ${ctests_SRC}
)

set_property(TARGET gtest PROPERTY COMPILE_WARNING_AS_ERROR OFF)
set_property(TARGET gtest_main PROPERTY COMPILE_WARNING_AS_ERROR OFF)

set_target_properties(gtest PROPERTIES COMPILE_WARNING_AS_ERROR OFF)
set_target_properties(gtest_main PROPERTIES COMPILE_WARNING_AS_ERROR OFF)

target_link_libraries(
    XTensorInterp_unittests
    PUBLIC
    XTensorInterp
    gtest
    gtest_main
)

add_test(
    NAME
    XTensorInterp_unittests
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)

set_property(TARGET XTensorInterp_unittests PROPERTY VERSION ${BUILD_VERSION})
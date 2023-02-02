project(XTensorInterp)

file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR} "*.hpp" "*.h")
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

set(
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_DIRECTORIES}
)

set(
    LINK_LIBRARIES
)

add_library(
    XTensorInterp
    ${INCLUDE_FILES}
    ${SRC_FILES}
)

set_target_properties(
    XTensorInterp
    PROPERTIES
    LINKER_LANGUAGE
    CXX
)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif()

target_include_directories(
    XTensorInterp
    SYSTEM BEFORE PUBLIC
    ${INCLUDE_DIRECTORIES}
)

target_link_libraries(
    XTensorInterp
    PUBLIC
    xtensor
    ${LINK_LIBRARIES}
)
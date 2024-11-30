# CMakeList.txt : CMake project for EmbeddedIOOperations, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.30[3.30])
option(EmbeddedIOOperations_build_tests "Build all of EmbeddedIOOperations tests" OFF)

set(TARGET		        EmbeddedIOOperations)
set(LIBRARIES_DIR	    ${CMAKE_SOURCE_DIR}/libs)

project(${TARGET} CXX)

Set(FETCHCONTENT_QUIET FALSE)
include(FetchContent)

FetchContent_Declare(
    OperationArchitecture
    GIT_REPOSITORY    https://github.com/FL0WL0W/OperationArchitecture
    GIT_TAG           main
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    SOURCE_DIR  ${LIBRARIES_DIR}/OperationArchitecture
)
FetchContent_MakeAvailable(OperationArchitecture)
FetchContent_Declare(
    EmbeddedIOServices
    GIT_REPOSITORY    https://github.com/FL0WL0W/EmbeddedIOServices
    GIT_TAG           main
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    SOURCE_DIR  ${LIBRARIES_DIR}/EmbeddedIOServices
)
FetchContent_MakeAvailable(EmbeddedIOServices)


# headers are always in include/
set(HDR_DIR		include)
file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS ${HDR_DIR}/*.h)
include_directories(${HDR_DIR})
# sources are always in src/
set(SRCS_DIR	src)
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS ${SRCS_DIR}/*.cpp)

# create library
add_library(${TARGET} STATIC ${HDRS} ${SRCS})
target_include_directories(${TARGET} PUBLIC "${HDR_DIR}")
target_link_libraries(${TARGET} OperationArchitecture)
target_link_libraries(${TARGET} EmbeddedIOServices)

if(EmbeddedIOOperations_build_tests)
    # include tests
    add_subdirectory (test)
endif()
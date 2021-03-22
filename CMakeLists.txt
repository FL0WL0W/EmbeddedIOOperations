# CMakeList.txt : CMake project for OperationArchitecture, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
option(EmbeddedIOOperations_build_tests "Build all of EmbeddedIOOperations tests" OFF)

set(TARGET		EmbeddedIOOperations)
set(LIBRARIES	libs)

project(${TARGET} CXX)

add_subdirectory (${LIBRARIES}/OperationArchitecture)
add_subdirectory (${LIBRARIES}/EmbeddedIOServices)

# headers are always in include/
set(HDR_DIR		include)
file(GLOB_RECURSE HDRS ${HDR_DIR}/*.h)
include_directories(${HDR_DIR})
# sources are always in src/
set(SRCS_DIR	src)
file(GLOB_RECURSE SRCS ${SRCS_DIR}/*.cpp)

# create library
add_library(${TARGET} STATIC ${HDRS} ${SRCS})
target_include_directories(${TARGET} PUBLIC ${HDR_DIR})
target_link_libraries(${TARGET} OperationArchitecture)
target_link_libraries(${TARGET} EmbeddedIOServices)



if(EmbeddedIOOperations_build_tests)
    # Include google tests
    add_subdirectory (${LIBRARIES}/googletest)
    # include tests
    add_subdirectory (test)
endif()

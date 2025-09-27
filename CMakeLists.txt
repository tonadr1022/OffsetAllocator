cmake_minimum_required(VERSION 3.28)

project(offsetAllocator)

set(SOURCE_FILES
    offsetAllocator.cpp
    offsetAllocator.hpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

option(OFFSET_ALLOCATOR_BUILD_TESTS "Build Offset Allocator Tests" ON)


if (OFFSET_ALLOCATOR_BUILD_TESTS)
  add_subdirectory(tests)
endif ()

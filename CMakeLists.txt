cmake_minimum_required(VERSION 3.15)

project(rbtree LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "A C++ implementation for red/black tree")
include(cmake/StandardProjectSettings.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Doxygen.cmake)
enable_doxygen()

include(cmake/StaticAnalyzers.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)

option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
  # target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()

set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")
include(cmake/Conan.cmake)
run_conan()

if(ENABLE_TESTING)
  enable_testing()
  message(
    "Building Tests."
  )
  add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
  message(
    "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html"
  )
  add_subdirectory(test_fuzz)
endif()

set(rbtree_SOURCES src/rbtree.cpp)
file(GLOB rbtree_SRC
    "src/*.cpp"
)

add_library(rbtree STATIC ${rbtree_SOURCES})
set_target_properties(rbtree PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/rbtree.hpp
)
target_include_directories(rbtree PRIVATE ${PROJECT_SOURCE_DIR}/src PUBLIC PUBLIC ${PROJECT_SOURCE_DIR}/include)
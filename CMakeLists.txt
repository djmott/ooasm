#@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.


cmake_minimum_required(VERSION 3.0.2)

project(ooasm CXX)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)
find_package(Doxygen)

ExternalProject_Add(XTL
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}/XTL_GIT"
  GIT_REPOSITORY "https://github.com/djmott/xtl.git"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/XTL"
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/XTL "${CMAKE_CURRENT_BINARY_DIR}/XTL_GIT/src/XTL"
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/XTL/include)

if(Unix OR Cygwin)
  link_libraries(dl pthread stdc++)
endif()


  set(SOURCE_FILES
  src/ooasm.cpp
  src/cli.hpp
  src/parse.hpp
  )



add_executable(ooasm ${SOURCE_FILES})

add_dependencies(ooasm XTL)

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
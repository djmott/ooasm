cmake_minimum_required(VERSION 3.0.2)

project(ooasm)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

ExternalProject_Add(XTL
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}/XTL_GIT"
  GIT_REPOSITORY "https://github.com/djmott/xtl.git"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/XTL"
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/XTL "${CMAKE_CURRENT_BINARY_DIR}/XTL_GIT/src/XTL"
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/XTL/include)

set(SOURCE_FILES
    ooasm.cpp
)



add_executable(ooasm ${SOURCE_FILES})
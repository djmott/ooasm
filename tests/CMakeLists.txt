#@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.

file(DOWNLOAD https://github.com/google/googletest/archive/release-1.8.0.tar.gz ${CMAKE_CURRENT_BINARY_DIR}/gtest/gtest.tar.gz)
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf gtest.tar.gz WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gtest)
file(GLOB GTEST_FILES ${CMAKE_CURRENT_BINARY_DIR}/gtest/**/*)
file(COPY ${GTEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/gtest)
include_directories(
  "${CMAKE_CURRENT_BINARY_DIR}/gtest/googletest/"
  "${CMAKE_CURRENT_BINARY_DIR}/gtest/googletest/include"
)

add_executable(unit_tests unit_tests.cpp test_cli.hpp test_x86.hpp)

if(UNIX OR CYGWIN)
  target_link_libraries(unit_tests dl pthread stdc++)
endif()

add_dependencies(unit_tests XTL ooasm)
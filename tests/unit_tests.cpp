/** @file
Unit Tests
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/
#include <xtd/parse.hpp>
#include <xtd/string.hpp>
#include <xtd/filesystem.hpp>
#include <cstdint>
#include <vector>
#include <iostream>
#include <memory>
/*
#include "../src/parse.hpp"
#include "../src/cli.hpp"
#include "../src/x86.hpp"
*/
#include "../src/parser.hpp"
#undef forever
#include "src/gtest-all.cc"

//#include "test_cli.hpp"
//#include "test_x86.hpp"
#include "test_parser.hpp"

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

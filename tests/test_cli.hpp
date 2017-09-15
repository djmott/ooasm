/** @file
ooasm::cli unit tests
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/


#include <xtd/parse.hpp>
#include <xtd/string.hpp>
#include "../src/cli.hpp"

TEST(test_cli, file_path){
  std::string s="--in=test1.asm";
  EXPECT_TRUE(!!ooasm::cli::parser::parse(s.begin(), s.end()));
  s="--out=test.bin";
  EXPECT_TRUE(!!ooasm::cli::parser::parse(s.begin(), s.end()));
  s="--format=dwarf";
  EXPECT_TRUE(!!ooasm::cli::parser::parse(s.begin(), s.end()));
  s="--format=snafo";
  EXPECT_FALSE(!!ooasm::cli::parser::parse(s.begin(), s.end()));

}
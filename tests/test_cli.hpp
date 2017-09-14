/** @file
ooasm::cli unit tests
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/


#include <xtd/parse.hpp>
#include "../src/cli.hpp"

TEST(test_cli, file_path){
  std::string s="/test";
  using parser = xtd::parser<ooasm::cli::file_path, true, xtd::parse::whitespace<>>;
  auto oAST = parser::parse(s.begin(), s.end());
}
/** @file
cli
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/


#include <xtd/parse.hpp>
#include <xtd/string.hpp>
#include "parse.hpp"
#include "cli.hpp"

int main(int argc, char * argv[]) {
  xtd::string sArgs="";
  for (int i=1 ; i<=argc ; i++){
    sArgs += argv[i];
    sArgs += " ";
  }

  auto oCmd = ooasm::cli::parser::parse(sArgs.begin(), sArgs.end());

  return 0;
}
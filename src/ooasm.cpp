/** @file
cli
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/


#include <xtd/parse.hpp>
#include <xtd/string.hpp>
#include <xtd/filesystem.hpp>
#include <cstdint>
#include <vector>
#include <iostream>
#include <memory>
#include "parse.hpp"
#include "cli.hpp"
#include "x86.hpp"



int usage(const char * sPath){
  std::cout << "Usage: " << sPath << " --in=<path> --out=<path> --format=<format>\n"
                                  << "Output formats: binary, dwarf\n";
  return -1;
}

int main(int argc, char * argv[]) {
  using namespace ooasm;

  cli::input_param::pointer oInput;
  cli::output_param::pointer oOutput;
  cli::format_param::pointer oFormat;

  for (int i=1 ; i<argc ; i++){
    xtd::string sArg = argv[i];
    auto oArg = ooasm::cli::parser::parse(sArg.begin(), sArg.end());
    if (!oArg) return usage(argv[0]);
    if (oArg->items()[0]->isa(typeid(cli::input_param))) oInput = std::dynamic_pointer_cast<cli::input_param>(oArg->items()[0]);
    else if (oArg->items()[0]->isa(typeid(cli::output_param))) oOutput = std::dynamic_pointer_cast<cli::output_param>(oArg->items()[0]);
    else if (oArg->items()[0]->isa(typeid(cli::format_param))) oFormat = std::dynamic_pointer_cast<cli::format_param>(oArg->items()[0]);
  }

  if (!oInput || !oOutput || !oFormat) return usage(argv[0]);

  auto oSource = oInput->Path();

  if (!xtd::filesystem::exists(oSource)){
    std::cout << "File not found: " << oSource.string() << '\n';
    return usage(argv[0]);
  }



  return 0;
}
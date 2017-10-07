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
#include <fstream>
#include <sstream>
#include <streambuf>
#include "parser.hpp"
#include "cli.hpp"


int usage(const char * sPath){
  std::cout << "Usage: " << sPath << " --in=<path> --out=<path> --format=<format>\n"
                                  << "Output formats: binary, dwarf\n";
  return -1;
}

int main(int argc, char * argv[]) {
  using namespace ooasm;

  cli::input_param::pointer oInParam;
  cli::output_param::pointer oOutput;
  cli::format_param::pointer oFormat;

  for (int i=1 ; i<argc ; i++){
    xtd::string sArg = argv[i];
    auto oArg = ooasm::cli::parser::parse(sArg.begin(), sArg.end());
    if (!oArg) return usage(argv[0]);
    if (oArg->items()[0]->isa(typeid(cli::input_param))) oInParam = std::dynamic_pointer_cast<cli::input_param>(oArg->items()[0]);
    else if (oArg->items()[0]->isa(typeid(cli::output_param))) oOutput = std::dynamic_pointer_cast<cli::output_param>(oArg->items()[0]);
    else if (oArg->items()[0]->isa(typeid(cli::format_param))) oFormat = std::dynamic_pointer_cast<cli::format_param>(oArg->items()[0]);
  }

  if (!oInParam || !oOutput || !oFormat) return usage(argv[0]);

  auto oInPath = oInParam->Path();

  if (!xtd::filesystem::exists(oInPath)){
    std::cout << "File not found: " << oInPath.string() << '\n';
    return usage(argv[0]);
  }

  std::ifstream oInFile(oInPath);
  if (oInFile.bad()) {
    std::cout << "Failure reading file: " << oInPath.string() << '\n';
  }

  std::string sInFile((std::istreambuf_iterator<char>(oInFile)), std::istreambuf_iterator<char>());

  auto oAST = ooasm::asm_parser::parse(sInFile.begin(), sInFile.end());

  if (oAST) {
    std::cout << "Successfully parsed " << oInPath.string() << '\n';
  }else{
    std::cout << "Failed to parse " << oInPath.string() << '\n';
  }

  return 0;
}
/** @file
Parser
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/
#pragma once

#include <xtd/parse.hpp>

namespace ooasm{
  namespace parse{
    using namespace xtd::parse;
    namespace _{
      STRING_(AL);
      STRING_(AH);
      STRING_(BL);
      STRING_(BH);
      STRING_(CL);
      STRING_(CH);
      STRING_(DL);
      STRING_(DH);

      STRING_(MOV);
    }


    struct grammar : rule<grammar,  _::MOV>{
      template <typename ..._argTs> grammar(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...){}
    };

  }

  using parser = xtd::parser<parse::grammar, true, parse::whitespace<' ', '\t', '\r'>>;

}
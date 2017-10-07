/** @file
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/

template <typename _ty>
bool can_parse(std::string s){
  auto oAST = xtd::parser<_ty, true, xtd::parse::whitespace<' ', '\r', '\t'>>::parse(s.begin(), s.end());
  return (oAST.get() ? true : false);

}

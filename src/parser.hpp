/** @file
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/
#pragma once


namespace ooasm{
  namespace grammar{
    using namespace xtd::parse;

    CHARACTER_(OPEN_BRACKET, '[');
    CHARACTER_(CLOSE_BRACKET, ']');
    CHARACTER_(COLON, ':');
    CHARACTER_(COMMA, ',');
    CHARACTER_(LF, '\n');
    STRING_(BYTE);
    STRING_(WORD);
    STRING_(DWORD);
    STRING_(QWORD);

    STRING_(AL);
    STRING_(CL);
    STRING_(DL);
    STRING_(BL);
    STRING_(AH);
    STRING_(CH);
    STRING_(DH);
    STRING_(BH);

    STRING_(AX);
    STRING_(CX);
    STRING_(DX);
    STRING_(BX);
    STRING_(SI);
    STRING_(DI);
    STRING_(SP);
    STRING_(BP);

    STRING_(EAX);
    STRING_(ECX);
    STRING_(EDX);
    STRING_(EBX);
    STRING_(ESI);
    STRING_(EDI);
    STRING_(ESP);
    STRING_(EBP);

    STRING_(RAX);
    STRING_(RCX);
    STRING_(RDX);
    STRING_(RBX);
    STRING_(RSI);
    STRING_(RDI);
    STRING_(RSP);
    STRING_(RBP);



#define RULE(_decl, _impl) \
    struct _decl : rule<_decl, _impl>{ \
      template <typename ... _ts> _decl(_ts&&...args) : rule(std::forward<_ts>(args)...){} \
    };

#define AND(...) and_<__VA_ARGS__>
#define OR(...) or_<__VA_ARGS__>

    RULE(al, AL);
    RULE(cl, CL);
    RULE(dl, DL);
    RULE(bl, BL);
    RULE(ah, AH);
    RULE(ch, CH);
    RULE(dh, DH);
    RULE(bh, BH);

    RULE(r8, OR(al, cl, dl, bl, ah, ch, dh, bh));


    struct start : rule<start, AND(r8)>{
      template <typename ... ts> start(ts&&...oArgs) : rule(std::forward<ts>(oArgs)...){}
    };
  }

  using asm_parser = xtd::parser<grammar::start, true, xtd::parse::whitespace<' ', '\t', '\r'>>;

}
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
      CHARACTER_(lf, '\n');
      STRING_(AL);
      STRING_(AH);
      STRING_(CL);
      STRING_(CH);
      STRING_(DL);
      STRING_(DH);
      STRING_(BL);
      STRING_(BH);
      STRING_(AX);
      STRING_(CX);
      STRING_(DX);
      STRING_(BX);
      STRING_(SP);
      STRING_(BP);
      STRING_(SI);
      STRING_(DI);
      STRING_(EAX);
      STRING_(ECX);
      STRING_(EDX);
      STRING_(EBX);
      STRING_(ESP);
      STRING_(EBP);
      STRING_(ESI);
      STRING_(EDI);

      STRING_(MOV);
      STRING_(AAA);
      STRING_(AAD);
      STRING_(AAM);
      STRING_(AAS);
      STRING_(ADC);
      STRING_(ADD);
      STRING_(ADDPD);
      STRING_(ADDSD);
      STRING_(ADDSS);
      STRING_(ADDSUBPD);
      STRING_(ADDSUBPS);
      STRING_(AND);
      STRING_(ANDPD);
      STRING_(ANDPS);
    }

    template <typename _regsz, uint8_t _bits, uint8_t _modrmval> struct reg : rule<reg<_regsz, _bits, _modrmval>, _regsz> {
      template <typename ..._argTs> reg(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
      static const uint8_t bits = _bits;
      static const uint8_t modrmval = _modrmval;
    };

    using al = reg<_::AL, 8, 0>;
    using ah = reg<_::AH, 8, 1>;
    using cl = reg<_::CL, 8, 2>;
    using ch = reg<_::CH, 8, 3>;
    using dl = reg<_::DL, 8, 4>;
    using dh = reg<_::DH, 8, 5>;
    using bl = reg<_::BL, 8, 6>;
    using bh = reg<_::BH, 8, 7>;

    using ax = reg<_::AX, 16, 0>;
    using cx = reg<_::CX, 16, 1>;
    using dx = reg<_::DX, 16, 2>;
    using bx = reg<_::BX, 16, 3>;
    using sp = reg<_::SP, 16, 4>;
    using bp = reg<_::BP, 16, 5>;
    using si = reg<_::SI, 16, 6>;
    using di = reg<_::DI, 16, 7>;

    using eax = reg<_::EAX, 32, 0>;
    using ecx = reg<_::ECX, 32, 1>;
    using edx = reg<_::EDX, 32, 2>;
    using ebx = reg<_::EBX, 32, 3>;
    using esp = reg<_::ESP, 32, 4>;
    using ebp = reg<_::EBP, 32, 5>;
    using esi = reg<_::ESI, 32, 6>;
    using edi = reg<_::EDI, 32, 7>;

    struct reg8 : rule<reg8, or_<al, ah, cl, ch, dl, dh, bl, bh>> {
      template <typename ..._argTs> reg8(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    struct reg16 : rule<reg8, or_<ax, cx, dx, bx, sp, bp, si, di>> {
      template <typename ..._argTs> reg16(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    struct reg32 : rule<reg8, or_<eax, ecx, edx, ebx, esp, ebp, esi, edi>> {
      template <typename ..._argTs> reg32(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };



    template <typename _op> struct zero_param_opcode : rule<zero_param_opcode<_op>, _op> {
      template <typename ..._argTs> zero_param_opcode(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    template <typename _op> struct modrm_opcode : rule<modrm_opcode<_op>, _op> {
      template <typename ..._argTs> modrm_opcode(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    using AAA = zero_param_opcode<_::AAA>;
    using AAD = zero_param_opcode<_::AAD>;
    using AAM = zero_param_opcode<_::AAM>;
    using AAS = zero_param_opcode<_::AAS>;

    struct instruction : rule<instruction, or_<AAA, AAD, AAM, AAS>> {
      template <typename ..._argTs> instruction(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    struct grammar : rule<grammar, zero_or_more_<instruction>> {
      template <typename ..._argTs> grammar(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

  }

  using asm_parser = xtd::parser<parse::grammar, true, parse::whitespace<' ', '\t', '\r', '\n'>>;

}
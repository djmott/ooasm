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
      REGEX(hex_literal, "0[xX][0-9A-Fa-f]+");
      REGEX(dec_literal, "[0-9]+");
      REGEX(oct_literal, "0[0-7]+");
      CHARACTER_(lf, '\n');
      CHARACTER_(OPEN_BRACKET, '[');
      CHARACTER_(CLOSE_BRACKET, ']');
      CHARACTER_(COLON, ':');
      CHARACTER_(PLUS, '+');
      CHARACTER_(MINUS, '-');
      CHARACTER_(MULTIPLY, '*');
      CHARACTER_(DIVIDE, '/');
      CHARACTER_(ESCAPE, '\\');
      CHARACTER_(COMMA, ',');
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
      STRING_(RAX);
      STRING_(RCX);
      STRING_(RDX);
      STRING_(RBX);
      STRING_(RSP);
      STRING_(RBP);
      STRING_(RSI);
      STRING_(RDI);

      STRING_(CS);
      STRING_(DS);
      STRING_(SS);
      STRING_(ES);
      STRING_(FS);
      STRING_(GS);

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


    struct integral_literal : rule<integral_literal, or_<_::hex_literal , _::dec_literal , _::oct_literal >>{
      template <typename ..._argTs> integral_literal(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    template <typename _regsz, uint8_t _bits, uint8_t _modrmval> struct reg : rule<reg<_regsz, _bits, _modrmval>, _regsz> {
      template <typename ..._argTs> reg(_argTs&&...oArgs) : rule<reg<_regsz,_bits,_modrmval>>(std::forward<_argTs>(oArgs)...) {}
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

    using cs = reg<_::CS, 16, 2>;
    using ds = reg<_::DS, 16, 3>;
    using ss = reg<_::SS, 16, 4>;
    using es = reg<_::ES, 16, 5>;
    using fs = reg<_::FS, 16, 6>;
    using gs = reg<_::GS, 16, 7>;

    using eax = reg<_::EAX, 32, 0>;
    using ecx = reg<_::ECX, 32, 1>;
    using edx = reg<_::EDX, 32, 2>;
    using ebx = reg<_::EBX, 32, 3>;
    using esp = reg<_::ESP, 32, 4>;
    using ebp = reg<_::EBP, 32, 5>;
    using esi = reg<_::ESI, 32, 6>;
    using edi = reg<_::EDI, 32, 7>;

    using rax = reg<_::RAX, 64, 0>;
    using rcx = reg<_::RCX, 64, 1>;
    using rdx = reg<_::RDX, 64, 2>;
    using rbx = reg<_::RBX, 64, 3>;
    using rsp = reg<_::RSP, 64, 4>;
    using rbp = reg<_::RBP, 64, 5>;
    using rsi = reg<_::RSI, 64, 6>;
    using rdi = reg<_::RDI, 64, 7>;

    struct reg8 : rule<reg8, or_<al, ah, cl, ch, dl, dh, bl, bh>> {
      template <typename ..._argTs> reg8(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    struct reg16 : rule<reg16, or_<ax, cx, dx, bx, sp, bp, si, di>> {
      template <typename ..._argTs> reg16(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    struct reg32 : rule<reg32, or_<eax, ecx, edx, ebx, esp, ebp, esi, edi>> {
      template <typename ..._argTs> reg32(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    struct reg64 : rule<reg8, or_<rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi>> {
      template <typename ..._argTs> reg64(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    namespace regs {
      struct accumulator : rule<accumulator, or_<al, ax, eax, rax>> {
        template<typename ..._argTs> accumulator(_argTs &&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
      };

      struct counter : rule<counter, or_<cl, cx, ecx, rcx>> {
        template<typename ..._argTs> counter(_argTs &&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
      };

      struct data : rule<data, or_<dl, dx, edx, rdx>> {
        template<typename ..._argTs> data(_argTs &&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
      };

      struct base : rule<base, or_<bl, bx, ebx, rbx>> {
        template<typename ..._argTs> base(_argTs &&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
      };

      struct gpreg : rule<base, or_<reg8, reg16, reg32, reg64>> {
        template<typename ..._argTs> gpreg(_argTs &&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
      };

      struct seg : rule<seg, or_<cs, ds, ss, es, fs, gs>>{
        template<typename ..._argTs> seg(_argTs &&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
      };
    }

    struct addr : rule<addr, or_<
      and_<zero_or_one_<and_<regs::seg, _::COLON>>, _::OPEN_BRACKET , regs::gpreg, _::CLOSE_BRACKET >,
      and_<zero_or_one_<and_<regs::seg, _::COLON>>, _::OPEN_BRACKET , integral_literal, _::CLOSE_BRACKET >,
      and_<zero_or_one_<and_<regs::seg, _::COLON>>, _::OPEN_BRACKET , regs::gpreg, _::PLUS , integral_literal, _::CLOSE_BRACKET >
    >>{
      template <typename ..._argTs> addr(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };


    template <typename _op> struct zero_param_opcode : rule<zero_param_opcode<_op>, _op> {
      template <typename ..._argTs> zero_param_opcode(_argTs&&...oArgs) : rule<zero_param_opcode<_op>, _op>(std::forward<_argTs>(oArgs)...) {}
    };

    template <typename _op> struct one_param_opcode : rule<one_param_opcode<_op>, _op> {
      template <typename ..._argTs> one_param_opcode(_argTs&&...oArgs) : rule<one_param_opcode<_op>, _op>(std::forward<_argTs>(oArgs)...) {}
    };

    template <typename _op> struct modrm_opcode : rule<modrm_opcode<_op>, _op> {
      template <typename ..._argTs> modrm_opcode(_argTs&&...oArgs) : rule<modrm_opcode<_op>>(std::forward<_argTs>(oArgs)...) {}
    };

    using AAA = zero_param_opcode<_::AAA>;
    using AAD = zero_param_opcode<_::AAD>;
    using AAM = zero_param_opcode<_::AAM>;
    using AAS = zero_param_opcode<_::AAS>;

    struct ADC : rule<ADC, or_<
      and_<_::ADC, regs::accumulator, _::COMMA, integral_literal>,
      and_<_::ADC, addr, _::COMMA, integral_literal>,
      and_<_::ADC, addr, _::COMMA, regs::gpreg>,
    >>{

    };

    struct instruction : rule<instruction, or_<AAA, AAD, AAM, AAS, ADC>> {
      template <typename ..._argTs> instruction(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

    struct grammar : rule<grammar, zero_or_more_<instruction>> {
      template <typename ..._argTs> grammar(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...) {}
    };

  }

  using asm_parser = xtd::parser<parse::grammar, true, parse::whitespace<' ', '\t', '\r', '\n'>>;

}
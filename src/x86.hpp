#pragma once


namespace ooasm{
  namespace x86{

    template <uint8_t _modrm_reg> struct reg { static const uint8_t reg_field = _modrm_reg; };

    using al = reg<0>;
    using ah = reg<1>;
    using cl = reg<2>;
    using ch = reg<3>;
    using dl = reg<4>;
    using dh = reg<5>;
    using bl = reg<6>;
    using bh = reg<7>;

    using ax = reg<0>;
    using cx = reg<1>;
    using dx = reg<2>;
    using bx = reg<3>;
    using sp = reg<4>;
    using bp = reg<5>;
    using si = reg<6>;
    using di = reg<7>;

    using eax = reg<0>;
    using ecx = reg<1>;
    using edx = reg<2>;
    using ebx = reg<3>;
    using esp = reg<4>;
    using ebp = reg<5>;
    using esi = reg<6>;
    using edi = reg<7>;

    using mm0 = reg<0>;
    using mm1 = reg<1>;
    using mm2 = reg<2>;
    using mm3 = reg<3>;
    using mm4 = reg<4>;
    using mm5 = reg<5>;
    using mm6 = reg<6>;
    using mm7 = reg<7>;


    using xmm0 = reg<0>;
    using xmm1 = reg<1>;
    using xmm2 = reg<2>;
    using xmm3 = reg<3>;
    using xmm4 = reg<4>;
    using xmm5 = reg<5>;
    using xmm6 = reg<6>;
    using xmm7 = reg<7>;

    template <uint8_t ... _binvals> struct opcode_literal{
      static constexpr std::vector<uint8_t > binary() {
        std::vector<uint8_t > vals{_binvals...};
        return vals;
      }
    };
    //prefixes group 1
    using lock = opcode_literal<0360 /*0xf0*/>;
    using repne = opcode_literal<0362 /*0xf2*/>;
    using rep = opcode_literal<0363 /*0xf3*/>;

    //prefixes group2
    using es = opcode_literal<046 /*0x26*/>;
    using cs = opcode_literal<056 /*0x2e*/>; //also branch not taken
    using ss = opcode_literal<066 /*0x36*/>; //also branch taken
    using ds = opcode_literal<076 /*0x3e*/>;
    using fs = opcode_literal<0144 /*0x64*/>;
    using gs = opcode_literal<0145 /*0x65*/>;

    //group 3
    using operand_override = opcode_literal<0146 /*0x66*/>;
    using address_override = opcode_literal<0147 /*0x67*/>;





    //represents [reg+reg] effective address fields in a modr/m opcode
    template <typename _base_reg, typename _offset_reg> struct modrm_effective_address;

    template <> struct modrm_effective_address<bx, si>{ static const uint8_t rm_field =0; };
    template <> struct modrm_effective_address<bx, di>{ static const uint8_t rm_field =1; };
    template <> struct modrm_effective_address<bp, si>{ static const uint8_t rm_field =2; };
    template <> struct modrm_effective_address<bp, di>{ static const uint8_t rm_field =3; };
    template <> struct modrm_effective_address<si, nullptr_t>{ static const uint8_t rm_field =4; };
    template <> struct modrm_effective_address<di, nullptr_t>{ static const uint8_t rm_field =5; };
    template <> struct modrm_effective_address<bp, nullptr_t>{ static const uint8_t rm_field =6; };
    template <> struct modrm_effective_address<bx, nullptr_t>{ static const uint8_t rm_field=7; };


    struct modrm_mod_field_no_disp{ static const uint8_t mod_field = 0; };
    struct modrm_mod_field_8b_disp{ static const uint8_t mod_field = 0100; };
    struct modrm_mod_field_16b_disp{ static const uint8_t mod_field = 0200; };

    template <int16_t _disp> struct modrm_mod_field
      : std::conditional<0==_disp, modrm_mod_field_no_disp,
          typename std::conditional<( (_disp < 0 && _disp >-128) || (_disp > 0 && _disp < 129) ),modrm_mod_field_8b_disp,modrm_mod_field_16b_disp>::type
        >::type{};


/*
    template <typename _reg1, typename _reg2> struct modrm;

    template <uint8_t _reg1id, uint8_t _reg2id> struct modrm<reg<_reg1id>, reg<_reg2id>> {
      using reg1 = reg<_reg1id>;
      using reg2 = reg<_reg2id>;
      static const uint8_t value = 0300 | (reg1::reg_field << 3) | reg2::reg_field;
    };

    template <uint8_t _reg1, typename _src_t, int16_t _disp> struct modrm {
      static const uint8_t value = modrm_mod_field<_disp>::mod_field |
        modrm_effective_address<_base_reg, _offset_reg>::rm_field |
        _reg_t::reg_field;
    };

    template <typename _reg_t, typename _base_reg, typename _offset_reg, int16_t _disp>
    struct modrm<_reg_t, modrm_effective_address<_base_reg, _offset_reg>, _disp>{
      static const uint8_t value = modrm_mod_field<_disp>::mod_field |
        modrm_effective_address<_base_reg, _offset_reg>::rm_field |
        _reg_t::reg_field;
    };
*/

  }
}
#pragma once


namespace ooasm{
  namespace x86{

    struct al{ static const uint8_t modrm_reg = 0; };
    struct ah{static const uint8_t modrm_reg = 1;};
    struct cl{static const uint8_t modrm_reg = 2;};
    struct ch{static const uint8_t modrm_reg = 3;};
    struct dl{static const uint8_t modrm_reg = 4;};
    struct dh{static const uint8_t modrm_reg = 5;};
    struct bl{static const uint8_t modrm_reg = 6;};
    struct bh{static const uint8_t modrm_reg = 7;};

    struct ax{static const uint8_t modrm_reg = 0;};
    struct cx{static const uint8_t modrm_reg = 1;};
    struct dx{static const uint8_t modrm_reg = 2;};
    struct bx{static const uint8_t modrm_reg = 3;};
    struct sp{static const uint8_t modrm_reg = 4;};
    struct bp{static const uint8_t modrm_reg = 5;};
    struct si{static const uint8_t modrm_reg = 6;};
    struct di{static const uint8_t modrm_reg = 7;};

    struct eax{static const uint8_t modrm_reg = 0;};
    struct ecx{static const uint8_t modrm_reg = 1;};
    struct edx{static const uint8_t modrm_reg = 2;};
    struct ebx{static const uint8_t modrm_reg = 3;};
    struct esp{static const uint8_t modrm_reg = 4;};
    struct ebp{static const uint8_t modrm_reg = 5;};
    struct esi{static const uint8_t modrm_reg = 6;};
    struct edi{static const uint8_t modrm_reg = 7;};

    struct mm0{static const uint8_t modrm_reg = 0;};
    struct mm1{static const uint8_t modrm_reg = 1;};
    struct mm2{static const uint8_t modrm_reg = 2;};
    struct mm3{static const uint8_t modrm_reg = 3;};
    struct mm4{static const uint8_t modrm_reg = 4;};
    struct mm5{static const uint8_t modrm_reg = 5;};
    struct mm6{static const uint8_t modrm_reg = 6;};
    struct mm7{static const uint8_t modrm_reg = 7;};

    struct xmm0{static const uint8_t modrm_reg = 0;};
    struct xmm1{static const uint8_t modrm_reg = 1;};
    struct xmm2{static const uint8_t modrm_reg = 2;};
    struct xmm3{static const uint8_t modrm_reg = 3;};
    struct xmm4{static const uint8_t modrm_reg = 4;};
    struct xmm5{static const uint8_t modrm_reg = 5;};
    struct xmm6{static const uint8_t modrm_reg = 6;};
    struct xmm7{static const uint8_t modrm_reg = 7;};


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

    template <> struct modrm_effective_address<bx, si>{ static const uint8_t modrm_rm_field=0; };
    template <> struct modrm_effective_address<bx, di>{ static const uint8_t modrm_rm_field=1; };
    template <> struct modrm_effective_address<bp, si>{ static const uint8_t modrm_rm_field=2; };
    template <> struct modrm_effective_address<bp, di>{ static const uint8_t modrm_rm_field=3; };
    template <> struct modrm_effective_address<si, nullptr_t>{ static const uint8_t modrm_rm_field=4; };
    template <> struct modrm_effective_address<di, nullptr_t>{ static const uint8_t modrm_rm_field=5; };
    template <> struct modrm_effective_address<bp, nullptr_t>{ static const uint8_t modrm_rm_field=6; };
    template <> struct modrm_effective_address<bx, nullptr_t>{ static const uint8_t modrm_rm_field=7; };


    struct modrm_mod_field_no_disp{ static const uint8_t mod_field = 0; };
    struct modrm_mod_field_8b_disp{ static const uint8_t mod_field = 0100; };
    struct modrm_mod_field_16b_disp{ static const uint8_t mod_field = 0200; };

/*
    template <int16_t _disp> struct modrm_mod_field
      : std::conditional< ( (_disp < 0 && _disp >-128) || (_disp > 0 && _disp < 129) ),modrm_mod_field_8b_disp,
          typename std::conditional<( (_disp < 0 && _disp < -127) || (_disp > 0 && _disp > 128) ),  modrm_mod_field_16b_disp, modrm_mod_field_no_disp >::type
      >::type{};
*/

    template <int16_t _disp> struct modrm_mod_field
      : std::conditional<0==_disp, modrm_mod_field_no_disp,
          typename std::conditional<( (_disp < 0 && _disp >-128) || (_disp > 0 && _disp < 129) ),modrm_mod_field_8b_disp,modrm_mod_field_16b_disp>::type
        >::type{};


    template <typename _dest_t, typename _src_t, int16_t _disp> struct modrm;

    template <typename _dest_t, typename _base_reg, typename _offset_reg, int16_t _disp>
    struct modrm<_dest_t, modrm_effective_address<_base_reg, _offset_reg>, _disp>{
      static const uint8_t value = modrm_mod_field<_disp>::mod_field;
    };

  }
}
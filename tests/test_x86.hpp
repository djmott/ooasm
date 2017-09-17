


TEST(test_x86, modrm_mod_field){
  ASSERT_EQ(0, ooasm::x86::modrm_mod_field_no_disp::mod_field);
}
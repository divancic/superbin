#include "SuperBin.h"
#include "SuperBinTest.h"
#include <gtest/gtest.h>
#include <string>
#include <iostream>

TEST(STATIC, fromBaseToBase) {
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("1111",2,16).c_str(), "F");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("1111",2,10).c_str(), "15");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("1111",2,8).c_str(), "17");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("10",8,16).c_str(), "8");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("10",8,10).c_str(), "8");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("10",8,2).c_str(), "1000");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("17",10,16).c_str(), "11");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("17",10,8).c_str(), "21");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("17",10,2).c_str(), "10001");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("F",16,10).c_str(), "15");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("F",16,8).c_str(), "17");
  EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("F",16,2).c_str(), "1111");
}



/**************************************************************************** 
 * CONSTRUCTORS
 ****************************************************************************/
TEST(CONSTRUCTOR, zero) {
  EXPECT_STREQ(dlib::SuperBin().to_string_unsigned_bin().c_str(), "00");
}

TEST(CONSTRUCTOR, bases) {
  EXPECT_STREQ(dlib::SuperBin("11").to_string_unsigned_bin().c_str(), "01011");
  EXPECT_STREQ(dlib::SuperBin("11", 2).to_string_unsigned_bin().c_str(), "011");
  EXPECT_STREQ(dlib::SuperBin("11", 8).to_string_unsigned_bin().c_str(), "01001");
  EXPECT_STREQ(dlib::SuperBin("11", 10).to_string_unsigned_bin().c_str(), "01011");
  EXPECT_STREQ(dlib::SuperBin("11", 16).to_string_unsigned_bin().c_str(), "010001");
}

TEST(CONSTRUCTOR, positive) {
  EXPECT_STREQ(dlib::SuperBin("11", 2, dlib::SuperBin::Sign::POS).to_string_unsigned_bin().c_str(), "011");
  EXPECT_STREQ(dlib::SuperBin("11", 8, dlib::SuperBin::Sign::POS).to_string_unsigned_bin().c_str(), "01001");
  EXPECT_STREQ(dlib::SuperBin("11", 10, dlib::SuperBin::Sign::POS).to_string_unsigned_bin().c_str(), "01011");
  EXPECT_STREQ(dlib::SuperBin("11", 16, dlib::SuperBin::Sign::POS).to_string_unsigned_bin().c_str(), "010001");
}

TEST(CONSTRUCTOR, negative) {
  EXPECT_STREQ(dlib::SuperBin("11", 2, dlib::SuperBin::Sign::NEG).to_string_unsigned_bin().c_str(), "101");
  EXPECT_STREQ(dlib::SuperBin("11", 8, dlib::SuperBin::Sign::NEG).to_string_unsigned_bin().c_str(), "10111");
  EXPECT_STREQ(dlib::SuperBin("11", 10, dlib::SuperBin::Sign::NEG).to_string_unsigned_bin().c_str(), "10101");
  EXPECT_STREQ(dlib::SuperBin("11", 16, dlib::SuperBin::Sign::NEG).to_string_unsigned_bin().c_str(), "101111");
}

TEST(CONSTRUCTOR, copy) {
  dlib::SuperBin sb_orig("11", 2, dlib::SuperBin::Sign::NEG);
  dlib::SuperBin sb_copy(sb_orig);
  EXPECT_STREQ(sb_orig.to_string_unsigned_bin().c_str(), sb_copy.to_string_unsigned_bin().c_str());
  sb_copy = sb_copy.bnot();
  EXPECT_STRNE(sb_orig.to_string_unsigned_bin().c_str(), sb_copy.to_string_unsigned_bin().c_str());
}

TEST(CONSTRUCTOR, assignment) {
  dlib::SuperBin sb_orig("11", 2, dlib::SuperBin::Sign::NEG);
  dlib::SuperBin sb_copy = sb_orig;
  EXPECT_STREQ(sb_orig.to_string_unsigned_bin().c_str(), sb_copy.to_string_unsigned_bin().c_str());
  sb_copy = sb_copy.bnot();
  EXPECT_STRNE(sb_orig.to_string_unsigned_bin().c_str(), sb_copy.to_string_unsigned_bin().c_str());
}



/**************************************************************************** 
 * CONVERTERS TO STRING
 ****************************************************************************/
TEST(TO_STRING, unsigned_bin) {
  dlib::SuperBin sb_pos("AA", 16, dlib::SuperBin::Sign::POS);
  EXPECT_STREQ(sb_pos.to_string_unsigned_bin().c_str(), "010101010");
  EXPECT_STREQ(sb_pos.to_string_unsigned_bin(4).c_str(), "1010");
  EXPECT_STREQ(sb_pos.to_string_unsigned_bin(7).c_str(), "0101010");
  EXPECT_STREQ(sb_pos.to_string_unsigned_bin(9).c_str(), "010101010");
  EXPECT_STREQ(sb_pos.to_string_unsigned_bin(15).c_str(), "000000010101010");

  dlib::SuperBin sb_neg("AA", 16, dlib::SuperBin::Sign::NEG);
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin().c_str(), "101010110");
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin(4).c_str(), "0110");
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin(7).c_str(), "1010110");
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin(9).c_str(), "101010110");
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin(15).c_str(), "111111101010110");
}



/**************************************************************************** 
 * ZERO TEST
 ****************************************************************************/
TEST(ZEROTEST, tz) {
  dlib::SuperBin sb_zero_impl;
  EXPECT_TRUE(sb_zero_impl.tz());

  dlib::SuperBin sb_zero_expl("0");
  EXPECT_TRUE(sb_zero_expl.tz());

  dlib::SuperBin sb_not_zero("1");
  EXPECT_FALSE(sb_not_zero.tz());
}

TEST(ZEROTEST, tnz) {
  dlib::SuperBin sb_zero_impl;
  EXPECT_FALSE(sb_zero_impl.tnz());

  dlib::SuperBin sb_zero_expl("0");
  EXPECT_FALSE(sb_zero_expl.tnz());

  dlib::SuperBin sb_not_zero("1");
  EXPECT_TRUE(sb_not_zero.tnz());
}



/**************************************************************************** 
 * LOGICAL
 ****************************************************************************/









TEST(LOGICAL, lnot) {
  dlib::SuperBin sb;
  EXPECT_TRUE(sb.lnot());
}

TEST(BITWISE, bnot) {
  dlib::SuperBin sb;
  EXPECT_TRUE(sb.tz());
  //EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("1111",2,16).c_str(), "F");

  dlib::SuperBin bnot_sb = sb.bnot();
  EXPECT_FALSE(bnot_sb.tz());
  //EXPECT_STREQ(dlib::SuperBin::fromBaseToBase("1111",2,16).c_str(), "F");
}

TEST(ARITHMETIC, inc) {
  dlib::SuperBin sb;
  sb.inc().inc().inc().inc();
}


  /*
  sb = new dlib::SuperBin("2", 10, dlib::SuperBin::Sign::NEG);
  EXPECT_STREQ(sb->output_bin().c_str(), "-10");
  delete sb;

  sb = new dlib::SuperBin("2", 10, dlib::SuperBin::Sign::POS);
  EXPECT_STREQ(sb->output_bin().c_str(), "10");
  delete sb;
  */

int
main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

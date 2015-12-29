#include "SuperBin.h"
#include "SuperBinTest.h"
#include <gtest/gtest.h>
#include <string>
#include <iostream>


/**************************************************************************** 
 * STATIC FUNCTIONS
 ****************************************************************************/
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

TEST(TO_STRING, _signed) {
  dlib::SuperBin sb_pos("AA", 16, dlib::SuperBin::Sign::POS);
  EXPECT_STREQ(sb_pos.to_string_signed(2).c_str(), "10101010");
  EXPECT_STREQ(sb_pos.to_string_signed(8).c_str(), "252");
  EXPECT_STREQ(sb_pos.to_string_signed(10).c_str(), "170");
  EXPECT_STREQ(sb_pos.to_string_signed(16).c_str(), "AA");
  EXPECT_STREQ(sb_pos.to_string_signed(2, true).c_str(), "+10101010");
  EXPECT_STREQ(sb_pos.to_string_signed(8, true).c_str(), "+252");
  EXPECT_STREQ(sb_pos.to_string_signed(10, true).c_str(), "+170");
  EXPECT_STREQ(sb_pos.to_string_signed(16, true).c_str(), "+AA");
  EXPECT_STREQ(sb_pos.to_string_signed(2, true, true).c_str(), "+10101010");
  EXPECT_STREQ(sb_pos.to_string_signed(8, true, true).c_str(), "+252");
  EXPECT_STREQ(sb_pos.to_string_signed(10, true, true).c_str(), "+170");
  EXPECT_STREQ(sb_pos.to_string_signed(16, true, true).c_str(), "+AA");

  EXPECT_STREQ(sb_pos.to_string_signed_bin().c_str(), "10101010");
  EXPECT_STREQ(sb_pos.to_string_signed_oct().c_str(), "252");
  EXPECT_STREQ(sb_pos.to_string_signed_dec().c_str(), "170");
  EXPECT_STREQ(sb_pos.to_string_signed_hex().c_str(), "AA");

  dlib::SuperBin sb_neg("AA", 16, dlib::SuperBin::Sign::NEG);
  EXPECT_STREQ(sb_neg.to_string_signed(2).c_str(), "-10101010");
  EXPECT_STREQ(sb_neg.to_string_signed(8).c_str(), "-252");
  EXPECT_STREQ(sb_neg.to_string_signed(10).c_str(), "-170");
  EXPECT_STREQ(sb_neg.to_string_signed(16).c_str(), "-AA");
  EXPECT_STREQ(sb_neg.to_string_signed(2, true).c_str(), "-10101010");
  EXPECT_STREQ(sb_neg.to_string_signed(8, true).c_str(), "-252");
  EXPECT_STREQ(sb_neg.to_string_signed(10, true).c_str(), "-170");
  EXPECT_STREQ(sb_neg.to_string_signed(16, true).c_str(), "-AA");
  EXPECT_STREQ(sb_neg.to_string_signed(2, true, true).c_str(), "-10101010");
  EXPECT_STREQ(sb_neg.to_string_signed(8, true, true).c_str(), "-252");
  EXPECT_STREQ(sb_neg.to_string_signed(10, true, true).c_str(), "-170");
  EXPECT_STREQ(sb_neg.to_string_signed(16, true, true).c_str(), "-AA");
  EXPECT_STREQ(sb_neg.to_string_signed(2, true, false).c_str(), "10101010");
  EXPECT_STREQ(sb_neg.to_string_signed(8, true, false).c_str(), "252");
  EXPECT_STREQ(sb_neg.to_string_signed(10, true, false).c_str(), "170");
  EXPECT_STREQ(sb_neg.to_string_signed(16, true, false).c_str(), "AA");

  EXPECT_STREQ(sb_neg.to_string_signed_bin().c_str(), "-10101010");
  EXPECT_STREQ(sb_neg.to_string_signed_oct().c_str(), "-252");
  EXPECT_STREQ(sb_neg.to_string_signed_dec().c_str(), "-170");
  EXPECT_STREQ(sb_neg.to_string_signed_hex().c_str(), "-AA");
}



/**************************************************************************** 
 * ZERO TEST
 ****************************************************************************/
TEST(ZEROTEST, tz) {
  EXPECT_TRUE(dlib::SuperBin().tz());
  EXPECT_TRUE(dlib::SuperBin("0").tz());
  EXPECT_FALSE(dlib::SuperBin("1").tz());
}

TEST(ZEROTEST, tnz) {
  EXPECT_FALSE(dlib::SuperBin().tnz());
  EXPECT_FALSE(dlib::SuperBin("0").tnz());
  EXPECT_TRUE(dlib::SuperBin("1").tnz());
}



/**************************************************************************** 
 * LOGICAL
 ****************************************************************************/
TEST(LOGICAL, lnot) {
  EXPECT_TRUE(dlib::SuperBin("0").lnot());
  EXPECT_FALSE(dlib::SuperBin("1").lnot());
}



/**************************************************************************** 
 * BITWISE
 ****************************************************************************/
TEST(BITWISE, bnot) {
  EXPECT_STREQ(dlib::SuperBin().bnot().to_string_unsigned_bin().c_str(), "11");
  EXPECT_STREQ(dlib::SuperBin("A",16).bnot().to_string_unsigned_bin().c_str(), "10101");
}



/**************************************************************************** 
 * ARITHMETIC FUNCTIONS
 ****************************************************************************/
TEST(ARITHMETIC, inc) {
  dlib::SuperBin sb("3",10,dlib::SuperBin::Sign::NEG);
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "101");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "110");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "111");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "000");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "001");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "010");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "011");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "0100");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "0101");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "0110");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "0111");
  sb = sb.inc();
  EXPECT_STREQ(sb.to_string_unsigned_bin().c_str(), "01000");
}



/**************************************************************************** 
 * MASTER
 ****************************************************************************/
int
main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

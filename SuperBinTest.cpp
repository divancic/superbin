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
 * SIZE
 ****************************************************************************/
TEST(SIZE, all) {
  dlib::SuperBin sb_pos("AA", 16, dlib::SuperBin::Sign::POS);
  dlib::SuperBin sb_pos_16 = sb_pos.cast(16);
  dlib::SuperBin sb_pos_32 = sb_pos.cast(32);
  dlib::SuperBin sb_pos_opt = sb_pos_32.cast(0);
  EXPECT_EQ(sb_pos_16.size(), 16);
  EXPECT_EQ(sb_pos_32.size(), 32);
  EXPECT_EQ(sb_pos_opt.size(), 9);
  EXPECT_STREQ(sb_pos_16.to_string_unsigned_bin().c_str(), "0000000010101010");
  EXPECT_STREQ(sb_pos_32.to_string_unsigned_bin().c_str(), "00000000000000000000000010101010");
  EXPECT_STREQ(sb_pos_opt.to_string_unsigned_bin().c_str(), "010101010");

  dlib::SuperBin sb_neg("AA", 16, dlib::SuperBin::Sign::NEG);
  dlib::SuperBin sb_neg_16 = sb_neg.cast(16);
  dlib::SuperBin sb_neg_32 = sb_neg.cast(32);
  dlib::SuperBin sb_neg_opt = sb_neg_32.cast(0);
  EXPECT_EQ(sb_neg_16.size(), 16);
  EXPECT_EQ(sb_neg_32.size(), 32);
  EXPECT_EQ(sb_neg_opt.size(), 9);
  EXPECT_STREQ(sb_neg_16.to_string_unsigned_bin().c_str(), "1111111101010110");
  EXPECT_STREQ(sb_neg_32.to_string_unsigned_bin().c_str(), "11111111111111111111111101010110");
  EXPECT_STREQ(sb_neg_opt.to_string_unsigned_bin().c_str(), "101010110");

  dlib::SuperBin sb_zero;
  EXPECT_STREQ(sb_zero.cast(0).to_string_unsigned_bin().c_str(), "00");
  EXPECT_STREQ(sb_zero.cast(8).to_string_unsigned_bin().c_str(), "00000000");
  EXPECT_STREQ(sb_zero.cast(8).bnot().to_string_unsigned_bin().c_str(), "11111111");
  EXPECT_STREQ(sb_zero.cast(8).bnot().cast(10).to_string_unsigned_bin().c_str(), "1111111111");
  EXPECT_STREQ(sb_zero.cast(8).bnot().cast(10).cast().to_string_unsigned_bin().c_str(), "11");
  EXPECT_EQ(sb_zero.size(), 2);
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

  EXPECT_STREQ(sb_pos.to_string_unsigned_oct().c_str(), "252");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(1).c_str(), "0");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(2).c_str(), "2");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(3).c_str(), "2");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(4).c_str(), "12");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(5).c_str(), "12");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(6).c_str(), "52");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(7).c_str(), "052");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(8).c_str(), "252");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(9).c_str(), "252");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(10).c_str(), "0252");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(11).c_str(), "0252");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(12).c_str(), "0252");
  EXPECT_STREQ(sb_pos.to_string_unsigned_oct(13).c_str(), "00252");

  EXPECT_STREQ(sb_pos.to_string_unsigned_hex().c_str(), "AA");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(1).c_str(), "0");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(2).c_str(), "2");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(3).c_str(), "2");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(4).c_str(), "A");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(5).c_str(), "0A");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(6).c_str(), "2A");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(7).c_str(), "2A");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(8).c_str(), "AA");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(9).c_str(), "0AA");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(10).c_str(), "0AA");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(11).c_str(), "0AA");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(12).c_str(), "0AA");
  EXPECT_STREQ(sb_pos.to_string_unsigned_hex(13).c_str(), "00AA");

  dlib::SuperBin sb_neg("AA", 16, dlib::SuperBin::Sign::NEG);
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin().c_str(), "101010110");
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin(4).c_str(), "0110");
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin(7).c_str(), "1010110");
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin(9).c_str(), "101010110");
  EXPECT_STREQ(sb_neg.to_string_unsigned_bin(15).c_str(), "111111101010110");

  EXPECT_STREQ(sb_neg.to_string_unsigned_oct().c_str(), "526");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(1).c_str(), "0");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(2).c_str(), "2");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(3).c_str(), "6");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(4).c_str(), "06");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(5).c_str(), "26");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(6).c_str(), "26");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(7).c_str(), "126");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(8).c_str(), "126");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(9).c_str(), "526");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(10).c_str(), "1526");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(11).c_str(), "3526");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(12).c_str(), "7526");
  EXPECT_STREQ(sb_neg.to_string_unsigned_oct(13).c_str(), "17526");

  EXPECT_STREQ(sb_neg.to_string_unsigned_hex().c_str(), "156");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(1).c_str(), "0");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(2).c_str(), "2");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(3).c_str(), "6");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(4).c_str(), "6");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(5).c_str(), "16");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(6).c_str(), "16");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(7).c_str(), "56");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(8).c_str(), "56");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(9).c_str(), "156");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(10).c_str(), "356");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(11).c_str(), "756");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(12).c_str(), "F56");
  EXPECT_STREQ(sb_neg.to_string_unsigned_hex(13).c_str(), "1F56");
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
  EXPECT_STREQ(dlib::SuperBin("0").lnot().to_string_unsigned_bin().c_str(), "01");
  EXPECT_STREQ(dlib::SuperBin("1").lnot().to_string_unsigned_bin().c_str(), "00");
}

TEST(LOGICAL, land) {
  dlib::SuperBin sb;
  EXPECT_FALSE(sb.land(sb));
  EXPECT_FALSE(sb.lnot().land(sb));
  EXPECT_FALSE(sb.land(sb.lnot()));
  EXPECT_TRUE(sb.lnot().land(sb.lnot()));
}

TEST(LOGICAL, lor) {
  dlib::SuperBin sb;
  EXPECT_FALSE(sb.lor(sb));
  EXPECT_TRUE(sb.lor(sb.lnot()));
  EXPECT_TRUE(sb.lnot().lor(sb));
  EXPECT_TRUE(sb.lnot().lor(sb.lnot()));
}

TEST(LOGICAL, lxor) {
  dlib::SuperBin sb;
  EXPECT_FALSE(sb.lxor(sb));
  EXPECT_TRUE(sb.lxor(sb.lnot()));
  EXPECT_TRUE(sb.lnot().lxor(sb));
  EXPECT_FALSE(sb.lnot().lxor(sb.lnot()));
}

/**************************************************************************** 
 * BITWISE
 ****************************************************************************/
TEST(BITWISE, bnot) {
  EXPECT_STREQ(dlib::SuperBin().bnot().to_string_unsigned_bin().c_str(), "11");
  EXPECT_STREQ(dlib::SuperBin("A",16).bnot().to_string_unsigned_bin().c_str(), "10101");
}

TEST(BITWISE, band) {
  dlib::SuperBin sb_1("3AA",16);
  dlib::SuperBin sb_2("2A5",16);
  dlib::SuperBin sb_3 = sb_2.band(sb_1);
  EXPECT_STREQ(sb_3.to_string_unsigned_bin().c_str(), "01010100000");
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

#include <gtest/gtest.h>
#include "ADELint.h"

/**************************************************************************** 
 * CONSTRUCTORS
 ****************************************************************************/
TEST(CONSTRUCTOR, zero) {
  EXPECT_STREQ(dlib::ADELint().to_string_unsigned_bin().c_str(), "00");
}

TEST(CONVERTER, to_string) {
  dlib::ADELint pos("AA", 16);
  EXPECT_STREQ(to_string_signed_bin(pos).c_str(), "10101010");
  EXPECT_STREQ(to_string_signed_oct(pos).c_str(), "252");
  EXPECT_STREQ(to_string_signed_dec(pos).c_str(), "170");
  EXPECT_STREQ(to_string_signed_hex(pos).c_str(), "AA");

  EXPECT_STREQ(pos.to_string_unsigned_bin().c_str(), "010101010");
  EXPECT_STREQ(pos.to_string_unsigned_bin(4).c_str(), "1010");
  EXPECT_STREQ(pos.to_string_unsigned_bin(7).c_str(), "0101010");
  EXPECT_STREQ(pos.to_string_unsigned_bin(9).c_str(), "010101010");
  EXPECT_STREQ(pos.to_string_unsigned_bin(15).c_str(), "000000010101010");

  EXPECT_STREQ(pos.to_string_unsigned_oct().c_str(), "252");
  EXPECT_STREQ(pos.to_string_unsigned_oct(1).c_str(), "0");
  EXPECT_STREQ(pos.to_string_unsigned_oct(2).c_str(), "2");
  EXPECT_STREQ(pos.to_string_unsigned_oct(3).c_str(), "2");
  EXPECT_STREQ(pos.to_string_unsigned_oct(4).c_str(), "12");
  EXPECT_STREQ(pos.to_string_unsigned_oct(5).c_str(), "12");
  EXPECT_STREQ(pos.to_string_unsigned_oct(6).c_str(), "52");
  EXPECT_STREQ(pos.to_string_unsigned_oct(7).c_str(), "052");
  EXPECT_STREQ(pos.to_string_unsigned_oct(8).c_str(), "252");
  EXPECT_STREQ(pos.to_string_unsigned_oct(9).c_str(), "252");
  EXPECT_STREQ(pos.to_string_unsigned_oct(10).c_str(), "0252");
  EXPECT_STREQ(pos.to_string_unsigned_oct(11).c_str(), "0252");
  EXPECT_STREQ(pos.to_string_unsigned_oct(12).c_str(), "0252");
  EXPECT_STREQ(pos.to_string_unsigned_oct(13).c_str(), "00252");

  EXPECT_STREQ(pos.to_string_unsigned_hex().c_str(), "AA");
  EXPECT_STREQ(pos.to_string_unsigned_hex(1).c_str(), "0");
  EXPECT_STREQ(pos.to_string_unsigned_hex(2).c_str(), "2");
  EXPECT_STREQ(pos.to_string_unsigned_hex(3).c_str(), "2");
  EXPECT_STREQ(pos.to_string_unsigned_hex(4).c_str(), "A");
  EXPECT_STREQ(pos.to_string_unsigned_hex(5).c_str(), "0A");
  EXPECT_STREQ(pos.to_string_unsigned_hex(6).c_str(), "2A");
  EXPECT_STREQ(pos.to_string_unsigned_hex(7).c_str(), "2A");
  EXPECT_STREQ(pos.to_string_unsigned_hex(8).c_str(), "AA");
  EXPECT_STREQ(pos.to_string_unsigned_hex(9).c_str(), "0AA");
  EXPECT_STREQ(pos.to_string_unsigned_hex(10).c_str(), "0AA");
  EXPECT_STREQ(pos.to_string_unsigned_hex(11).c_str(), "0AA");
  EXPECT_STREQ(pos.to_string_unsigned_hex(12).c_str(), "0AA");
  EXPECT_STREQ(pos.to_string_unsigned_hex(13).c_str(), "00AA");

  dlib::ADELint neg("AA", 16, -1);
  EXPECT_STREQ(to_string_signed_bin(neg).c_str(), "-10101010");
  EXPECT_STREQ(to_string_signed_oct(neg).c_str(), "-252");
  EXPECT_STREQ(to_string_signed_dec(neg).c_str(), "-170");
  EXPECT_STREQ(to_string_signed_hex(neg).c_str(), "-AA");

  EXPECT_STREQ(neg.to_string_unsigned_bin().c_str(), "101010110");
  EXPECT_STREQ(neg.to_string_unsigned_bin(4).c_str(), "0110");
  EXPECT_STREQ(neg.to_string_unsigned_bin(7).c_str(), "1010110");
  EXPECT_STREQ(neg.to_string_unsigned_bin(9).c_str(), "101010110");
  EXPECT_STREQ(neg.to_string_unsigned_bin(15).c_str(), "111111101010110");

  EXPECT_STREQ(neg.to_string_unsigned_oct().c_str(), "526");
  EXPECT_STREQ(neg.to_string_unsigned_oct(1).c_str(), "0");
  EXPECT_STREQ(neg.to_string_unsigned_oct(2).c_str(), "2");
  EXPECT_STREQ(neg.to_string_unsigned_oct(3).c_str(), "6");
  EXPECT_STREQ(neg.to_string_unsigned_oct(4).c_str(), "06");
  EXPECT_STREQ(neg.to_string_unsigned_oct(5).c_str(), "26");
  EXPECT_STREQ(neg.to_string_unsigned_oct(6).c_str(), "26");
  EXPECT_STREQ(neg.to_string_unsigned_oct(7).c_str(), "126");
  EXPECT_STREQ(neg.to_string_unsigned_oct(8).c_str(), "126");
  EXPECT_STREQ(neg.to_string_unsigned_oct(9).c_str(), "526");
  EXPECT_STREQ(neg.to_string_unsigned_oct(10).c_str(), "1526");
  EXPECT_STREQ(neg.to_string_unsigned_oct(11).c_str(), "3526");
  EXPECT_STREQ(neg.to_string_unsigned_oct(12).c_str(), "7526");
  EXPECT_STREQ(neg.to_string_unsigned_oct(13).c_str(), "17526");

  EXPECT_STREQ(neg.to_string_unsigned_hex().c_str(), "156");
  EXPECT_STREQ(neg.to_string_unsigned_hex(1).c_str(), "0");
  EXPECT_STREQ(neg.to_string_unsigned_hex(2).c_str(), "2");
  EXPECT_STREQ(neg.to_string_unsigned_hex(3).c_str(), "6");
  EXPECT_STREQ(neg.to_string_unsigned_hex(4).c_str(), "6");
  EXPECT_STREQ(neg.to_string_unsigned_hex(5).c_str(), "16");
  EXPECT_STREQ(neg.to_string_unsigned_hex(6).c_str(), "16");
  EXPECT_STREQ(neg.to_string_unsigned_hex(7).c_str(), "56");
  EXPECT_STREQ(neg.to_string_unsigned_hex(8).c_str(), "56");
  EXPECT_STREQ(neg.to_string_unsigned_hex(9).c_str(), "156");
  EXPECT_STREQ(neg.to_string_unsigned_hex(10).c_str(), "356");
  EXPECT_STREQ(neg.to_string_unsigned_hex(11).c_str(), "756");
  EXPECT_STREQ(neg.to_string_unsigned_hex(12).c_str(), "F56");
  EXPECT_STREQ(neg.to_string_unsigned_hex(13).c_str(), "1F56");
}


TEST(CONVERTER, to_int) {
  dlib::ADELint o;
  long int i;

  for (i = 0; i < 1111; ++i) {
    o = dlib::ADELint(std::to_string(i), 10);
    EXPECT_TRUE(o.to_int() == i);
    o = dlib::ADELint(std::to_string(i), 10, -1);
    EXPECT_TRUE(o.to_int() == -i);
  }

  i = std::numeric_limits<int>::max();
  o = dlib::ADELint(std::to_string(i), 10);
  EXPECT_TRUE(o.to_int() == i);
  o = dlib::ADELint(std::to_string(i), 10, -1);
  EXPECT_TRUE(o.to_int() == -i);

  for (i = static_cast<long int>(std::numeric_limits<int>::max()) + 1;
      i < static_cast<long int>(std::numeric_limits<int>::max()) + 1111;
      ++i) {
  o = dlib::ADELint(std::to_string(i), 10);
  EXPECT_TRUE(o.to_int() == std::numeric_limits<int>::lowest());
  o = dlib::ADELint(std::to_string(i), 10, -1);
  EXPECT_TRUE(o.to_int() == std::numeric_limits<int>::lowest());
  }
}

/*
TEST(CONSTRUCTOR, bases) {
  EXPECT_STREQ(dlib::SuperBin("11").to_string_unsigned_bin().c_str(), "01011");
  EXPECT_STREQ(dlib::SuperBin("11", 2).to_string_unsigned_bin().c_str(), "011");
  EXPECT_STREQ(dlib::SuperBin("11", 8).to_string_unsigned_bin().c_str(), "01001");
  EXPECT_STREQ(dlib::SuperBin("11", 10).to_string_unsigned_bin().c_str(), "01011");
  EXPECT_STREQ(dlib::SuperBin("11", 16).to_string_unsigned_bin().c_str(), "010001");
}
*/

/**************************************************************************** 
 * MASTER
 ****************************************************************************/
int
main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

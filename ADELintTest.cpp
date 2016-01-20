#include <gtest/gtest.h>
#include "ADELint.h"

/**************************************************************************** 
 * CONSTRUCTORS
 ****************************************************************************/
TEST(CONSTRUCTOR, zero) {
  EXPECT_STREQ(dlib::ADELint().to_string_unsigned_bin().c_str(), "00");
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

#include "SuperBin.h"
#include "SuperBinTest.h"
#include <gtest/gtest.h>
#include <string>
#include <iostream>

/*
TEST(STATIC, binary_not) {
  std::string result;
  EXPECT_STREQ(dlib::SuperBin::binary_not("0000").c_str(), "1111");
  EXPECT_STREQ(dlib::SuperBin::binary_not("0101").c_str(), "1010");
  EXPECT_STREQ(dlib::SuperBin::binary_not("0111").c_str(), "1000");
  EXPECT_STREQ(dlib::SuperBin::binary_not("1110").c_str(), "0001");
  EXPECT_STREQ(dlib::SuperBin::binary_not("1111").c_str(), "0000");
}

TEST(STATIC, binary_inc) {
  std::string result;
  EXPECT_STREQ(dlib::SuperBin::binary_inc("0000").c_str(), "0001");
  EXPECT_STREQ(dlib::SuperBin::binary_inc("0100").c_str(), "0101");
  EXPECT_STREQ(dlib::SuperBin::binary_inc("0111").c_str(), "1000");
  EXPECT_STREQ(dlib::SuperBin::binary_inc("1110").c_str(), "1111");
  EXPECT_STREQ(dlib::SuperBin::binary_inc("1111").c_str(), "0000");
}

TEST(STATIC, binary_compl) {
  std::string result;
  EXPECT_STREQ(dlib::SuperBin::binary_compl("0001").c_str(), "1111");
  EXPECT_STREQ(dlib::SuperBin::binary_compl("0100").c_str(), "1100");
  EXPECT_STREQ(dlib::SuperBin::binary_compl("0111").c_str(), "1001");
  EXPECT_STREQ(dlib::SuperBin::binary_compl("1110").c_str(), "0010");
  EXPECT_STREQ(dlib::SuperBin::binary_compl("1111").c_str(), "0001");
}
*/

TEST(STATIC, zero) {
  /*
  dlib::SuperBin *sb;

  sb = new dlib::SuperBin("2", 10, dlib::SuperBin::Sign::NEG);
  EXPECT_STREQ(sb->output_bin().c_str(), "-10");
  delete sb;

  sb = new dlib::SuperBin("2", 10, dlib::SuperBin::Sign::POS);
  EXPECT_STREQ(sb->output_bin().c_str(), "10");
  delete sb;
  */
}

int
main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

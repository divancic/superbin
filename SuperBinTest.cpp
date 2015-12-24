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

TEST(ZEROTEST, tz_tnz) {
  dlib::SuperBin sb;

  EXPECT_TRUE(sb.tz());
  EXPECT_FALSE(sb.tnz());

  /*
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

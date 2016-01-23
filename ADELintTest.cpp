#include <gtest/gtest.h>
#include "ADELint.h"

const long int loops = 11;

using namespace dlib;
using namespace std;



/**************************************************************************** 
 * CONSTRUCTORS
 ****************************************************************************/
TEST(CONSTRUCTOR, zero) {
  EXPECT_STREQ(to_string_unsigned_bin(ADELint(), 0).c_str(), "00");
}

TEST(CONSTRUCTOR, bases) {
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11"    ), 0).c_str(), "01011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  2), 0).c_str(), "011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  8), 0).c_str(), "01001");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 10), 0).c_str(), "01011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 16), 0).c_str(), "010001");
}

TEST(CONSTRUCTOR, positive) {
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  2), 0).c_str(), "011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  8), 0).c_str(), "01001");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 10), 0).c_str(), "01011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 16), 0).c_str(), "010001");
}

TEST(CONSTRUCTOR, negative) {
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  2, -1), 0).c_str(), "101");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  8, -1), 0).c_str(), "10111");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 10, -1), 0).c_str(), "10101");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 16, -1), 0).c_str(), "101111");

  EXPECT_STREQ(to_string_unsigned_bin(ADELint("01", 10, -1), 0).c_str(), "11");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("02", 10, -1), 0).c_str(), "10");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("03", 10, -1), 0).c_str(), "101");

  EXPECT_STREQ(to_string_unsigned_bin(ADELint("03", 10, -1), 0).c_str(), "101");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("04", 10, -1), 0).c_str(), "100");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("05", 10, -1), 0).c_str(), "1011");

  EXPECT_STREQ(to_string_unsigned_bin(ADELint("07", 10, -1), 0).c_str(), "1001");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("08", 10, -1), 0).c_str(), "1000");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("09", 10, -1), 0).c_str(), "10111");

  EXPECT_STREQ(to_string_unsigned_bin(ADELint("15", 10, -1), 0).c_str(), "10001");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("16", 10, -1), 0).c_str(), "10000");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("17", 10, -1), 0).c_str(), "101111");
}

TEST(CONSTRUCTOR, copy) {
  ADELint orig("11", 2, -1);
  ADELint copy(orig);
  EXPECT_STREQ(to_string_unsigned_bin(orig, 0).c_str(), to_string_unsigned_bin(copy, 0).c_str());
  copy = neg(orig);
  EXPECT_STRNE(to_string_unsigned_bin(orig, 0).c_str(), to_string_unsigned_bin(copy, 0).c_str());
}

TEST(CONSTRUCTOR, assignment) {
  ADELint orig("11", 2, -1);
  ADELint copy = orig;
  EXPECT_STREQ(to_string_unsigned_bin(orig, 0).c_str(), to_string_unsigned_bin(copy, 0).c_str());
  copy = neg(orig);
  EXPECT_STRNE(to_string_unsigned_bin(orig, 0).c_str(), to_string_unsigned_bin(copy, 0).c_str());
}



/**************************************************************************** 
 * CONVERTERS
 ****************************************************************************/

TEST(CONVERTER, to_string) {
  ADELint pos("AA", 16);
  EXPECT_STREQ(to_string_signed_bin(pos).c_str(), "10101010");
  EXPECT_STREQ(to_string_signed_oct(pos).c_str(), "252");
  EXPECT_STREQ(to_string_signed_dec(pos).c_str(), "170");
  EXPECT_STREQ(to_string_signed_hex(pos).c_str(), "AA");

  EXPECT_STREQ(to_string_unsigned_bin(pos, 0).c_str(), "010101010");
  EXPECT_STREQ(to_string_unsigned_bin(pos, 4).c_str(), "1010");
  EXPECT_STREQ(to_string_unsigned_bin(pos, 7).c_str(), "0101010");
  EXPECT_STREQ(to_string_unsigned_bin(pos, 9).c_str(), "010101010");
  EXPECT_STREQ(to_string_unsigned_bin(pos, 15).c_str(), "000000010101010");

  EXPECT_STREQ(to_string_unsigned_oct(pos, 0).c_str(), "252");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 1).c_str(), "0");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 2).c_str(), "2");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 3).c_str(), "2");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 4).c_str(), "12");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 5).c_str(), "12");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 6).c_str(), "52");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 7).c_str(), "052");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 8).c_str(), "252");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 9).c_str(), "252");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 10).c_str(), "0252");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 11).c_str(), "0252");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 12).c_str(), "0252");
  EXPECT_STREQ(to_string_unsigned_oct(pos, 13).c_str(), "00252");

  // TODO(doki): friend functions and defaults
  EXPECT_STREQ(to_string_unsigned_hex(pos, 0).c_str(), "AA");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 1).c_str(), "0");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 2).c_str(), "2");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 3).c_str(), "2");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 4).c_str(), "A");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 5).c_str(), "0A");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 6).c_str(), "2A");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 7).c_str(), "2A");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 8).c_str(), "AA");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 9).c_str(), "0AA");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 10).c_str(), "0AA");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 11).c_str(), "0AA");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 12).c_str(), "0AA");
  EXPECT_STREQ(to_string_unsigned_hex(pos, 13).c_str(), "00AA");

  ADELint neg("AA", 16, -1);
  EXPECT_STREQ(to_string_signed_bin(neg).c_str(), "-10101010");
  EXPECT_STREQ(to_string_signed_oct(neg).c_str(), "-252");
  EXPECT_STREQ(to_string_signed_dec(neg).c_str(), "-170");
  EXPECT_STREQ(to_string_signed_hex(neg).c_str(), "-AA");

  EXPECT_STREQ(to_string_unsigned_bin(neg, 0).c_str(), "101010110");
  EXPECT_STREQ(to_string_unsigned_bin(neg, 4).c_str(), "0110");
  EXPECT_STREQ(to_string_unsigned_bin(neg, 7).c_str(), "1010110");
  EXPECT_STREQ(to_string_unsigned_bin(neg, 9).c_str(), "101010110");
  EXPECT_STREQ(to_string_unsigned_bin(neg, 15).c_str(), "111111101010110");

  EXPECT_STREQ(to_string_unsigned_oct(neg, 0).c_str(), "526");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 1).c_str(), "0");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 2).c_str(), "2");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 3).c_str(), "6");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 4).c_str(), "06");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 5).c_str(), "26");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 6).c_str(), "26");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 7).c_str(), "126");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 8).c_str(), "126");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 9).c_str(), "526");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 10).c_str(), "1526");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 11).c_str(), "3526");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 12).c_str(), "7526");
  EXPECT_STREQ(to_string_unsigned_oct(neg, 13).c_str(), "17526");

  EXPECT_STREQ(to_string_unsigned_hex(neg, 0).c_str(), "156");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 1).c_str(), "0");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 2).c_str(), "2");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 3).c_str(), "6");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 4).c_str(), "6");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 5).c_str(), "16");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 6).c_str(), "16");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 7).c_str(), "56");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 8).c_str(), "56");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 9).c_str(), "156");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 10).c_str(), "356");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 11).c_str(), "756");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 12).c_str(), "F56");
  EXPECT_STREQ(to_string_unsigned_hex(neg, 13).c_str(), "1F56");
}

TEST(CONVERTER, to_int) {
  for (auto i = 0; i < loops; ++i) {
    ADELint o = ADELint(to_string(i), 10);
    EXPECT_TRUE(o.to_int() == i);
    EXPECT_TRUE(neg(o).to_int() == -i);
  }

  long int i = numeric_limits<int>::max();
  ADELint o = ADELint(to_string(i), 10);
  EXPECT_TRUE(o.to_int() == i);
  EXPECT_TRUE(neg(o).to_int() == -i);

  long int max_int = static_cast<long int>(numeric_limits<int>::max());
  for (auto i = max_int + 1; i < max_int + loops; ++i) {
    ADELint o = ADELint(to_string(i), 10);
    EXPECT_TRUE(o.to_int() == numeric_limits<int>::lowest());
    EXPECT_TRUE(neg(o).to_int() == numeric_limits<int>::lowest());
  }
}



/**************************************************************************** 
 * ARITHMETIC FUNCTIONS
 ****************************************************************************/
TEST(ARITHMETIC, neg) {
  ADELint o = ADELint("17", 10);

  EXPECT_STREQ(neg(o).to_string_signed_dec().c_str(), "-17");
  EXPECT_STREQ(neg(neg(o)).to_string_signed_dec().c_str(), "17");
  EXPECT_STREQ(neg(neg(neg(o))).to_string_signed_dec().c_str(), "-17");
}

TEST(ARITHMETIC, add) {
  for (auto i = 0; i < loops; ++i) {
    for (auto j = 0; j < loops; ++j) {
      ADELint a = ADELint(to_string(i));
      ADELint b = ADELint(to_string(j));

      EXPECT_TRUE(stoi(add(a, b).to_string_signed_dec()) == i + j);
      EXPECT_TRUE(stoi(add(a, neg(b)).to_string_signed_dec()) == i + (-j));
      EXPECT_TRUE(stoi(add(neg(a), b).to_string_signed_dec()) == (-i) + j);
      EXPECT_TRUE(stoi(add(neg(a), neg(b)).to_string_signed_dec()) == (-i) + (-j));
    }
  }
}

TEST(ARITHMETIC, sub) {
  for (auto i = 0; i < loops; ++i) {
    for (auto j = 0; j < loops; ++j) {
      ADELint a = ADELint(to_string(i));
      ADELint b = ADELint(to_string(j));

      EXPECT_TRUE(stoi(sub(a, b).to_string_signed_dec()) == i - j);
      EXPECT_TRUE(stoi(sub(a, neg(b)).to_string_signed_dec()) == i - (-j));
      EXPECT_TRUE(stoi(sub(neg(a), b).to_string_signed_dec()) == (-i) - j);
      EXPECT_TRUE(stoi(sub(neg(a), neg(b)).to_string_signed_dec()) == (-i) - (-j));
    }
  }
}

TEST(ARITHMETIC, mul) {
  for (auto i = 0; i < loops; ++i) {
    for (auto j = 0; j < loops; ++j) {
      ADELint a = ADELint(to_string(i));
      ADELint b = ADELint(to_string(j));

      EXPECT_TRUE(stoi(mul(a, b).to_string_signed_dec()) == i * j);
      EXPECT_TRUE(stoi(mul(a, neg(b)).to_string_signed_dec()) == i * (-j));
      EXPECT_TRUE(stoi(mul(neg(a), b).to_string_signed_dec()) == (-i) * j);
      EXPECT_TRUE(stoi(mul(neg(a), neg(b)).to_string_signed_dec()) == (-i) * (-j));
    }
  }
}

TEST(ARITHMETIC, div) {
  for (auto i = 0; i < loops; ++i) {
    for (auto j = 1; j < loops; ++j) {
      ADELint a = ADELint(to_string(i));
      ADELint b = ADELint(to_string(j));

      EXPECT_TRUE(stoi(div(a, b).to_string_signed_dec()) == i / j);
      EXPECT_TRUE(stoi(div(a, neg(b)).to_string_signed_dec()) == i / (-j));
      EXPECT_TRUE(stoi(div(neg(a), b).to_string_signed_dec()) == (-i) / j);
      EXPECT_TRUE(stoi(div(neg(a), neg(b)).to_string_signed_dec()) == (-i) / (-j));
    }
  }
}

TEST(ARITHMETIC, mod) {
  for (auto i = 0; i < loops; ++i) {
    for (auto j = 1; j < loops; ++j) {
      ADELint a = ADELint(to_string(i));
      ADELint b = ADELint(to_string(j));

      EXPECT_TRUE(stoi(mod(a, b).to_string_signed_dec()) == i % j);
      EXPECT_TRUE(stoi(mod(a, neg(b)).to_string_signed_dec()) == i % (-j));
      EXPECT_TRUE(stoi(mod(neg(a), b).to_string_signed_dec()) == (-i) % j);
      EXPECT_TRUE(stoi(mod(neg(a), neg(b)).to_string_signed_dec()) == (-i) % (-j));
    }
  }
}



/**************************************************************************** 
 * MASTER
 ****************************************************************************/
int
main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

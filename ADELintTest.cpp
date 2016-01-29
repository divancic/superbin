#include <gtest/gtest.h>
#include "ADELint.h"

const long int loops = 111;

using namespace dlib;
using namespace std;



/**************************************************************************** 
 * CONSTRUCTORS
 ****************************************************************************/
TEST(CONSTRUCTOR, zero) {
  EXPECT_STREQ(to_string_unsigned_bin(ADELint()).c_str(), "00");
}

TEST(CONSTRUCTOR, bases) {
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11"    )).c_str(), "01011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  2)).c_str(), "011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  8)).c_str(), "01001");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 10)).c_str(), "01011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 16)).c_str(), "010001");
}

TEST(CONSTRUCTOR, positive) {
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  2)).c_str(), "011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  8)).c_str(), "01001");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 10)).c_str(), "01011");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 16)).c_str(), "010001");
}

TEST(CONSTRUCTOR, negative) {
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  2, -1)).c_str(), "101");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11",  8, -1)).c_str(), "10111");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 10, -1)).c_str(), "10101");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("11", 16, -1)).c_str(), "101111");

  EXPECT_STREQ(to_string_unsigned_bin(ADELint("01", 10, -1)).c_str(), "11");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("02", 10, -1)).c_str(), "10");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("03", 10, -1)).c_str(), "101");

  EXPECT_STREQ(to_string_unsigned_bin(ADELint("03", 10, -1)).c_str(), "101");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("04", 10, -1)).c_str(), "100");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("05", 10, -1)).c_str(), "1011");

  EXPECT_STREQ(to_string_unsigned_bin(ADELint("07", 10, -1)).c_str(), "1001");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("08", 10, -1)).c_str(), "1000");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("09", 10, -1)).c_str(), "10111");

  EXPECT_STREQ(to_string_unsigned_bin(ADELint("15", 10, -1)).c_str(), "10001");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("16", 10, -1)).c_str(), "10000");
  EXPECT_STREQ(to_string_unsigned_bin(ADELint("17", 10, -1)).c_str(), "101111");
}

TEST(CONSTRUCTOR, copy) {
  ADELint orig("11", 2, -1);
  ADELint copy(orig);
  EXPECT_STREQ(to_string_unsigned_bin(orig).c_str(), to_string_unsigned_bin(copy).c_str());
  copy = neg(orig);
  EXPECT_STRNE(to_string_unsigned_bin(orig).c_str(), to_string_unsigned_bin(copy).c_str());
}

TEST(CONSTRUCTOR, assignment) {
  ADELint orig("11", 2, -1);
  ADELint copy = orig;
  EXPECT_STREQ(to_string_unsigned_bin(orig).c_str(), to_string_unsigned_bin(copy).c_str());
  copy = neg(orig);
  EXPECT_STRNE(to_string_unsigned_bin(orig).c_str(), to_string_unsigned_bin(copy).c_str());
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

  EXPECT_STREQ(to_string_unsigned_bin(pos).c_str(), "010101010");
  EXPECT_STREQ(to_string_unsigned_bin(pos, 4).c_str(), "1010");
  EXPECT_STREQ(to_string_unsigned_bin(pos, 7).c_str(), "0101010");
  EXPECT_STREQ(to_string_unsigned_bin(pos, 9).c_str(), "010101010");
  EXPECT_STREQ(to_string_unsigned_bin(pos, 15).c_str(), "000000010101010");

  EXPECT_STREQ(to_string_unsigned_oct(pos).c_str(), "252");
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

  EXPECT_STREQ(to_string_unsigned_hex(pos).c_str(), "AA");
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

  EXPECT_STREQ(to_string_unsigned_bin(neg).c_str(), "101010110");
  EXPECT_STREQ(to_string_unsigned_bin(neg, 4).c_str(), "0110");
  EXPECT_STREQ(to_string_unsigned_bin(neg, 7).c_str(), "1010110");
  EXPECT_STREQ(to_string_unsigned_bin(neg, 9).c_str(), "101010110");
  EXPECT_STREQ(to_string_unsigned_bin(neg, 15).c_str(), "111111101010110");

  EXPECT_STREQ(to_string_unsigned_oct(neg).c_str(), "526");
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

  EXPECT_STREQ(to_string_unsigned_hex(neg).c_str(), "156");
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
    ADELint a = ADELint(to_string(i));
    ADELint b = ADELint(to_string(0));
    EXPECT_TRUE(stoi(div(a, b).to_string_signed_dec()) == 0);
  }

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
    ADELint a = ADELint(to_string(i));
    ADELint b = ADELint(to_string(0));
    EXPECT_TRUE(stoi(mod(a, b).to_string_signed_dec()) == 0);
  }

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
 * COMPARISONS
 ****************************************************************************/

TEST(COMPARISONS, equal) {
  for (auto i = 0; i < loops; ++i) {
    for (auto j = 0; j < loops; ++j) {
      ADELint a = ADELint(to_string(i));
      ADELint b = ADELint(to_string(j));

      EXPECT_STREQ(to_string_unsigned_bin(equal(a, b)).c_str(), (i == j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(equal(neg(a), b)).c_str(), (-i == j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(equal(a, neg(b))).c_str(), (i == -j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(equal(neg(a), neg(b))).c_str(), (-i == -j ? "01" : "00"));

      EXPECT_STREQ(to_string_unsigned_bin(not_equal(a, b)).c_str(), (i != j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(not_equal(neg(a), b)).c_str(), (-i != j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(not_equal(a, neg(b))).c_str(), (i != -j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(not_equal(neg(a), neg(b))).c_str(), (-i != -j ? "01" : "00"));
    }
  }
}

TEST(COMPARISONS, less) {
  for (auto i = 0; i < loops; ++i) {
    for (auto j = 0; j < loops; ++j) {
      ADELint a = ADELint(to_string(i));
      ADELint b = ADELint(to_string(j));

      EXPECT_STREQ(to_string_unsigned_bin(less_then(a, b)).c_str(), (i < j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(less_then(neg(a), b)).c_str(), (-i < j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(less_then(a, neg(b))).c_str(), (i < -j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(less_then(neg(a), neg(b))).c_str(), (-i < -j ? "01" : "00"));

      EXPECT_STREQ(to_string_unsigned_bin(less_or_equal(a, b)).c_str(), (i <= j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(less_or_equal(neg(a), b)).c_str(), (-i <= j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(less_or_equal(a, neg(b))).c_str(), (i <= -j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(less_or_equal(neg(a), neg(b))).c_str(), (-i <= -j ? "01" : "00"));
    }
  }
}

TEST(COMPARISONS, greater) {
  for (auto i = 0; i < loops; ++i) {
    for (auto j = 0; j < loops; ++j) {
      ADELint a = ADELint(to_string(i));
      ADELint b = ADELint(to_string(j));

      EXPECT_STREQ(to_string_unsigned_bin(greater_then(a, b)).c_str(), (i > j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(greater_then(neg(a), b)).c_str(), (-i > j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(greater_then(a, neg(b))).c_str(), (i > -j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(greater_then(neg(a), neg(b))).c_str(), (-i > -j ? "01" : "00"));

      EXPECT_STREQ(to_string_unsigned_bin(greater_or_equal(a, b)).c_str(), (i >= j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(greater_or_equal(neg(a), b)).c_str(), (-i >= j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(greater_or_equal(a, neg(b))).c_str(), (i >= -j ? "01" : "00"));
      EXPECT_STREQ(to_string_unsigned_bin(greater_or_equal(neg(a), neg(b))).c_str(), (-i >= -j ? "01" : "00"));
    }
  }
}



/**************************************************************************** 
 * LOGICAL
 ****************************************************************************/

TEST(LOGICAL, lnot) {
  for (auto i = 0; i < loops; ++i) {
    EXPECT_STREQ(lnot(ADELint(to_string(i))).to_string_unsigned_bin().c_str(), !i ? "01" : "00" );
  }
}

TEST(LOGICAL, land) {
  for (auto i = 1; i < loops; ++i) {
    ADELint o(to_string(i));
    EXPECT_STREQ(land(o, o).to_string_unsigned_bin().c_str(), i && i ? "01" : "00");
    EXPECT_STREQ(land(lnot(o), o).to_string_unsigned_bin().c_str(), !i && i ? "01" : "00");
    EXPECT_STREQ(land(o, lnot(o)).to_string_unsigned_bin().c_str(), i && !i ? "01" : "00");
    EXPECT_STREQ(land(lnot(o), lnot(o)).to_string_unsigned_bin().c_str(), !i && !i ? "01" : "00");
  }
}

TEST(LOGICAL, lor) {
  for (auto i = 1; i < loops; ++i) {
    ADELint o(to_string(i));
    EXPECT_STREQ(lor(o, o).to_string_unsigned_bin().c_str(), i || i ? "01" : "00");
    EXPECT_STREQ(lor(lnot(o), o).to_string_unsigned_bin().c_str(), !i || i ? "01" : "00");
    EXPECT_STREQ(lor(o, lnot(o)).to_string_unsigned_bin().c_str(), i || !i ? "01" : "00");
    EXPECT_STREQ(lor(lnot(o), lnot(o)).to_string_unsigned_bin().c_str(), !i || !i ? "01" : "00");
  }
}

TEST(LOGICAL, lxor) {
  for (auto i = 1; i < loops; ++i) {
    ADELint o(to_string(i));
    EXPECT_STREQ(lxor(o, o).to_string_unsigned_bin().c_str(), "00");
    EXPECT_STREQ(lxor(lnot(o), o).to_string_unsigned_bin().c_str(), "01");
    EXPECT_STREQ(lxor(o, lnot(o)).to_string_unsigned_bin().c_str(), "01");
    EXPECT_STREQ(lxor(lnot(o), lnot(o)).to_string_unsigned_bin().c_str(), "00");
  }
}



/**************************************************************************** 
 * BITWISE
 ****************************************************************************/

TEST(BITWISE, not_and_or_xor) {
  for (auto i = 1; i < loops; ++i) {
    ADELint a(to_string(i));
    ADELint b = bnot(a);
    EXPECT_STREQ(to_string_signed_dec(band(a, b)).c_str(), "0");
    EXPECT_STREQ(to_string_signed_dec(band(a, a)).c_str(), to_string(i).c_str());
    EXPECT_STREQ(to_string_signed_dec(bor(b, b)).c_str(), to_string(-(i+1)).c_str());
    EXPECT_STREQ(to_string_signed_dec(bor(a, b)).c_str(), "-1");
    EXPECT_STREQ(to_string_signed_dec(bor(a, a)).c_str(), to_string(i).c_str());
    EXPECT_STREQ(to_string_signed_dec(bor(b, b)).c_str(), to_string(-(i+1)).c_str());
    EXPECT_STREQ(to_string_signed_dec(bxor(a, b)).c_str(), "-1");
    EXPECT_STREQ(to_string_signed_dec(bxor(a, a)).c_str(), "0");
    EXPECT_STREQ(to_string_signed_dec(bxor(b, b)).c_str(), "0");
  }
}



/**************************************************************************** 
 * SHIFTS
 ****************************************************************************/

TEST(SHIFT, logical_shift_left) {
  for (long long int i = 0; i < (sizeof(long long int) << 3) - 1 - 8; ++i) {
    ADELint n(to_string(i));

    // zero
    ADELint a;
    EXPECT_STREQ(to_string_signed_dec(logical_shift_left(a, n)).c_str(), "0");

    // positive one
    a = ADELint("1", 10, +1);
    EXPECT_STREQ(to_string_signed_dec(logical_shift_left(a, n)).c_str()
        , to_string(static_cast<long long int>(+1) << i).c_str());

    // negative one
    a = ADELint("1", 10, -1);
    EXPECT_STREQ(to_string_signed_dec(logical_shift_left(a, n)).c_str()
        , to_string(static_cast<long long int>(-1) << i).c_str());

    // multibit positive
    a = ADELint("AA", 16, +1);
    EXPECT_STREQ(to_string_signed_dec(logical_shift_left(a, n)).c_str()
        , to_string(static_cast<long long int>(+0xAA) << i).c_str());

    // multibit negative
    a = ADELint("AA", 16, -1);
    EXPECT_STREQ(to_string_signed_dec(logical_shift_left(a, n)).c_str()
        , to_string(static_cast<long long int>(-0xAA) << i).c_str());
  }
}

TEST(SHIFT, logical_shift_right) {
  for (int i = 0; i < (sizeof(int) << 3) - 1 - 8; ++i) {
    ADELint n(to_string(i));

    // zero
    ADELint a;
    EXPECT_STREQ(to_string_signed_dec(logical_shift_right(a, n)).c_str(), "0");

    // positive one (second to highest bit -> not to make it negative)
    a = logical_shift_left(ADELint("1", 10, +1), ADELint(to_string((sizeof(int) << 3) - 2)));
    EXPECT_STREQ(to_string_signed_dec(logical_shift_right(a, n)).c_str()
        , to_string((static_cast<int>(+1) << ((sizeof(int) << 3) - 2)) >> i).c_str());

    // negative one -> should rewrite this not to make it compiler specific
    a = ADELint("1", 2, -1);
    for (int j = 0; j < ((sizeof(int) << 3) - 2); j++) {
      a = bor(logical_shift_left(a, ADELint(to_string(1))), ADELint(to_string(1)));
    }
    EXPECT_STREQ(to_string_signed_dec(logical_shift_right(a, n)).c_str()
        , to_string(static_cast<int>((static_cast<long>(1) << ((sizeof(int) << 3) - i)) - 1)).c_str());
  }
}

TEST(SHIFT, arithmetic_shift_right) {
  for (int i = 0; i < (sizeof(int) << 3) - 1 - 8; ++i) {
    ADELint n(to_string(i));

    // zero
    ADELint a;
    EXPECT_STREQ(to_string_signed_dec(arithmetic_shift_right(a, n)).c_str(), "0");

    // positive one (second to highest bit -> not to make it negative)
    a = logical_shift_left(ADELint("1", 10, +1), ADELint(to_string((sizeof(int) << 3) - 2)));
    EXPECT_STREQ(to_string_signed_dec(arithmetic_shift_right(a, n)).c_str()
        , to_string((static_cast<int>(+1) << ((sizeof(int) << 3) - 2)) >> i).c_str());

    // negative one -> should rewrite this not to make it compiler specific
    a = ADELint("1", 2, -1);
    for (int j = 0; j < ((sizeof(int) << 3) - 2); j++) {
      a = bor(logical_shift_left(a, ADELint(to_string(1))), ADELint(to_string(1)));
    }
    EXPECT_STREQ(to_string_signed_dec(arithmetic_shift_right(a, n)).c_str()
        , to_string((-1 >> i) >> i).c_str());
  }
}



/**************************************************************************** 
 * BIT MANIPULATORS
 ****************************************************************************/

TEST(BIT_MANIPULATORS, set) {
  ADELint p("17", 10, +1);
  ADELint n("17", 10, -1);

  EXPECT_STREQ(set_bits(p, ADELint("2"), ADELint("1")).to_string_unsigned_bin().c_str(), "010001");
  EXPECT_STREQ(set_bits(n, ADELint("2"), ADELint("1")).to_string_unsigned_bin().c_str(), "101111");

  EXPECT_STREQ(set_bits(p, ADELint("1"),ADELint("1")).to_string_unsigned_bin().c_str(), "010011");
  EXPECT_STREQ(set_bits(n, ADELint("4"),ADELint("4")).to_string_unsigned_bin().c_str(), "111111");

  EXPECT_STREQ(set_bits(p, ADELint("0"),ADELint("4")).to_string_unsigned_bin().c_str(), "011111");
  EXPECT_STREQ(set_bits(n, ADELint("0"),ADELint("4")).to_string_unsigned_bin().c_str(), "111111");

  EXPECT_STREQ(set_bits(p, ADELint("6"),ADELint("10")).to_string_unsigned_bin().c_str(), "011111010001");
  EXPECT_STREQ(set_bits(n, ADELint("6"),ADELint("10")).to_string_unsigned_bin().c_str(), "111111101111");

  EXPECT_STREQ(set_bit(p, ADELint("0")).to_string_unsigned_bin().c_str(), "010001");
  EXPECT_STREQ(set_bit(n, ADELint("0")).to_string_unsigned_bin().c_str(), "101111");

  EXPECT_STREQ(set_bit(p, ADELint("1")).to_string_unsigned_bin().c_str(), "010011");
  EXPECT_STREQ(set_bit(n, ADELint("4")).to_string_unsigned_bin().c_str(), "111111");

  EXPECT_STREQ(set_bit(p, ADELint("6")).to_string_unsigned_bin().c_str(), "01010001");
  EXPECT_STREQ(set_bit(n, ADELint("6")).to_string_unsigned_bin().c_str(), "11101111");

  EXPECT_STREQ(set_bit(p, ADELint("8")).to_string_unsigned_bin().c_str(), "0100010001");
  EXPECT_STREQ(set_bit(n, ADELint("8")).to_string_unsigned_bin().c_str(), "1111101111");
}

TEST(BIT_MANIPULATORS, clear) {
  ADELint p("17", 10, +1);
  ADELint n("17", 10, -1);

  EXPECT_STREQ(clear_bits(p, ADELint("2"), ADELint("1")).to_string_unsigned_bin().c_str(), "010001");
  EXPECT_STREQ(clear_bits(n, ADELint("2"), ADELint("1")).to_string_unsigned_bin().c_str(), "101111");

  EXPECT_STREQ(clear_bits(p, ADELint("1"),ADELint("1")).to_string_unsigned_bin().c_str(), "010001");
  EXPECT_STREQ(clear_bits(n, ADELint("4"),ADELint("4")).to_string_unsigned_bin().c_str(), "101111");

  EXPECT_STREQ(clear_bits(p, ADELint("0"),ADELint("4")).to_string_unsigned_bin().c_str(), "000000");
  EXPECT_STREQ(clear_bits(n, ADELint("0"),ADELint("4")).to_string_unsigned_bin().c_str(), "100000");

  EXPECT_STREQ(clear_bits(p, ADELint("6"),ADELint("10")).to_string_unsigned_bin().c_str(), "000000010001");
  EXPECT_STREQ(clear_bits(n, ADELint("6"),ADELint("10")).to_string_unsigned_bin().c_str(), "100000101111");

  EXPECT_STREQ(clear_bit(p, ADELint("0")).to_string_unsigned_bin().c_str(), "010000");
  EXPECT_STREQ(clear_bit(n, ADELint("0")).to_string_unsigned_bin().c_str(), "101110");

  EXPECT_STREQ(clear_bit(p, ADELint("1")).to_string_unsigned_bin().c_str(), "010001");
  EXPECT_STREQ(clear_bit(n, ADELint("4")).to_string_unsigned_bin().c_str(), "101111");

  EXPECT_STREQ(clear_bit(p, ADELint("6")).to_string_unsigned_bin().c_str(), "00010001");
  EXPECT_STREQ(clear_bit(n, ADELint("6")).to_string_unsigned_bin().c_str(), "10101111");

  EXPECT_STREQ(clear_bit(p, ADELint("8")).to_string_unsigned_bin().c_str(), "0000010001");
  EXPECT_STREQ(clear_bit(n, ADELint("8")).to_string_unsigned_bin().c_str(), "1011101111");
}

/*
 not_bit
 get_bit
 get_bit_unsigned
 */


/**************************************************************************** 
 * MASTER
 ****************************************************************************/
int
main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <iostream>
#include <string>

#include "ADELint.h"

using namespace dlib;
using namespace std;

int
main(int argc, char *argv[]) {
  string str_a, str_b;
  int base_a, base_b;
  int signum_a, signum_b;

  cout << "Enter first number digits: ";
  cin >> str_a;
  cout << "Enter first number base: ";
  cin >> base_a;
  cout << "Enter first number signum (<0 -> negative, positive otherwise); ";
  cin >> signum_a;

  cout << "Enter second number digits: ";
  cin >> str_b;
  cout << "Enter second number base: ";
  cin >> base_b;
  cout << "Enter second number signum (<0 -> negative, positive otherwise); ";
  cin >> signum_b;

  // arbitrary base and signum (2nd and 3rd parameter)
  ADELint a = ADELint(str_a, base_a, signum_a);
  ADELint b = ADELint(str_b, base_b, signum_b);

  // converters to string
  cout << endl << "TO STRING:" << endl;
  cout << "a = "
       << to_string_signed_bin(a) << "/bin, "
       << to_string_signed_oct(a) << "/oct, "
       << to_string_signed_dec(a) << "/dec, "
       << to_string_signed_hex(a) << "/hex, "
       << to_string_unsigned_bin(a) << "/ubin, "
       << to_string_unsigned_oct(a) << "/uoct, "
       << to_string_unsigned_hex(a) << "/uhex"
       << endl;
  cout << "b = "
       << to_string_signed_bin(b) << "/bin, "
       << to_string_signed_oct(b) << "/oct, "
       << to_string_signed_dec(b) << "/dec, "
       << to_string_signed_hex(b) << "/hex, "
       << to_string_unsigned_bin(b) << "/ubin, "
       << to_string_unsigned_oct(b) << "/uoct, "
       << to_string_unsigned_hex(b) << "/uhex"
       << endl;

  // converter to int
  cout << endl << "TO INT:" << endl;
  cout << "a = " << to_int(a) << endl;
  cout << "b = " << to_int(b) << endl;

  // arithmetic
  cout << endl << "ARITHMETIC:" << endl;
  cout << "a = " << to_string_signed_dec(a) << endl;
  cout << "b = " << to_string_signed_dec(b) << endl;
  cout << "  - a = " << to_string_signed_dec(neg(a)) << endl;
  cout << "  - b = " << to_string_signed_dec(neg(b)) << endl;
  cout << "a + b = " << to_string_signed_dec(add(a, b)) << endl;
  cout << "a - b = " << to_string_signed_dec(sub(a, b)) << endl;
  cout << "a * b = " << to_string_signed_dec(mul(a, b)) << endl;
  cout << "a / b = " << to_string_signed_dec(div(a, b)) << endl;
  cout << "a \% b = " << to_string_signed_dec(mod(a, b)) << endl;

  // comparison
  cout << endl << "COMPARISON:" << endl;
  cout << "a = " << to_string_signed_dec(a) << endl;
  cout << "b = " << to_string_signed_dec(b) << endl;
  cout << "a == b ? " << (to_int(equal(a, b)) ? "true" : "false") << endl;
  cout << "a != b ? " << (to_int(not_equal(a, b)) ? "true" : "false") << endl;
  cout << "a  < b ? " << (to_int(less_than(a, b)) ? "true" : "false") << endl;
  cout << "a <= b ? " << (to_int(less_or_equal(a, b)) ? "true" : "false") << endl;
  cout << "a  > b ? " << (to_int(greater_than(a, b)) ? "true" : "false") << endl;
  cout << "a >= b ? " << (to_int(greater_or_equal(a, b)) ? "true" : "false") << endl;

  // logical
  cout << endl << "LOGICAL:" << endl;
  cout << "a = " << to_string_signed_dec(a) << endl;
  cout << "b = " << to_string_signed_dec(b) << endl;
  cout << "  not a ? " << (to_int(lnot(a)) ? "true" : "false") << endl;
  cout << "  not b ? " << (to_int(lnot(b)) ? "true" : "false") << endl;
  cout << "a and b ? " << (to_int(land(a, b)) ? "true" : "false") << endl;
  cout << "a  or b ? " << (to_int(lor(a, b)) ? "true" : "false") << endl;
  cout << "a xor b ? " << (to_int(lxor(a, b)) ? "true" : "false") << endl;

  // bitwise
  cout << endl << "BITWISE:" << endl;
  cout << "a = " << to_string_unsigned_bin(a) << endl;
  cout << "b = " << to_string_unsigned_bin(b) << endl;
  cout << "  not a = " << to_string_unsigned_bin(bnot(a)) << endl;
  cout << "  not b = " << to_string_unsigned_bin(bnot(b)) << endl;
  cout << "a and b = " << to_string_unsigned_bin(band(a, b)) << endl;
  cout << "a  or b = " << to_string_unsigned_bin(bor(a, b)) << endl;
  cout << "a xor b = " << to_string_unsigned_bin(bxor(a, b)) << endl;

  // shifts
  cout << endl << "SHIFTS:" << endl;
  cout << "a = " << to_string_unsigned_bin(a) << endl;
  cout << "logical shift left a by one = " << to_string_unsigned_bin(logical_shift_left(a, ADELint("1"))) << endl;
  cout << "logical shift right a by one = " << to_string_unsigned_bin(logical_shift_right(a, ADELint("1"))) << endl;
  cout << "arithmetic shift right a by one = " << to_string_unsigned_bin(arithmetic_shift_right(a, ADELint("1"))) << endl;
  cout << "b = " << to_string_unsigned_bin(b) << endl;
  cout << "logical shift left b by one = " << to_string_unsigned_bin(logical_shift_left(b, ADELint("1"))) << endl;
  cout << "logical shift right b by one = " << to_string_unsigned_bin(logical_shift_right(b, ADELint("1"))) << endl;
  cout << "arithmetic shift right b by one = " << to_string_unsigned_bin(arithmetic_shift_right(b, ADELint("1"))) << endl;

  // bit manipulators
  cout << endl << "BIT MANIPULATORS:" << endl;
  cout << "a = " << to_string_unsigned_bin(a) << endl;
  cout << "set bits 0 through 3 of a = " << to_string_unsigned_bin(set_bits(a, ADELint("0"), ADELint("3"))) << endl;
  cout << "clear bits 0 through 3 of a = " << to_string_unsigned_bin(clear_bits(a, ADELint("0"), ADELint("3"))) << endl;
  cout << "invert bits 0 through 3 of a = " << to_string_unsigned_bin(not_bits(a, ADELint("0"), ADELint("3"))) << endl;
  cout << "get bits 0 through 3 of a = " << to_string_unsigned_bin(get_bits(a, ADELint("0"), ADELint("3"))) << endl;
  cout << "get bits unsigned 0 through 3 of a = " << to_string_unsigned_bin(get_bits_unsigned(a, ADELint("0"), ADELint("3"))) << endl;
  cout << "b = " << to_string_unsigned_bin(b) << endl;
  cout << "set bits 0 through 3 of b = " << to_string_unsigned_bin(set_bits(b, ADELint("0"), ADELint("3"))) << endl;
  cout << "clear bits 0 through 3 of b = " << to_string_unsigned_bin(clear_bits(b, ADELint("0"), ADELint("3"))) << endl;
  cout << "invert bits 0 through 3 of b = " << to_string_unsigned_bin(not_bits(b, ADELint("0"), ADELint("3"))) << endl;
  cout << "get bits 0 through 3 of b = " << to_string_unsigned_bin(get_bits(b, ADELint("0"), ADELint("3"))) << endl;
  cout << "get bits unsigned 0 through 3 of a = " << to_string_unsigned_bin(get_bits_unsigned(b, ADELint("0"), ADELint("3"))) << endl;

  return 0;
}

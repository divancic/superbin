#include <string>

#include "SuperBin.h"

int
main(void) {
  //  SuperBin sb(SuperBin::Sign::POS, "65535", SuperBin::Base::DEC);
  /*
  dlib::SuperBin sb;

  std::string fromNumber("12"), toNumber;
  unsigned int fromBase = 8, toBase = 2;
  sb.fromBaseToBase(fromNumber, fromBase, &toNumber, toBase);

  std::cout
    << fromNumber << " (" << fromBase << ") -> "
    << toNumber << " (" << toBase << ")" << std::endl;

  dlib::SuperBin sb2(fromNumber);
  dlib::SuperBin sb3("10");
  */

  /* TEST za statičke */
  /*
  std::string fromNumber("12"), toNumber;
  unsigned int fromBase = 8, toBase = 2;

  toNumber = dlib::SuperBin::fromBaseToBase(fromNumber, fromBase, toBase);
  std::cout
    << fromNumber << " (" << fromBase << ") -> "
    << toNumber << " (" << toBase << ")" << std::endl;
  */

  /* TEST za to string */
  /*
  {
  dlib::SuperBin sb("12", 10, dlib::SuperBin::Sign::NEG);
  std::cout << sb.to_string_signed_bin() << std::endl;
  std::cout << sb.to_string_signed_oct() << std::endl;
  std::cout << sb.to_string_signed_dec() << std::endl;
  std::cout << sb.to_string_signed_hex() << std::endl;
  sb.test();
  }
  {
  dlib::SuperBin sb("12", 10, dlib::SuperBin::Sign::POS);
  std::cout << sb.to_string_signed_bin() << std::endl;
  std::cout << sb.to_string_signed_oct() << std::endl;
  std::cout << sb.to_string_signed_dec() << std::endl;
  std::cout << sb.to_string_signed_hex() << std::endl;
  }
  */
  dlib::SuperBin::test();
}

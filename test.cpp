#include <string>

#include "SuperBin.h"

int
main(void) {
  //  SuperBin sb(SuperBin::Sign::POS, "65535", SuperBin::Base::DEC);
  SuperBin sb;

  std::string fromNumber("12"), toNumber;
  unsigned int fromBase = 8, toBase = 2;
  sb.fromBaseToBase(fromNumber, fromBase, toNumber, toBase);

  std::cout
    << fromNumber << " (" << fromBase << ") -> "
    << toNumber << " (" << toBase << ")" << std::endl;

  SuperBin sb2(fromNumber);
  SuperBin sb3("10");
}

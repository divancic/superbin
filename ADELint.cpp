#include <string>

#include "ADELint.h"

namespace dlib {

/**
 * Default constructor: constructs 0.
 */
ADELint::ADELint() : SuperBin() {}

/**
 * Constructor which constructs a number passed by in string, in a given base
 * and with a given signum (neagtive if signum < 0, positive if signum >= 0)
 */
ADELint::ADELint(std::string number, int base, int signum) {
  SuperBin(number, base,
    (signum < 0) ? SuperBin::Sign::NEG : SuperBin::Sign::POS);
}

}  // namespace dlib

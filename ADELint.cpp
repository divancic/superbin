#include <string>
#include <iostream>

#include "ADELint.h"

namespace dlib {

/**************************************************************************** 
 * CONSTRUCTORS
 ****************************************************************************/

/**
 * Default constructor: constructs 0
 */
ADELint::ADELint() : SuperBin() {}

/**
 * Constructor which constructs a number passed by in string, in a given base
 * and with a given signum (neagtive if signum < 0, positive if signum >= 0)
 */
ADELint::ADELint(std::string number, int base, int signum) :
  SuperBin(number, base,
      (signum < 0) ? SuperBin::Sign::NEG : SuperBin::Sign::POS) {}

/**
 * Constructor which constructs a number passed by as a pointer to a C-string,
 * in a given base and with a given signum (neagtive if signum < 0, positive
 * if signum >= 0)
 */
ADELint::ADELint(const char *number, int base, int signum) :
  ADELint(std::string(number), base, signum) {}

/**
 * Copy constructor
 */
ADELint::ADELint(const ADELint &src) : SuperBin(src) {}

/**
 * Copy assignment operator
 */
ADELint&
ADELint::operator=(const ADELint &rhs) {
  SuperBin::operator=(rhs);

  return *this;
}



/**************************************************************************** 
 * CONVERTERS TO STRING
 ****************************************************************************/

std::string
ADELint::to_string_signed_bin(void) const {
  return SuperBin::to_string_signed_bin();
}

std::string
ADELint::to_string_signed_oct(void) const {
  return SuperBin::to_string_signed_oct();
}

std::string
ADELint::to_string_signed_dec(void) const {
  return SuperBin::to_string_signed_dec();
}

std::string
ADELint::to_string_signed_hex(void) const {
  return SuperBin::to_string_signed_hex();
}

std::string
ADELint::to_string_unsigned_bin(int no_of_bits) const {
  return SuperBin::to_string_unsigned_bin(no_of_bits);
}

std::string
ADELint::to_string_unsigned_oct(int no_of_bits) const {
  return SuperBin::to_string_unsigned_oct(no_of_bits);
}

std::string
ADELint::to_string_unsigned_hex(int no_of_bits) const {
  return SuperBin::to_string_unsigned_hex(no_of_bits);
}

std::string
to_string_signed_bin(const ADELint &op) {
  return op.to_string_signed_bin();
}

std::string
to_string_signed_oct(const ADELint &op) {
  return op.to_string_signed_oct();
}

std::string
to_string_signed_dec(const ADELint &op) {
  return op.to_string_signed_dec();
}

std::string
to_string_signed_hex(const ADELint &op) {
  return op.to_string_signed_hex();
}

std::string
to_string_unsigned_bin(const ADELint &op, int no_of_bits) {
  return op.to_string_unsigned_bin(no_of_bits);
}

std::string
to_string_unsigned_oct(const ADELint &op, int no_of_bits) {
  return op.to_string_unsigned_oct(no_of_bits);
}

std::string
to_string_unsigned_hex(const ADELint &op, int no_of_bits) {
  return op.to_string_unsigned_hex(no_of_bits);
}



/**************************************************************************** 
 * CONVERTER TO INT
 ****************************************************************************/

int
ADELint::to_int(void) const {
  return SuperBin::to_int();
}

int
to_int(const ADELint &op) {
  return op.to_int();
}



/**************************************************************************** 
 * ARITHMETIC
 ****************************************************************************/
















/**************************************************************************** 
 * ZERO TEST
 ****************************************************************************/
/**************************************************************************** 
 * LOGICAL
 ****************************************************************************/
/**************************************************************************** 
 * BITWISE
 ****************************************************************************/
/**************************************************************************** 
 * SHIFTS
 ****************************************************************************/
/**************************************************************************** 
 * BIT MANIPULATORS
 ****************************************************************************/
/**************************************************************************** 
 * COMPARISONS
 ****************************************************************************/








}  // namespace dlib

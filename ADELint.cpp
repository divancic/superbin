#include <string>
#include <iostream>

#include "ADELint.h"

namespace dlib {

/**************************************************************************** 
 * CONSTRUCTORS
 ****************************************************************************/

/**
 * A private constructor that constructs from the base class.
 */
ADELint::ADELint(const SuperBin& base) {
  m_number = base.to_string_unsigned_bin();
}

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

ADELint
ADELint::neg(void) const {
  return ADELint(SuperBin::neg());
}

ADELint
ADELint::add(const ADELint &rhs) const {
  return ADELint(SuperBin::add(rhs));
}

ADELint
ADELint::sub(const ADELint &rhs) const {
  return ADELint(SuperBin::sub(rhs));
}

ADELint
ADELint::mul(const ADELint &rhs) const {
  return ADELint(SuperBin::mul(rhs));
}

ADELint
ADELint::div(const ADELint &rhs) const {
  return ADELint(::dlib::to_int(rhs) ? SuperBin::div(rhs) : "");
}

ADELint
ADELint::mod(const ADELint &rhs) const {
  return ADELint(::dlib::to_int(rhs) ? SuperBin::mod(rhs) : "");
}

ADELint
neg(const ADELint &op) {
  return op.neg();
}

ADELint
add(const ADELint &lhs, const ADELint &rhs) {
  return lhs.add(rhs);
}

ADELint
sub(const ADELint &lhs, const ADELint &rhs) {
  return lhs.sub(rhs);
}

ADELint
mul(const ADELint &lhs, const ADELint &rhs) {
  return lhs.mul(rhs);
}

ADELint
div(const ADELint &lhs, const ADELint &rhs) {
  return lhs.div(rhs);
}

ADELint
mod(const ADELint &lhs, const ADELint &rhs) {
  return lhs.mod(rhs);
}



/**************************************************************************** 
 * COMPARISONS
 ****************************************************************************/

ADELint
ADELint::equal(const ADELint &rhs) const {
  return ADELint(SuperBin::eq(rhs));
}

ADELint
ADELint::not_equal(const ADELint &rhs) const {
  return ADELint(SuperBin::ne(rhs));
}

ADELint
ADELint::less_then(const ADELint &rhs) const {
  return ADELint(SuperBin::lt(rhs));
}

ADELint
ADELint::less_or_equal(const ADELint &rhs) const {
  return ADELint(SuperBin::le(rhs));
}

ADELint
ADELint::greater_then(const ADELint &rhs) const {
  return ADELint(SuperBin::gt(rhs));
}

ADELint
ADELint::greater_or_equal(const ADELint &rhs) const {
  return ADELint(SuperBin::ge(rhs));
}

ADELint
equal(const ADELint &lhs, const ADELint &rhs) {
  return lhs.equal(rhs);
}

ADELint
not_equal(const ADELint &lhs, const ADELint &rhs) {
  return lhs.not_equal(rhs);
}

ADELint
less_then(const ADELint &lhs, const ADELint &rhs) {
  return lhs.less_then(rhs);
}

ADELint
less_or_equal(const ADELint &lhs, const ADELint &rhs) {
  return lhs.less_or_equal(rhs);
}

ADELint
greater_then(const ADELint &lhs, const ADELint &rhs) {
  return lhs.greater_then(rhs);
}

ADELint
greater_or_equal(const ADELint &lhs, const ADELint &rhs) {
  return lhs.greater_or_equal(rhs);
}



/**************************************************************************** 
 * LOGICAL
 ****************************************************************************/

ADELint
ADELint::lnot(void) const {
  return ADELint(SuperBin::lnot());
}

ADELint
ADELint::land(const ADELint &rhs) const {
  return ADELint(SuperBin::land(rhs));
}

ADELint
ADELint::lor(const ADELint &rhs) const {
  return ADELint(SuperBin::lor(rhs));
}

ADELint
ADELint::lxor(const ADELint &rhs) const {
  return ADELint(SuperBin::lxor(rhs));
}

ADELint
lnot(const ADELint &op) {
  return op.lnot();
}

ADELint
land(const ADELint &lhs, const ADELint &rhs) {
  return lhs.land(rhs);
}

ADELint
lor(const ADELint &lhs, const ADELint &rhs) {
  return lhs.lor(rhs);
}

ADELint
lxor(const ADELint &lhs, const ADELint &rhs) {
  return lhs.lxor(rhs);
}



/**************************************************************************** 
 * BITWISE
 ****************************************************************************/

ADELint
ADELint::bnot(void) const {
  return ADELint(SuperBin::bnot());
}

ADELint
ADELint::band(const ADELint &rhs) const {
  return ADELint(SuperBin::band(rhs));
}

ADELint
ADELint::bor(const ADELint &rhs) const {
  return ADELint(SuperBin::bor(rhs));
}

ADELint
ADELint::bxor(const ADELint &rhs) const {
  return ADELint(SuperBin::bxor(rhs));
}

ADELint
bnot(const ADELint &op) {
  return op.bnot();
}

ADELint
band(const ADELint &lhs, const ADELint &rhs) {
  return lhs.band(rhs);
}

ADELint
bor(const ADELint &lhs, const ADELint &rhs) {
  return lhs.bor(rhs);
}

ADELint
bxor(const ADELint &lhs, const ADELint &rhs) {
  return lhs.bxor(rhs);
}



/**************************************************************************** 
 * SHIFTS
 ****************************************************************************/

ADELint
ADELint::logical_shift_left(const ADELint& no_of_bits) const {
  return ADELint(SuperBin::shl(no_of_bits.to_int()));
}

ADELint
ADELint::logical_shift_right(const ADELint& no_of_bits) const {
  return ADELint(SuperBin::shr(no_of_bits.to_int()));
}

ADELint
ADELint::arithmetic_shift_right(const ADELint& no_of_bits) const {
  return ADELint(SuperBin::sar(no_of_bits.to_int()));
}

ADELint
logical_shift_left(const ADELint& op, const ADELint& no_of_bits) {
  return op.logical_shift_left(no_of_bits);
}

ADELint
logical_shift_right(const ADELint& op, const ADELint& no_of_bits) {
  return op.logical_shift_right(no_of_bits);
}

ADELint
arithmetic_shift_right(const ADELint& op, const ADELint& no_of_bits) {
  return op.arithmetic_shift_right(no_of_bits);
}



/**************************************************************************** 
 * BIT MANIPULATORS
 ****************************************************************************/

ADELint
ADELint::set_bit(const ADELint& pos) const {
  return set_bits(pos, pos);
}

ADELint
ADELint::clear_bit(const ADELint& pos) const {
  return clear_bits(pos, pos);
}

ADELint
ADELint::not_bit(const ADELint& pos) const {
  return not_bits(pos, pos);
}

ADELint
ADELint::get_bit(const ADELint& pos) const {
  return get_bits(pos, pos);
}

ADELint
ADELint::get_bit_unsigned(const ADELint& pos) const {
  return get_bits_unsigned(pos, pos);
}

ADELint
ADELint::set_bits(const ADELint& pos_l, const ADELint& pos_m) const {
  return ADELint(SuperBin::setbs(dlib::to_int(pos_l), dlib::to_int(pos_m)));
}

ADELint
ADELint::clear_bits(const ADELint& pos_l, const ADELint& pos_m) const {
  return ADELint(SuperBin::clearbs(dlib::to_int(pos_l), dlib::to_int(pos_m)));
}

ADELint
ADELint::not_bits(const ADELint& pos_l, const ADELint& pos_m) const {
  return ADELint(SuperBin::notbs(dlib::to_int(pos_l), dlib::to_int(pos_m)));
}

ADELint
ADELint::get_bits(const ADELint& pos_l, const ADELint& pos_m) const {
  return ADELint(SuperBin::getbs(dlib::to_int(pos_l), dlib::to_int(pos_m)));
}

ADELint
ADELint::get_bits_unsigned(const ADELint& pos_l, const ADELint& pos_m) const {
  return ADELint(SuperBin::getubs(dlib::to_int(pos_l), dlib::to_int(pos_m)));
}

ADELint
set_bit(const ADELint& op, const ADELint& pos) {
  return op.set_bit(pos);
}

ADELint
clear_bit(const ADELint& op, const ADELint& pos) {
  return op.clear_bit(pos);
}

ADELint
not_bit(const ADELint& op, const ADELint& pos) {
  return op.not_bit(pos);
}

ADELint
get_bit(const ADELint& op, const ADELint& pos) {
  return op.get_bit(pos);
}

ADELint
get_bit_unsigned(const ADELint& op, const ADELint& pos) {
  return op.get_bit_unsigned(pos);
}

ADELint
set_bits(const ADELint& op, const ADELint& pos_l, const ADELint& pos_m) {
  return op.set_bits(pos_l, pos_m);
}

ADELint
clear_bits(const ADELint& op, const ADELint& pos_l, const ADELint& pos_m) {
  return op.clear_bits(pos_l, pos_m);
}

ADELint
not_bits(const ADELint& op, const ADELint& pos_l, const ADELint& pos_m) {
  return op.not_bits(pos_l, pos_m);
}

ADELint
get_bits(const ADELint& op, const ADELint& pos_l, const ADELint& pos_m) {
  return op.get_bits(pos_l, pos_m);
}

ADELint
get_bits_unsigned(const ADELint& op,
    const ADELint& pos_l, const ADELint& pos_m) {
  return op.get_bits_unsigned(pos_l, pos_m);
}

}  // namespace dlib

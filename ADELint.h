#ifndef ADELINT_H_
#define ADELINT_H_

#include <string>
#include "SuperBin.h"

namespace dlib {


// FORWARD DECLARATIONS: needed because of default parameters
// in friend functions (friends cannot have defaults inside a
// class) + makes these functions available in dlib namespace
class ADELint;
std::string to_string_signed_bin(const ADELint &op);
std::string to_string_signed_oct(const ADELint &op);
std::string to_string_signed_dec(const ADELint &op);
std::string to_string_signed_hex(const ADELint &op);
std::string to_string_unsigned_bin(const ADELint &op, int no_of_bits = 0);
std::string to_string_unsigned_oct(const ADELint &op, int no_of_bits = 0);
std::string to_string_unsigned_hex(const ADELint &op, int no_of_bits = 0);


class ADELint : public SuperBin {
 private:
  // PRIVATE CONSTRUCTOR
  explicit ADELint(const SuperBin& base);

 public:
  // CONSTRUCTORS
  ADELint();
  explicit ADELint(std::string number, int base = 10, int signum = 0);
  explicit ADELint(const char *number, int base = 10, int signum = 0);
  ADELint(const ADELint &src);
  ADELint& operator=(const ADELint &rhs);



  // CONVERTERS TO STRING
  std::string to_string_signed_bin(void) const;
  std::string to_string_signed_oct(void) const;
  std::string to_string_signed_dec(void) const;
  std::string to_string_signed_hex(void) const;

  std::string to_string_unsigned_bin(int no_of_bits = 0) const;
  std::string to_string_unsigned_oct(int no_of_bits = 0) const;
  std::string to_string_unsigned_hex(int no_of_bits = 0) const;

  friend std::string to_string_signed_bin(
      const ADELint &op);
  friend std::string to_string_signed_oct(
      const ADELint &op);
  friend std::string to_string_signed_dec(
      const ADELint &op);
  friend std::string to_string_signed_hex(
      const ADELint &op);

  friend std::string to_string_unsigned_bin(
      const ADELint &op, int no_of_bits);
  friend std::string to_string_unsigned_oct(
      const ADELint &op, int no_of_bits);
  friend std::string to_string_unsigned_hex(
      const ADELint &op, int no_of_bits);



  // CONVERTER TO INT
  int to_int(void) const;

  friend int to_int(
      const ADELint &op);



  // ARITHMETIC (div & mod return zero if rhs == 0)
  ADELint neg(void) const;
  ADELint add(const ADELint &rhs) const;
  ADELint sub(const ADELint &rhs) const;
  ADELint mul(const ADELint &rhs) const;
  ADELint div(const ADELint &rhs) const;
  ADELint mod(const ADELint &rhs) const;

  friend ADELint neg(
      const ADELint &op);
  friend ADELint add(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint sub(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint mul(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint div(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint mod(
      const ADELint &lhs, const ADELint &rhs);



  // COMPARISON (TRUE = -1 | FALSE = 0)
  ADELint equal(const ADELint &rhs) const;
  ADELint not_equal(const ADELint &rhs) const;
  ADELint less_than(const ADELint &rhs) const;
  ADELint less_or_equal(const ADELint &rhs) const;
  ADELint greater_than(const ADELint &rhs) const;
  ADELint greater_or_equal(const ADELint &rhs) const;

  friend ADELint equal(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint not_equal(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint less_than(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint less_or_equal(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint greater_than(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint greater_or_equal(
      const ADELint &lhs, const ADELint &rhs);



  // LOGICAL
  ADELint lnot(void) const;
  ADELint land(const ADELint &rhs) const;
  ADELint lor(const ADELint &rhs) const;
  ADELint lxor(const ADELint &rhs) const;

  friend ADELint lnot(
      const ADELint &op);
  friend ADELint land(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint lor(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint lxor(
      const ADELint &lhs, const ADELint &rhs);



  // BITWISE
  ADELint bnot(void) const;
  ADELint band(const ADELint &rhs) const;
  ADELint bor(const ADELint &rhs) const;
  ADELint bxor(const ADELint &rhs) const;

  friend ADELint bnot(
      const ADELint &op);
  friend ADELint band(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint bor(
      const ADELint &lhs, const ADELint &rhs);
  friend ADELint bxor(
      const ADELint &lhs, const ADELint &rhs);



  // SHIFTS
  ADELint logical_shift_left(const ADELint& no_of_bits) const;
  ADELint logical_shift_right(const ADELint& no_of_bits) const;
  ADELint arithmetic_shift_right(const ADELint& no_of_bits) const;

  friend ADELint
    logical_shift_left(const ADELint& op, const ADELint& no_of_bits);
  friend ADELint
    logical_shift_right(const ADELint& op, const ADELint& no_of_bits);
  friend ADELint
    arithmetic_shift_right(const ADELint& op, const ADELint& no_of_bits);



  // BIT MANIPULATORS
  ADELint set_bit(const ADELint& pos) const;
  ADELint clear_bit(const ADELint& pos) const;
  ADELint not_bit(const ADELint& pos) const;
  ADELint get_bit(const ADELint& pos) const;
  ADELint get_bit_unsigned(const ADELint& pos) const;

  ADELint set_bits(const ADELint& pos_l, const ADELint& pos_m) const;
  ADELint clear_bits(const ADELint& pos_l, const ADELint& pos_m) const;
  ADELint not_bits(const ADELint& pos_l, const ADELint& pos_m) const;
  ADELint get_bits(const ADELint& pos_l, const ADELint& pos_m) const;
  ADELint get_bits_unsigned(const ADELint& pos_l, const ADELint& pos_m) const;

  friend ADELint set_bit(
      const ADELint& op, const ADELint& pos);
  friend ADELint clear_bit(
      const ADELint& op, const ADELint& pos);
  friend ADELint not_bit(
      const ADELint& op, const ADELint& pos);
  friend ADELint get_bit(
      const ADELint& op, const ADELint& pos);
  friend ADELint get_bit_unsigned(
      const ADELint& op, const ADELint& pos);

  friend ADELint set_bits(const ADELint& op,
      const ADELint& pos_l, const ADELint& pos_m);
  friend ADELint clear_bits(const ADELint& op,
      const ADELint& pos_l, const ADELint& pos_m);
  friend ADELint not_bits(const ADELint& op,
      const ADELint& pos_l, const ADELint& pos_m);
  friend ADELint get_bits(const ADELint& op,
      const ADELint& pos_l, const ADELint& pos_m);
  friend ADELint get_bits_unsigned(const ADELint& op,
      const ADELint& pos_l, const ADELint& pos_m);
};

};  // namespace dlib

#endif  // ADELINT_H_

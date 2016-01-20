#ifndef ADELINT_H_
#define ADELINT_H_

#include <string>
#include "SuperBin.h"

namespace dlib {

class ADELint : public SuperBin {
 public:
  // CONSTRUCTORS
  ADELint();
  explicit ADELint(std::string number, int base = 10, int signum = 0);
  explicit ADELint(const char *number, int base = 10, int signum = 0);
  ADELint(const ADELint &src);
  ADELint& operator=(const ADELint &rhs);



  // CONVERTERS TO STRING
  /*
  std::string to_string_signed_bin(void) const;
  std::string to_string_signed_oct(void) const;
  std::string to_string_signed_dec(void) const;
  std::string to_string_signed_hex(void) const;

  std::string to_string_unsigned_bin(int no_of_bits = 0) const;
  std::string to_string_unsigned_oct(int no_of_bits = 0) const;
  std::string to_string_unsigned_hex(int no_of_bits = 0) const;

  friend std::string to_string_signed_bin(const ADELint &lhs);
  friend std::string to_string_signed_oct(const ADELint &lhs);
  friend std::string to_string_signed_dec(const ADELint &lhs);
  friend std::string to_string_signed_hex(const ADELint &lhs);

  friend std::string to_string_unsigned_bin(const ADELint &lhs, int no_of_bits);
  friend std::string to_string_unsigned_oct(const ADELint &lhs, int no_of_bits);
  friend std::string to_string_unsigned_hex(const ADELint &lhs, int no_of_bits);
  */



  // CONVERTER TO INT
  int to_int(void) const;

  friend int to_int(const ADELint &lhs);



  // ARITHMETIC (div & mod return zero if rhs == 0)
  ADELint neg(void) const;
  ADELint add(const ADELint &rhs) const;
  ADELint sub(const ADELint &rhs) const;
  ADELint mul(const ADELint &rhs) const;
  ADELint div(const ADELint &rhs) const;
  ADELint mod(const ADELint &rhs) const;

  friend ADELint neg(const ADELint &lhs);
  friend ADELint add(const ADELint &lhs, const ADELint &rhs);
  friend ADELint sub(const ADELint &lhs, const ADELint &rhs);
  friend ADELint mul(const ADELint &lhs, const ADELint &rhs);
  friend ADELint div(const ADELint &lhs, const ADELint &rhs);
  friend ADELint mod(const ADELint &lhs, const ADELint &rhs);



  // COMPARISON (TRUE = -1 | FALSE = 0)
  ADELint equal(const ADELint &rhs) const;
  ADELint not_equal(const ADELint &rhs) const;
  ADELint less_then(const ADELint &rhs) const;
  ADELint less_or_equal(const ADELint &rhs) const;
  ADELint greater_then(const ADELint &rhs) const;
  ADELint greater_or_equal(const ADELint &rhs) const;

  friend ADELint equal(const ADELint &lhs, const ADELint &rhs);
  friend ADELint not_equal(const ADELint &lhs, const ADELint &rhs);
  friend ADELint less_then(const ADELint &lhs, const ADELint &rhs);
  friend ADELint less_or_equal(const ADELint &lhs, const ADELint &rhs);
  friend ADELint greater_then(const ADELint &lhs, const ADELint &rhs);
  friend ADELint greater_or_equal(const ADELint &lhs, const ADELint &rhs);



  // LOGICAL (TRUE = -1 | FALSE = 0)
  ADELint lnot(void) const;
  ADELint land(const ADELint &rhs) const;
  ADELint lor(const ADELint &rhs) const;
  ADELint lxor(const ADELint &rhs) const;

  friend ADELint lnot(const ADELint &lhs);
  friend ADELint land(const ADELint &lhs, const ADELint &rhs);
  friend ADELint lor(const ADELint &lhs, const ADELint &rhs);
  friend ADELint lxor(const ADELint &lhs, const ADELint &rhs);



  // BITWISE
  ADELint bnot(void) const;
  ADELint band(const ADELint &rhs) const;
  ADELint bor(const ADELint &rhs) const;
  ADELint bxor(const ADELint &rhs) const;

  friend ADELint bnot(const ADELint &lhs);
  friend ADELint band(const ADELint &lhs, const ADELint &rhs);
  friend ADELint bor(const ADELint &lhs, const ADELint &rhs);
  friend ADELint bxor(const ADELint &lhs, const ADELint &rhs);



  // SHIFTS
  ADELint logical_shift_left(ADELint no_of_bits) const;
  ADELint logical_shift_right(ADELint no_of_bits) const;
  ADELint arithmetic_shift_right(ADELint no_of_bits) const;

  friend ADELint logical_shift_left(const ADELint &lhs, ADELint no_of_bits);
  friend ADELint logical_shift_right(const ADELint &lhs, ADELint no_of_bits);
  friend ADELint arithmetic_shift_right(const ADELint &lhs, ADELint no_of_bits);



  // BIT
  ADELint set_bit(ADELint index) const;
  ADELint clear_bit(ADELint index) const;
  ADELint not_bit(ADELint index) const;
  ADELint get_bit(ADELint index) const;
  ADELint get_bit_unsigned(ADELint index) const;

  ADELint set_bits(ADELint index_l, ADELint index_m) const;
  ADELint clear_bits(ADELint index_l, ADELint index_m) const;
  ADELint not_bits(ADELint index_l, ADELint index_m) const;
  ADELint get_bits(ADELint index_l, ADELint index_m) const;
  ADELint get_bits_unsigned(ADELint index_l, ADELint index_m) const;

  friend ADELint set_bit(const ADELint &lhs, ADELint index);
  friend ADELint clear_bit(const ADELint &lhs, ADELint index);
  friend ADELint not_bit(const ADELint &lhs, ADELint index);
  friend ADELint get_bit(const ADELint &lhs, ADELint index);
  friend ADELint get_bit_unsigned(const ADELint &lhs, ADELint index);

  friend ADELint set_bits(const ADELint &lhs, ADELint pos_l, ADELint pos_m);
  friend ADELint clear_bits(const ADELint &lhs, ADELint pos_l, ADELint pos_m);
  friend ADELint not_bits(const ADELint &lhs, ADELint pos_l, ADELint pos_m);
  friend ADELint get_bits(const ADELint &lhs, ADELint pos_l, ADELint pos_m);
  friend ADELint
    get_bits_unsigned(const ADELint &lhs, ADELint pos_l, ADELint pos_m);
};

};  // namespace dlib

#endif  // ADELINT_H_

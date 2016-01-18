#ifndef ADELINT_H_
#define ADELINT_H_

namespace dlib {

class AdelInt {
 public:
  // CONSTRUCTORS
  AdelInt();
  AdelInt(std::string number, int base = 10, int signum);
  AdelInt(const char *number, int base = 10, int signum);
  AdelInt(const AdelInt &src);
  AdelInt& operator=(const AdelInt &rhs);



  // CONVERTERS TO STRING
  std::string to_string_signed_bin(void) const;
  std::string to_string_signed_oct(void) const;
  std::string to_string_signed_dec(void) const;
  std::string to_string_signed_hex(void) const;

  std::string to_string_unsigned_bin(int no_of_bits = 0) const;
  std::string to_string_unsigned_oct(int no_of_bits = 0) const;
  std::string to_string_unsigned_hex(int no_of_bits = 0) const;

  friend std::string to_string_signed_bin(const AdelInt &lhs) const;
  friend std::string to_string_signed_oct(const AdelInt &lhs) const;
  friend std::string to_string_signed_dec(const AdelInt &lhs) const;
  friend std::string to_string_signed_hex(const AdelInt &lhs) const;

  friend std::string to_string_unsigned_bin(const AdelInt &lhs, int no_of_bits = 0) const;
  friend std::string to_string_unsigned_oct(const AdelInt &lhs, int no_of_bits = 0) const;
  friend std::string to_string_unsigned_hex(const AdelInt &lhs, int no_of_bits = 0) const;



  // CONVERTER TO INT
  int to_int(void) const;

  friend int to_int(const AdelInt &lhs);



  // ARITHMETIC (div & mod return zero if rhs == 0)
  AdelInt neg(void) const;
  AdelInt add(const AdelInt &rhs) const;
  AdelInt sub(const AdelInt &rhs) const;
  AdelInt mul(const AdelInt &rhs) const;
  AdelInt div(const AdelInt &rhs) const;
  AdelInt mod(const AdelInt &rhs) const;

  friend AdelInt neg(const AdelInt &lhs);
  friend AdelInt add(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt sub(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt mul(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt div(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt mod(const AdelInt &lhs, const AdelInt &rhs);



  // COMPARISON (TRUE = -1 | FALSE = 0)
  AdelInt equal(const AdelInt &rhs) const;
  AdelInt not_equal(const AdelInt &rhs) const;
  AdelInt less_then(const AdelInt &rhs) const;
  AdelInt less_or_equal(const AdelInt &rhs) const;
  AdelInt greater_then(const AdelInt &rhs) const;
  AdelInt greater_or_equal(const AdelInt &rhs) const;

  friend AdelInt equal(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt not_equal(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt less_then(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt less_or_equal(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt greater_then(const AdelInt &lhs, const AdelInt &rhs);
  friend AdelInt greater_or_equal(const AdelInt &lhs, const AdelInt &rhs);



  // LOGICAL (TRUE = -1 | FALSE = 0)
  AdelInt lnot(void) const;
  AdelInt land(const AdelInt &rhs) const;
  AdelInt lor(const AdelInt &rhs) const;
  AdelInt lxor(const AdelInt &rhs) const;

  friend AdelInt lnot(const AdelInt &lhs) const;
  friend AdelInt land(const AdelInt &lhs, const AdelInt &rhs) const;
  friend AdelInt lor(const AdelInt &lhs, const AdelInt &rhs) const;
  friend AdelInt lxor(const AdelInt &lhs, const AdelInt &rhs) const;



  // BITWISE
  AdelInt bnot(void) const;
  AdelInt band(const AdelInt &rhs) const;
  AdelInt bor(const AdelInt &rhs) const;
  AdelInt bxor(const AdelInt &rhs) const;

  friend AdelInt bnot(const AdelInt &lhs) const;
  friend AdelInt band(const AdelInt &lhs, const AdelInt &rhs) const;
  friend AdelInt bor(const AdelInt &lhs, const AdelInt &rhs) const;
  friend AdelInt bxor(const AdelInt &lhs, const AdelInt &rhs) const;



  // SHIFTS
  AdelInt logical_shift_left(AdelInt no_of_bits) const;
  AdelInt logical_shift_right(AdelInt no_of_bits) const;
  AdelInt arithmetic_shift_right(AdelInt no_of_bits) const;

  friend AdelInt logical_shift_left(const AdelInt &lhs, AdelInt no_of_bits) const;
  friend AdelInt logical_shift_right(const AdelInt &lhs, AdelInt no_of_bits) const;
  friend AdelInt arithmetic_shift_right(const AdelInt &lhs, AdelInt no_of_bits) const;



  // BIT
  AdelInt set_bit(AdelInt index) const;
  AdelInt clear_bit(AdelInt index) const;
  AdelInt not_bit(AdelInt index) const;
  AdelInt get_bit(AdelInt index) const;
  AdelInt get_bit_unsigned(AdelInt index) const;

  AdelInt set_bits(AdelInt index_l, AdelInt index_m) const;
  AdelInt clear_bits(AdelInt index_l, AdelInt index_m) const;
  AdelInt not_bits(AdelInt index_l, AdelInt index_m) const;
  AdelInt get_bits(AdelInt index_l, AdelInt index_m) const;
  AdelInt get_bits_unsigned(AdelInt index_l, AdelInt index_m) const;

  friend AdelInt set_bit(const AdelInt &lhs, AdelInt index) const;
  friend AdelInt clear_bit(const AdelInt &lhs, AdelInt index) const;
  friend AdelInt not_bit(const AdelInt &lhs, AdelInt index) const;
  friend AdelInt get_bit(const AdelInt &lhs, AdelInt index) const;
  friend AdelInt get_bit_unsigned(const AdelInt &lhs, AdelInt index) const;

  friend AdelInt set_bits(const AdelInt &lhs, AdelInt index_l, AdelInt index_m) const;
  friend AdelInt clear_bits(const AdelInt &lhs, AdelInt index_l, AdelInt index_m) const;
  friend AdelInt not_bits(const AdelInt &lhs, AdelInt index_l, AdelInt index_m) const;
  friend AdelInt get_bits(const AdelInt &lhs, AdelInt index_l, AdelInt index_m) const;
  friend AdelInt get_bits_unsigned(const AdelInt &lhs, AdelInt index_l, AdelInt index_m) const;
};

};  // namespace dlib

#endif  // ADELINT_H_

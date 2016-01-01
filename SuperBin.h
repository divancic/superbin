#ifndef SUPERBIN_H_
#define SUPERBIN_H_

#include <string>

namespace dlib {

class SuperBin {
 public:
  /**
   * An enum describing signum.
   */
  enum class Sign : char { POS = '0', NEG = '1' };

 private:
  /**
   * Number is represented by std::string object. Each character represents
   * one binary digit. The upper bit represents signum - 0 positive or zero,
   * 1 negative. If it is a negative, it is a 2's complement representation
   * of the equal positive number.
   */
  std::string m_number;

 public:
  /**************************************************************************** 
   * STATIC FUNCTIONS
   ****************************************************************************/

  /**
   * Converts number fromNumber in base fromBase to toNumber in base toBase.
   * Numbers are passed as a reference to std::string (fromNumber) and
   * pointer to std::string (toNumber). Bases are passed as unsigned int.
   *
   * \param fromNumber number to be converted
   * \param fromBase number to be converted is in this base
   * \param toNumber pointer to std::string where result is going to be stored
   * \param toBase base of the resulting number
   *
   * This function is static in order to be called without an object creation,
   * e.g. dlib::SuperBin::fromBaseToBase(...);
   */
  static void
  fromBaseToBase(
        const std::string &fromNumber
      , unsigned int fromBase
      , std::string *toNumber
      , unsigned int toBase);

  /**
   * Converts number fromNumber in base fromBase to a number in base toBase.
   * Number is returned as a std::string object.
   *
   * \param fromNumber number to be converted
   * \param fromBase number to be converted is in this base
   * \param toBase base of the resulting number
   *
   * \return std::string object representing converted number
   *
   * This function is static in order to be called without an object creation,
   * e.g. dlib::SuperBin::fromBaseToBase(...);
   */
  static std::string
  fromBaseToBase(
        const std::string &fromNumber
      , unsigned int fromBase
      , unsigned int toBase) {
    std::string toNumber;
    fromBaseToBase(fromNumber, fromBase, &toNumber, toBase);
    return (toNumber);
  }



  /**************************************************************************** 
   * CONSTRUCTORS
   ****************************************************************************/

  /**
   * Default constructor constructs 'zero'.
   */
  SuperBin();

  /**
   * \param number a string representation of the number to be constructed
   * \param base a number's base (default 10)
   * \param sign a sign (default positive)
   */
  SuperBin(
      std::string number
    , unsigned int base = 10
    , Sign sign = Sign::POS);

  /**
   * \param number a const char* representation of the number to be constructed
   * \param base a number's base (default 10)
   * \param sign a sign (default positive)
   */
  SuperBin(
      const char *number
    , unsigned int base = 10
    , Sign sign = Sign::POS);

  /**
   * \param bool_value boolean value of the number to be constructed
   */
  SuperBin(
      bool bool_value);

  /**
   * Copy constructor.
   */
  SuperBin(
      const SuperBin& rhs);

  /**
   * Copy assignment operator.
   */
  SuperBin& operator=(
      const SuperBin& rhs);



  /**************************************************************************** 
   * NUMBER SIZE
   ****************************************************************************/

  /**
   * Cast into new SuperBin with the given number of bits.
   * If the requested bitsize is greater than the current size the number will
   * be expanded according to the signum (with ones if it is negative or with
   * zeros if it is postivie). On the other hand, if the requested bitsize iz
   * smaller than the current size number will be shorten optimally (e.g.
   * 0000010 -> 010, 111111110 -> 10, etc.)
   */
  SuperBin
  cast(
      unsigned int no_of_bits = 0) const;

  /**
   * Get the current size (in bits).
   */
  unsigned int
  size(
      void) const;



  /**************************************************************************** 
   * CONVERTERS TO STRING
   ****************************************************************************/

  /**
   * This function converts a number to a std::string.
   *
   * \param base the base requested.
   * \param out_sign_pos print signum for positive numbers.
   * \param out_sign_neg print signum for negative numbers.
   */
  std::string
  to_string_signed(
      unsigned int base
    , bool out_sign_pos = false
    , bool out_sign_neg = true) const;

  /**
   * \return String containing a signed number in binary.
   */
  std::string
  to_string_signed_bin(
      void) const;

  /**
   * \return String containing a signed number in octal.
   */
  std::string
  to_string_signed_oct(
      void) const;

  /**
   * \return String containing a signed number in decimal.
   */
  std::string
  to_string_signed_dec(
      void) const;

  /**
   * \return String containing a signed number in hexadecimal.
   */
  std::string
  to_string_signed_hex(
      void) const;

  /**
   * This method returns a number in a string in a binary format. If negative,
   * the 2's complement is returned. The parameter dictates how many bits is
   * returned. If the number is smaller than requested number of bits it will
   * be padded with 0 or 1 depending on signum. If the number is larger
   * only adequate amount of least significant bits will be returned.
   *
   * \param no_of_bits Number of bits to output (default: 0 = all).
   *
   * \return String containing an unsigned number in binary.
   */
  std::string
  to_string_unsigned_bin(
      unsigned int no_of_bits = 0) const;

  /**
   * This method returns a number in a string in a octal format. If
   * negative, the 2's complement is returned. The parameter dictates how many
   * bits is returned. If the number is smaller than requested number of bits
   * it will be padded with 0 or 1 depending on signum. If the number is larger
   * only adequate amount of least significant bits will be returned.
   *
   * Note: one oct digit represent three bits.
   *
   * \param no_of_bits Number of bits to output (default: 0 = all).
   *
   * \return String containing an unsigned number in octal format.
   */
  std::string
  to_string_unsigned_oct(
      unsigned int no_of_bits = 0) const;

  /**
   * This method returns a number in a string in a hexadecimal format. If
   * negative, the 2's complement is returned. The parameter dictates how many
   * bits is returned. If the number is smaller than requested number of bits
   * it will be padded with 0 or 1 depending on signum. If the number is larger
   * only adequate amount of least significant bits will be returned.
   *
   * Note: one hex digit represent four bits.
   *
   * \param no_of_bits Number of bits to output (default: 0 = all).
   *
   * \return String containing an unsigned number in hexadecimal format.
   */
  std::string
  to_string_unsigned_hex(
      unsigned int no_of_bits = 0) const;



  /**************************************************************************** 
   * CONVERTER TO INT
   ****************************************************************************/

  /**
   * This method converts to integer.
   *
   * Todo(doki): size check? converter to other (larger) types?
   *
   * \return Returns an integer.
   */
  int
  to_int(
      void) const;



  /**************************************************************************** 
   * ZERO TEST
   ****************************************************************************/

  /**
   * Zero check.
   *
   * \return true if zero, false otherwise.
   */
  bool
  tz(
      void) const;

  /**
   * Check if not zero.
   *
   * \return true if not zero, false otherwise.
   */
  bool
  tnz(
      void) const;



  /**************************************************************************** 
   * LOGICAL
   ****************************************************************************/

  /**
   * c-like logical not.
   * (zero is interpreted as false, other numbers as true)
   *
   * \return true if zero, false otherwise.
   */
  SuperBin
  lnot(
      void) const;

  /**
   * c-like logical and.
   * (zero is interpreted as false, other numbers as true)
   *
   * \param rhs Right hand side operand.
   *
   * \return true if neither operand is zero.
   */
  SuperBin
  land(
      const SuperBin &rhs) const;

  /**
   * c-like logical or.
   * (zero is interpreted as false, other numbers as true)
   *
   * \param rhs Right hand side operand.
   *
   * \return true if either operand not zero.
   */
  SuperBin
  lor(
      const SuperBin &rhs) const;

  /**
   * c-like logical xor.
   * (zero is interpreted as false, other numbers as true)
   *
   * \param rhs Right hand side operand.
   *
   * \return true if one IS zero and the other IS NOT zero.
   */
  SuperBin
  lxor(
      const SuperBin &rhs) const;



  /**************************************************************************** 
   * BITWISE
   ****************************************************************************/

  /**
   * Bitwise not.
   *
   * \return bitwise not.
   */
  SuperBin
  bnot(
      void) const;

  /**
   * Bitwise and.
   *
   * \param rhs Right hand side operand.
   *
   * \return bitwise and of two operands.
   */
  SuperBin
  band(
      const SuperBin &rhs) const;

  /**
   * Bitwise or.
   *
   * \param rhs Right hand side operand.
   *
   * \return bitwise or of two operands.
   */
  SuperBin
  bor(
      const SuperBin &rhs) const;

  /**
   * Bitwise xor.
   *
   * \param rhs Right hand side operand.
   *
   * \return bitwise xor of two operands.
   */
  SuperBin
  bxor(
      const SuperBin &rhs) const;



  /**************************************************************************** 
   * SHIFTS
   ****************************************************************************/

  /**
   * Logical shift left by given number of bits.
   *
   * \param no_of_bits number of bits to shift by.
   *
   * \return number shifted left by given number of bits.
   */
  SuperBin
  shl(
      unsigned int no_of_bits) const;

  /**
   * Logical shift right by given number of bits.
   *
   * \param no_of_bits number of bits to shift by.
   *
   * \return number shifted right by given number of bits.
   */
  SuperBin
  shr(
      unsigned int no_of_bits) const;

  /**
   * Arithmetic shift left by given number of bits.
   * (equal to logical shift left - added for completeness)
   *
   * \param no_of_bits number of bits to shift by.
   *
   * \return number (arithmetically) shifted left by given number of bits.
   */
  SuperBin
  sal(
      unsigned int no_of_bits) const;

  /**
   * Arithmetic shift right by given number of bits.
   * (if the number is positive, the most significant bit is
   * set to 0, otherwise, if the number is negative the most
   * significant bit is set to 1)
   *
   * \param no_of_bits number of bits to shift by.
   *
   * \return number (arithmetically) shifted right by given number of bits.
   */
  SuperBin
  sar(
      unsigned int no_of_bits) const;



  /**************************************************************************** 
   * BIT MANIPULATORS
   ****************************************************************************/

  /**
   * Set all bits at indexes between (and including) n and m.
   *
   * \param index_n starting index
   * \param index_m ending index
   *
   * \return new object with requested bits set.
   */
  SuperBin
  setb(
      unsigned int index_n
    , unsigned int index_m) const;

  /**
   * Clear all bits at indexes between (and including) n and m.
   *
   * \param index_n starting index
   * \param index_m ending index
   *
   * \return new object with requested bits cleared.
   */
  SuperBin
  clearb(
      unsigned int index_n
    , unsigned int index_m) const;

  /**
   * Inverse state of all bits at indexes between (and including) n and m.
   *
   * \param index_n starting index
   * \param index_m ending index
   *
   * \return new object with requested bits inverted.
   */
  SuperBin
  notb(
      unsigned int index_n
    , unsigned int index_m) const;

  /**
   * Get all bits at indexes between (and including) n and m.
   *
   * \param index_n starting index
   * \param index_m ending index
   *
   * \return new object with requested bits.
   */
  SuperBin
  getb(
      unsigned int index_n
    , unsigned int index_m) const;



  /**************************************************************************** 
   * COMPARISONS
   ****************************************************************************/

  /**
   * EQual.
   *
   * \param rhs Right hand side operand.
   *
   * \return true if equal, false otherwise.
   */
  bool
  eq(
      const SuperBin &rhs) const;

  /**
   * Not Equal.
   *
   * \param rhs Right hand side operand.
   *
   * \return true if not equal, false otherwise.
   */
  bool
  ne(
      const SuperBin &rhs) const;

  /**
   * Less Then.
   *
   * \param rhs Right hand side operand.
   *
   * \return true if less, false otherwise.
   */
  bool
  lt(
      const SuperBin &rhs) const;

  /**
   * Less or Equal.
   *
   * \param rhs Right hand side operand.
   *
   * \return true if less or equal, false otherwise.
   */
  bool
  le(
      const SuperBin &rhs) const;

  /**
   * Greater Then.
   *
   * \param rhs Right hand side operand.
   *
   * \return true if greater, false otherwise.
   */
  bool
  gt(
      const SuperBin &rhs) const;

  /**
   * Greater or Equal.
   *
   * \param rhs Right hand side operand.
   *
   * \return true if greater or equal, false otherwise.
   */
  bool
  ge(
      const SuperBin &rhs) const;



  /**************************************************************************** 
   * ARITHMETIC FUNCTIONS
   ****************************************************************************/

  /**
   * \return Returns a 2's complement.
   */
  SuperBin
  neg(
      void) const;

  /**
   * \return Increment by one.
   */
  SuperBin
  inc(
      void) const;

  /**
   * \return Decrement by one.
   */
  SuperBin
  dec(
      void) const;

  /**
   * \param rhs Right hand side operand.
   *
   * \return Sum of two numbers.
   */
  SuperBin
  add(
      const SuperBin &rhs) const;

  /**
   * \param rhs Right hand side operand.
   *
   * \return Subtraction of two numbers.
   */
  SuperBin
  sub(
      const SuperBin &rhs) const;

  /**
   * \param rhs Right hand side operand.
   *
   * \return Multiplication of two numbers.
   */
  SuperBin
  mul(
      const SuperBin &rhs) const;

  /**
   * \param rhs Right hand side operand.
   *
   * \return Division of two numbers.
   */
  SuperBin
  div(
      const SuperBin &rhs) const;

  /**
   * \param rhs Right hand side operand.
   *
   * \return Mod of two numbers.
   */
  SuperBin
  mod(
      const SuperBin &rhs) const;
};

}  // namespace dlib

#endif  // SUPERBIN_H_

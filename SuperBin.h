#ifndef SUPERBIN_H_
#define SUPERBIN_H_

#include <string>

namespace dlib {

class SuperBin {
 public:
  /**
   * An enum describing signum.
   */
  enum Class Sign { POS = 0, NEG = 1 };

 private:
  std::string m_number;

 public:
  static void
  fromBaseToBase(
        const std::string &fromNumber
      , unsigned int fromBase
      , std::string *toNumber
      , unsigned int toBase);

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
   * \param number a string representation of the number to be constructed.
   * \param base a number's base (default 10)
   * \param sign a sign (default positive)
   */
  explicit
  SuperBin(
      std::string number
    , unsigned int base = 10
    , Sign sign = Sign::POS);



  /**************************************************************************** 
   * CONVERTERS TO STRING
   ****************************************************************************/

  /**
   * This function converts a number to a std::string.
   *
   * \param base the base requested.
   * \param out_sign_pos is signum required for positive numbers.
   * \param out_sign_neg is signum required for negative numbers.
   */
  std::string
  to_string_signed(
      unsigned int base
    , bool out_sign_pos = false
    , bool out_sign_neg = true) const;

  /**
   * \return String containing a signen number in binary.
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
   * \param no_of_bits Number of bits to output.
   *
   * \return String containing an unsigned number in binary.
   *
   * \sa to_string_unsigned_hex()
   */
  std::string
  to_string_unsigned_bin(
      unsigned int no_of_bits) const;

  /**
   * This method returns a number in a string in a hexadecimal format. If
   * negative, the 2's complement is returned. The parameter dictates how many
   * bits is returned. If the number is smaller than requested number of bits
   * it will be padded with 0 or 1 depending on signum. If the number is larger
   * only adequate amount of least significant bits will be returned.
   *
   * Note: one hex digit represent four bits.
   *
   * \param no_of_bits Number of bits to output.
   *
   * \return String containing an unsigned number in hexadecimal format.
   *
   * \sa to_string_unsigned_bin()
   */
  std::string
  to_string_unsigned_hex(
      unsigned int no_of_bits) const;



  /**************************************************************************** 
   * CONVERTER TO INT
   ****************************************************************************/

  /**
   * This method converts to integer.
   *
   * Todo(doki): size check?
   *
   * \return Returns an integer.
   */
  int
  to_int(
      void) const;



  /**************************************************************************** 
   * CHECK IF ZERO?
   ****************************************************************************/

  /**
   * Zero check.
   *
   * \return true if zero, false otherwise.
   */
  bool
  is_zero(
      void) const;



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
   * \param rhs Right hand side.
   *
   * \return Sum of two numbers.
   */
  SuperBin
  add(
      const SuperBin &rhs) const;

  /**
   * \param rhs Right hand side.
   *
   * \return Subtraction of two numbers.
   */
  SuperBin
  sub(
      const SuperBin &rhs) const;

  /**
   * \param rhs Right hand side.
   *
   * \return Multiplication of two numbers.
   */
  SuperBin
  mul(
      const SuperBin &rhs) const;

  /**
   * \param rhs Right hand side.
   *
   * \return Division of two numbers.
   */
  SuperBin
  div(
      const SuperBin &rhs) const;

  /**
   * \param rhs Right hand side.
   *
   * \return Mod of two numbers.
   */
  SuperBin
  mod(
      const SuperBin &rhs) const;
};

}  // namespace dlib

#endif  // SUPERBIN_H_

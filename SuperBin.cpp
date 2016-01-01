#include <vector>
#include <queue>
#include <string>
#include <iostream>

#include "SuperBin.h"

namespace dlib {

/**************************************************************************** 
 * CONSTRUCTORS
 ****************************************************************************/

/**
 * Default constructor: construct zero.
 */
SuperBin::SuperBin() {
  m_number = "00";
}

/**
 * Full-blown constructor (pt.1).
 */
SuperBin::SuperBin(
    std::string number
  , unsigned int base
  , Sign sign) {
  m_number = SuperBin::fromBaseToBase(number, base, 2);

  // insert signum bit
  m_number.insert(m_number.begin(), '0');

  // construct a 2's complement if it is a negative number
  if (Sign::NEG == sign) { m_number = bnot().inc().m_number; }
}

/**
 * Full-blown constructor (pt.2)
 *
 * NOTE: need to have this constructor! if it would not exist, when creating
 * object with SuperBin("...") a string would be interpreted as a const char*
 * which is then converted to bool (rather than constructing a std::string
 * object) and the object ends up constructed with SuperBin(bool). to
 * explicitly construct with SuperBin(std::string, ...) one would have to
 * call a constructor like this: ... SuperBin(std::string("..."),...
 * i wanted to avoid this. also note this ctor is defined as delegating one
 * (calls SuperBin(std::string, ...) to do the real work).
 */
SuperBin::SuperBin(
    const char *number
  , unsigned int base
  , Sign sign) : SuperBin(std::string(number), base, sign) {}

/**
 * Boolean constructor.
 */
SuperBin::SuperBin(
    bool bool_value) {
  m_number = bool_value ? "01" : "00";
}

/**
 * Copy constructor.
 */
SuperBin::SuperBin(
    const SuperBin& rhs) {
  m_number = rhs.m_number;
}

/**
 * Copy assignment operator.
 */
SuperBin&
SuperBin::operator=(
    const SuperBin &rhs) {
  m_number = rhs.m_number;
  return *this;
}



/**************************************************************************** 
 * SIZE
 ****************************************************************************/
/**
 * Cast into new SuperBin with the given number of bits.
 */
SuperBin
SuperBin::cast(
    unsigned int no_of_bits) const {
  SuperBin result(*this);

  // if the requested number of bits is larger than the current size
  // add signum bits at the beginning until requested number equals
  // size
  while (no_of_bits > result.m_number.size()) {
    result.m_number.insert(result.m_number.begin(), result.m_number[0]); }

  // if the actual size is more than two bits (signum + data) and
  // the requested number of bits is smaller than actual size and
  // two front bits are equal (both signums, either 0 or 1
  // then it is save to remove the bit at the front
  while ((result.m_number.size() > 2) &&
      (no_of_bits < result.m_number.size()) &&
      (result.m_number[1] == result.m_number[0])) {
    result.m_number.erase(result.m_number.begin());
  }

  return result;
}

/**
 * Get the current size in bits.
 */
unsigned int
SuperBin::size(
    void) const {
  return m_number.size();
}



/**************************************************************************** 
 * CONVERTERS TO STRING
 ****************************************************************************/
/**
 * Put number in requested base to std::string with signum (optional).
 */
std::string
SuperBin::to_string_signed(
    unsigned int base
  , bool out_sign_pos
  , bool out_sign_neg) const {
  // determine sign
  Sign sign = (m_number.front() == '0') ? Sign::POS : Sign::NEG;

  // if the number is negative take it out of 2's complement form
  std::string number = (Sign::NEG == sign ? bnot().inc().m_number : m_number);

  // convert to requested base
  std::string result = fromBaseToBase(number, 2, base);

  // add sign as the first character
  if (Sign::POS == sign && out_sign_pos) { result = '+' + result; }
  if (Sign::NEG == sign && out_sign_neg) { result = '-' + result; }

  return result;
}

/**
 * Put number in binary to std::string with signum (if negative).
 */
std::string
SuperBin::to_string_signed_bin(
    void) const {
  return to_string_signed(2);
}

/**
 * Put number in octal to std::string with signum (if negative).
 */
std::string
SuperBin::to_string_signed_oct(
    void) const {
  return to_string_signed(8);
}

/**
 * Put number in decimal to std::string with signum (if negative).
 */
std::string
SuperBin::to_string_signed_dec(
    void) const {
  return to_string_signed(10);
}

/**
 * Put number in hexadecimal to std::string with signum (if negative).
 */
std::string
SuperBin::to_string_signed_hex(
    void) const {
  return to_string_signed(16);
}

/**
 * Print number in binary (as is) with (optional) number of digits.
 */
std::string
SuperBin::to_string_unsigned_bin(
    unsigned int no_of_bits) const {
  std::string result = m_number;

  if (0 != no_of_bits) {
    // insert bits if requested more than size
    while (result.size() < no_of_bits) {
      result.insert(result.begin(), result[0]); }

    // remove bits if requested less than size
    while (result.size() > no_of_bits) {
      result.erase(result.begin()); }
  }

  return result;
}

/**
 * Print number in octal. Optional parameter dictates how many bits
 * is translated to octal.
 */
std::string
SuperBin::to_string_unsigned_oct(
    unsigned int no_of_bits) const {
  std::string result
    = fromBaseToBase(to_string_unsigned_bin(no_of_bits), 2, 8);

  while (result.size() < (no_of_bits / 3) + ((no_of_bits % 3) ? 1 : 0)) {
    result.insert(result.begin(), '0');
  }

  return result;
}

/**
 * Print number in hexadecimal. Optional parameter dictates how many bits
 * is translated to hexadecimal.
 */
std::string
SuperBin::to_string_unsigned_hex(
    unsigned int no_of_bits) const {
  std::string result
    = fromBaseToBase(to_string_unsigned_bin(no_of_bits), 2, 16);

  while (result.size() < (no_of_bits / 4) + ((no_of_bits % 4) ? 1 : 0)) {
    result.insert(result.begin(), '0');
  }

  return result;
}



/**************************************************************************** 
 * ZERO TEST
 ****************************************************************************/

/**
 * Zero check.
 */
bool
SuperBin::tz(
    void) const {
  for (auto it = m_number.cbegin(); it != m_number.end(); ++it) {
    if ((*it) != '0') { return false; }
  }
  return true;
}

/**
 * Check if not zero.
 */
bool
SuperBin::tnz(
    void) const {
  return !tz();
}



/**************************************************************************** 
 * LOGICAL
 ****************************************************************************/

/**
 * Logical NOT
 */
SuperBin
SuperBin::lnot(
    void) const {
  return SuperBin(tz() ? true : false);
}

/**
 * Logical AND
 */
SuperBin
SuperBin::land(
    const SuperBin &rhs) const {
  return SuperBin(!tz() && !rhs.tz() ? true : false);
}

/**
 * Logical OR
 */
SuperBin
SuperBin::lor(
    const SuperBin &rhs) const {
  return SuperBin(!tz() || !rhs.tz() ? true : false);
}

/**
 * Logical XOR
 */
SuperBin
SuperBin::lxor(
    const SuperBin &rhs) const {
  return SuperBin(((tz() && !rhs.tz()) || (!tz() && rhs.tz())) ? true : false);
}



/**************************************************************************** 
 * BITWISE
 ****************************************************************************/

/**
 * Bitwise not.
 * TODO(doki): removing leading zeros? consider not(1110) = 1; not(1) = 0 ??
 */
SuperBin
SuperBin::bnot(
    void) const {
  SuperBin result(*this);

  for (auto it = result.m_number.begin(); it != result.m_number.end(); ++it) {
    (*it) = ((*it) == '0' ? '1' : '0');
  }

  return result;
}



/**************************************************************************** 
 * ARITHMETIC FUNCTIONS
 ****************************************************************************/

/**
 * Increment by one.
 * TODO(doki): lose leading zeros when n-bit -1 goes to 0
 */
SuperBin
SuperBin::inc(
    void) const {
  SuperBin result(*this);

  // determine signum: if it is a positive number, we must ensure it
  // will stay postive (0 is the leading digit) - see below.
  Sign sign = (result.m_number.front() == '0') ? Sign::POS : Sign::NEG;

  char bcarry = 1;
  for (auto bit = result.m_number.rbegin();
       bit != result.m_number.rend();
       ++bit) {
    char bres = *bit + bcarry;
    bcarry = ((bres & 2) == 2);
    (*bit) = (bres & 1) + '0';
  }

  // if the above code finished with an overflow the signum for
  // a postive number changed so we must add '0' in front
  // consider:
  //  inc(00) -> 01 (decimal 0 -> 1)
  //  inc(01) -> 010 (decimal 1 -> 2) NOT 10 (decimal -2)!!
  if ((sign == Sign::POS) && (result.m_number.front() == '1')) {
    result.m_number.insert(result.m_number.begin(), '0');
  }

  return result;
}

/**
 * Decrement by one.
 * TODO(doki): lose leading zeros when n-bit +1 goes to 0
 */
SuperBin
SuperBin::dec(
    void) const {
  SuperBin result(*this);

  return result;
}



/**************************************************************************** 
 * STATIC FUNCTIONS
 ****************************************************************************/

using Digit = unsigned int;

void
SuperBin::fromBaseToBase(
    const std::string &fromNumber,
    unsigned int fromBase,
    std::string *toNumber,
    unsigned int toBase) {
  // do we have a stupid caller?
  if ((fromBase < 2) || (toBase < 2)) { return; }

  /*
   * we switch two buffers (numerator and result) with named pointers.
   * at the beginning the numerator is set to the number which is going
   * to be converted to the given base in string.
   */
  std::vector<Digit> buffer[2];
  std::vector<Digit> *numerator = &buffer[0], *result = &buffer[1];

  /* 
   * beware: ugly parsing code!
   * checks each input digit and makes a copy in internal buffer
   */
  for (auto fromDigit : fromNumber) {
    // basically makes sure digit is valid (e.g. it is not something like "!")
    // and is in in range (e.g. it is not "F" if base 10 is given)
    if (!(
      ((fromDigit >= '0')
        && (fromDigit <=
          (fromBase > 10 ? '9' : '0' + static_cast<char>(fromBase) - 1)))

      || (fromBase > 10 ?
        ((fromDigit >= 'A')
         && (fromDigit <=
           ('A' - 10 + static_cast<char>(fromBase) - 1))) : false)

      || (fromBase > 10 ?
        ((fromDigit >= 'a')
         && (fromDigit <=
           ('a' - 10 + static_cast<char>(fromBase) - 1))) : false))) { break; }

    // pushes the numeric value ('7' -> 7, 'F' -> 15, ... ) to the buffer
    numerator->push_back(fromDigit -
        ((fromDigit >= '0') && (fromDigit <= '9') ? '0' :
        ((fromDigit >= 'A') && (fromDigit <= 'Z') ? 'A' - 10 : 'a' - 10)));
  }

  /*
   * basic old-school maethod of conversion - while there is a result after
   * division (not 0) repeat the procedure.
   */
  while (!numerator->empty()) {
    unsigned int num = 0;
    auto numerator_it = numerator->cbegin();

    /*
     * single division of number with given base:
     * (1) result (num) is taken for next division (e.g. if we're dividing
     *     256 and 10, the result (25) is going to be divided in the next
     *     loop)
     * (2) remainder (the thing inserted in the output string, i.e. num
     *     after innermost while loop) is stored for the output (first
     *     remainder represents the least significant bits of the number
     *     in given base). NOTE: that's why we push the remainder at the front
     *     of the string (insert) instead at the back (as we do with vectors).
     */
    while (numerator_it != numerator->cend()) {
      /*
       * first multiply previous reminder (now in num) with the base the
       * numbers are written in (fromBase), then add digit of the big
       * number and finally increase the iterator to point to the
       * next digit (or one past the end).
      */
      (num *= fromBase) += *numerator_it++;

      /*
       * are we eligible to divide by toBase? is accumulated number
       * larger or equal to the toBase?
       */
      if (num >= toBase) {
        /*
         * store a result of division (it's a digit of result) and save the
         * reminder for the loop that follows (it will be multiplied by the
         * fromBase)
         *
         * NOTE: this part can be improved, i.e. if we KNOW, e.g., the
         * requested toBase is hex, we could shift right by 4 (effectively
         * dividing by 16). same goes for bin and oct.
         */
        result->push_back(num / toBase);
        num %= toBase;

      /*
       * if we are not eligible to divide by toBase (think of 127 and dividing
       * by 10: 1 can't be divided by 10) we should output 0 (in case of 127
       * and 10 the "real" result is 012, but leading zero is omited).
       *
       * we'll avoid this for leading 0s (again, think of 127 and 10, we want
       * the result in form of 12 not 012) - that's the reason for
       * "if (!result->empty()) ... "
       */
      } else { if (!result->empty()) { result->push_back(0); } }

      /*
       * if and only if we're at the end, meaning we have divided the whole
       * number than what remains is the digit of the result. digits are
       * calculated in lsb to msb order and that's the reason why we push
       * each digit in front (i.e. string::insert with cbegin).
       */
      if (numerator_it == numerator->cend()) {
        toNumber->insert(toNumber->cbegin(), num + (num < 10 ? '0' : 'A' - 10));
      }
    }

    /*
     * after the division, result represents the next numerator so
     * we switch them and clear the result for the next run.
     */
    numerator = result;
    result = &((result == &buffer[0]) ? buffer[1] : buffer[0]);
    result->clear();
  }
}

}  // namespace dlib

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
 * CONVERTER TO INT
 ****************************************************************************/

/**
 * TODO(doki) implement this
 */
int
SuperBin::to_int(
    void) const {
  return 0;
}



/**************************************************************************** 
 * ZERO TEST
 ****************************************************************************/

/**
 * Zero check.
 * TODO(doki) make return SuperBin
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
 * TODO(doki) make return SuperBin
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
 * Bitwise NOT
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

/**
 * Bitwise AND
 */
SuperBin
SuperBin::band(
    const SuperBin &rhs) const {
  // find the operand with more bits
  SuperBin const *operand = (this->size() > rhs.size() ? this : &rhs);

  // set the result to the other operand which is expanded to the number
  // of bits of first operand
  SuperBin result = (operand == this ? rhs : *this).cast(operand->size());

  // logical and on each bit
  for (unsigned int i = 0; i < result.size(); ++i) {
    result.m_number[i] &= operand->m_number[i]; }

  return result;
}

/**
 * Bitwise OR
 */
SuperBin
SuperBin::bor(
    const SuperBin &rhs) const {
  // find the operand with more bits
  SuperBin const *operand = (this->size() > rhs.size() ? this : &rhs);

  // set the result to the other operand which is expanded to the number
  // of bits of first operand
  SuperBin result = (operand == this ? rhs : *this).cast(operand->size());

  // logical or on each bit
  for (unsigned int i = 0; i < result.size(); ++i) {
    result.m_number[i] |= operand->m_number[i]; }

  return result;
}

/**
 * Bitwise XOR
 */
SuperBin
SuperBin::bxor(
    const SuperBin &rhs) const {
  // find the operand with more bits
  SuperBin const *operand = (size() > rhs.size() ? this : &rhs);

  // set the result to the other operand which is expanded to the number
  // of bits of first operand
  SuperBin result = (operand == this ? rhs : *this).cast(operand->size());

  // logical or on each bit
  for (unsigned int i = 0; i < result.size(); ++i) {
    /* 1st variant:
     * XOR(a,b) = OR(a,b) & !AND(a,b), therefore I test to see the second
     * expression, if it is true, I'm doing OR, if it is not I simply
     * return '0'.
     */
    // result.m_number[i] =
    //   !(result.m_number[i] & operand->m_number[i] & 1) ?
    //   result.m_number[i] |= operand->m_number[i] : '0';

    /* 2nd variant:
     * Uses C's XOR but I have two subtractions and one addition.
     */
    result.m_number[i] =
      ((result.m_number[i] - '0') ^ (operand->m_number[i] - '0')) + '0';

    // In the end, when compiled, second version produces better code.
  }

  return result;
}



/**************************************************************************** 
 * SHIFTS
 ****************************************************************************/

/**
 * Logical shift left by given number of bits.
 */
SuperBin
SuperBin::shl(
    unsigned int no_of_bits) const {
  SuperBin result(*this);

  for (unsigned int i = 0; i < no_of_bits; ++i) {
    result.m_number.push_back('0');
  }

  return result;
}

/**
 * Logical shift right by given number of bits.
 */
SuperBin
SuperBin::shr(
    unsigned int no_of_bits) const {
  // return if requested a shift by 0 bits
  if (!no_of_bits) { return *this; }

  // return 0 if requested a shift right by more bits than the number has
  if (no_of_bits >= size()) { return SuperBin(); }

  // else make a copy
  SuperBin result(*this);

  // and pop requested number of bits from back
  for (unsigned int i = 0; i < no_of_bits; ++i) {
    result.m_number.pop_back();
  }

  // add zero infront (if negative and shifting by more than zero)
  if (result.size() == 1 || m_number[0] == '1') {
    result.m_number.insert(result.m_number.begin(), '0');
  }

  return result;
}

/**
 * Arithmetic shift left by given number of bits.
 */
SuperBin
SuperBin::sal(
    unsigned int no_of_bits) const {
  return shl(no_of_bits);
}

/**
 * Arithmetic shift right by given number of bits.
 */
SuperBin
SuperBin::sar(
    unsigned int no_of_bits) const {
  // return if requested a shift by 0 bits
  if (!no_of_bits) { return *this; }

  // if a request to shift right by more bits than the number has
  if (no_of_bits >= size() - 1) {
    // return either 0 or -1 depending on signum
    return SuperBin((m_number[0] == '0' ? "0" : "1"),
        10, dlib::SuperBin::Sign::NEG);
  }

  // else simply make a copy
  SuperBin result(*this);

  // and pop requested number of bits from back
  for (unsigned int i = 0; i < no_of_bits; ++i) {
    result.m_number.pop_back();
  }

  return result;
}



/**************************************************************************** 
 * BIT MANIPULATORS
 ****************************************************************************/

/**
 * Set bits
 */
SuperBin
SuperBin::setbs(
    unsigned int index_l
  , unsigned int index_m) const {
  if (index_l > index_m) return *this;

  // make a copy
  SuperBin result(*this);

  // cast the binary representation if index_m out of range
  // (if index_m = 7 -> 8th bit requested -> number has to have 9 bits)
  if (index_m >= result.m_number.size()) { result = result.cast(index_m + 2); }

  // set requested bits on a copy
  for (unsigned int i = index_l; i <= index_m; ++i) {
    result.m_number[result.m_number.size() - 1 - i] = '1';
  }

  return result;
}

/**
 * Set bit
 */
SuperBin
SuperBin::setb(
    unsigned int index) const {
  SuperBin result(*this);

  if (index >= result.m_number.size()) { result = result.cast(index + 2); }

  result.m_number[result.m_number.size() - 1 - index] = '1';

  return result;
}

/**
 * Clear bits
 */
SuperBin
SuperBin::clearbs(
    unsigned int index_l
  , unsigned int index_m) const {
  if (index_l > index_m) return *this;

  SuperBin result(*this);

  if (index_m >= result.m_number.size()) { result = result.cast(index_m + 2); }

  for (unsigned int i = index_l; i <= index_m; ++i) {
    result.m_number[result.m_number.size() - 1 - i] = '0';
  }

  return result;
}

/**
 * Clear bit
 */
SuperBin
SuperBin::clearb(
    unsigned int index) const {
  SuperBin result(*this);

  if (index >= result.m_number.size()) { result = result.cast(index + 2); }

  result.m_number[result.m_number.size() - 1 - index] = '0';

  return result;
}

/**
 * Invert bits
 */
SuperBin
SuperBin::notbs(
    unsigned int index_l
  , unsigned int index_m) const {
  if (index_l > index_m) return *this;

  SuperBin result(*this);

  if (index_m >= result.m_number.size()) { result = result.cast(index_m + 2); }

  for (unsigned int i = index_l; i <= index_m; ++i) {
    result.m_number[result.m_number.size() - 1 - i] =
      result.m_number[result.m_number.size() - 1 - i] == '0' ? '1' : '0';
  }

  return result;
}

/**
 * Invert bit
 */
SuperBin
SuperBin::notb(
    unsigned int index) const {
  SuperBin result(*this);

  if (index >= result.m_number.size()) { result = result.cast(index + 2); }

  result.m_number[result.m_number.size() - 1 - index] =
    result.m_number[result.m_number.size() - 1 - index] == '0' ? '1' : '0';

  return result;
}

/**
 * Get bits
 */
SuperBin
SuperBin::getbs(
    unsigned int index_l
  , unsigned int index_m) const {
  if (index_l > index_m) return *this;

  // construct a result
  SuperBin result;

  // but empty the bit holder
  result.m_number = "";

  // extract bits and insert them in result
  for (unsigned int i = index_l; i <= index_m; ++i) {
    result.m_number.insert(result.m_number.begin(),
        // if index_m greater or equal to the size
        // of current number, insert signum
        m_number[(m_number.size() - 1 > i) ?  m_number.size() - 1 - i : 0]);
  }

  return result;
}

/**
 * Get bit
 */
SuperBin
SuperBin::getb(
    unsigned int index) const {
  SuperBin result;
  result.m_number = "0";

  if (index >= m_number.size()) {
    result.m_number[0] = m_number[0];
  } else {
    result.m_number[0] = m_number[m_number.size() - 1 - index];
  }

  return result;
}

/**
 * Get bits and ensure the result is unsigned.
 */
SuperBin
SuperBin::getubs(
    unsigned int index_l
  , unsigned int index_m) const {
  if (index_l > index_m) return *this;

  SuperBin result = getbs(index_l, index_m);

  if (result.m_number.front() == '1') {
    result.m_number.insert(result.m_number.begin(), '0');
  }

  return result;
}

/**
 * Get bits and ensure the result is unsigned.
 */
SuperBin
SuperBin::getub(
    unsigned int index) const {
  SuperBin result = getb(index);

  if (result.m_number.front() == '1') {
    result.m_number.insert(result.m_number.begin(), '0');
  }

  return result;
}



/**************************************************************************** 
 * COMPARISONS
 ****************************************************************************/

/**
 * EQual.
 */
SuperBin
SuperBin::eq(
    const SuperBin &rhs) const {
  // get the reference of the operand with more bits
  SuperBin const *operand1 = (size() > rhs.size() ? this : &rhs);

  // make the copy of the other operand and cast it to the same number of bits
  SuperBin operand2 = (operand1 == this ? rhs : *this).cast(operand1->size());

  // compare all bits starting from msb
  for (unsigned int i = 0; i < operand1->size(); ++i) {
    if (operand1->m_number[i] != operand2.m_number[i]) {
      return SuperBin(false);
    }
  }

  // if we got here, all bits are equal
  return SuperBin(true);
}

/**
 * Not Equal.
 */
SuperBin
SuperBin::ne(
    const SuperBin &rhs) const {
  return eq(rhs).lnot();
}

/**
 * Less Then.
 */
SuperBin
SuperBin::lt(
    const SuperBin &rhs) const {
  return ge(rhs).lnot();
}

/**
 * Not Less Then.
 */
SuperBin
SuperBin::nlt(
    const SuperBin &rhs) const {
  return ge(rhs);
}

/**
 * Less or Equal.
 */
SuperBin
SuperBin::le(
    const SuperBin &rhs) const {
  // case when A < 0 && B > 0 returns true
  // TODO(doki): replace with tneg and tpos
  if (m_number[0] == '1' && rhs.m_number[0] == '0') { return SuperBin(true); }

  // case when A > 0 && B < 0 returns false
  // TODO(doki): replace with tneg and tpos
  if (m_number[0] == '0' && rhs.m_number[0] == '1') { return SuperBin(false); }

  // get the reference of the operand with more bits
  SuperBin const *operand1 = (size() > rhs.size() ? this : &rhs);

  // make the copy of the other operand and cast it to the same number of bits
  SuperBin operand2 = (operand1 == this ? rhs : *this).cast(operand1->size());

  // compare all bits starting from msb
  for (unsigned int i = 0; i < operand1->size(); ++i) {
    // if they are equal, continue with next
    if (operand1->m_number[i] == operand2.m_number[i]) { continue; }

    // if the bits are not equal
    if (operand1->m_number[i] < operand2.m_number[i]) {
      // if the bit in the first operand is smaller (0)
      // than the bit in the second operand (1) AND the
      // first operand is this object than this number
      // is smaller than the other (rhs).
      return SuperBin(operand1 == this ? true : false);
    } else {
      // if the bit in the first operand is larger (1)
      // than the bit in the second operand (0) AND the
      // first operand is this object than this number
      // is larger than the other (rhs).
      return SuperBin(operand1 == this ? false : true);
    }
    // this also works for negative numbers (2's complement). consider:
    // -5 (1011) and -4 (1100). if this holds 1011 and rhs holds 1100,
    // operand1 will point to 1100, and operand2 will hold 1011. the
    // first bit is equal so continue is executed. for the next bit,
    // first comparison fails and we end up in else. as operand1
    // differs from this, we return true. we can also consider the
    // oposite: 1100 and 1011. in this case this holds 1100, and  rhs
    // holds 1011 and therefore operand1 points to 1011 and operand2
    // holds 1100. first bit is equal, however, when comparing the
    // second bit, the if expression is true, operand1 points to rhs
    // so we return false.
  }

  // if we got here, all bits are equal
  return SuperBin(true);
}

/**
 * Not Less or Equal.
 */
SuperBin
SuperBin::nle(
    const SuperBin &rhs) const {
  return gt(rhs);
}

/**
 * Greater Then.
 */
SuperBin
SuperBin::gt(
    const SuperBin &rhs) const {
  return le(rhs).lnot();
}

/**
 * Not Greater Then.
 */
SuperBin
SuperBin::ngt(
    const SuperBin &rhs) const {
  return le(rhs);
}

/**
 * Greater or Equal.
 */
SuperBin
SuperBin::ge(
    const SuperBin &rhs) const {
  // case when A > 0 && B < 0 returns true
  if (m_number[0] == '0' && rhs.m_number[0] == '1') { return SuperBin(true); }

  // case when A < 0 && B > 0 returns false
  if (m_number[0] == '1' && rhs.m_number[0] == '0') { return SuperBin(false); }

  // get the reference of the operand with more bits
  SuperBin const *operand1 = (size() > rhs.size() ? this : &rhs);

  // make the copy of the other operand and cast it to the same number of bits
  SuperBin operand2 = (operand1 == this ? rhs : *this).cast(operand1->size());

  // compare all bits starting from msb - for explenation see le()
  for (unsigned int i = 0; i < operand1->size(); ++i) {
    if (operand1->m_number[i] == operand2.m_number[i]) { continue; }
    if (operand1->m_number[i] > operand2.m_number[i]) {
      return SuperBin(operand1 == this ? true : false);
    } else {
      return SuperBin(operand1 == this ? false : true);
    }
  }

  return SuperBin(true);
}

/**
 * Not Greater or Equal.
 */
SuperBin
SuperBin::nge(
    const SuperBin &rhs) const {
  return lt(rhs);
}



/**************************************************************************** 
 * ARITHMETIC FUNCTIONS
 ****************************************************************************/

/**
 * Negate the number (return 2's complement).
 * TODO(doki): replace all calls to bnot().inc() with neg().
 */
SuperBin
SuperBin::neg(
    void) const {
  return (bnot().inc());
}

/**
 * Increment by one.
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

  return result.cast();
}

/**
 * Decrement by one.
 */
SuperBin
SuperBin::dec(
    void) const {
  SuperBin result(*this);

  return result;
}

/**
 * Addition.
 * TODO(doki): optimize me please! :)
 */
SuperBin
SuperBin::add(
    const SuperBin& rhs) const {
  // get the reference of the operand with more bits
  SuperBin const *operand1 = (size() > rhs.size() ? this : &rhs);

  // make the copy of the other operand and cast it to the same number of bits
  SuperBin operand2 = (operand1 == this ? rhs : *this).cast(operand1->size());

  SuperBin result;
  result.m_number = "";

  // sum bit-by-bit
  char carry = 0;
  char bit = '0';
  for (int i = operand2.size() - 1; i >= 0; --i) {
    if (!carry) {
      bit = ((operand2.m_number[i] - '0') ^
        (operand1->m_number[i] - '0')) + '0';
      carry = ((operand2.m_number[i] - '0') &
        (operand1->m_number[i] - '0'));
    } else {
     bit = (((operand2.m_number[i] - '0') ^
        (operand1->m_number[i] - '0')) ? 0 : 1) + '0';
      carry = ((operand2.m_number[i] - '0') |
        (operand1->m_number[i] - '0'));
    }
    result.m_number.insert(result.m_number.begin(), bit);
  }
  if ((result.m_number[0] == '1') && (operand1->m_number[0] == '0')
      && (operand2.m_number[0] == '0')) {
    result.m_number.insert(result.m_number.begin(), '0');
  } else if ((result.m_number[0] == '0') && (operand1->m_number[0] == '1')
      && (operand2.m_number[0] == '1')) {
    result.m_number.insert(result.m_number.begin(), '1');
  }

  return result;
}

/**
 * Subtraction.
 */
SuperBin
SuperBin::sub(
    const SuperBin& rhs) const {
  return add(rhs.neg());
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

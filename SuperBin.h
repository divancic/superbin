#ifndef SUPERBIN_H_
#define SUPERBIN_H_

#include <vector>
#include <queue>
#include <iostream>
#include <string>

// TODO(doki):
// - srediti konstruktore
// - u operator = dodati predznak
// - okrenuti smjer vector<0> LSB
// - ispisivati pomoću reverznog iteratora
// - add
// - sub
// - mul
// - div
// - modulo
// - ispis u bazi
//


class SuperBin {
 public:
  enum class Base { BIN, OCT, DEC, HEX };
  enum class Sign { POS = 0, NEG = 1 };

 private:
  using Bit = unsigned int;
  using Digit = unsigned int;

  Sign m_sign;
  std::size_t m_size;
  std::vector<Bit> m_number;

 public:
  // SuperBin(); // creates 0
  // SuperBin(str, base, pred)
  // toBase(base,sign)
  //
  // <F12>output(base,sign) // ispisuje broj u bazi
  // output[_dec|_bin_|_oct|_hex](sign) // ispisuje broj u bazi s/bez predznaka
  // output[_dec|_bin_|_oct|_hex] // ispisuje broj u bazi s predznakom
  // output[|_unsigned_bin|_unsigned_hex](broj bitova) // dvojni komplement
  // is_zero
  SuperBin() : m_sign(Sign::POS), m_size(1) { m_number.resize(m_size, 0); }
  explicit  SuperBin(std::string number
      , unsigned int base = 10, Sign sign = Sign::POS);

  void fromBaseToBase(const std::string &fromNumber, unsigned int fromBase
      , std::string &toNumber, unsigned int toBase);
  std::string fromBaseToBase(const std::string &fromNumber
      , unsigned int fromBase, unsigned int toBase);
};

SuperBin::SuperBin(std::string number, unsigned int base, Sign sign)
  : m_sign(sign) {
  std::string binary = fromBaseToBase(number, base, 2);

  for (auto i : binary) { std::cout << i; } std::cout << std::endl;
}


// GENERIC
//-----------------------------------------------------------------------------
std::string
SuperBin::fromBaseToBase(
    const std::string &fromNumber,
    unsigned int fromBase,
    unsigned int toBase) {
  std::string toNumber;
  fromBaseToBase(fromNumber, fromBase, toNumber, toBase);
  return (toNumber);
}

void
SuperBin::fromBaseToBase(
    const std::string &fromNumber,
    unsigned int fromBase,
    std::string &toNumber,
    unsigned int toBase) {
  // do we have a stupid caller?
  if ((fromBase < 2) || (toBase < 2)) { return; }

  /*
   * two buffers: for numerator and result
   * we switch them with named pointers. at the beginning the numerator
   * is set to the number which is going to be converted to the given
   * base in string.
   */
  std::vector<Digit> buffer[2];
  std::vector<Digit> *numerator = &buffer[0], *result = &buffer[1];

  /* 
   * BEWARE: ugly parsing code!
   * checks each input digit and makes a copy in internal buffer
   */
  for (auto fromDigit : fromNumber) {
    // basically makes sure digit is valid (e.g. it is not something like "!")
    // and is in in range (e.g. it is not "F" if base 10 is given)
    if (!(
      ((fromDigit >= '0')
        && (fromDigit <= (fromBase > 10 ? '9' : '0' + fromBase - 1)))
      || (fromBase > 10 ?
        ((fromDigit >= 'A')
         && (fromDigit <= ('A' - 10 + fromBase - 1))) : false)
      || (fromBase > 10 ?
        ((fromDigit >= 'a')
         && (fromDigit <= ('a' - 10 + fromBase - 1))) : false))) { break; }

    // pushes the numeric value ('7' -> 7, 'F' -> 15, ... ) to the buffer
    numerator->push_back(fromDigit -
        ((fromDigit >= '0') && (fromDigit <= '9') ? '0' :
        ((fromDigit >= 'A') && (fromDigit <= 'Z') ? 'A' - 10 : 'a' - 10)));
  }

  //  std::cout << "Diag: "; for (auto it: *numerator)
  //  { std::cout << it; } std::cout << std::endl;

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
        toNumber.insert(toNumber.cbegin(), num + (num < 10 ? '0' : 'A' - 10));
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

#endif  // SUPERBIN_H_

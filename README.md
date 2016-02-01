# SuperBin

## Introduction

SuperBin strives to be a generic C++ class for arbitrary large numbers. It is not an efficient implementation. I started building it for [ADEL](https://github.com/divancic/superbin#adelint) (read on) but soon realised it could be much more than that. Class is kind of half-done: it has all the backbone methods, but it does not have any C++ operators and such defined (at least not at the time of this writing).

The class stores the numbers internally in a binary format so all operations are performed on large binary numbers. Other formats (octal, decimal, hexadecimal, or any arbitrary format) may be given as an input or requested as an output (see [Examples](https://github.com/divancic/superbin#examples)).

## Getting it

Well, that's easy. :-)

* via **git clone**: git clone https://github.com/divancic/superbin
* by clicking on **Download ZIP** (see above): https://github.com/divancic/superbin/archive/master.zip
* or on a **file-by-file basis** (you really only need two files: [SuperBin.cpp](https://raw.githubusercontent.com/divancic/superbin/master/SuperBin.cpp) and [SuperBin.h](https://raw.githubusercontent.com/divancic/superbin/master/SuperBin.h))

## Getting Started

No special requirements here. Just include **SuperBin.cpp** in your project and **SuperBin.h** as a header file from where you are going to be using it.

## Docs

WTF?! Go see examples.

## Examples

Coming soon...

## Tests

Tests are **basic** and **ugly** (but that is mainly because they are written by me ;-)). I used [Google Test](https://github.com/google/googletest). If you are thinking of extending this library and use it in your endeavors, I strongly suggest you use Google Test. It is an excellent thing that may make your life easier.

## ADELint

### Introduction

As stated in the text above, I started working on SuperBin to be used as ADEL (Assembler DEscription Language) integer. However, in some point I decided it would be wiser to distinguish C++ class which represent a large numbers and can be used as a built-in type (well, almost) to a class which is used by ADEL and has some special methods and their parameters (e.g. generic type class would return a boolean when comparing two large numbers, but class targeted to ADEL has to return ADELint which represents either true or false depending on a value). Therefore ADELint was born as a subclass of SuperBin. It simply inherits SuperBin publicly and defines its own methods. That's it.

### Getting it

See [SuperBin - Getting it](https://github.com/divancic/superbin#getting-it) above. If you choose the **file-by-file** aproach in adition to **SuperBin.cpp** and **SuperBin.h** you also need [ADELint.cpp](https://raw.githubusercontent.com/divancic/superbin/master/ADELint.cpp) and [ADELint.h](https://raw.githubusercontent.com/divancic/superbin/master/ADELint.h).

## Getting Started

As with the **SuperBin** there are no special requirements. Just include **ADELint.cpp** in your project and **ADELint.h** as a header file from where you are going to be using it. **NOTE: You do not have to include SuperBin.h!!!**

### Examples
 
Basic example:

```cpp
#include <iostream>

#include "ADELint.h"

using namespace dlib;
using namespace std;

int
main(int argc, char *argv[]) {
  ADELint a, b, c;

  a = ADELint("17");
  b = ADELint("13");
  c = add(a, b);

  cout << "Result is: " << to_string_signed_dec(c) << endl;

  return 0;
}
```

If you save the above code in a file named example.cpp, and you have **SuperBin.cpp**, **SuperBin.h**, **ADELint.cpp** and **ADELint.h** present in your local directory, you would get the binary by invoking the compiler like this:
```bash
$ g++ SuperBin.cpp ADELint.cpp example.cpp -std=c++11 -o example
```
**NOTE:** -std=c++11

For a more detailed example check out [ADELintExample.cpp](https://github.com/divancic/superbin/blob/master/examples/ADELintExample.cpp)

### Tests

See [SuperBin - Tests](https://github.com/divancic/superbin#tests).


### Bonuses

* +10011000110111111110011000 is the exact length of the Equator (in meters).
* +10101011110010 is the depth of the deepest known point in Earth's oceans (Mariana Trench) (in meters)
* +10001010010000 is the elevation of Mount Everest (in meters).
* +10001011010100101110100101101001101100 is the astronomical unit, a distance from Earth to the sun (in meters),
+10001110111100111100001001010 is the speed of light (in meters per second), and therefore it takes the sunlight
+111110011 seconds (8 minutes and 19 seconds) to travel from the Sun to the Earth.

# SuperBin

## Introduction

SuperBin strives to be a generic C++ class for arbitrary large numbers. I started building it for [ADEL](https://github.com/divancic/superbin#adelint) (read on) but soon realised it could be much more than that. Class is kind of half-done: it has all the backbone methods, but it does not have any C++ operators and such defined (at least not at the time of this writing).

The class stores the numbers internally in a binary format so all operations are performed on large binary numbers. Other formats (octal, decimal, hexadecimal, or any arbitrary format) may be given as an input or requested as an output (see examples).

## Getting it

Well, that's easy. :-)

* via **git clone**: git clone https://github.com/divancic/superbin
* by clicking on **Download ZIP** (see above): https://github.com/divancic/superbin/archive/master.zip
* or on a **file-by-file basis** (you really only need two files: [SuperBin.cpp](https://raw.githubusercontent.com/divancic/superbin/master/SuperBin.cpp) and [SuperBin.h](https://raw.githubusercontent.com/divancic/superbin/master/SuperBin.h))

## Getting Started

No special requirements here. Just include **SuperBin.cpp** in your project and **SuperBin.h** as a header file from where you are going to be using it.

## Examples

TBD

## Tests

Tests are **basic** and **ugly** (but that is mainly because they are written by me ;-)). I used [Google Test](https://github.com/google/googletest). If you are thinking of extending this library and use it in your endeavors, I strongly suggest you use Google Test. It is an excellent thing that may make your life easier.

## ADELint

### Introduction

### Getting

### Usage

### Tests

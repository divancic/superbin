
CPPLINT				= cpplint
CPPLINT_FLAGS	+= --verbose=0 --filter=-legal/copyright

CXX						= clang++
CPPFLAGS			+=
CXXFLAGS			+= -std=c++11 -Wall -Wextra -Wpedantic -g
#CXXFLAGS			+= -Wno-vla-extension -Wno-unused-variable

.PHONY: all clean

all: SuperBin.o

SuperBin.o: SuperBin.h SuperBin.cpp
	$(CPPLINT) $(CPPLINT_FLAGS) SuperBin.h
	$(CPPLINT) $(CPPLINT_FLAGS) SuperBin.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c SuperBin.cpp

clean:
	rm -f SuperBin.o

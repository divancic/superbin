
CPPLINT				= cpplint
CPPLINT_FLAGS	+= --verbose=0 --filter=-legal/copyright

CXX						= clang++
CPPFLAGS			+=
CXXFLAGS			+= -std=c++11 -Wall -Wextra -Wpedantic -g
#CXXFLAGS			+= -Wno-vla-extension -Wno-unused-variable

GTEST_DIR			= googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h																\
								$(GTEST_DIR)/include/gtest/internal/*.h												\
GTEST_SOURCES = $(GTEST_DIR)/src/*.cc																					\
								$(GTEST_DIR)/src/*.h																					\
								$(GTEST_HEADERS)

.PHONY: all clean SuperBin

all: test

test: test.cpp SuperBin libgtest.a
	$(CPPLINT) $(CPPLINT_FLAGS) test.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) test.cpp -o $@ libgtest.a -lpthread

SuperBin.o: SuperBin.h SuperBin.cpp
	$(CPPLINT) $(CPPLINT_FLAGS) SuperBin.h
	$(CPPLINT) $(CPPLINT_FLAGS) SuperBin.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c SuperBin.cpp

libgtest.a: $(GTEST_SOURCES)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc
	$(AR) $(ARFLAGS) $@ gtest-all.o
	rm gtest-all.o

clean:
	rm -f test test.o libgtest.a

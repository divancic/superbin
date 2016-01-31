
CPPLINT				= cpplint
CPPLINT_FLAGS	+= --verbose=0 --filter=-legal/copyright

CXX						= clang++
CPPFLAGS			+=
CXXFLAGS			+= -std=c++11 -Wall -g -I$(GTEST_DIR)/include
#CXXFLAGS			+= -Wpedantic -Wextra 
#CXXFLAGS			+= -Wno-vla-extension -Wno-unused-variable

GTEST_DIR			= googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h																\
								$(GTEST_DIR)/include/gtest/internal/*.h												\
GTEST_SOURCES = $(GTEST_DIR)/src/*.cc																					\
								$(GTEST_DIR)/src/*.h																					\
								$(GTEST_HEADERS)

.PHONY: all clean SuperBinTest ADELintTest

all:
ifneq ($(wildcard $(GTEST_DIR)/.*),)
	@echo "NOTE: google test found, building SuperBin tests."
	@echo "If you want just SuperBin library do a:"
	@echo "    make libSuperBin.a"
	make SuperBinTest ADELintTest
else
	@echo "NOTE: google test not found, building SuperBin library only."
	@echo "If you want tests too fetch google test like this:"
	@echo "    git clone https://github.com/google/googletest"
	make libSuperBin.a libADELint.a
endif

ADELintTest: ADELintTest.cpp ADELint.o SuperBin.o libgtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) ADELintTest.cpp -o $@ ADELint.o SuperBin.o libgtest.a -lpthread

libADELint.a: ADELint.o
	$(AR) $(ARFLAGS) $@ libADELint.o
	rm ADELint.o

ADELint.o: ADELint.h ADELint.cpp
	$(CPPLINT) $(CPPLINT_FLAGS) ADELint.h
	$(CPPLINT) $(CPPLINT_FLAGS) ADELint.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ADELint.cpp

libSuperBin.a: SuperBin.o
	$(AR) $(ARFLAGS) $@ SuperBin.o
	rm SuperBin.o

SuperBinTest: SuperBinTest.cpp SuperBin.o libgtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) SuperBinTest.cpp -o $@ SuperBin.o libgtest.a -lpthread

SuperBin.o: SuperBin.h SuperBin.cpp
	$(CPPLINT) $(CPPLINT_FLAGS) SuperBin.h
	$(CPPLINT) $(CPPLINT_FLAGS) SuperBin.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c SuperBin.cpp

libgtest.a: $(GTEST_SOURCES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc
	$(AR) $(ARFLAGS) $@ gtest-all.o
	rm gtest-all.o

clean:
	rm -f libgtest.a
	rm -f SuperBin.o libSuperBin.a SuperBinTest
	rm -f ADELint.o libADELint.a ADELintTest

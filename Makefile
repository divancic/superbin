.PHONY: all clean SuperBin
all: test

test: SuperBin test.cpp
	cpplint --verbose=0 --filter=-legal/copyright test.cpp
	clang++ -std=c++11 -Wall -Wpedantic -g test.cpp -o test

SuperBin: SuperBin.h
	cpplint --verbose=0 --filter=-legal/copyright SuperBin.h

clean:
	rm -f test


#Other (sometimes used) compile flags/targets
#clang++ -std=c++14 -Wall -Wpedantic -Wno-vla-extension -Wno-unused-variable -g test.cpp -o test

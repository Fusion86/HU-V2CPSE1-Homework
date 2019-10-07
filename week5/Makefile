# Created by Wouter "Fusion86" Visser
# Licensed under the Specerijen met Eigen Risico Public License

.PHONY: all run clean
all: test

test: test.cpp set.hpp
	g++ -std=c++17 test.cpp -o test -I $(HOME)/Sources/Catch2/single_include/

run: all
	./test

clean:
	rm test

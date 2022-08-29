run: program
	./program

program: main.cpp my_vector.hpp
	g++ -std=c++17 -Wall --pedantic-error -o $@ $^

clean:
	rm -f ./program

.PHONY: run clean

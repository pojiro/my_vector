run: program
	./program

program: main.cpp my_vector.hpp
	g++ -std=c++17 -Wall --pedantic-error -o $@ $^

clean:
	rm -f ./program

watch:
	@while true; do \
	  inotifywait -qq --recursive --event modify --timeout 0 --exclude ".*\.swp" .; \
	  make run; \
	done

.PHONY: watch run clean

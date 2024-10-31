# Suppresses "Entering directory" and "Leaving directory" messages in recursive make calls
MAKEFLAGS += --no-print-directory

# The cpp file where int main() exists
main = main

# Compiles the code with the c++11 standard and automatically locates .cpp and .o files
gpp_11_o = g++ -std=c++11 -c
cpps = $(wildcard *.cpp)
ofiles = $(cpps:.cpp=.o)

# Prevents output from file
.SILENT:

# Default rule to build the executable
$(main): $(ofiles)
	g++ $^ -o $@

# Rule to compile source files to object files
%.o: %.cpp %.h
	$(gpp_11_o) $< -o $@

# Rule to run the program
run: $(main)
	./$(main)
	rm -f  *.o *.gcda *.gcno *.gcov, $(main) #optional

# Rule to clean up generated files, including those from coverage
clean:
	rm -f *.o *.gcda *.gcno *.gcov *.gcov.json *.gcov.json.gz
	rm -f debug $(main) coverage.info
	rm -rf coverage_report

# Creates a debug build which checks for breakpoints in VSC
debug:
	$(MAKE) run
	g++ -std=c++11 -g3 -DDEBUG *.cpp -o debug

# Shows which lines are executed when running the program
coverage:
	g++ -std=c++11 -g -fprofile-arcs -ftest-coverage *.cpp -o $(main) 
	./$(main)
	gcov -f -m -r -j $(main).cpp
	if [ -f *.gcov.json ]; then gzip -f *.gcov.json; fi
	rm -f *.o *.gcda *.gcno *.gcov *.gcov.json.gz debug $(main) coverage.info
	rm -rf coverage_report

# Checks memory usage/leaks
valgrind:
	g++ -std=c++11 -g *.cpp -o $(main) 
	valgrind --leak-check=full ./$(main)
	rm -f *.o *.gcda *.gcno *.gcov, debug $(main) #optional

# Shortcut for 'run' target
r:
	@$(MAKE) run

# Shortcut for 'clean' target
c:
	$(MAKE) clean

# Shortcut for 'debug' target
d: 
	$(MAKE)	debug

# Shortcut for 'coverage' target
cv:
	$(MAKE)	coverage

# Shortcut for 'valgrind' target
v: 
	$(MAKE)	valgrind

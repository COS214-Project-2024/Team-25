# Suppresses "Entering directory" and "Leaving directory" messages in recursive make calls
MAKEFLAGS += --no-print-directory

# The cpp file where int main() exists
main = main
test = test_runner

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11
TEST_FLAGS = -DTESTING

# Find all cpp files except test files
MAIN_SRCS = $(filter-out doctest%.cpp, $(wildcard *.cpp))
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

# Test sources (including the test file)
TEST_SRCS = $(filter-out main.cpp, $(wildcard *.cpp))
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Prevents output from file
.SILENT:

# Default rule to build the executable
$(main): $(MAIN_OBJS)
	$(CXX) $^ -o $@

# Build tests
$(test): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) $^ -o $@

# Rule to compile source files to object files
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the main program
run: $(main)
	./$(main)
	rm -f *.o *.gcda *.gcno *.gcov $(main) #optional

# Rule to run tests
test: $(test)
	./$(test)
	rm -f *.o *.gcda *.gcno *.gcov $(test) #optional

# Rule to clean up generated files
clean:
	rm -f *.o *.gcda *.gcno *.gcov *.gcov.json *.gcov.json.gz
	rm -f debug $(main) $(test) coverage.info
	rm -rf coverage_report
	clear

# Creates a debug build
debug:
	$(MAKE) run
	$(CXX) $(CXXFLAGS) -g3 -DDEBUG *.cpp -o debug

# Coverage analysis
coverage:
	$(CXX) $(CXXFLAGS) -g -fprofile-arcs -ftest-coverage *.cpp -o $(main) 
	./$(main)
	gcov -f -m -r -j $(main).cpp
	if [ -f *.gcov.json ]; then gzip -f *.gcov.json; fi
	rm -f *.o *.gcda *.gcno *.gcov *.gcov.json.gz debug $(main) coverage.info
	rm -rf coverage_report

# Memory leak check
valgrind:
	$(CXX) $(CXXFLAGS) -g $(MAIN_SRCS) -o $(main)  # Changed from *.cpp to $(MAIN_SRCS)
	valgrind --leak-check=full ./$(main)
	rm -f *.o *.gcda *.gcno *.gcov debug $(main)

# Shortcuts
r:
	@$(MAKE) run

t:
	@$(MAKE) test

c:
	$(MAKE) clean

d: 
	$(MAKE)	debug

cv:
	$(MAKE)	coverage

v: 
	$(MAKE)	valgrind

.PHONY: run test clean debug coverage valgrind r t c d cv v
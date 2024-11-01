# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I./h\ files

# Target executable
TARGET = main

# Target for doctest executable
TEST_TARGET = doctest_exec

# Source files and object files
SRC = main.cpp Buildings.cpp Citizen.cpp CityGrowth.cpp Government.cpp Resources.cpp Routines.cpp TaxSystem.cpp Transportation.cpp Utilities.cpp 

OBJ = $(SRC:.cpp=.o)

# Test files
TEST_SRC = doctest.cpp Buildings.cpp Citizen.cpp CityGrowth.cpp Government.cpp Resources.cpp Routines.cpp TaxSystem.cpp Transportation.cpp Utilities.cpp 
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Default target: build the executable
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Link object files to create the doctest executable
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(TARGET)

# Run the executable, ensuring it’s built first
run: all
	./$(TARGET)


# Target to build and run the doctest executable
test: $(TEST_TARGET)
	./$(TEST_TARGET)

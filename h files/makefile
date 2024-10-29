# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I./h\ files

# Target executable
TARGET = main

# Source files and object files
SRC = main.cpp Utilities.cpp Resources.cpp CityGrowth.cpp TaxSystem.cpp Buildings.cpp Citizen.cpp
OBJ = $(SRC:.cpp=.o)

# Default target: build the executable
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(TARGET)

# Run the executable, ensuring it’s built first
run: all
	./$(TARGET)

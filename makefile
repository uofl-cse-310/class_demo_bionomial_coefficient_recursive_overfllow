# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Macro flags
MACROFLAGS = -DMAX_N=30

# Target binary name
TARGET = binomial_coefficient

# Source files
SRC = binomial_coefficient.cpp

# Build target
all: $(TARGET)

# Compile target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(MACROFLAGS) -o $(TARGET) $(SRC)

# Test target
test: $(TARGET)
	./$(TARGET)

# Clean target
clean:
	rm -f $(TARGET)

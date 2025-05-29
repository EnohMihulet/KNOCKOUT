# Compiler and flags
CXX        := g++
CXXFLAGS   := -std=c++17 -Wall -Wextra -Iinclude $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
LDFLAGS    := $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)

# Directories
SRCDIR     := src
BUILDDIR   := build

# Target executable
TARGET     := knockout

# Find all .cpp files under SRCDIR
SOURCES    := $(shell find $(SRCDIR) -name '*.cpp')
# Map src/XYZ.cpp → build/XYZ.o
OBJECTS    := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile step: create build/.../*.o from src/.../*.cpp
# Automatically make directories as needed
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game
run: all
	./$(TARGET)

# Clean out binaries and objects
clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all run clean
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
DEBUG_FLAGS = -g -DDEBUG

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Target executable
TARGET = music_platform

# Source files
SOURCES = $(SRC_DIR)/Song.cpp \
          $(SRC_DIR)/Playlist.cpp \
          $(SRC_DIR)/Library.cpp \
          $(SRC_DIR)/MusicPlayer.cpp \
          $(SRC_DIR)/FileManager.cpp \
          $(SRC_DIR)/main.cpp

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: directories $(BIN_DIR)/$(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# Link object files to create executable
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@
	@echo "Build complete! Executable: $(BIN_DIR)/$(TARGET)"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all
	@echo "Debug build complete!"

# Run the application
run: all
	@echo "Running $(TARGET)..."
	@./$(BIN_DIR)/$(TARGET)

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete!"

# Clean and rebuild
rebuild: clean all

# Install (optional - copy to system path)
install: all
	@echo "Installing $(TARGET)..."
	@cp $(BIN_DIR)/$(TARGET) /usr/local/bin/
	@echo "Installation complete!"

# Uninstall
uninstall:
	@echo "Uninstalling $(TARGET)..."
	@rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstallation complete!"

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  debug    - Build with debug symbols"
	@echo "  run      - Build and run the application"
	@echo "  clean    - Remove build files"
	@echo "  rebuild  - Clean and build"
	@echo "  install  - Install to system (requires sudo)"
	@echo "  uninstall- Remove from system (requires sudo)"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all directories debug run clean rebuild install uninstall help
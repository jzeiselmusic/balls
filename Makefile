# Compiler
CC = gcc

# Target architecture
ARCH = -arch arm64

# Source file
SRC = main.c

# Output binary
TARGET = out

# Library directories and libraries
LIBS = -lraylib

# Compiler flags
CFLAGS = $(ARCH)

# Linker flags
LDFLAGS = $(LIBS) -rpath /usr/local/lib
# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET)

# Define the compiler
CC := gcc
# Check if CROSS_COMPILE is specified
ifneq ($(CROSS_COMPILE),)
    CC := $(CROSS_COMPILE)
endif

# Define the target executable
TARGET := writer
# Define the source file
SRC := writer.c
# Define object file
OBJ := $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^

# Clean target to remove built files
clean:
	rm -f $(TARGET) $(OBJ)

# Specify phony targets
.PHONY: all clean

CC := gcc

CFLAGS := -Wall -Wextra
LDFLAGS := 

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
OBJ_DIR := $(BUILD_DIR)/obj

TARGET := project

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all
all: $(BIN_DIR)/$(TARGET)

-include $(DEPS)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< $(CFLAGS) -MMD -MP -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: run
run:
	./$(BIN_DIR)/$(TARGET)

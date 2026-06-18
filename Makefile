CC := g++ # Compiler Name

SIM := spike pk # Simulator Name

C_FLAGS := -std=c++11 -w -MMD # Compiler Flags

TARGET := a.out # ELF Name

TEST_EXEC := t.out

SRC_DIR := src # Source directory

TEST_DIR := test

BUILD_DIR := build

INCLUDE_DIR := include # Header files directory

#SRC_FILES := $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp))
SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
T_OBJ_FILES := $(filter-out %/main.o, $(OBJ_FILES))
TEST_FILES := $(T_OBJ_FILES) $(BUILD_DIR)/$(TEST_DIR)/test.o
DEP_FILES := $(patsubst %.o,%.d,$(OBJ_FILES))


help:
	@-echo "Use make <target> to compile or run a program"
	@-echo "The possible targets are as follows:"
	@-echo "     run              To execute ELF file thorugh simulator."
	@-echo "     test             To execute the test cases."
	@-echo "     clean            Cleanup the build directory."
	@-echo "     help             To get this menu"
	@-echo "-------------------------------------------------------------------"
	@-echo "Set the following parameters to customize the compilation flow."
	@-echo "     SRC_DIR          Space-separated list of directories containing .c files"
	@-echo "     BUILD_DIR        Path of build directory"
	@-echo "     INCLUDE_DIR      Space-separated list of directories containing .h files"

run: $(BUILD_DIR)/$(TARGET)
	./$<

test: $(BUILD_DIR)/$(TEST_EXEC)
	./$<

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) -c -I$(INCLUDE_DIR) $(C_FLAGS) -MF $(patsubst %.o,%.d,$@) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJ_FILES)
	@$(CC) $^ -o $@

$(BUILD_DIR)/$(TEST_EXEC): $(TEST_FILES)
	@$(CC) $^ -o $@

-include $(DEP_FILES)

print:
	@echo "$(SRC_FILES)"
	@echo "$(OBJ_FILES)"
	@echo "$(DEP_FILES)"
clean:
	@clear
	@rm -rf $(BUILD_DIR)

.PHONY: help preprocess compile assemble link run test clean


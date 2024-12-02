CC := clang++
CFLAGS := -std=c++14 -O3
INCLUDE := -I./include -I./src -I./external/eigen
SRC := $(wildcard src/*.cpp)

TEST_DIR := test
TEST_SRC := $(wildcard $(TEST_DIR)/*.cpp)
BUILD_DIR := $(TEST_DIR)/build

test: $(BUILD_DIR)/test_exec
	$(BUILD_DIR)/test_exec

$(BUILD_DIR)/test_exec: $(SRC) $(TEST_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^
	@clear

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

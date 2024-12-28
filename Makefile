# Detect the operating system
UNAME_S := $(shell uname -s)

# Set the compiler based on the operating system
ifeq ($(UNAME_S),Darwin)
	CXX = /usr/bin/clang++
	GTEST_DIR = /opt/homebrew/Cellar/googletest/1.15.2
	GTEST_LIB = $(GTEST_DIR)/lib
else
	CXX = g++
	GTEST_DIR = ?
	GTEST_LIB = ?
endif

CXXFLAGS = -std=c++23 -Wall -Wextra -O2
TARGET = simple-svg
SRC = main_1.0.0.cpp
BUILD_DIR = build
TARGET_PATH = $(BUILD_DIR)/$(TARGET)

TEST_DIR = test
TEST_TARGET = $(TEST_DIR)/simple_svg_test

.PHONY: all run clean install compile_commands test

all: $(TARGET_PATH)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET_PATH): $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET_PATH) $(SRC)

run: $(TARGET_PATH)
	@pushd $(BUILD_DIR) > /dev/null && \
	./$(TARGET) && \
	popd > /dev/null

$(TEST_TARGET): $(TEST_TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_TARGET).cpp \
		-I$(GTEST_DIR)/include \
		-L$(GTEST_LIB) \
		-lgtest -lgtest_main -pthread

test: $(TEST_TARGET) run-test

run-test:
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TEST_TARGET)

install: $(TARGET_PATH)
	cp $(TARGET_PATH) /usr/local/bin/$(TARGET)

compile_commands: | $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
	ln -sf $(BUILD_DIR)/compile_commands.json .

cmake_build: | $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

cmake_run: cmake_build
	@pushd $(BUILD_DIR) > /dev/null && \
	./$(TARGET) && \
	popd > /dev/null

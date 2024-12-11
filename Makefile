CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g


TARGET = bin/simple_svg
SRCS = main_1.0.0.cpp

.PHONY: all clean run create_bin

all: create_bin $(TARGET)

create_bin:
	mkdir -p bin

$(TARGET): $(SRCS) | create_bin
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(TARGET)

run: $(TARGET)
	pushd bin && ./simple_svg && popd

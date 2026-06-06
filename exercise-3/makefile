CXX = g++
# Added -fsanitize=address for memory safety checks
CXXFLAGS = -Wall -Wextra -std=c++17 -fsanitize=address -g
LDFLAGS = -fsanitize=address

SRC_DIR = src
BUILD_DIR = build
ASM_DIR = asm

CLIENT = $(BUILD_DIR)/client
SERVER = $(BUILD_DIR)/server

.PHONY: all clean asm

all: $(BUILD_DIR) $(CLIENT) $(SERVER)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(ASM_DIR):
	mkdir -p $(ASM_DIR)

$(CLIENT): $(SRC_DIR)/tcp_echo_client.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

$(SERVER): $(SRC_DIR)/tcp_echo_server.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Target to generate assembly files
asm: $(ASM_DIR)
	$(CXX) $(CXXFLAGS) -S $(SRC_DIR)/tcp_echo_client.cc -o $(ASM_DIR)/tcp_echo_client.s
	$(CXX) $(CXXFLAGS) -S $(SRC_DIR)/tcp_echo_server.cc -o $(ASM_DIR)/tcp_echo_server.s

clean:
	rm -rf $(BUILD_DIR) $(ASM_DIR)
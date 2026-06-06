CXX = g++
# Added -fsanitize=address for memory safety checks
CXXFLAGS = -Wall -Wextra -std=c++17 -fsanitize=address -g
LDFLAGS = -fsanitize=address

SRC_DIR = src
BUILD_DIR = build
ASM_DIR = asm_files

# Target binaries
CLIENT = $(BUILD_DIR)/client
SERVER = $(BUILD_DIR)/server

# Shared objects
UTILS_OBJ = $(BUILD_DIR)/utils.o

.PHONY: all clean asm

all: $(BUILD_DIR) $(CLIENT) $(SERVER)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(ASM_DIR):
	mkdir -p $(ASM_DIR)

# Rule for shared utility object
$(UTILS_OBJ): $(SRC_DIR)/utils.cpp $(SRC_DIR)/utils.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for client object and binary
$(BUILD_DIR)/tcp_echo_client.o: $(SRC_DIR)/tcp_echo_client.cpp $(SRC_DIR)/utils.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(CLIENT): $(BUILD_DIR)/tcp_echo_client.o $(UTILS_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Rule for server object and binary
$(BUILD_DIR)/tcp_echo_server.o: $(SRC_DIR)/tcp_echo_server.cpp $(SRC_DIR)/utils.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SERVER): $(BUILD_DIR)/tcp_echo_server.o $(UTILS_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Target to generate assembly files
asm: $(ASM_DIR)
	$(CXX) $(CXXFLAGS) -S $(SRC_DIR)/tcp_echo_client.cpp -o $(ASM_DIR)/tcp_echo_client.s
	$(CXX) $(CXXFLAGS) -S $(SRC_DIR)/tcp_echo_server.cpp -o $(ASM_DIR)/tcp_echo_server.s
	$(CXX) $(CXXFLAGS) -S $(SRC_DIR)/utils.cpp -o $(ASM_DIR)/utils.s

clean:
	rm -rf $(BUILD_DIR) $(ASM_DIR)
# For the refactored code
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC_DIR = refactored
BUILD_DIR = build

CLIENT = $(BUILD_DIR)/client
SERVER = $(BUILD_DIR)/server

.PHONY: all clean

all: $(BUILD_DIR) $(CLIENT) $(SERVER)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CLIENT): $(SRC_DIR)/tcp_echo_client.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(SERVER): $(SRC_DIR)/tcp_echo_server.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)
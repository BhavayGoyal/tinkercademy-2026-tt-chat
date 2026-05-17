// using src/tcp_echo_client.cc as a reference
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <optional>

const int kPort = 8080;
const std::string kServerAddress = "127.0.0.1";
const int kBufferSize = 1024;

std::optional<std::string> parse_arguments(int argc, char* argv[]) {
    if (argc > 1) return std::string(argv[1]);
    return std::nullopt;
}

int create_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        exit(EXIT_FAILURE);
    }
    return sock;
}

sockaddr_in setup_address(const std::string& ip, int port) {
    sockaddr_in address{}; // {} zero-initializes the struct, preventing garbage values
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported\n";
        exit(EXIT_FAILURE);
    }
    return address;
}

void connect_to_server(int sock, const sockaddr_in& address) {
    if (connect(sock, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Connection Failed\n";
        close(sock);
        exit(EXIT_FAILURE);
    }
}

void send_all(int sock, const std::string& message) {
    size_t total_sent = 0;
    while (total_sent < message.size()) {
        ssize_t sent = send(sock, message.c_str() + total_sent, message.size() - total_sent, 0);
        if (sent < 0) {
            std::cerr << "Failed to send data\n";
            break;
        }
        total_sent += sent;
    }
    std::cout << "Sent: " << message << "\n";
}

void receive_response(int sock) {
    char buffer[kBufferSize] = {0};
    ssize_t read_size = read(sock, buffer, kBufferSize - 1); // Read up to kBufferSize - 1 to leave room for the null terminator
    if (read_size > 0) {
        buffer[read_size] = '\0';
        std::cout << "Received: " << buffer << "\n";
    } else if (read_size == 0) {
        std::cout << "Server closed connection.\n";
    } else {
        std::cerr << "Read error\n";
    }
}

int main(int argc, char* argv[]) {
    std::string message = parse_arguments(argc, argv).value_or("Default Message from Client");

    int my_sock = create_socket();
    sockaddr_in server_address = setup_address(kServerAddress, kPort);

    connect_to_server(my_sock, server_address);
    send_all(my_sock, message);
    receive_response(my_sock);

    close(my_sock);
    return 0;
}
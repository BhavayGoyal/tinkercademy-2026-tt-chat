// using src/tcp_echo_server.cc as a reference
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const int kPort = 8080;
const int kBufferSize = 1024;

int setup_server(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error\n";
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 ||
        setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        std::cerr << "setsockopt error\n";
        close(sock);
        exit(EXIT_FAILURE);
    }

    sockaddr_in address{}; // {} zero-initializes the struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sock, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "bind failed\n";
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (listen(sock, 3) < 0) {
        std::cerr << "listen failed\n";
        close(sock);
        exit(EXIT_FAILURE);
    }

    return sock;
}

// we should run a loop to check that everything is sent back to the client 
void send_all(int sock, const char* buffer, size_t length) {
    size_t total_sent = 0;
    while (total_sent < length) {
        ssize_t sent = send(sock, buffer + total_sent, length - total_sent, 0);
        if (sent < 0) {
            std::cerr << "Failed to send data back to client\n";
            break;
        }
        total_sent += sent;
    }
}

void handle_client(int client_sock) {
    char buffer[kBufferSize] = {0};
    
    // Read up to kBufferSize - 1
    ssize_t read_size = read(client_sock, buffer, kBufferSize - 1);
    
    if (read_size > 0) {
        buffer[read_size] = '\0'; // Guarantee null termination
        std::cout << "Received: " << buffer << "\n";
        
        send_all(client_sock, buffer, read_size);
        std::cout << "Echo message sent\n";
    } else if (read_size == 0) {
        std::cout << "Client disconnected.\n";
    } else {
        std::cerr << "Read error\n";
    }

    close(client_sock);
}

void run_server_loop(int server_sock) {
    sockaddr_in address{};
    socklen_t addrlen = sizeof(address);

    std::cout << "Server listening on port " << kPort << "\n";

    while (true) {
        int new_sock = accept(server_sock, (struct sockaddr*)&address, &addrlen);
        if (new_sock < 0) {
            std::cerr << "accept error\n";
            continue;
        }
        
        handle_client(new_sock);
    }
}

int main() {
    int server_sock = setup_server(kPort);
    run_server_loop(server_sock);
    
    close(server_sock); 
    return 0;
}
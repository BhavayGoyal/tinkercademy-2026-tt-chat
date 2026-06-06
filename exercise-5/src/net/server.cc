#include "server.h"
#include "../utils.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

namespace tt::chat::net {

Server::Server(int port) {
  sock_ = socket(AF_INET, SOCK_STREAM, 0);
  check_error(sock_ < 0, "Socket creation error");

  int opt = 1;
  int err_code = setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
  check_error(err_code < 0, "setsockopt error");

  address_ = {};
  address_.sin_family = AF_INET;
  address_.sin_addr.s_addr = INADDR_ANY;
  address_.sin_port = htons(port);
}

Server::~Server() {
  if (sock_ >= 0) {
    close(sock_);
  }
}

void Server::Start() {
  int err_code = bind(sock_, (sockaddr*)&address_, sizeof(address_));
  check_error(err_code < 0, "Bind failed");

  err_code = listen(sock_, 3);
  check_error(err_code < 0, "Listen failed");
  
  std::cout << "Server listening on port " << ntohs(address_.sin_port) << "\n";
}

void Server::Run() {
  socklen_t addr_len = sizeof(address_);
  while (true) {
    int client_sock = accept(sock_, (sockaddr*)&address_, &addr_len);
    check_error(client_sock < 0, "Accept error");
    HandleAccept(client_sock);
  }
}

void Server::HandleAccept(int client_sock) {
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  ssize_t read_size = read(client_sock, buffer, kBufferSize - 1);

  if (read_size > 0) {
    buffer[read_size] = '\0';
    std::cout << "Received: " << buffer << "\n";
    send_all(client_sock, buffer, read_size);  // ✅ Clean and simple
    std::cout << "Echo message sent\n";
  } else if (read_size == 0) {
    std::cout << "Client disconnected.\n";
  } else {
    std::cerr << "Read error on client socket " << client_sock << "\n";
  }
  close(client_sock);
}



} // namespace tt::chat::net

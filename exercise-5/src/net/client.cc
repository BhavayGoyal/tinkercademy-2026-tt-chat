#include "client.h"
#include "../utils.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

namespace tt::chat::net {

Client::Client(const std::string& ip, int port) {
  sock_ = socket(AF_INET, SOCK_STREAM, 0);
  check_error(sock_ < 0, "Socket creation error");

  server_address_ = {};
  server_address_.sin_family = AF_INET;
  server_address_.sin_port = htons(port);

  int err_code = inet_pton(AF_INET, ip.c_str(), &server_address_.sin_addr);
  check_error(err_code <= 0, "Invalid address/ Address not supported");
}

Client::~Client() {
  if (sock_ >= 0) {
    close(sock_);
  }
}

void Client::Connect() {
  int err_code = connect(sock_, (sockaddr*)&server_address_, sizeof(server_address_));
  check_error(err_code < 0, "Connection Failed");
}

void Client::SendAndReceive(const std::string& message) {
  const int kBufferSize = 1024;
  char recv_buffer[kBufferSize] = {0};

  send(sock_, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";

  ssize_t read_size = read(sock_, recv_buffer, kBufferSize);
  check_error(read_size < 0, "Read error");
  
  if (read_size > 0) {
    std::cout << "Received: " << recv_buffer << "\n";
  } else if (read_size == 0) {
    std::cout << "Server closed connection.\n";
  }
}

} // namespace tt::chat::net

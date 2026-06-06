#pragma once

#include <arpa/inet.h>
#include <string>

namespace tt::chat::net {

class Client {
 public:
  Client(const std::string& ip, int port);
  ~Client();

  void Connect();
  void SendAndReceive(const std::string& message);

 private:
  int sock_;
  sockaddr_in server_address_;
};

} // namespace tt::chat::net

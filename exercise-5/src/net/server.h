#pragma once

#include <netinet/in.h>

namespace tt::chat::net {

class Server {
 public:
  Server(int port);
  ~Server();

  void Start();
  void Run();

 private:
  void HandleAccept(int client_sock);

  int sock_;
  sockaddr_in address_;
};

} // namespace tt::chat::net

#include "net/client.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <message>\n";
    return EXIT_FAILURE;
  }

  const std::string kServerAddress = "127.0.0.1";
  const int kPort = 8080;
  std::string message = argv[1];

  tt::chat::net::Client client(kServerAddress, kPort);
  client.Connect();
  client.SendAndReceive(message);

  return 0;
}

#include "net/server.h"

int main() {
  const int kPort = 8080;
  tt::chat::net::Server server(kPort);
  server.Start();
  server.Run();

  return 0;
}

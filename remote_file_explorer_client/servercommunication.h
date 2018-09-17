#ifndef SERVERCOMMUNICATION_H
#define SERVERCOMMUNICATION_H
#include "request.h"
#include "response.h"

using namespace file_remote_explorer_library;
namespace remote_file_explorer_client {
class ServerCommunication
{
public:
  virtual Response getResponse(Request request) = 0;
  virtual ~ServerCommunication() = 0;
};
}
#endif // SERVERCOMMUNICATION_H

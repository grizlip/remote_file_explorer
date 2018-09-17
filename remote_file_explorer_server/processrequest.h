#ifndef PROCESSREQUEST_H
#define PROCESSREQUEST_H
#include "request.h"
#include "response.h"

using namespace file_remote_explorer_library;
namespace remote_file_explorer_server {
class ProcessRequest
{
public:
  ProcessRequest();
  Response getResponse(Request r);
};
}
#endif // PROCESSREQUEST_H

#ifndef SERVERCOMMUNICATIONMOCK_H
#define SERVERCOMMUNICATIONMOCK_H
#include "servercommunication.h"

using namespace remote_file_explorer_client;
class ServerCommunicationMock : public ServerCommunication
{
public:
  explicit ServerCommunicationMock(Response r)
    : m_response(r)
  {
  }
  Response getResponse(Request request) override;

  inline Request getRequest() const { return m_request; }

  ~ServerCommunicationMock() override {}

private:
  Response m_response;
  Request m_request;
};

#endif // SERVERCOMMUNICATIONMOCK_H

#include "servercommunicationmock.h"

Response
ServerCommunicationMock::getResponse(Request request)
{
  m_request = request;
  return m_response;
}


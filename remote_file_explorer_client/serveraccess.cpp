#include "serveraccess.h"
#include "request.h"
#include "response.h"
#include <QHostAddress>
#include <QTcpSocket>

using namespace file_remote_explorer_library;
namespace remote_file_explorer_client {
void
ServerAccess::setNewPath(QString path)
{
  QStringList args = { path };
  executeCommand(COMMAND_GET_FILES_LIST, args);
  // todo: do something with response.
}

QString
ServerAccess::getFile(QString path)
{
  QStringList args = { path };
  QString result = executeCommand(COMMAND_GET_FILE, args).getResposne().first();
  return result;
}

Response
ServerAccess::executeCommand(Command command, QStringList args)
{
  Request r(command, args);
  return m_serverCommunication->getResponse(r);
}
}

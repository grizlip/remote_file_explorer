#ifndef SERVERACCESS_H
#define SERVERACCESS_H

#include "servercommunication.h"
#include <QObject>
#include <QString>
#include <QStringList>
namespace remote_file_explorer_client {
class ServerAccess
{
public:
  explicit ServerAccess(ServerCommunication& serverCommunication)
    : m_serverCommunication(&serverCommunication)
  {
  }
  QString getFile(QString path);
  void setNewPath(QString path);

protected:
  inline Response executeCommand(file_remote_explorer_library::Command command,
                                 QStringList args);

private:
  ServerCommunication* m_serverCommunication;
};
}
#endif // SERVERACCESS_H

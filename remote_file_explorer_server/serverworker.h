#ifndef SERVERWORKER_H
#define SERVERWORKER_H
#include "processrequest.h"
#include <QTcpSocket>
#include <QThread>
namespace remote_file_explorer_server {
class ServerWorker : public QThread
{
  Q_OBJECT
public:
  explicit ServerWorker(int socketDescriptor, QObject* parent);
  void run() override;

signals:
  void error(QTcpSocket::SocketError socketError);

private:
  int m_socketDescriptor;
  ProcessRequest m_processRequest;
};
}
#endif // SERVERWORKER_H

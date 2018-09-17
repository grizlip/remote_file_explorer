#ifndef REMOTEFILESERVER_H
#define REMOTEFILESERVER_H

#include <QObject>
#include <QTcpServer>

namespace remote_file_explorer_server {
class RemoteFileServer : public QTcpServer
{
  Q_OBJECT
public:
  explicit RemoteFileServer(QObject* parent = nullptr);

protected:
  void incomingConnection(qintptr handle) override;
signals:

public slots:
  void startServer();
};
}
#endif // REMOTEFILESERVER_H

#include "remotefileserver.h"
#include "serverworker.h"
#include <QString>
#include <QTcpServer>
#include <QtNetwork>

namespace remote_file_explorer_server {
RemoteFileServer::RemoteFileServer(QObject* parent)
  : QTcpServer(parent)
{
}

void
RemoteFileServer::incomingConnection(qintptr socketDescriptor)
{
  ServerWorker* thread = new ServerWorker(socketDescriptor, this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();
}

void
RemoteFileServer::startServer()
{
  if (!this->listen(QHostAddress::Any, 8080)) {
    qDebug() << "Can't start server.";
  } else {
    qDebug() << "Using port: " << this->serverPort();
  }
}
}

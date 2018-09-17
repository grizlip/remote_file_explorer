#include "serverworker.h"
#include "processrequest.h"
#include "request.h"
#include "response.h"
#include <QFileInfo>
#include <QtNetwork>
using namespace file_remote_explorer_library;
namespace remote_file_explorer_server {
ServerWorker::ServerWorker(int socketDescriptor, QObject* parent)
  : QThread(parent)
  , m_socketDescriptor(socketDescriptor)
{
}

void
ServerWorker::run()
{
  QByteArray outBlock;
  QByteArray inBlock;
  inBlock.resize(1024);
  QDataStream out(&outBlock, QIODevice::WriteOnly);
  QDataStream in(&inBlock, QIODevice::ReadWrite);
  out.setVersion(QDataStream::Qt_5_10);
  in.setVersion(QDataStream::Qt_5_10);

  QStringList newFiles;
  QTcpSocket tcpSocket;
  QScopedPointer<Response> write;

  if (!tcpSocket.setSocketDescriptor(m_socketDescriptor)) {
    emit error(tcpSocket.error());
    return;
  }

  if (tcpSocket.waitForReadyRead()) {
    tcpSocket.read(inBlock.data(), 1024);
    Request read;
    in >> read;
    Response r = m_processRequest.getResponse(read);
    write.reset(new Response(OK, r.getResposne()));
  } else {
    write.reset(new Response(NOOK, newFiles));
  }

  out << *write.get();
  tcpSocket.write(outBlock);
  tcpSocket.disconnectFromHost();
  tcpSocket.waitForDisconnected();
}
}

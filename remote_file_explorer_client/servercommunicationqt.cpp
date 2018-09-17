#include "servercommunicationqt.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QTcpSocket>

using namespace file_remote_explorer_library;

namespace remote_file_explorer_client {
Response
ServerCommunicationQT::getResponse(Request request)
{
  Response res;
  QByteArray outBlock;
  QByteArray inBlock;
  inBlock.resize(1024);
  QDataStream out(&outBlock, QIODevice::WriteOnly);
  QDataStream in(&inBlock, QIODevice::ReadWrite);
  out.setVersion(QDataStream::Qt_5_10);
  in.setVersion(QDataStream::Qt_5_10);
  out << request;
  QTcpSocket tcpClient;
  tcpClient.connectToHost(m_host, 8080);
  if (tcpClient.waitForConnected()) {
    tcpClient.write(outBlock);

    if (tcpClient.waitForReadyRead()) {
      tcpClient.read(inBlock.data(), 1024);
      in >> res;
      if (res.getStatus() == OK) {
        switch (request.getCommand()) {
          case COMMAND_GET_FILE: {
            QString result = res.getResposne().first();
            emit newFilePreview(result);
            break;
          }
          case COMMAND_GET_FILES_LIST: {
            QList<QString> currentFileList;
            for (auto item : res.getResposne()) {
              currentFileList.push_back(item);
            }
            emit newFilesList(currentFileList);
            break;
          }
        }
      }
    } else {
      qDebug() << "Client did not recieve anything!";
    }
  } else {
    qDebug() << "Can't connect to host!";
  }

  tcpClient.disconnectFromHost();
  tcpClient.waitForDisconnected();
  return res;
}
}

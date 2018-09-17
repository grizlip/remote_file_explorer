#include <QtNetwork>
#include "networkfilemodel.h"

NetworkFileModel::NetworkFileModel(const QString path, QObject *parent)
    : QObject(parent)
{
    tcpClient.connectToHost(QHostAddress::LocalHost, 8080);

    connect(&tcpClient, SIGNAL(connected()), this, SLOT(startTransfer()));
    connect(&tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(updateClientProgress(qint64)));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void NetworkFileModel::startTransfer()
{
    // called when the TCP client connected to the loopback server

}

void NetworkFileModel::updateServerProgress()
{

}


void NetworkFileModel::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    tcpClient.close();

}


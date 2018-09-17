#ifndef NETWORKFILEMODEL_H
#define NETWORKFILEMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QTcpSocket>
#include "stringlistmodel.h"

class NetworkFileModel : QObject
{
    Q_OBJECT

public:
    NetworkFileModel(const QString path, QObject *parent = nullptr);
protected:
    void startTransfer();
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError socketError);


private:

    QTcpSocket tcpClient;

};

#endif // NETWORKFILEMODEL_H

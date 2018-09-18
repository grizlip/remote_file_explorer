#ifndef SERVERCOMMUNICATIONQT_H
#define SERVERCOMMUNICATIONQT_H
#include <QObject>

#include "request.h"
#include "response.h"
#include "servercommunication.h"

using namespace file_remote_explorer_library;
namespace remote_file_explorer_client {
class ServerCommunicationQT : public QObject, public ServerCommunication
{
  Q_OBJECT
public:
  explicit ServerCommunicationQT(QString host, QObject* parent = nullptr)
    : QObject(parent)
    , m_host(host)
  {
  }
  Response getResponse(Request request) override;
signals:
  void newFilesList(QList<QString>& list);
  void newFilePreview(const QString& string);

private:
  QString m_host;
};
}
#endif // SERVERCOMMUNICATIONQT_H

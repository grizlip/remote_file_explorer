#ifndef RESPONSE_H
#define RESPONSE_H
#include "remote_file_explorer_library.h"
#include <QDataStream>
#include <QString>
#include <QStringList>

#if defined RESPONSE_H
#define REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT Q_DECL_EXPORT
#else
#define REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT Q_DECL_IMPORT
#endif
namespace file_remote_explorer_library {
enum ResponseStatus
{
  OK,
  NOOK
};

class REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT Response
{
public:
  explicit Response(ResponseStatus s, QStringList response)
    : m_status(s)
    , m_response(response)
  {
  }
  explicit Response() {}

  ResponseStatus getStatus() { return m_status; }

  const QStringList getResposne() { return m_response; }
  friend QDataStream& operator>>(QDataStream& str, Response& m);
  friend QDataStream& operator<<(QDataStream& str, const Response& m);

private:
  ResponseStatus m_status;
  QStringList m_response;
};
REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT QDataStream& operator<<(
  QDataStream& str, const Response& m);

REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT QDataStream& operator>>(
  QDataStream& str, Response& m);
}
#endif // RESPONSE_H

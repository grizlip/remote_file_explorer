#ifndef REQUEST_H
#define REQUEST_H
#include "remote_file_explorer_library.h"
#include <QDataStream>
#include <QString>
#include <QStringList>

#if defined REQUEST_H
#define REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT Q_DECL_EXPORT
#else
#define REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT Q_DECL_IMPORT
#endif
namespace file_remote_explorer_library {
enum Command
{
  COMMAND_GET_FILES_LIST,
  COMMAND_GET_FILE
};

class REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT Request
{

public:
  explicit Request(Command command, QStringList args)
    : m_command(command)
    , m_arguments(args)
  {
  }
  explicit Request() {}
  Command getCommand() { return m_command; }
  const QStringList getArguments() { return m_arguments; }

  friend QDataStream& operator>>(QDataStream& str, Request& m);
  friend QDataStream& operator<<(QDataStream& str, const Request& m);

private:
  Command m_command;
  QStringList m_arguments;
};
REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT QDataStream& operator<<(
  QDataStream& str, const Request& m);

REMOTE_FILE_EXPLORER_LIBRARYSHARED_EXPORT QDataStream& operator>>(
  QDataStream& str, Request& m);
}
#endif // REQUEST_H

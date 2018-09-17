#include "request.h"
namespace file_remote_explorer_library {
QDataStream&
operator<<(QDataStream& str, const Request& m)
{
  str << m.m_command;
  str << m.m_arguments.size();
  for (auto loopStr : m.m_arguments) {
    str << loopStr;
  }
  return str;
}
QDataStream&
operator>>(QDataStream& str, Request& m)
{
  m.m_command = (Command)get<qint32>(str);
  qint32 size = get<qint32>(str);
  for (int i = 0; i < size; i++) {
    m.m_arguments << get<QString>(str);
  }
  return str;
}
}

#include "response.h"
namespace file_remote_explorer_library {

QDataStream&
operator>>(QDataStream& str, Response& m)
{
  m.m_status = (ResponseStatus)get<qint32>(str);
  qint32 size = get<qint32>(str);
  for (int i = 0; i < size; i++) {
    m.m_response << get<QString>(str);
  }
  return str;
}
QDataStream&
operator<<(QDataStream& str, const Response& m)
{
  str << m.m_status;
  str << m.m_response.size();
  for (auto loopStr : m.m_response) {
    str << loopStr;
  }
  return str;
}
}

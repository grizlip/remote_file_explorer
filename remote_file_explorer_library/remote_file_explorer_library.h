#ifndef FILE_REMOTE_EXPLORER_LIBRARY_H
#define FILE_REMOTE_EXPLORER_LIBRARY_H

#include <QtCore/qglobal.h>
template <typename T>
T
get(QDataStream& str)
{
  T value;
  str >> value;
  return value;
}

#endif // FILE_REMOTE_EXPLORER_LIBRARY

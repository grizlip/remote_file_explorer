#include "processrequest.h"
#include <QDirIterator>
#include <QScopedPointer>

using namespace file_remote_explorer_library;
namespace remote_file_explorer_server {
ProcessRequest::ProcessRequest()
{
}

Response
ProcessRequest::getResponse(Request read)
{
  QScopedPointer<Response> write;
  QStringList newFiles;
  Command c = read.getCommand();
  switch (c) {
    case COMMAND_GET_FILES_LIST: {
      QString path = read.getArguments().first();
      if (!path.isEmpty()) {
        QDirIterator it(path, QDirIterator::NoIteratorFlags);
        while (it.hasNext()) {
          it.next();
          if (!(it.fileName() == ".")) {
            newFiles.push_back(it.fileName());
          }
        }
      }
      write.reset(new Response(OK, newFiles));
      break;
    }
    case COMMAND_GET_FILE: {
      QString path = read.getArguments().first();
      QFileInfo fi(path);

      if (!fi.exists() || fi.suffix() != "txt") {
        QString message("No preview available.");
        newFiles.push_back(message);

      } else {
        QFile f(path);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
          QString result(f.readAll());
          newFiles.push_back(result);
        } else {
          QString message("No preview available.");
          newFiles.push_back(message);
        }
      }
      write.reset(new Response(OK, newFiles));
      break;
    }
    default: {
      write.reset(new Response(NOOK, newFiles));
      break;
    }
  }
  return *write.get();
}
}

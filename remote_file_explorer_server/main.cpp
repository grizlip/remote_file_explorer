#include "remotefileserver.h"
#include <QCoreApplication>
#include <QTimer>

using namespace remote_file_explorer_server;
int
main(int argc, char* argv[])
{
  QCoreApplication a(argc, argv);

  RemoteFileServer t;

  /* Code below is to start the server when main event loop is up */
  QTimer::singleShot(0, &t, SLOT(startServer()));
  return a.exec();
}

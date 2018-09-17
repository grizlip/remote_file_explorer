#include "serveraccess.h"
#include "servercommunicationqt.h"
#include "stringlistmodel.h"
#include "textpreview.h"
#include <QApplication>
#include <QFileSystemModel>
#include <QListView>
#include <QScopedPointer>
#include <QSplitter>
#include <QTreeView>

using namespace remote_file_explorer_client;

int
main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  QScopedPointer<QSplitter> splitter{ new QSplitter };
  ServerCommunicationQT scQT("localhost", splitter.get());
  ServerAccess sa(scQT);
  StringListModel* slm1 =
    new StringListModel(QDir::currentPath(), &sa, splitter.get());
  QObject::connect(&scQT, SIGNAL(newFilesList(QList<QString>&)), slm1,
                   SLOT(newFilesListAvilable(QList<QString>&)));

  QListView* list = new QListView(splitter.get());

  list->setDragEnabled(true);
  list->setAcceptDrops(true);
  list->setSpacing(5);
  list->setMovement(QListView::Snap);
  list->setDropIndicatorShown(true);
  QObject::connect(list, SIGNAL(doubleClicked(const QModelIndex&)), slm1,
                   SLOT(doubleClick(const QModelIndex&)));
  list->setModel(slm1);

  TextPreview* tp = new TextPreview(&sa, splitter.get());
  tp->setText("Drop files here!");
  slm1->setInitialPath();
  splitter->setWindowTitle("Drag'n'Drop example");
  splitter->show();

  return app.exec();
}

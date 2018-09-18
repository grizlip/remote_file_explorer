#include "textpreview.h"
#include <QFile>
#include <QFile>
#include <QFileInfo>
#include <QtWidgets>
namespace remote_file_explorer_client {
TextPreview::TextPreview(ServerAccess* sa, QWidget* parent)
  : QTextEdit(parent)
{
  m_sa = sa;
  setReadOnly(true);
}

void
TextPreview::dragEnterEvent(QDragEnterEvent* event)
{
  if (event->mimeData()->hasFormat("text/x-drag-and-drop-piece"))
    event->accept();
  else
    event->ignore();
}

void
TextPreview::dragLeaveEvent(QDragLeaveEvent* event)
{
  event->accept();
}

void
TextPreview::dragMoveEvent(QDragMoveEvent* event)
{

  if (event->mimeData()->hasFormat("text/x-drag-and-drop-piece")) {

    event->accept();
  } else {
    event->ignore();
  }
}

void
TextPreview::dropEvent(QDropEvent* event)
{
  if (event->mimeData()->hasFormat("text/x-drag-and-drop-piece")) {
    QByteArray pieceData =
      event->mimeData()->data("text/x-drag-and-drop-piece");
    QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
    QString s;
    dataStream >> s;
    QString text = m_sa->getFile(s);
    this->setText(text);
    event->setDropAction(Qt::MoveAction);
    event->accept();

  } else {

    event->ignore();
  }
}
}

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
TextPreview::setContents(const QString& fileName)
{
  QFileInfo fi(fileName);
  srcUrl = QUrl::fromLocalFile(fi.absoluteFilePath());
  QFile file(fileName);
  if (file.open(QIODevice::ReadOnly)) {
    QString data(file.readAll());
    if (fileName.endsWith(".html"))
      setHtml(data);
    else
      setPlainText(data);
  }
}

QVariant
TextPreview::loadResource(int type, const QUrl& name)
{
  if (type == QTextDocument::ImageResource) {
    QFile file(srcUrl.resolved(name).toLocalFile());
    if (file.open(QIODevice::ReadOnly))
      return file.readAll();
  }
  return QTextEdit::loadResource(type, name);
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

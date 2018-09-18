#ifndef TEXTPREVIEW_H
#define TEXTPREVIEW_H

#include "serveraccess.h"
#include <QTextEdit>
#include <QUrl>

namespace remote_file_explorer_client {

class TextPreview : public QTextEdit
{
  Q_OBJECT

public:
  TextPreview(ServerAccess* sa, QWidget* parent = nullptr);

private:
  void dragLeaveEvent(QDragLeaveEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;
  void dragEnterEvent(QDragEnterEvent* event) override;

  ServerAccess* m_sa;
};
}
#endif // TEXTPREVIEW_H

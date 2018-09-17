#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H
#include "serveraccess.h"
#include <QAbstractListModel>
#include <QDebug>
#include <QDirIterator>
#include <QMutex>
#include <QTime>

namespace remote_file_explorer_client {
class StringListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  StringListModel(const QString path, ServerAccess* sa,
                  QObject* parent = nullptr)
    : QAbstractListModel(parent)
    , m_currentPath(path)
  {
    m_sa = sa;
  }

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  bool insertRows(int row, int count,
                  const QModelIndex& parent = QModelIndex()) override;

  bool removeRows(int row, int count,
                  const QModelIndex& parent = QModelIndex()) override;

  bool removeRow(int row, const QModelIndex& parent = QModelIndex());

  bool setData(const QModelIndex& index, const QVariant& value,
               int role) override;

  Qt::ItemFlags flags(const QModelIndex& index) const override
  {
    if (index.isValid())
      return (QAbstractListModel::flags(index) | Qt::ItemIsDragEnabled |
              Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    return Qt::NoItemFlags;
  }

  bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row,
                    int column, const QModelIndex& parent) override;
  QMimeData* mimeData(const QModelIndexList& indexes) const override;
  QStringList mimeTypes() const override;

  Qt::DropActions supportedDropActions() const override
  {
    return Qt::IgnoreAction;
  }

  Qt::DropActions supportedDragActions() const override
  {
    return Qt::CopyAction;
  }
  void setInitialPath();
public slots:
  void doubleClick(const QModelIndex&);
  void newFilesListAvilable(QList<QString>& list);

protected:
  ServerAccess* m_sa;
  QStringList stringList;
  QString m_currentPath;
};
}
#endif // STRINGLISTMODEL_H

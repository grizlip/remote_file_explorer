#include "stringlistmodel.h"
#include <QDataStream>
#include <QFile>
#include <QFileInfo>
#include <QMimeData>
#include <QTextStream>
#include <qiodevice.h>
namespace remote_file_explorer_client {
int
StringListModel::rowCount(const QModelIndex& parent) const
{
  (void)parent;
  return stringList.count();
}

QVariant
StringListModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= stringList.size())
    return QVariant();

  if (role == Qt::DisplayRole)
    return stringList.at(index.row());
  else
    return QVariant();
}

QVariant
StringListModel::headerData(int section, Qt::Orientation orientation,
                            int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    return QString("Column %1").arg(section);
  else
    return QString("Row %1").arg(section);
}

bool
StringListModel::insertRows(int row, int count, const QModelIndex& parent)
{
  bool result = false;

  beginInsertRows(parent, row, row + count - 1);

  for (int i = 0; i < count; i++) {
    stringList.insert(row, "");
    result = true;
  }

  endInsertRows();

  return result;
}

bool
StringListModel::removeRow(int row, const QModelIndex& parent)
{
  bool result = false;

  result = QAbstractListModel::removeRow(row, parent);

  return result;
}

bool
StringListModel::removeRows(int row, int count, const QModelIndex& parent)
{
  bool result = false;
  if (row + count > 0) {
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i++) {
      stringList.removeAt(row);
      result = true;
    }

    endRemoveRows();
  }
  return result;
}

bool
StringListModel::setData(const QModelIndex& index, const QVariant& value,
                         int role)
{
  bool result = false;
  if (!index.isValid())
    result = false;

  if (index.row() >= stringList.size())
    result = false;

  if (role == Qt::EditRole) {
    if (stringList.count() > 0) {
      stringList.replace(index.row(), value.toString());
    } else {
      stringList.push_back(value.toString());
    }
    emit dataChanged(QModelIndex(), QModelIndex());
    result = true;
  }

  return result;
}

bool
StringListModel::dropMimeData(const QMimeData* data, Qt::DropAction action,
                              int row, int column, const QModelIndex& parent)
{
  if (!data->hasFormat("text/x-drag-and-drop-piece"))
    return false;

  if (action == Qt::IgnoreAction)
    return true;

  if (column > 0)
    return false;

  if (row == -1) {
    // here we are trying to put something after last item
    row = stringList.count();
  }
  QByteArray encodedData = data->data("text/x-drag-and-drop-piece");
  QDataStream stream(&encodedData, QIODevice::ReadOnly);
  QString string;
  stream >> string;

  beginInsertRows(parent, row, row);
  stringList.insert(row, string);
  endInsertRows();

  return true;
}

QMimeData*
StringListModel::mimeData(const QModelIndexList& indexes) const
{
  QMimeData* mimeData = new QMimeData();
  QByteArray encodedData;

  QDataStream stream(&encodedData, QIODevice::WriteOnly);

  foreach (QModelIndex index, indexes) {
    if (index.isValid()) {
      stream << QDir::cleanPath(m_currentPath + QDir::separator() +
                                data(index, Qt::DisplayRole).toString());
    }
  }

  mimeData->setData("text/x-drag-and-drop-piece", encodedData);

  return mimeData;
}

QStringList
StringListModel::mimeTypes() const
{
  QStringList types;
  types << "text/x-drag-and-drop-piece";
  return types;
}

void
StringListModel::newFilesListAvilable(QList<QString>& list)
{
  this->stringList.clear();
  auto it = list.begin();

  int row = 0;
  while (it != list.end()) {
    if (!(it.i->t() == ".")) {
      beginInsertRows(QModelIndex(), row, row);
      this->stringList.push_back(it.i->t());
      row++;
      endInsertRows();
    }
    it++;
  }
}

void
StringListModel::doubleClick(const QModelIndex& index)
{
  if (index.isValid()) {

    QVariant data = this->data(index, Qt::DisplayRole);
    QDir dir(m_currentPath);

    QString newSelection = data.toString();

    if (".." == newSelection) {
      dir.cdUp();
      this->m_currentPath = dir.absolutePath();
    } else if (!("." == newSelection)) {

      QString newPath =
        QDir::cleanPath(m_currentPath + QDir::separator() + newSelection);
      QFileInfo fileInfo(newPath);

      if (!fileInfo.isFile() && fileInfo.exists()) {
        this->m_currentPath = newPath;
      }
    }
    m_sa->setNewPath(m_currentPath);
  }
}
void
StringListModel::setInitialPath()
{
  m_sa->setNewPath(m_currentPath);
}
}

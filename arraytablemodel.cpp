#include "arraytablemodel.h"

ArrayTableModel::ArrayTableModel(QObject* parent) : QAbstractTableModel(parent)
{
}

void ArrayTableModel::setUnsortedData(const QVector<int>& unsortedData)
{
    beginResetModel();
    m_unsortedData = unsortedData;
    m_sortedData.clear();
    endResetModel();
}

void ArrayTableModel::setSortedData(const QVector<int>& sortedData)
{
    m_sortedData = sortedData;
    emit dataChanged(index(0, 1), index(rowCount() - 1, 1), {Qt::DisplayRole});
}

int ArrayTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return qMax(m_unsortedData.size(), m_sortedData.size());
}

int ArrayTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 2; // Single column for the array elements
}

QVariant ArrayTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int col = index.column();

        if (row >= 0 && row < m_unsortedData.size())
        {
            if (col == 0)
                return m_unsortedData[row]; // Return unsorted array element for column 0
        }

        if (row >= 0 && row < m_sortedData.size())
        {
            if (col == 1)
                return m_sortedData[row]; // Return sorted array element for column 1
        }
    }

    return QVariant();
}

QVariant ArrayTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        // Set custom column names
        if (section == 0) {
            return QVariant("Unsorted");
        } else if (section == 1) {
            return QVariant("Sorted");
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

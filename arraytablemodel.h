#ifndef ARRAYTABLEMODEL_H
#define ARRAYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class ArrayTableModel : public QAbstractTableModel
{
public:
    explicit ArrayTableModel(QObject* parent = nullptr);
    void setUnsortedData(const QVector<int>& unsortedData);
    void setSortedData(const QVector<int>& sortedData);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QVector<int> m_unsortedData;
    QVector<int> m_sortedData;
};

#endif // ARRAYTABLEMODEL_H

#ifndef SORTINGALGORITHMVISUALIZER_H
#define SORTINGALGORITHMVISUALIZER_H

#include "arraytablemodel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SortingAlgorithmVisualizer; }
QT_END_NAMESPACE

class SortingAlgorithmVisualizer : public QMainWindow
{
    Q_OBJECT

public:
    SortingAlgorithmVisualizer(QWidget *parent = nullptr);
    ~SortingAlgorithmVisualizer();

private slots:
    void generateArrayClicked();
    void startButtonClicked();
    void algorithmComboCurrentIndexChanged(int index);

private:
    Ui::SortingAlgorithmVisualizer *ui;
    ArrayTableModel *arrayTableModel;
    QVector<int> unsortedArray;
    QVector<int> sortedArray;

    void generateArray(int size, int start, int end, QVector<int>& unsortedArray);
    QString elapsedTime(QVector<int> (SortingAlgorithmVisualizer::*)());
    QVector<int> bubbleSort();
    QVector<int> selectionSort();
    QVector<int> insertionSort();
    QVector<int> mergeSort();
    QVector<int> mergeSortRecursive(const QVector<int>& array);
    QVector<int> merge(const QVector<int>& left, const QVector<int>& right);
    QVector<int> quickSort();
    QVector<int> quickSortRecursive(QVector<int>& array, int start, int end);
    int partition(QVector<int>& array, int start, int end);
    QVector<int> heapSort();
    void heapify(QVector<int>& array, int size, int parentIndex);
    QVector<int> radixSort();
    void countingSort(QVector<int>& array, int size, int pos);
    void swap(QVector<int>& array, int index1, int index2);
};
#endif // SORTINGALGORITHMVISUALIZER_H

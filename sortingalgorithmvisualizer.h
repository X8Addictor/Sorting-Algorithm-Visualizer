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

private:
    Ui::SortingAlgorithmVisualizer *ui;
    ArrayTableModel *arrayTableModel;
    QVector<int> unsortedArray;

    void generateArray(int size, int start, int end, QVector<int>& unsortedArray);
    QVector<int> bubbleSort();
    QVector<int> selectionSort();
    QVector<int> insertionSort();
    QVector<int> mergeSort();
    QVector<int> mergeSortRecursive(const QVector<int>& array);
    QVector<int> merge(const QVector<int>& left, const QVector<int>& right);
    QVector<int> quickSort();
    QVector<int> quickSortRecursive(QVector<int>& array, int low, int high);
    int partition(QVector<int>& array, int low, int high);
    QVector<int> heapSort();
    void heapify(QVector<int>& array, int size, int rootIndex);
    QVector<int> radixSort();
    void countingSort(QVector<int>& array, int size, int exp);
    void swap(QVector<int>& array, int index1, int index2);
};
#endif // SORTINGALGORITHMVISUALIZER_H

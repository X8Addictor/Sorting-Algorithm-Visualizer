#include "sortingalgorithmvisualizer.h"
#include "ui_sortingalgorithmvisualizer.h"
#include <QAbstractTableModel>

SortingAlgorithmVisualizer::SortingAlgorithmVisualizer(QWidget *parent) : QMainWindow(parent), ui(new Ui::SortingAlgorithmVisualizer)
{
    ui->setupUi(this); // Setting up the UI

    arrayTableModel = new ArrayTableModel(this); // Creating an instance for of the ArrayTableModel
    ui->arrayTableView->setModel(arrayTableModel); // Setting the model for the arrayTableView

    // Setting placeholder texts for size, start and end
    ui->arraySizeLineEdit->setPlaceholderText("50");
    ui->rangeStartLineEdit->setPlaceholderText("0");
    ui->rangeEndLineEdit->setPlaceholderText("99");

    // Connecting signal to slots
    connect(ui->generateArrayButton, &QPushButton::clicked, this, &SortingAlgorithmVisualizer::generateArrayClicked);
    connect(ui->startButton, &QPushButton::clicked, this, &SortingAlgorithmVisualizer::startButtonClicked);
}

SortingAlgorithmVisualizer::~SortingAlgorithmVisualizer()
{
    delete ui; // Deleting the UI after use
}

// Event handler for the "Generate Array" button
void SortingAlgorithmVisualizer::generateArrayClicked()
{
    QString arraySizeLineEdit, rangeStartLineEdit, rangeEndLineEdit;
    int size, start, end;

    // Retreiving the size, start and end values
    arraySizeLineEdit = ui->arraySizeLineEdit->text();
    rangeStartLineEdit = ui->rangeStartLineEdit->text();
    rangeEndLineEdit = ui->rangeEndLineEdit->text();

    // Setting default values if the inputs are empty
    size = 50;
    start = 0;
    end = 99;

    // Checking for empty inputs for size, start and end
    if(!arraySizeLineEdit.isEmpty())
    {
        size = ui->arraySizeLineEdit->text().toInt();
    }

    if(!rangeStartLineEdit.isEmpty())
    {
        start = ui->rangeStartLineEdit->text().toInt();
    }

    if(!rangeEndLineEdit.isEmpty())
    {
        end = ui->rangeEndLineEdit->text().toInt();
    }

    unsortedArray.resize(size); // Resize the unsortedArray
    generateArray(size, start, end, unsortedArray); // Generating the array using the given parameters

    arrayTableModel->setUnsortedData(unsortedArray); // Setting the unsorted array dat in the ArrayTableModel
}

// Event handler for "Start" button
void SortingAlgorithmVisualizer::startButtonClicked()
{
    QVector<int> sortedArray; // Creating a QVector to store the sorted array

    int select;
    select = ui->algorithmCombo->currentIndex() + 1; // Retrieving the selected algorithm index from the combo box

    switch (select)
    {
    case 1:
        sortedArray = bubbleSort();
        break;

    case 2:
        sortedArray = selectionSort();
        break;

    case 3:
        sortedArray = insertionSort();
        break;

    case 4:
        sortedArray = mergeSort();
        break;

    case 5:
        sortedArray = quickSort();
        break;

    case 6:
        sortedArray = heapSort();
        break;

    case 7:
        sortedArray = radixSort();
        break;
    }

    arrayTableModel->setSortedData(sortedArray); // Setting the sorted array data in the ArrayTableModel
}

// Function for generating the array based on given paratmeters
void SortingAlgorithmVisualizer::generateArray(int size, int start, int end, QVector<int>& unsortedArray)
{
    srand(time(nullptr));

    for(int i = 0; i < size; i++)
    {
            unsortedArray[i] = start + (rand() % end + 1);
    }
}

// Functions for sorting algorithms
QVector<int> SortingAlgorithmVisualizer::bubbleSort()
{
    QVector<int> sortedArray;

    // Performing bubble sort
    int n = unsortedArray.size();
    sortedArray = unsortedArray;

    for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (sortedArray[j] > sortedArray[j + 1]) {
                    swap(sortedArray, j, j + 1);
                }
            }
    }

    return sortedArray;
}

QVector<int> SortingAlgorithmVisualizer::selectionSort()
{
    QVector<int> sortedArray;

    // Performing selection sort
    int n = unsortedArray.size();
    sortedArray = unsortedArray;

    for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (sortedArray[j] < sortedArray[minIndex]) {
                    minIndex = j;
                }
            }
            swap(sortedArray, minIndex, i);
    }

    return sortedArray;
}

QVector<int> SortingAlgorithmVisualizer::insertionSort()
{
    QVector<int> sortedArray;

    // Performing insertion sort
    int n = unsortedArray.size();
    sortedArray = unsortedArray;

    for (int i = 1; i < n; i++) {
            int key = sortedArray[i];
            int j = i - 1;
            while (j >= 0 && sortedArray[j] > key) {
                sortedArray[j + 1] = sortedArray[j];
                j--;
            }
            sortedArray[j + 1] = key;
    }

    return sortedArray;
}

QVector<int> SortingAlgorithmVisualizer::mergeSort()
{
    QVector<int> sortedArray;

    // Performing merge sort
    sortedArray = mergeSortRecursive(unsortedArray);

    return sortedArray;
}

QVector<int> SortingAlgorithmVisualizer::mergeSortRecursive(const QVector<int>& array)
{
    int n = array.size();
    if (n <= 1) {
            return array;
    }

    int mid = n / 2;
    QVector<int> left = mergeSortRecursive(array.mid(0, mid));
    QVector<int> right = mergeSortRecursive(array.mid(mid));

    return merge(left, right);
}

QVector<int> SortingAlgorithmVisualizer::merge(const QVector<int>& left, const QVector<int>& right)
{
    int leftSize = left.size();
    int rightSize = right.size();
    int i = 0, j = 0, k = 0;
    QVector<int> mergedArray(leftSize + rightSize);

    while (i < leftSize && j < rightSize) {
            if (left[i] <= right[j]) {
                mergedArray[k] = left[i];
                i++;
            } else {
                mergedArray[k] = right[j];
                j++;
            }
            k++;
    }

    while (i < leftSize) {
            mergedArray[k] = left[i];
            i++;
            k++;
    }

    while (j < rightSize) {
            mergedArray[k] = right[j];
            j++;
            k++;
    }

    return mergedArray;
}

QVector<int> SortingAlgorithmVisualizer::quickSort()
{
    QVector<int> sortedArray;

    // Performing quick sort
    sortedArray = quickSortRecursive(unsortedArray, 0, unsortedArray.size() - 1);

    return sortedArray;
}

QVector<int> SortingAlgorithmVisualizer::quickSortRecursive(QVector<int>& array, int low, int high)
{
    if (low < high) {
            int pivotIndex = partition(array, low, high);
            quickSortRecursive(array, low, pivotIndex - 1);
            quickSortRecursive(array, pivotIndex + 1, high);
    }

    return array;
}

int SortingAlgorithmVisualizer::partition(QVector<int>& array, int low, int high)
{
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
            if (array[j] <= pivot) {
                i++;
                swap(array, i, j);
            }
    }

    // Swap the pivot element
    swap(array, i + 1, high);

    return i + 1;
}

QVector<int> SortingAlgorithmVisualizer::heapSort()
{
    QVector<int> sortedArray;

    // Performing heap sort
    int n = unsortedArray.size();
    sortedArray = unsortedArray;

    for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(sortedArray, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
            swap(sortedArray, 0, i);

            heapify(sortedArray, i, 0);
    }

    return sortedArray;
}

void SortingAlgorithmVisualizer::heapify(QVector<int>& array, int size, int rootIndex)
{
    int largest = rootIndex;
    int leftChild = 2 * rootIndex + 1;
    int rightChild = 2 * rootIndex + 2;

    if (leftChild < size && array[leftChild] > array[largest]) {
            largest = leftChild;
    }

    if (rightChild < size && array[rightChild] > array[largest]) {
            largest = rightChild;
    }

    if (largest != rootIndex) {
            swap(array, rootIndex, largest);

            heapify(array, size, largest);
    }
}

QVector<int> SortingAlgorithmVisualizer::radixSort()
{
    QVector<int> sortedArray;

    // Performing radix sort
    int n = unsortedArray.size();
    sortedArray = unsortedArray;

    // Find the maximum element to determine the number of digits
    int maxElement = sortedArray[0];
    for (int i = 1; i < n; i++) {
            if (sortedArray[i] > maxElement) {
                maxElement = sortedArray[i];
            }
    }

    // Perform counting sort for each digit
    for (int exp = 1; maxElement / exp > 0; exp *= 10) {
            countingSort(sortedArray, n, exp);
    }

    return sortedArray;
}

void SortingAlgorithmVisualizer::countingSort(QVector<int>& array, int size, int exp)
{
    QVector<int> output(size);
    QVector<int> count(10, 0);

    // Count the occurrences of each digit
    for (int i = 0; i < size; i++) {
            ++count[(array[i] / exp) % 10];
    }

    // Calculate the cumulative count
    for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = size - 1; i >= 0; i--) {
            output[count[(array[i] / exp) % 10] - 1] = array[i];
            --count[(array[i] / exp) % 10];
    }

    // Copy the output array to the original array
    for (int i = 0; i < size; i++) {
            array[i] = output[i];
    }
}

void SortingAlgorithmVisualizer::swap(QVector<int>& array, int index1, int index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

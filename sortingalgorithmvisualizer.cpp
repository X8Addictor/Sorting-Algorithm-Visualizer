#include "sortingalgorithmvisualizer.h"
#include "ui_sortingalgorithmvisualizer.h"
#include <QAbstractTableModel>
#include <QElapsedTimer>

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
    connect(ui->algorithmCombo, &QComboBox::currentIndexChanged, this, &SortingAlgorithmVisualizer::algorithmComboCurrentIndexChanged);
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
    if (unsortedArray.size() <= 0)
    {
        return;
    }

    int select;
    select = ui->algorithmCombo->currentIndex(); // Retrieving the selected algorithm index from the combo box

    QString timeTaken;

    switch (select)
    {
    case 1:
        timeTaken = elapsedTime(&SortingAlgorithmVisualizer::bubbleSort);
        break;

    case 2:
        timeTaken = elapsedTime(&SortingAlgorithmVisualizer::selectionSort);
        break;

    case 3:
        timeTaken = elapsedTime(&SortingAlgorithmVisualizer::insertionSort);
        break;

    case 4:
        timeTaken = elapsedTime(&SortingAlgorithmVisualizer::mergeSort);
        break;

    case 5:
        timeTaken = elapsedTime(&SortingAlgorithmVisualizer::quickSort);
        break;

    case 6:
        timeTaken = elapsedTime(&SortingAlgorithmVisualizer::heapSort);
        break;

    case 7:
        timeTaken = elapsedTime(&SortingAlgorithmVisualizer::radixSort);
        break;
    }

    arrayTableModel->setSortedData(sortedArray); // Setting the sorted array data in the ArrayTableModel
    ui->timeTakenLabel->setText(timeTaken); // Setting the time taken for an algorithm to complete
}

// Function to calculate the time taken for an algorithm to complete
QString SortingAlgorithmVisualizer::elapsedTime(QVector<int> (SortingAlgorithmVisualizer::*algorithm)())
{
    QElapsedTimer timer;
    timer.start();

    sortedArray = (this->*algorithm)();

    qint64 timeElapsed = timer.nsecsElapsed(); // Time elapsed in nanoseconds
    QString timeTaken;
    int size = sortedArray.size();


    if (size >= 5000)
    {
        timeElapsed /= 1000000; // Conversion to milliseconds
        timeTaken = QString::number(timeElapsed) + " ms";
    }
    else
    {
        timeElapsed /= 1000; // Conversion to microseconds
        timeTaken = QString::number(timeElapsed) + " μs";
    }

    return timeTaken;
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

// Bubble sort function
QVector<int> SortingAlgorithmVisualizer::bubbleSort()
{
    QVector<int> sortedArray;

    // Performing bubble sort
    int size = unsortedArray.size();
    sortedArray = unsortedArray;

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (sortedArray[j] > sortedArray[j + 1])
            {
                swap(sortedArray, j, j + 1); // Swap with right adjacent value
            }
        }
    }

    return sortedArray;
}

// Selection sort function
QVector<int> SortingAlgorithmVisualizer::selectionSort()
{
    QVector<int> sortedArray;

    // Performing selection sort
    int size = unsortedArray.size();
    sortedArray = unsortedArray;

    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i; // Assiging minIndex of the current iteration
        for (int j = i + 1; j < size; j++)
        {
            if (sortedArray[j] < sortedArray[minIndex])
            {
                minIndex = j; // Reassigning minIndex if lower value is found
            }
        }
        swap(sortedArray, minIndex, i); // Swap minIndex value to current index
    }

    return sortedArray;
}

// Insertion sort function
QVector<int> SortingAlgorithmVisualizer::insertionSort()
{
    QVector<int> sortedArray;

    // Performing insertion sort
    int size = unsortedArray.size();
    sortedArray = unsortedArray;

    for (int i = 1; i < size; i++)
    {
        int key = sortedArray[i]; // Temporary key to compare with left adjacent values
        int j = i - 1;
        while (j >= 0 && sortedArray[j] > key)
        {
            sortedArray[j + 1] = sortedArray[j]; // Shifting values to left if current index value is greater than key
            j--;
        }
        sortedArray[j + 1] = key; // Moving key to current index after left shift
    }

    return sortedArray;
}

// Merge sort function
QVector<int> SortingAlgorithmVisualizer::mergeSort()
{
    QVector<int> sortedArray;

    // Performing merge sort
    sortedArray = mergeSortRecursive(unsortedArray); // Recursively splitting, sorting and merging the array

    return sortedArray;
}

// Helper function to split the array from the middle
QVector<int> SortingAlgorithmVisualizer::mergeSortRecursive(const QVector<int>& array)
{
    int size = array.size();
    if (size <= 1) // Base case
    {
        return array;
    }

    int mid = size / 2; // Middle index
    QVector<int> left = mergeSortRecursive(array.mid(0, mid)); // Recursive call for left side array
    QVector<int> right = mergeSortRecursive(array.mid(mid)); // Recursive call for right side array

    return merge(left, right);
}

// Helper function to merge the array
QVector<int> SortingAlgorithmVisualizer::merge(const QVector<int>& left, const QVector<int>& right)
{
    int leftSize = left.size();
    int rightSize = right.size();
    int i = 0, j = 0, k = 0;
    QVector<int> mergedArray(leftSize + rightSize);

    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
        {
            mergedArray[k] = left[i]; // Adding left array value if smaller than right array value
            i++;
        } else
        {
            mergedArray[k] = right[j]; // Adding right array value if smaller than left array value
            j++;
        }
        k++;
    }

    while (i < leftSize)
    {
        mergedArray[k] = left[i]; // Adding remaining left array values
        i++;
        k++;
    }

    while (j < rightSize)
    {
        mergedArray[k] = right[j]; // Adding remaining right array values
        j++;
        k++;
    }

    return mergedArray;
}

// Quick sort function
QVector<int> SortingAlgorithmVisualizer::quickSort()
{
    QVector<int> sortedArray;

    // Performing quick sort
    sortedArray = quickSortRecursive(unsortedArray, 0, unsortedArray.size() - 1); // Recursively splitting, sorting and merging the array

    return sortedArray;
}

// Helper function
QVector<int> SortingAlgorithmVisualizer::quickSortRecursive(QVector<int>& array, int start, int end)
{
    if (end <= start) // Base case
    {
        return array;
    }

    int pivotIndex = partition(array, start, end);
    quickSortRecursive(array, start, pivotIndex - 1); // Recursive call for left side array
    quickSortRecursive(array, pivotIndex + 1, end); // Recursive call for right side array

    return array;
}

// Helper function to split the array based on the pivot value
int SortingAlgorithmVisualizer::partition(QVector<int>& array, int start, int end)
{
    int pivot = array[end]; // Assigning the last index value as pivot value
    int i = start - 1;

    for (int j = start; j <= end - 1; j++)
    {
        if (array[j] <= pivot) {
            i++;
            swap(array, i, j); // Swap current index value if greater than pivot value
        }
    }

    swap(array, i + 1, end); // Swaping the pivot element

    return i + 1; // Returning the pivot index
}

// Heap sort function
QVector<int> SortingAlgorithmVisualizer::heapSort()
{
    QVector<int> sortedArray;

    // Performing heap sort
    int n = unsortedArray.size();
    sortedArray = unsortedArray;

    // First loop to create max heap tree structure to start sorting
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(sortedArray, n, i);
    }

    // Second loop to sort and create max heap structure after an iteration of sorting
    for (int i = n - 1; i > 0; i--)
    {
        swap(sortedArray, 0, i);
        heapify(sortedArray, i, 0);
    }

    return sortedArray;
}

// Helper function to rearrange the elements in max heap format
void SortingAlgorithmVisualizer::heapify(QVector<int>& array, int size, int parentIndex)
{
    int largest = parentIndex; // Root node
    int leftChild = 2 * parentIndex + 1; // Child node on the left
    int rightChild = 2 * parentIndex + 2; // Child note on the right

    if (leftChild < size && array[leftChild] > array[largest])
    {
        largest = leftChild; // Assigns index of left child node if greater than parent node
    }

    if (rightChild < size && array[rightChild] > array[largest])
    {
        largest = rightChild; // Assigns index of right child node if greater than parent node
    }

    if (largest != parentIndex)
    {
        swap(array, parentIndex, largest); // Swap if parent node is not greater of left and right child node
        heapify(array, size, largest);
    }
}

// Radix sort function
QVector<int> SortingAlgorithmVisualizer::radixSort()
{
    QVector<int> sortedArray;

    // Performing radix sort
    int n = unsortedArray.size();
    sortedArray = unsortedArray;

    // Finding the maximum element to determine the number of digits
    int maxElement = sortedArray[0];
    for (int i = 1; i < n; i++)
    {
        if (sortedArray[i] > maxElement)
        {
            maxElement = sortedArray[i];
        }
    }

    // Performing counting sort for each digit
    for (int pos = 1; maxElement / pos > 0; pos *= 10)
    {
        countingSort(sortedArray, n, pos);
    }

    return sortedArray;
}

// Helper function
void SortingAlgorithmVisualizer::countingSort(QVector<int>& array, int size, int pos)
{
    QVector<int> output(size);
    QVector<int> count(10, 0);

    // Counting the occurrences of each digit
    for (int i = 0; i < size; i++)
    {
        ++count[(array[i] / pos) % 10];
    }

    // Calculating the cumulative count
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // Building the output array
    for (int i = size - 1; i >= 0; i--)
    {
        output[count[(array[i] / pos) % 10] - 1] = array[i];
        --count[(array[i] / pos) % 10];
    }

    // Copying the output array to the original array
    for (int i = 0; i < size; i++)
    {
        array[i] = output[i];
    }
}

// Swap function to swap 2 elements within the array
void SortingAlgorithmVisualizer::swap(QVector<int>& array, int index1, int index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

// Event handler for displaying the time and space complexity
void SortingAlgorithmVisualizer::algorithmComboCurrentIndexChanged(int index)
{
    ui->currentTimeComplexityLabel->setTextFormat(Qt::RichText);

    switch (index)
    {
    case 0:
        ui->currentTimeComplexityLabel->clear();
        ui->currentSpaceComplexityLabel->clear();
        break;

    case 1:
        ui->currentTimeComplexityLabel->setText("O(n<sup>2</sup>)");
        ui->currentSpaceComplexityLabel->setText("O(1)");
        break;

    case 2:
        ui->currentTimeComplexityLabel->setText("O(n<sup>2</sup>)");
        ui->currentSpaceComplexityLabel->setText("O(1)");
        break;

    case 3:
        ui->currentTimeComplexityLabel->setText("O(n<sup>2</sup>)");
        ui->currentSpaceComplexityLabel->setText("O(1)");
        break;

    case 4:
        ui->currentTimeComplexityLabel->setText("O(n log n)");
        ui->currentSpaceComplexityLabel->setText("O(n)");
        break;

    case 5:
        ui->currentTimeComplexityLabel->setText("O(n log n)");
        ui->currentSpaceComplexityLabel->setText("O(log n)");
        break;

    case 6:
        ui->currentTimeComplexityLabel->setText("O(n log n)");
        ui->currentSpaceComplexityLabel->setText("O(1)");
        break;

    case 7:
        ui->currentTimeComplexityLabel->setText("O(d * (n + k))");
        ui->currentSpaceComplexityLabel->setText("O(n + k)");
        break;
    }
}


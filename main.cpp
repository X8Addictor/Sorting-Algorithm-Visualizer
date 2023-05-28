#include "sortingalgorithmvisualizer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Initializing and starting the QApplication
    QApplication a(argc, argv);
    SortingAlgorithmVisualizer w;
    w.show();
    return a.exec();
}

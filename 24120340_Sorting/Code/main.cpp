#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>


#include "BubbleSort.h"
#include "CountingSort.h"
#include "DataGenerator.h"
#include "FlashSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "RadixSort.h"
#include "SelectionSort.h"
#include "ShakerSort.h"
#include "ShellSort.h"
#include "WriteToCSV.h"

using namespace std;
using namespace std::chrono;
typedef void (*sortAlgo)(int *, int);

sortAlgo s[] = {selectionSort, insertionSort, 
                bubbleSort, shakerSort, shellSort,
                heapSort, mergeSort, quickSort,
                countingSort, radixSort, flashSort};

const string algoName[11] = {
    "selection-sort", "insertion-sort", "bubble-sort",
    "shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort",
    "counting-sort", "radix-sort", "flash-sort"};

const string dataDistribution[4] = {"RandomData", "SortedData", "ReverseData",
                                    "NearlySortedData"};

const int dataSize[4] = {10000, 30000, 50000, 100000};

double process(int *a, int n, sortAlgo f, int nameIdx)
{
    auto start = system_clock::now();
    f(a, n);
    auto stop = system_clock::now();
    std::chrono::duration<double, std::milli> timeCost = stop - start;
    double ms = timeCost.count();
    cout << setw(25) << left << (algoName[nameIdx]) << setw(25)
         << right << fixed << setprecision(3) << ms << " ms\t->";
    if (is_sorted(a, a + n))
        cout << "SUCCEED!\n";
    else
        cout << "NOOOOOO!\n";
    return ms;
}

bool validAlgo(const string &algo)
{
    for (int i = 0; i < 11; i++)
    {
        if (algoName[i] == algo)
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    int *source = NULL;
    int *a = NULL;


    // Chose the way to sort array

    if (argc != 7)
    {
        cout << "./main.exe -a <Sort_way> -i <input_txt> -o <output_txt'";
        return 0;
    }

    string sort_way, input_file, output_file;

    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            sort_way = argv[i + 1];
            if (!validAlgo(sort_way))
            {
                cout << "Invalid sorting algorithm.";
                return 0;
            }
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            input_file = argv[i + 1];
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            output_file = argv[i + 1];
        }
        else
        {
            cout << "Invalid argument: " << argv[i];
            return 0;
        }
    }

    ifstream file(input_file);
    if (!file)
    {
        cout << "Invalid file.";
    }
    int num;
    file >> num;
    int* arr = new int[num];
    for (int i = 0; i < num; i++)
    {
        file >> arr[i];
    }
    file.close();

    auto it = find(begin(algoName), end(algoName), sort_way);
    if (it != end(algoName))
    {
        int idx = distance(begin(algoName), it);
        process(arr, num, s[idx], idx);
    }
    else
    {
        cout << "Invalid sorting algorithm specified.";
        delete[] arr;
        return 0;
    }

    ofstream output(output_file);
    if (!output)
    {
        cout << "Unable to open output file.";
        delete[] arr;
        return 0;
    }
    for (int i = 0; i < num; i++)
    {
        output << arr[i] << " ";
    }
    output.close();
    delete[] arr;
    return 0;
}

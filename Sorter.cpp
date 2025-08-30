#include <iostream>
#include <vector>
#include <string>
#include "SortImpls.cpp"
#include <sys/time.h>

using namespace std;

void InitArray(vector<int> &, int);
void InitArrayMid(vector<int> &, int);
void PrintArrayDetails(const vector<int> &, string);
int elapsed(timeval &startTime, timeval &endTime);
void insertSorted(vector<int>& sortedVec, int value);
vector<int> sortVector(const vector<int>& vec);
vector<int> reverseVector(const vector<int>& sortedVec);

int main(int argc, char *argv[])
{
    int size = 0;
    string sort_name = "";
    bool printOut = true;
    int index1 = 0;
    int index2 = -1;

    if ((argc < 3) || (argc > 6))
    {
        cerr << "Usage: Sorter SORT_TYPE ARRAY_SIZE [YES|NO] [INDEX1 INDEX2]" << endl;
        return -1;
    }

    sort_name = string(argv[1]);
    size = atoi(argv[2]);
    if (size <= 0)
    {
        cerr << "Array size must be positive" << endl;
        return -1;
    }

    if (argc >= 4)
    {
        string printArr = string(argv[3]);
        if (printArr == "NO")
        {
            printOut = false;
        }
        else if (printArr != "YES")
        {
            cerr << "Usage: Sorter SORT_TYPE ARRAY_SIZE [YES|NO] [INDEX1 INDEX2]" << endl;
            return -1;
        }
    }

    // Parse indices if BubbleSort and provided
    if (sort_name == "BubbleSort" && argc == 6) {
        index1 = atoi(argv[4]);
        index2 = atoi(argv[5]);

        if (index1 < 0 || index2 >= size || index1 > index2) {
            cerr << "Invalid indices for BubbleSort. Ensure 0 <= index1 <= index2 < ARRAY_SIZE." << endl;
            return -1;
        }
    } else {
        // Default indices for other sorting methods or BubbleSort without specified range
        index1 = 0;
        index2 = size - 1;
    }

    srand(1);
    vector<int> items(size);
    InitArrayMid(items, size);

    if (printOut)
    {
        cout << "Initial:" << endl;
        PrintArrayDetails(items, string("items"));
    }

    struct timeval startTime, endTime;
    gettimeofday(&startTime, 0); // Linux

    // Choose sorting method
    if (sort_name == "BubbleSort")
    {
        BubbleSort(items, index1, index2);
    }
    else if (sort_name == "InsertionSort")
    {
        InsertionSort(items, 0, size - 1);
    }
    else if (sort_name == "MergeSort")
    {
        MergeSort(items, 0, size - 1);
    }
    else if (sort_name == "QuickSort")
    {
        QuickSort(items, 0, size - 1);
    }
    else if (sort_name == "ShellSort")
    {
        ShellSort(items, 0, size - 1);
    }
    else
    {
        cerr << "Unknown sort type: " << sort_name << endl;
        return -1;
    }

    gettimeofday(&endTime, 0);

    if (printOut)
    {
        cout << "Sorted:" << endl;
        PrintArrayDetails(items, string("items"));
    }

    int elapsed_secs = elapsed(startTime, endTime);
    cout << "Time (ms): " << elapsed_secs << endl;
    return 0;
}

void InitArray(vector<int> &array, int randMax)
{
    if (randMax < 0)
    {
        return;
    }

    vector<int> pool(randMax);

    for (int i = 0; i < randMax; i++)
    {
        pool[i] = i;
    }

    int spot;

    for (int i = 0; i < randMax; i++)
    {
        spot = rand() % (pool.size());
        array[i] = pool[spot];
        pool.erase(pool.begin() + spot);
    }
}

void InitArrayMid(vector<int> &array, int randMax)
{
    if (randMax < 0)
    {
        return;
    }

    vector<int> pool(randMax);

    for (int i = 0; i < randMax; i++)
    {
        pool[i] = i;
        array[i] = i;
    }

    int spot;
    int i1 = 0.01*randMax;
    int i2 = 0.99*randMax;

    for (int i = i1; i < i2; i++)
    {
        spot = rand() % (pool.size());
        array[i] = pool[spot];
        pool.erase(pool.begin() + spot);
    }
}

void PrintArrayDetails(const vector<int> &array, string name)
{
    int size = array.size();

    for (int i = 0; i < size; i++)
    {
        cout << name << "[" << i << "] = " << array[i] << endl;
    }
}

// Function to calculate elapsed time if using gettimeofday (Linux)
int elapsed( timeval &startTime, timeval &endTime )
{
    return ( endTime.tv_sec - startTime.tv_sec ) * 1000000 + ( endTime.tv_usec -
    startTime.tv_usec );
}
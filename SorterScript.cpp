#include <iostream>
#include <vector>
#include <string>
#include "SortImpls.cpp"
#include <sys/time.h>

using namespace std;

void InitArray(vector<int> &, int);
void InitArrayMid(vector<int> &, int);
int elapsed(timeval &startTime, timeval &endTime);
void RunScript();
void InitOrderedArray(vector<int> &, int);
void InitReversedArray(vector<int> &, int);
double RunSort(const string& sort_name, vector<int>& items);

int main(int argc, char *argv[])
{
    RunScript();
    return 0;
}

void RunScript()
{
    vector<int> sizes;
    sizes.push_back(100);
    sizes.push_back(1000);
    sizes.push_back(5000);
    sizes.push_back(10000);
    sizes.push_back(50000);
    sizes.push_back(100000);
    sizes.push_back(500000);
    sizes.push_back(1000000);

    vector<int> sizes_n2;
    sizes_n2.push_back(100);
    sizes_n2.push_back(250);
    sizes_n2.push_back(500);
    sizes_n2.push_back(1000);
    sizes_n2.push_back(2500);
    sizes_n2.push_back(5000);
    sizes_n2.push_back(7500);
    sizes_n2.push_back(10000);

    vector<string> sorts;
    sorts.push_back("BubbleSort");
    sorts.push_back("InsertionSort");
    sorts.push_back("MergeSort");
    sorts.push_back("QuickSort");
    sorts.push_back("ShellSort");

    int repetitions = 3;

    for (const string& sort_name : sorts)
    {
        vector<int> applicable_sizes = sizes;

        // Use smaller sizes for O(n^2) algorithms
        if (sort_name == "BubbleSort" || sort_name == "InsertionSort")
        {
            applicable_sizes = sizes_n2;
        }

        cout << "Testing " << sort_name << ":\n";

        for (int size : applicable_sizes) {
            cout << "Array Size: " << size << endl;
            double totalRandom = 0.0, totalOrdered = 0.0, totalPartial = 0.0, totalReversed = 0.0;

            for (int rep = 0; rep < repetitions; ++rep)
            {
                vector<int> items(size);

                // Random list
                InitArray(items, size);
                totalRandom += RunSort(sort_name, items);

                // Ordered list
                InitOrderedArray(items, size);
                totalOrdered += RunSort(sort_name, items);

                // Partially ordered list
                InitArrayMid(items, size);
                totalPartial += RunSort(sort_name, items);

                // Reversed list
                InitReversedArray(items, size);
                totalReversed += RunSort(sort_name, items);
            }

            // Averaging times and output
            cout << "Average Random: " << totalRandom / repetitions << " ms" << endl;
            cout << "Average Ordered: " << totalOrdered / repetitions << " ms" << endl;
            cout << "Average Partial: " << totalPartial / repetitions << " ms" << endl;
            cout << "Average Reversed: " << totalReversed / repetitions << " ms" << endl;
            cout << "-----------------------" << endl;
        }
    }
}

double RunSort(const string& sort_name, vector<int>& items)
{
    struct timeval startTime, endTime;
    gettimeofday(&startTime, 0);

    if (sort_name == "BubbleSort")
    {
        BubbleSort(items, 0, items.size() - 1);
    }
    else if (sort_name == "InsertionSort")
    {
        InsertionSort(items, 0, items.size() - 1);
    }
    else if (sort_name == "MergeSort")
    {
        MergeSort(items, 0, items.size() - 1);
    }
    else if (sort_name == "QuickSort")
    {
        QuickSort(items, 0, items.size() - 1);
    }
    else if (sort_name == "ShellSort")
    {
        ShellSort(items, 0, items.size() - 1);
    }

    gettimeofday(&endTime, 0);
    return elapsed(startTime, endTime) / 1000.0; // convert microseconds to milliseconds
}

// Initialize ordered array
void InitOrderedArray(vector<int> &array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = i;
    }
}

// Initialize reversed array
void InitReversedArray(vector<int> &array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = size - i - 1;
    }
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

// Function to calculate elapsed time using gettimeofday
int elapsed(timeval &startTime, timeval &endTime)
{
    return (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
}

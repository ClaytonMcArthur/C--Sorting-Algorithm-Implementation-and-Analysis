#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int>& nums, int left, int mid, int right);
int Partition(vector<int>& nums, int start, int end);

void BubbleSort(vector<int>& nums, int start, int end)
{
    bool notDone = false;

    // Part 1 and 2: Bubble sort with optimization (O(n) if already sorted)
    while (!notDone)
    {
        notDone = true;  // Assume sorted unless we find a swap
        for (int i = start; i < end - 1; i++)
        {  // End-1 to avoid out-of-bounds
            if (nums[i] > nums[i + 1])
            {  // If elements are out of order
                swap(nums[i], nums[i + 1]);
                notDone = false;  // We need another pass if we swapped
            }
        }
    }
}

// Overloaded BubbleSort for Part 3: Sorting only between index1 and index2
void BubbleSort(vector<int>& nums, int start, int end, int index1, int index2)
{
    bool notDone = false;

    // Make sure the range is valid
    if (index1 < start) index1 = start;
    if (index2 > end) index2 = end;

    // Part 1 and 2: Bubble sort with optimization (O(n) if already sorted) between index1 and index2
    while (!notDone) {
        notDone = true;
        for (int i = index1; i < index2 - 1; i++) {  // End-1 to avoid out-of-bounds
            if (nums[i] > nums[i + 1]) {
                swap(nums[i], nums[i + 1]);
                notDone = false;
            }
        }
    }
}

void InsertionSort(vector<int>& nums, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        int v = nums[i];
        int j = i-1;
        while (j >= 0 && nums[j] > v)
        {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = v;
    }
}

void MergeSort(vector<int>& nums, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;

        MergeSort(nums, start, mid);
        MergeSort(nums, mid + 1, end);

        Merge(nums, start, mid, end);
    }

}

void Merge(vector<int>& nums, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = nums[left + i];
    }

    for (int j = 0; j < n2; j++)
    {
        R[j] = nums[mid + 1 + j];
    }

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            nums[k] = L[i];
            i++;
        }
        else
        {
            nums[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        nums[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        nums[k] = R[j];
        j++;
        k++;
    }
}

void QuickSort(vector<int>& nums, int start, int end)
{
    if (start < end)
    {

        int pi = Partition(nums, start, end);

        QuickSort(nums, start, pi - 1);
        QuickSort(nums, pi + 1, end);
    }
}

int Partition(vector<int>& nums, int start, int end)
{
    // Median of three: find the median of the first, middle, and last elements
    int mid = start + (end - start) / 2;

    // Sorting the first, middle, and last elements to find the median
    if (nums[start] > nums[mid])
    {
        swap(nums[start], nums[mid]);
    }
    if (nums[start] > nums[end])
    {
        swap(nums[start], nums[end]);
    }
    if (nums[mid] > nums[end])
    {
        swap(nums[mid], nums[end]);
    }
    // After sorting, the median is now at nums[mid]
    int pivot = nums[mid];

    // Move the pivot to the end for partitioning
    swap(nums[mid], nums[end]);

    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
        if (nums[j] <= pivot)
        {
            i++;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[end]);

    return (i + 1);
}

void ShellSort(vector<int>& nums, int start, int end)
{
    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};

    for (int gap : gaps)
    {
        for (int i = start + gap; i < end; i++)
        {
            int temp = nums[i];
            int j;

            for (j = i; (j >= start + gap) && (nums[j - gap] > temp); j -= gap)
            {
                nums[j] = nums[j - gap];
            }

            nums[j] = temp;
        }
    }
}

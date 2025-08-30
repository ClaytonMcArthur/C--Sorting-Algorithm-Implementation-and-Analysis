# Sorting Benchmarks (C++)

Benchmark and compare classic sorting algorithms across data sizes and input orders.

## Algorithms
- **BubbleSort** with early‑exit optimization and optional in‑range sort (`index1..index2`)
- **InsertionSort**
- **MergeSort**
- **QuickSort** (median‑of‑three pivot)
- **ShellSort** (Sedgewick gap sequence)

## Files
- `SortImpls.cpp` — all sort implementations
- `Sorter.cpp` — single‑run driver with timing and optional printing
- `SorterScript.cpp` — batch runner that averages 3 trials for each case
- `RunTimeMeasurementResults.txt` — sample output (averaged timings)
- `Lab3Report.pdf` — graphs & discussion
- `Lab3.pdf` — assignment prompt

## Build
```bash
g++ -std=c++17 -O2 Sorter.cpp -o Sorter
g++ -std=c++17 -O2 SorterScript.cpp -o SorterScript
```

## Usage
```bash
# Sort once
./Sorter SORT_TYPE ARRAY_SIZE [YES|NO] [INDEX1 INDEX2]

# Examples
./Sorter QuickSort 10000 NO
./Sorter BubbleSort 100 YES 10 30   # only BubbleSort accepts an index range
```

- `SORT_TYPE`: `BubbleSort | InsertionSort | MergeSort | QuickSort | ShellSort`
- `YES|NO`: print the array before/after the run (omit to print by default)

## Batch measurements
Run the full experiment suite and print averaged results for **random**, **ordered**, **partially ordered**, and **reversed** inputs:
```bash
./SorterScript > RunTimeMeasurementResults.txt
```

## Results (summary)
- Bubble/Insertion: **best O(n)** on ordered, **worst O(n²)** on reversed/random.
- Merge/Quick: about **O(n log n)**; Quick uses median‑of‑three to avoid bad pivots.
- Shell: typical **O(n^3/2)** with Sedgewick gaps.
See `Lab3Report.pdf` and `RunTimeMeasurementResults.txt` for data and plots.

## Timing
All timings use `gettimeofday` and report microseconds; the script averages three repetitions per case and size.

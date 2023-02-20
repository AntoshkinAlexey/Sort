#ifndef SORT__SORT_H_
#define SORT__SORT_H_

#include <cstdint>
#include <vector>

class Sort {
public:
    Sort() = delete;

    static void SelectionSort(std::vector<uint32_t>&);
    static void BubbleSort(std::vector<uint32_t>&);
    static void BubbleSortFirstIverson(std::vector<uint32_t>&);
    static void BubbleSortSecondIverson(std::vector<uint32_t>&);
    static void InsertionSort(std::vector<uint32_t>&);
    static void BinaryInsertionSort(std::vector<uint32_t>&);
    static void CountingSort(std::vector<uint32_t>&);
    static void RadixSort(std::vector<uint32_t>&);
    static void MergeSort(std::vector<uint32_t>&);
    static void QuickSort(std::vector<uint32_t>&);
    static void HeapSort(std::vector<uint32_t>&);
    static void ShellSortCiuraSequence(std::vector<uint32_t>&);
    static void ShellSortShellSequence(std::vector<uint32_t>&);
    static bool CheckSorted(const std::vector<uint32_t>&);

    static uint32_t operation_number;

private:
    // Массив для хранения последовательности Циура.
    static const std::vector<uint32_t> kShellDistance;
};

#endif // SORT__SORT_H_

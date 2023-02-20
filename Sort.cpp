#include "Sort.h"
#include <iterator>
#include <cmath>

// Счётчик элементарных операций.
uint32_t Sort::operation_number = 0;

// Последовательность Циура.
const std::vector<uint32_t> Sort::kShellDistance = {3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1};

/// Проверка массива на отсортированность.
/// \param data Массив.
/// \return True, если массив отсортирован по неубыванию. False иначе.
bool Sort::CheckSorted(const std::vector<uint32_t>& data) {
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] < data[i - 1]) {
            return false;
        }
    }
    return true;
}

/// Сортировка выбором.
/// \param data Массив.
void Sort::SelectionSort(std::vector<uint32_t>& data) {
    operation_number += 1;
    for (size_t i = 0; i + 1 < data.size(); ++i, operation_number += 3) {
        // Находим позицию минимального элемента, начиная с индекса i.
        size_t min_index = i;
        operation_number += 3;
        for (size_t j = i + 1; j < data.size(); ++j, operation_number += 2) {
            if (data[j] < data[min_index]) {
                operation_number += 4;
                min_index = j;
            }
        }
        // Ставим минимальный элемент на позицию i.
        operation_number += 1;
        if (min_index != i) {
            operation_number += 3;
            std::swap(data[i], data[min_index]);
        }
    }
}

/// Сортировка пузырьком.
/// \param data Массив.
void Sort::BubbleSort(std::vector<uint32_t>& data) {
    operation_number += 1;
    for (size_t i = 0; i + 1 < data.size(); ++i, operation_number += 3) {
        operation_number += 1;
        for (size_t j = 0; j + i + 1 < data.size(); ++j, operation_number += 4) {
            // Меняем местами соседние элементы, если они идут в неправильном порядке.
            operation_number += 4;
            if (data[j + 1] < data[j]) {
                operation_number += 4;
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

/// Сортировка пузырьком с условием Айверсона 1.
/// \param data Массив.
void Sort::BubbleSortFirstIverson(std::vector<uint32_t>& data) {
    size_t i = 0;
    bool flag = true;
    operation_number += 2;
    // Сортируем, пока происходит хотя бы один свап элементов.
    while (flag) {
        flag = false;
        operation_number += 3;
        for (size_t j = 0; j + i + 1 < data.size(); ++j, operation_number += 4) {
            operation_number += 5;
            if (data[j] > data[j + 1]) {
                operation_number += 5;
                std::swap(data[j], data[j + 1]);
                // Запоминаем, что пара элементов поменялась.
                flag = true;
            }
        }
        operation_number += 1;
        ++i;
    }
}

/// Сортировка пузырьком с условием Айверсона 1+2.
/// \param data Массив.
void Sort::BubbleSortSecondIverson(std::vector<uint32_t>& data) {
    size_t last = data.size();
    // Сортируем, пока происходит хотя бы один свап элементов.
    operation_number += 1;
    while (last != -1) {
        operation_number += 3;
        int new_last = -1;
        for (size_t j = 0; j + 1 < last; ++j, operation_number += 3) {
            operation_number += 4;
            if (data[j] > data[j + 1]) {
                operation_number += 6;
                std::swap(data[j], data[j + 1]);
                // Запоминаем последнюю позицию, на которой поменялись два элемента местами.
                new_last = j + 1;
            }
        }
        operation_number += 1;
        last = new_last;
    }
}

/// Сортировка простыми вставками.
/// \param data Массив.
void Sort::InsertionSort(std::vector<uint32_t>& data) {
    operation_number += 1;
    for (size_t i = 1; i < data.size(); ++i, operation_number += 2) {
        uint32_t temp = data[i];
        size_t j = i;
        operation_number += 3;
        // Ищем позицию для вставки текущего элемента, параллельно сдвигая остальные элементы вправо.
        while (j >= 1 && data[j - 1] > temp) {
            operation_number += 9;
            data[j] = data[j - 1];
            --j;
        }
        operation_number += 2;
        data[j] = temp;
    }
}

/// Сортировка бинарными вставками.
/// \param data Массив.
void Sort::BinaryInsertionSort(std::vector<uint32_t>& data) {
    operation_number += 1;
    for (size_t i = 1; i < data.size(); ++i, operation_number += 2) {
        // Ищем позицию для встваки бинарным поиском.
        operation_number += std::ceil(std::log2(i)) * 7 + 5;
        size_t pos = std::upper_bound(data.begin(), data.begin() + i, data[i]) - data.begin();
        // Делаем сдвиг элементов.
        for (size_t j = i; j > pos; --j, operation_number += 6) {
            std::swap(data[j], data[j - 1]);
        }
    }
}

/// Сортировка подсчётом (устойчивая).
/// \param data Массив.
void Sort::CountingSort(std::vector<uint32_t>& data) {
    operation_number += data.size() * 2;
    std::vector<size_t> count(*std::max_element(data.begin(), data.end()) + 1);
    for (uint32_t i : data) {
        operation_number += data.size() * 3;
        // Подсчитываем элементы.
        ++count[i];
    }
    // Для устойчивости храним сумму на префиксе.
    for (size_t i = 1; i < count.size(); ++i, operation_number += 6) {
        count[i] += count[i - 1];
    }
    operation_number += data.size();
    std::vector<uint32_t> answer(data.size());
    for (int32_t i = data.size() - 1; i >= 0; --i, operation_number += 11) {
        // Ставим элемент в нужную позицию.
        answer[count[data[i]] - 1] = data[i];
        --count[data[i]];
    }
    for (uint32_t i = 0; i < answer.size(); ++i, operation_number += 5) {
        data[i] = answer[i];
    }
}

/// Получение цифры числа, стоящей на позиции pos в системе счисления notation.
/// \param value Число.
/// \param pos Позиция цифры.
/// \param notation Система счисления.
/// \return Цифра.
int32_t GetDigit(int32_t value, int32_t pos, int32_t notation = 32) {
    Sort::operation_number += 6;
    return (((notation - 1) << (pos * 5)) & value) >> (pos * 5);
}

/// Рекурсивный вызов цифровой сортировки.
/// \param data Массив.
/// \param left Левая граница диапазона.
/// \param right Правая граница диапазона.
/// \param pos Номер текущего разряда.
/// \param notation Система счисления.
void DigitSort(std::vector<uint32_t>& data,
               int32_t left,
               int32_t right,
               int32_t pos,
               int32_t notation = 32) {
    Sort::operation_number += 3;
    if (left >= right || pos < 0) {
        return;
    }
    Sort::operation_number += notation;
    std::vector<size_t> count(notation);
    // Подсчитываем цифры, стоящие на разряде pos, всех чисел из диапазона [left, right].
    for (uint32_t i = left; i <= right; ++i, Sort::operation_number += 5) {
        ++count[GetDigit(data[i], pos)];
    }
    for (uint32_t i = 1; i < notation; ++i, Sort::operation_number += 6) {
        count[i] += count[i - 1];
    }
    // Делаем устойчивую сортировку подсчётом.
    std::vector<uint32_t> answer(right - left + 1);
    Sort::operation_number += right - left + 1;
    for (uint32_t i = left; i <= right; ++i, Sort::operation_number += 11) {
        int32_t digit = GetDigit(data[i], pos);
        answer[count[digit] - 1] = data[i];
        --count[digit];
    }
    for (uint32_t i = left; i <= right; ++i, Sort::operation_number += 6) {
        data[i] = answer[i - left];
    }
    // Запускаемся в блоки одинаковых цифр.
    for (int32_t i = 0; i < notation; ++i, Sort::operation_number += 11) {
        DigitSort(data,
                  left + count[i],
                  left + (i + 1 < notation ? count[i + 1] : (right - left + 1)) - 1,
                  pos - 1);
    }
}

/// Цифровая сортировка.
/// \param data Массив.
void Sort::RadixSort(std::vector<uint32_t>& data) {
    operation_number += 1;
    DigitSort(data, 0, data.size() - 1, 3);
}

/// Слияние двух частей массива в одну.
/// \param begin Итератор на начало полуинтервала.
/// \param mid Итератор на середину.
/// \param end Итератор на конец полуинтервала.
void Merge(std::vector<uint32_t>::iterator begin,
           std::vector<uint32_t>::iterator mid,
           std::vector<uint32_t>::iterator end) {
    auto left = begin;
    auto right = mid;
    std::vector<uint32_t> temp(std::distance(begin, end));
    Sort::operation_number += 3 + temp.size();
    size_t top = 0;
    // Слияние двух частей массива в одну с использованием метода двух указателей.
    while (left != mid && right != end) {
        if (*left <= *right) {
            temp[top++] = *left++;
        } else {
            temp[top++] = *right++;
        }
        Sort::operation_number += 11;
    }
    while (left != mid) {
        temp[top++] = *left++;
        Sort::operation_number += 6;
    }
    while (right != end) {
        temp[top++] = *right++;
        Sort::operation_number += 6;
    }

    Sort::operation_number += 2;
    top = 0;
    for (auto it = begin; it != end; ++it, Sort::operation_number += 6) {
        *it = temp[top++];
    }
}

/// Разделение массива на две части.
/// \param begin Итератор на начало полуинтервала.
/// \param end Итератор на конец полуинтервала.
void Split(std::vector<uint32_t>::iterator begin, std::vector<uint32_t>::iterator end) {
    size_t length = std::distance(begin, end);
    Sort::operation_number += length + 2;
    if (length == 1) {
        return;
    }
    auto mid = begin + length / 2;
    Sort::operation_number += 1;
    // Делим массив посередине и запускаемся в обе части.
    Split(begin, mid);
    Split(mid, end);
    // Производим слияние двух частей массива.
    Merge(begin, mid, end);
}

/// Сортировка слиянием.
/// \param data Массив.
void Sort::MergeSort(std::vector<uint32_t>& data) {
    operation_number += 2;
    Split(data.begin(), data.end());
}

/// Рекурсивный запуск быстрой сортировки относительно опроного элемента.
/// \param data Массив.
/// \param first Начало диапазона.
/// \param last Конец диапазона.
void PivotSort(std::vector<uint32_t>& data, int32_t first, int32_t last) {
    Sort::operation_number += 4;
    int32_t i = first, j = last;
    // Опорный элемент.
    uint32_t pivot = data[first];

    // Реализуем сортировку Хоара. Ищем элементы, которые стоят неправильно относительно опорного.
    do {
        while (data[i] < pivot) {
            ++i;
            Sort::operation_number += 2;
        }
        while (data[j] > pivot) {
            --j;
            Sort::operation_number += 2;
        }

        if (i <= j) {
            // Меняем неправильные элементы местами.
            Sort::operation_number += 6;
            if (data[i] > data[j]) {
                std::swap(data[i], data[j]);
                Sort::operation_number += 3;
            }
            ++i;
            --j;
        }
        Sort::operation_number += 1;
    } while (i <= j);

    Sort::operation_number += 2;
    if (i < last) {
        PivotSort(data, i, last);
    }
    if (first < j) {
        PivotSort(data, first, j);
    }
}

/// Быстрая сортировка (первый элемент опорный).
/// \param data Массив.
void Sort::QuickSort(std::vector<uint32_t>& data) {
    Sort::operation_number += 1;
    PivotSort(data, 0, data.size() - 1);
}

/// Проталкивание элемент pos в низ кучи, пока это необходимо.
/// \param data Куча.
/// \param last Конец кучи.
/// \param pos Позиция текущего элемента.
void Heapify(std::vector<uint32_t>& data, uint32_t last, uint32_t pos) {
    uint32_t largest = pos;
    uint32_t left = 2 * pos + 1;
    uint32_t right = 2 * pos + 2;
    Sort::operation_number += 18;
    // Находим максимального потомка.
    if (left < last && data[left] > data[largest]) {
        largest = left;
        Sort::operation_number += 1;
    }
    if (right < last && data[right] > data[largest]) {
        largest = right;
        Sort::operation_number += 1;
    }
    // Меняем потомка с текущим элементом, если это нужно для сохранения свойств кучи.
    if (largest != pos) {
        std::swap(data[pos], data[largest]);
        Sort::operation_number += 3;
        Heapify(data, last, largest);
    }
}

/// Пирамидальная сортировка.
/// \param data Массив.
void Sort::HeapSort(std::vector<uint32_t>& data) {
    // Создание кучи.
    Sort::operation_number += 5;
    for (int32_t i = data.size() / 2 - 1; i >= 0; --i, operation_number += 2) {
        Heapify(data, data.size(), i);
    }

    // Сортировка элементов.
    for (int32_t i = data.size() - 1; i >= 0; --i, operation_number += 5) {
        std::swap(data[0], data[i]);
        Heapify(data, i, 0);
    }
}

/// Сортировка Шелла на последовательности Циура.
/// \param data Массив.
void Sort::ShellSortCiuraSequence(std::vector<uint32_t>& data) {
    // Проходимся по последовательности Циура, выбирая текущую длину.
    operation_number += kShellDistance.size();
    for (const auto len : kShellDistance) {
        for (uint32_t i = len; i < data.size(); ++i, operation_number += 7) {
            uint32_t tmp = data[i];
            uint32_t j = i;
            // Используем цикл из сортировки вставками для элементов, стоящих на расстоянии len.
            for (; j >= len && tmp < data[j - len]; j -= len, operation_number += 7) {
                data[j] = data[j - len];
            }
            data[j] = tmp;
        }
    }
}

/// Сортировка Шелла на последовательности Шелла.
/// \param data Массив.
void Sort::ShellSortShellSequence(std::vector<uint32_t>& data) {
    // Проходимся по последовательности Шелла.
    for (uint32_t len = data.size() / 2; len != 0; len /= 2, operation_number += 2) {
        for (uint32_t i = len; i < data.size(); ++i, operation_number += 7) {
            uint32_t tmp = data[i];
            uint32_t j = i;
            // Используем цикл из сортировки вставками для элементов, стоящих на расстоянии len.
            for (; j >= len && tmp < data[j - len]; j -= len, operation_number += 7) {
                data[j] = data[j - len];
            }
            data[j] = tmp;
        }
    }
}
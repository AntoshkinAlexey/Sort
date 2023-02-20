/*
 * АиСД-2, 2023, задание 5
 * Антошкин Алексей Александрович, БПИ212
 * Clion
 *
 * Сделано:
 * 1) Реализованы все сортировки и все виды генерации массива
 * 2) Используются указатели на функции
 * 3) Есть проверка отсортированности массива
 * 4) Предусмотрена возможность вывода массивов в файл output.txt при добавлении #define DEBUG
 * 5) Есть комментарии в коде
 * 6) Подсчитываются усреднённые за 20 запусков время и количество элементарных операций.
 *
 * Не сделано:
 */

#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "Array.h"
#include "Sort.h"
#include "CSVWriter.h"

#define DEBUG

/// Вывод данных в файл.
/// \param sout Поток вывода в файл.
/// \param data Данные.
/// \param isNew Проверка на то, является ли массив исходным.
void OutputData(std::ofstream& sout, const std::vector<uint32_t>& data, bool isNew = false) {
    if (isNew) {
        sout << "Initial array: ";
    }
    for (const auto element : data) {
        sout << element << ' ';
    }
    sout << "\n\n";
}

/// Точка входа.
/// \return Код завершения программы.
int main() {
#ifdef DEBUG
    // Создаём файл для вывода массивов.
    std::ofstream sout("output.txt");
#endif
    CSVWriter table1, table2;
    table1.newRow() << "Length";
    table2.newRow() << "Length";

    // Создаём вектор названий сортировок.
    std::vector<std::string> sortName = {
        "SelectionSort",
        "BubbleSort",
        "BubbleSortFirstIverson",
        "BubbleSortSecondIverson",
        "InsertionSort",
        "BinaryInsertionSort",
        "CountingSort",
        "RadixSort",
        "MergeSort",
        "QuickSort",
        "HeapSort",
        "ShellSortCiuraSequence",
        "ShellSortShellSequence"
    };

    // Создаём вектор названий типов генерации массива.
    std::vector<std::string> arrayType = {
        "random_5",
        "max_random",
        "almost",
        "reversed",
    };

    // Создаём вектор функций для дальнейшего вызова сортировок.
    std::vector<std::function<void(std::vector<uint32_t>&)>> funcs = {
        Sort::SelectionSort,
        Sort::BubbleSort,
        Sort::BubbleSortFirstIverson,
        Sort::BubbleSortSecondIverson,
        Sort::InsertionSort,
        Sort::BinaryInsertionSort,
        Sort::CountingSort,
        Sort::RadixSort,
        Sort::MergeSort,
        Sort::QuickSort,
        Sort::HeapSort,
        Sort::ShellSortCiuraSequence,
        Sort::ShellSortShellSequence
    };

    // Создаём вектор типов генерации массива для дальнейшей генерации массива определённого вида.
    std::vector<std::function<void(std::vector<uint32_t>&)>> arraysTypes = {
        Array::RandFromZeroToFive,
        Array::RandFromZeroToFourThousand,
        Array::AlmostSorted,
        Array::Reversed,
    };

    // Заполняем .csv файл.
    for (uint32_t sort_number = 0; sort_number < funcs.size(); ++sort_number) {
        for (uint32_t array_number = 0; array_number < arraysTypes.size(); ++array_number) {
            table1 << sortName[sort_number] + " " + arrayType[array_number] + " Time(ns.)";
            table1 << sortName[sort_number] + " " + arrayType[array_number] + " Operations";
            table2 << sortName[sort_number] + " " + arrayType[array_number] + " Time(ns.)";
            table2 << sortName[sort_number] + " " + arrayType[array_number] + " Operations";
        }
    }

    std::vector<std::vector<uint32_t>> arrays;
    for (const auto& array : arraysTypes) {
        std::vector<uint32_t> data;
        // Генерируем массив.
        array(data);
        arrays.emplace_back(data);
#ifdef DEBUG
        // Вывод массива в файл.
        OutputData(sout, data, true);
#endif
    }

    // Создаём два вида проходов по длинам массива.
    std::vector<std::tuple<size_t, size_t, size_t>> ranges = {
        std::make_tuple(50, 300, 50),
        std::make_tuple(100, 4100, 100)
    };
    // Перебираем вид прохода по длинам массива.
    for (const auto& [from, to, step] : ranges) {
        // Перебираем длину массива.
        for (size_t length = from; length <= to; length += step) {
            if (step == 50) {
                table1.newRow() << length;
            } else {
                table2.newRow() << length;
            }
            // Создаём переменную для хранения номера вызываемой сортировки.
            size_t sort_number = 0;
            // Проход по видам сортировок.
            for (const auto& func : funcs) {
                // Увеличиваем номер вызываемой сортировки.
                ++sort_number;
#ifdef DEBUG
                sout << "Sort number: " << sort_number << "\n";
#endif
                // Проход по видам генерации массивов.
                for (auto data : arrays) {
                    uint64_t sum_time = 0;
                    uint64_t sum_operations = 0;
                    // Запускаем сортировку несколько раз, чтобы усреднить время работы.
                    for (size_t num = 0; num < 20; ++num) {
                        // Копируем length элементов в новый вектор.
                        std::vector<uint32_t> data_copy(data.begin(), data.begin() + length);
                        // Обнуляем счётчик элементарных операций.
                        Sort::operation_number = 0;
                        // Старт таймера.
                        auto start = std::chrono::high_resolution_clock::now();
                        // Сортируем массив.
                        func(data_copy);
                        // Остановка таймера.
                        auto elapsed = std::chrono::high_resolution_clock::now() - start;
                        // Суммируем общее время.
                        sum_time +=
                            std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
                        sum_operations += Sort::operation_number;
#ifdef DEBUG
                        // Проверка массива на отсортированность
                        if (Sort::CheckSorted(data_copy)) {
                            sout << "Sorted\n";
                        } else {
                            sout << "Unsorted\n";
                        }
#endif
                    }
                    if (step == 50) {
                        table1 << int64_t(std::round(static_cast<double>(sum_time) / 20));
                        table1 << int64_t(std::round(static_cast<double>(sum_operations) / 20));
                    } else {
                        table2 << int64_t(std::round(static_cast<double>(sum_time) / 20));
                        table2 << int64_t(std::round(static_cast<double>(sum_operations) / 20));
                    }
                }
            }
        }
    }
    table1.writeToFile("212_AntoshkinAlexeyAlexandrovich_table1.csv");
    table2.writeToFile("212_AntoshkinAlexeyAlexandrovich_table2.csv");
#ifdef DEBUG
    // Закрываем файл для записи.
    sout.close();
#endif
    return 0;
}

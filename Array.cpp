#include "Array.h"

// Создаём генератор рандомных чисел.
std::mt19937 Array::random_generator_(std::chrono::steady_clock::now().time_since_epoch().count());

/// Генерация массива с числами от 0 до 5.
/// \param data Массив.
void Array::RandFromZeroToFive(std::vector<uint32_t>& data) {
    for (size_t i = 0; i < kSize; ++i) {
        // Указываем диапазон генерации чисел от 0 до 5.
        std::uniform_int_distribution<int32_t> range(0, 5);
        data.emplace_back(range(random_generator_));
    }
}

/// Генерация массива с числами от 0 до 4000.
/// \param data Массив.
void Array::RandFromZeroToFourThousand(std::vector<uint32_t>& data) {
    for (size_t i = 0; i < kSize; ++i) {
        // Указываем диапазон генерации чисел от 0 до 4000.
        std::uniform_int_distribution<int32_t> range(0, 4000);
        data.emplace_back(range(random_generator_));
    }
}

/// Генерация почти отсортированного массива с числами от 0 до 4000.
/// \param data Массив.
void Array::AlmostSorted(std::vector<uint32_t>& data) {
    for (size_t i = 0; i < kSize; ++i) {
        // Указываем диапазон генерации чисел от 0 до 4000.
        std::uniform_int_distribution<int32_t> range(0, 4000);
        data.emplace_back(range(random_generator_));
    }
    // Сортируем массив.
    std::sort(data.begin(), data.end());
    for (size_t i = 0; i < kSize; i += 1000) {
        // В каждой тысяче элементов меняем 25 рандомных пар.
        for (size_t j = 0; j < 25; ++j) {
            // Указываем возможный диапазон индекса из текущей тысячи.
            std::uniform_int_distribution<int32_t> range(i, std::min(kSize - 1, i + 999));
            // Меняем местами два рандомных элемента.
            std::swap(data[range(random_generator_)], data[range(random_generator_)]);
        }
    }
}

/// Генерация массива с числами от 1 до 4100 отсортированными в порядке невозрастания.
/// \param data Массив.
void Array::Reversed(std::vector<uint32_t>& data) {
    for (size_t i = 0; i < kSize; ++i) {
        // Указываем диапазон генерации чисел от 0 до 4100.
        std::uniform_int_distribution<int32_t> range(1, 4100);
        data.emplace_back(range(random_generator_));
    }
    // Сортируем полученный массив в порядке убывания.
    std::sort(data.rbegin(), data.rend());
}

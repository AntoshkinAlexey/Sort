#ifndef SORT__ARRAY_H_
#define SORT__ARRAY_H_

#include <chrono>
#include <cstdint>
#include <random>
#include <vector>

class Array {
public:
    Array() = delete;
    static void RandFromZeroToFive(std::vector<uint32_t>&);
    static void RandFromZeroToFourThousand(std::vector<uint32_t>&);
    static void AlmostSorted(std::vector<uint32_t>&);
    static void Reversed(std::vector<uint32_t>&);

private:
    // Константный размер массива.
    static const size_t kSize = 4100;
    static std::mt19937 random_generator_;
};

#endif // SORT__ARRAY_H_

#ifndef UTILITY_H
#define UTILITY_H

#include <chrono>

template <typename Func, typename... Args>
double measureTime(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

#endif // UTILITY_H

//
// Created by Vica on 21.03.2024.
//

#ifndef ASDC_FIBONACCI_H
#define ASDC_FIBONACCI_H
#include <iostream>
#include <vector>
#include "../info.h"
int min(int x, int y) { return (x <= y) ? x : y; }

int fibonacciSearch(const std::vector<City>& cities, size_t x, size_t n)
{
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    while (fib > 1) {
        size_t i = min(offset + fib2, n - 1);

        if (cities[i].id < x) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        else if (cities[i].id > x) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        else {
            return i;
        }
    }

    if (fib1 && cities[offset + 1].id == x)
        return offset + 1;

    return -1;
}


#endif //ASDC_FIBONACCI_H

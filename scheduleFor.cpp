//
// Created by 22126 on 2021/10/20.
//

#include <iostream>
#include <omp.h>
#include <chrono>

#define main08 main08
using namespace std;

int f(int num) {

    int sum = 0;
    for (int i = 1; i <= num; ++i) {
        sum += i * i;
    }
    return sum;
}

int main08() {

    int sum = 0;
    auto start = std::chrono::high_resolution_clock::now();

# pragma omp parallel for num_threads(1) default(none) reduction(+:sum) schedule(static, 1)
    for (int i = 0; i < 20000; ++i) {
        sum += f(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::ratio<1, 1>> diff = end - start;
    cout << diff.count();
}
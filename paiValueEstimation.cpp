//
// Created by 22126 on 2021/10/15.
//

#include <iostream>
#include <omp.h>
#include <ctime>

#define main04 main04
using namespace std;

int main04() {
    double factor = 1.0, sum = 0.0;

#pragma omp parallel for num_threads(10) default(none) shared(factor) reduction(+:sum)
    for (int i = 0; i < 10000; ++i) {
        factor = (i % 2 == 0) ? 1.0 : -1.0;
        sum += factor / (2 * i + 1);
    }
    cout << sum * 4;

    return 0;
}
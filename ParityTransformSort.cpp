//
// Created by 22126 on 2021/10/17.
//

#include <iostream>
#include <chrono>

#define main05 main05

using namespace std;

int main05() {

    int N = 100000;
    int *a = new int[N];
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 20;
    }


    auto start = std::chrono::high_resolution_clock::now();
    for (int k = 0; k < N; ++k) {
        int temp, i;
        if (k % 2 == 0)
# pragma omp parallel for num_threads(2) default(none) shared(a, N), private(i, temp)
            for (int i = 1; i < N; i += 2) {
                if (a[i - 1] > a[i]) {
                    temp = a[i];
                    a[i] = a[i - 1];
                    a[i - 1] = temp;
                }
            }
        else
#pragma omp parallel for num_threads(2) default(none) shared(a, N), private(i, temp)
            for (i = 1; i < N - 1; i += 2) {
                if (a[i] > a[i + 1]) {
                    temp = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = temp;
                }
            }

    }

    auto end = std::chrono::high_resolution_clock::now();

    return 0;
}
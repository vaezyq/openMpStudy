//
// Created by 22126 on 2021/10/15.
//

#include <omp.h>
#include <iostream>
#include <ctime>
#include <chrono>


using namespace std;

#define main02 main02

double f(double x) {
    return x * x;
}

int main02() {

    double leftIndex, rightIndex;
    int n;
    cin >> leftIndex >> rightIndex >> n;
    double area = 0;
    double h = (rightIndex - leftIndex) / n;


    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i <= n; ++i) {
        double l = leftIndex + (i - 1) * h;
        double r = leftIndex + i * h;
        area += (f(l) + f(r)) / 2;
    }
    area *= h;
    cout << area;
//    auto end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double, std::ratio<1, 1>> diff = end - start;
//    cout << diff.count();


    cout << "****************" << endl;

    //并行版本

//采用n/len个线程


    auto start1 = std::chrono::high_resolution_clock::now();
    area = 0;
    int len = 100000;
# pragma omp parallel num_threads(n/len) default(none) shared(n, leftIndex, rightIndex, h, len) reduction(+:area)
    {
        int k = omp_get_thread_num();
        double result = 0;
        for (int i = k * len + 1; i <= (k + 1) * len; ++i) {
            double l = leftIndex + (i - 1) * h;
            double r = leftIndex + i * h;
            result += (f(l) + f(r)) / 2;
        }
        area += result;

    }


    area *= h;
    cout << area;
//
//    auto end1 = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double, std::ratio<1, 1>> diff1 = end1 - start1;
//    cout << diff1.count();

    return 0;
}
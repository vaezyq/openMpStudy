//
// Created by 22126 on 2021/10/15.
//

#include <omp.h>
#include <iostream>
#include <ctime>
#include <chrono>


using namespace std;

#define main03 main03

double f1(double x) {
    return x * x;
}

int main03() {

//    串行版本
    double leftIndex, rightIndex;
    int n;
    cin >> leftIndex >> rightIndex >> n;
    double area = 0;
    double h = (rightIndex - leftIndex) / n;


    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i <= n; ++i) {
        double l = leftIndex + (i - 1) * h;
        double r = leftIndex + i * h;
        area += (f1(l) + f1(r)) / 2;
    }
    area *= h;
    cout << area;

    cout << "****************" << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::ratio<1, 1>> diff = end - start;
    cout << diff.count();

    //    使用parallel for的并行版本

    area = 0;

    auto start1 = std::chrono::high_resolution_clock::now();
    double result = 0;
# pragma omp parallel for num_threads(10) default(none) shared(n, leftIndex, h) reduction(+:area)
    for (int i = 1; i <= n; ++i) {
        double l = leftIndex + (i - 1) * h;
        double r = leftIndex + i * h;
        area += (f1(l) + f1(r)) / 2;
    }


    area *= h;
    cout << "using parallel for" << endl;
    cout << area;

    cout << "****************" << endl;
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::ratio<1, 1>> diff1 = end1 - start1;
    cout << diff1.count();

}
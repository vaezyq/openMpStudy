//
// Created by vae on 2022/1/6.
//

#include <iostream>
#include <cmath>
#include <omp.h>
#include <vector>

#define main11 main11

using namespace std;


double f(double x) {
    return pow(x, 2);
}

double integrationCal(double left, double right, int div) {
    double sum = 0;
    double step = (right - left) / static_cast<float>(div);
    sum += (f(left) + f(right)) / 2;
#pragma omp parallel for default(none) shared(div, left, step, sum)
    for (auto i = 1; i < div; ++i) {
        double xIndex = left + step * i;
        double temp = f(xIndex);
#pragma cricital
        {
            sum += temp;
        };
    }
    sum *= step;
    return sum;
}


double integrationCal_v3(double left, double right, int div) {
    double sum = 0;
    double step = (right - left) / static_cast<float>(div);
    sum += (f(left) + f(right)) / 2;
#pragma omp parallel for default(none) shared(div, left, step) reduction(+: sum)
    for (auto i = 1; i < div; ++i) {
        double xIndex = left + step * i;
        sum += f(xIndex);
    }
    sum *= step;
    return sum;
}

void maxVec() {
    vector<int> a{1, 2, 3, 0, 8, 6};
    int maxElem = a[0];

#pragma parallel for reduction(max:maxElem)
    for (auto i = a.begin() + 1; i != a.end(); ++i) {
        if (*i > maxElem) {
            maxElem = *i;
        }
    }

    cout << maxElem;

}


int main11() {

//    cout << integrationCal_v3(0.0, 3.0, 1000);
    maxVec();
//    int n = omp_get_max_threads();
//    cout << n << endl;
//    auto num = 0.0;
//    double left = 0.0, right = 3.0;
//    int step = 1000 / n;
//#pragma omp parallel default(none) shared(right, left, n, num, step)
//    {
//
//        auto id = omp_get_thread_num();
//        double threadLeft = (right - left) * id / n;
//        double threadRight = threadLeft + (right - left) / n;
//#pragma omp critical
//        {
//            num += integrationCal(threadLeft, threadRight, step);
//        };
//    }
//    cout << num;
}
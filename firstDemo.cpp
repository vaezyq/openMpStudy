//
// Created by 22126 on 2021/10/15.
//

#include <iostream>
#include <omp.h>
#include <ctime>




#define main01 main01


using namespace std;

void hello() {
    printf("this is the thread num %d of d \n", omp_get_thread_num(), omp_get_num_threads());
}

int main01() {

    int thread_num = 5;

    clock_t start, stop;
/*  clock_t是clock()函数返回的变量类型  */
    double duration;


    start = clock();
#   pragma omp parallel num_threads(thread_num) default(none) shared(thread_num)
    for (int i = 0; i < thread_num; ++i) {
        if (omp_get_thread_num() == i) {
            hello();
        }
    }
    stop = clock();
    duration = ((double) (stop - start));
    cout << duration << endl;

    cout << "****************" << endl;

    clock_t start1, stop1;
/*  clock_t是clock()函数返回的变量类型  */
    double duration1;


    start1 = clock();
#   pragma omp parallel num_threads(thread_num) default(none) shared(thread_num)
    hello();


    stop1 = clock();
    duration1 = ((double) (stop1 - start1));
    cout << duration1 << endl;


}

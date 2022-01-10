//
// Created by vae on 2022/1/6.
//

#include <iostream>
#include <omp.h>
#include <cstdlib>
// 这两个为什么加了依旧找不到
//#include <QtCore/QThread>


#include <QThread>
//#include <QFuture>
#define main10 main

using namespace std;


class MyThread : public QThread {
private:
    int id;
public:
    MyThread(int id) : id(id) {};

    void run() {
        cout << "1";
    }


};

#define main13 main13

int main13() {
    MyThread t(0);
    t.start();
    t.wait();
    return 0;

    int numThr = 5;
#pragma omp parallel num_threads(numThr) default(none) shared(cout)
    cout << "the thread number is" << " " << omp_get_thread_num();
}

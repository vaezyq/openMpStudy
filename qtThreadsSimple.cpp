//
// Created by vae on 2022/1/9.
//

#include <QThread>
#include <iostream>
#include <vector>

#define main21 main21
using namespace std;


class MyThread : public QThread {
private:
    int id;
public:
    explicit MyThread(int id) : id(id) {};

    void run() override {
        cout << "hello from" << id << endl;
    }
};

int main21() {
    vector<MyThread *> vec;
    int num = 5;
    for (auto i = 0; i < num; ++i) {
        vec.push_back(new MyThread(i));
        vec[i]->start();
    }

    for (auto i = 0; i < num; ++i) {
        vec[i]->wait();
    }

    return 0;
}
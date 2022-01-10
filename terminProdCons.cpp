//
// Created by vae on 2022/1/10.
//

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <iostream>

using namespace std;

const int BUFFSIZE = 100;

template<typename T>
class Producer : public QThread {
private:
    int ID;
    static QSemaphore *slotsAvail;
    static QSemaphore *resAvail;
    static QMutex l1;
    static QSemaphore numProducts;
    static T *buffer;
    static int in;
public:
    static T (*produce)();

    static void initClass(int numP, QSemaphore *s, QSemaphore *a, T *b, T(*prod)());

    explicit Producer<T>(int i) : ID(i) {};

    void run() override;

};

template<typename T> QSemaphore Producer<T>::numProducts;
template<typename T> QSemaphore *Producer<T>::slotsAvail;
template<typename T> QSemaphore *Producer<T>::resAvail;
template<typename T> QMutex Producer<T>::l1;
template<typename T> T *Producer<T>::buffer;
template<typename T> int Producer<T>::in = 0;

template<typename T>
void Producer<T>::initClass(int numP, QSemaphore *s, QSemaphore *a, T *b, T (*prod)()) {
    numProducts.release(numP);
    slotsAvail = s;
    resAvail = a;
    buffer = b;
    produce = prod;
}

template<typename T>
void Producer<T>::run() {
    while (numProducts.tryAcquire()) {
        T item = (*produce)();
        slotsAvail->acquire(); // wait for an empty slot in the buffer
        l1.lock();
        int tmpIn = in;
        in = (in + 1) % BUFFSIZE; // update the in index safely
        l1.unlock();
        buffer[tmpIn] = item; // store the item
        resAvail->release(); // signal resource availability
    }
}


template<>
int (*Producer<int>::produce)() = NULL;

int main() {


}
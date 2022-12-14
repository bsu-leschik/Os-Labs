#ifndef MATRIX_BUFFEREDCHANNEL_H
#define MATRIX_BUFFEREDCHANNEL_H

#include <utility>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <exception>
#include <iostream>

template<class T>
class BufferedChannel {
private:
    std::mutex _locker;
    std::mutex _lockerRcv;
    std::condition_variable _condition;
    std::queue<T> *_container;
    bool closed;
    int _size;

public:
    explicit BufferedChannel(int size) {
        _container = new std::queue<T>();
        _size = size;
        closed = false;
    }

    void Send(T value) {
        if (closed) {
            throw std::runtime_error("channel is closed");
        }
        std::unique_lock lock(_locker);
        _condition.wait(lock, [this](){return this->_container->size() < this->_size;});
        _container->push(value);
        _condition.notify_one();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> lock(_lockerRcv);

        _condition.wait(lock, [this](){return !this->_container->empty() || closed;});

        if (closed && _container->empty()){
            _condition.notify_one();
            return {T(), false};
        }

        auto result = std::pair<T, bool>(_container->front(), true);
        _container->pop();
        _condition.notify_one();

        return result;

    }

    void Close() {
        closed = true;
        _condition.notify_one();
    }

    ~BufferedChannel(){
        delete _container;
    }
};


#endif //MATRIX_BUFFEREDCHANNEL_H

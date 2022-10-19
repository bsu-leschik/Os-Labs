#ifndef MATRIX_BUFFEREDCHANNEL_H
#define MATRIX_BUFFEREDCHANNEL_H

#include <utility>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <exception>

template<class T>
class BufferedChannel {
private:
    std::mutex _locker;
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
        if (closed){
            return {T(), false};
        }

        std::unique_lock<std::mutex> lock(_locker);
        _condition.wait(lock, [this](){return !this->_container->empty();});
        auto result = std::pair<T, bool>(_container->front(), true);
        _container->pop();
        _condition.notify_one();
        return result;

    }

    void Close() {
        closed = true;
    }

    ~BufferedChannel(){
        delete _container;
    }
};


#endif //MATRIX_BUFFEREDCHANNEL_H

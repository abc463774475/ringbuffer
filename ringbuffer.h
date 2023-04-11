//
// Created by hxd on 2023/4/11.
//

#ifndef RINGBUFFER_RINGBUFFER_H
#define RINGBUFFER_RINGBUFFER_H

#include <iostream>
#include <utility>

using namespace std;

template <typename T>
class ringbuffer {
private:
    T *buffer;
    int size;
    int head;
    int tail;
public:
    ringbuffer(int size) {
        this->size = size;
        buffer = new T[size];
        head = 0;
        tail = 0;
    }

    ~ringbuffer() {
        delete[] buffer;
        buffer = nullptr;
    }

    bool push(const T &data) {
        if (is_full()) {
            return false;
        }
        buffer[tail] = data;
        tail = (tail + 1) % size;

        return true;
    }

    // push T *data
    bool push(T *data) {
        if (is_full()) {
            return false;
        }
        buffer[tail] = *data;
        tail = (tail + 1) % size;

        return true;
    }

    // push T &&
    bool push(T &&data) {
        if (is_full()) {
            return false;
        }
        buffer[tail] = std::move(data);
        tail = (tail + 1) % size;

        return true;
    }

    // emplace
    template <typename... Args>
    bool emplace(Args&&... args) {
        if (is_full()) {
            return false;
        }
        buffer[tail] = T(std::forward<Args>(args)...);
        tail = (tail + 1) % size;
        return true;
    }

    bool pop(T &data) {
        if (is_empty()) {
            return false;
        }
        data = buffer[head];
        head = (head + 1) % size;
        return true;
    }

    inline bool is_empty() {
        return tail == head;
    }

    inline bool is_full() {
        return (tail + 1) % size == head;
    }

    inline int get_size() {
        return size;
    }

    inline int get_head() {
        return head;
    }

    inline int get_tail() {
        return tail;
    }
};


#endif //RINGBUFFER_RINGBUFFER_H

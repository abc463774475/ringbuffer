#include <iostream>
#include "ringbuffer.h"
#include <chrono>
#include <thread>

class Test {
private:
    int id = 0;
    int value = 0;
    char data[100];

public:
    Test() {
//        std::cout << "Test()" << std::endl;
    }
    Test(int id, int value) : id(id), value(value) {
//        std::cout << "Test(int id, int value)" << std::endl;
    }

    void display() {
        std::cout << "id: " << id << ", value: " << value << std::endl;
    }
};

// 获取当前时间ms c++
long long get_current_time() {
    // c++ 11
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return millis;
}

ringbuffer<Test> rb(1000000);

const int num = 1000000;

void test_push() {
    auto start = get_current_time();
    auto failed = 0;
    for (int i = 0; i < num; i++) {
        Test t(i, i);
        if (!rb.push(t)) {
            failed++;
        }
    }

    auto end = get_current_time();
    std::cout << "test_push() time: " << end - start << "ms" << std::endl;
    std::cout << "test_push() failed: " << failed << std::endl;
}

void test_pop() {
    auto start = get_current_time();
    auto failed = 0;
    for (int i = 0; i < num; i++) {
        Test t;
        auto bret = rb.pop(t);
        if (!bret) {
            failed++;
        }
    }

    auto end = get_current_time();
    std::cout << "test_pop() time: " << end - start << "ms" << std::endl;
    std::cout << "test_pop() failed: " << failed << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::thread t1(test_push);
    std::thread t2(test_pop);
    t1.join();
    t2.join();

    return 0;
}

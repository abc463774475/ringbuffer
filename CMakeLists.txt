cmake_minimum_required(VERSION 3.22)
project(ringbuffer)

set(CMAKE_CXX_STANDARD 20)

add_executable(ringbuffer main.cpp ringbuffer.cpp ringbuffer.h)

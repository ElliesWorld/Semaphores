#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>
#include <semaphore.h>

class CircularBuffer
{
public:
    CircularBuffer(size_t size);
    ~CircularBuffer();

    void put(int item);
    int get();

private:
    size_t size_;
    std::vector<int> buffer_;
    size_t head_;
    size_t tail_;
    size_t count_;

    sem_t mutex_;
    sem_t empty_slots_;
    sem_t full_slots_;
};

#endif 

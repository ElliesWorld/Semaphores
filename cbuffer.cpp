#include "cbuffer.h"
#include <iostream>

CircularBuffer::CircularBuffer(size_t size)
    : size_(size), buffer_(size), head_(0), tail_(0), count_(0)
{
    sem_init(&mutex_, 0, 1);          // Binary semaphore for mutual exclusion
    sem_init(&empty_slots_, 0, size); // Semaphore to track empty slots
    sem_init(&full_slots_, 0, 0);     // Semaphore to track full slots
}

CircularBuffer::~CircularBuffer()
{
    sem_destroy(&mutex_);
    sem_destroy(&empty_slots_);
    sem_destroy(&full_slots_);
}

void CircularBuffer::put(int item)
{
    sem_wait(&empty_slots_); // Wait for an empty slot
    sem_wait(&mutex_);       // Wait for exclusive access to the buffer

    buffer_[head_] = item;
    head_ = (head_ + 1) % size_;
    count_++;

    sem_post(&mutex_);      // Release exclusive access to the buffer
    sem_post(&full_slots_); // Signal that a new item is available
}

int CircularBuffer::get()
{
    sem_wait(&full_slots_); // Wait for a full slot
    sem_wait(&mutex_);      // Wait for exclusive access to the buffer

    int item = buffer_[tail_];
    buffer_[tail_] = 0; // Optional: Clear the slot for debugging
    tail_ = (tail_ + 1) % size_;
    count_--;

    sem_post(&mutex_);       // Release exclusive access to the buffer
    sem_post(&empty_slots_); // Signal that a new slot is available

    return item;
}

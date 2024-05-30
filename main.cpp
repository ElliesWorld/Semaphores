#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include "cbuffer.h"

void producer(CircularBuffer &buffer)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 100);
    std::uniform_int_distribution<> sleep_dist(100, 500);

    while (true)
    {
        int item = dist(gen);
        std::cout << "Producer produced: " << item << std::endl;
        buffer.put(item);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));
    }
}

void consumer(CircularBuffer &buffer, int id)
{
    std::uniform_int_distribution<> sleep_dist(100, 500);
    std::mt19937 gen(std::random_device{}());

    while (true)
    {
        int item = buffer.get();
        std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_dist(gen)));
    }
}

int main()
{
    const size_t buffer_size = 8;
    CircularBuffer buffer(buffer_size);

    std::thread producer_thread(producer, std::ref(buffer));

    std::vector<std::thread> consumer_threads;
    for (int i = 0; i < 4; ++i)
    {
        consumer_threads.emplace_back(consumer, std::ref(buffer), i + 1);
    }

    producer_thread.join();
    for (auto &thread : consumer_threads)
    {
        thread.join();
    }

    return 0;
}

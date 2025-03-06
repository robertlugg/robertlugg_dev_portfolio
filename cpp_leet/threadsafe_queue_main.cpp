// Demonstrate a threadsafe queue

/*
Compile using:
g++ -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion \
    -Wnull-dereference -Wformat=2 -fsanitize=address,undefined \
    -fstack-protector-strong -std=c++20 -g -Werror threadsafe_queue_main.cpp -o tsq

*/
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include "threadsafe_queue.cpp"

using namespace std::chrono_literals;

struct ParallelEnvironment
{
    std::mutex mtx;
    std::atomic<int16_t> number_submitted{0};
    std::atomic<int16_t> number_received{0};
    ThreadsafeQueue data_queue = ThreadsafeQueue();
    std::atomic<int> data_in_queue{0};
    std::atomic<bool> consumers_should_stop{false};
    std::condition_variable cv_data_available;

public:
    ParallelEnvironment() {};
};

void producer(ParallelEnvironment &penv, const std::string &word1, const std::string &word2, const int count)
{
    for (int i = 0; i < count; ++i)
    {
        std::this_thread::sleep_for(100ms);
        print({word1, word2}, "Producing: ");
        penv.data_queue.incoming({word1, word2});
        penv.number_submitted++;
        penv.data_in_queue++;
        penv.cv_data_available.notify_one();
    }
}

void consumer(ParallelEnvironment &penv)
{
    std::unique_lock<std::mutex> lock(penv.mtx);
    while (true)
    {
        std::cout << std::boolalpha << penv.consumers_should_stop << ": " << penv.data_queue.queue.size() << std::endl;
        lock.lock();
        penv.cv_data_available.wait(lock, [&]()
                                    { return !penv.data_queue.queue.empty() || penv.consumers_should_stop.load(); });
        std::cout << "locked" << std::endl;
        if (penv.data_queue.queue.empty() && penv.consumers_should_stop) {
            break;
        }
        auto &todo = penv.data_queue.outgoing();
        lock.unlock();
        print(todo, "Consuming: ");
        // work being done here
        penv.number_received++;
        penv.data_in_queue--;
        std::this_thread::sleep_for(100ms);
    }
}

int main()
{

    ParallelEnvironment penv{};

    std::vector<std::jthread> producer_threads;
    for (int i = 0; i < 1; ++i)
    {
        std::string w1, w2;
        w1 = "CHello";
        w2 = "There";
        producer_threads.push_back(std::jthread(producer, std::ref(penv), w1, w2, 5));
    }

    std::this_thread::sleep_for(2000ms);
    std::vector<std::jthread> consumer_threads;
    for (int i = 0; i < 1; ++i)
    {
        consumer_threads.push_back(std::jthread(consumer, std::ref(penv)));
    }

    // Wait for all producers to exit, then signal consumers to exit
    for (auto &t : producer_threads)
    {
        t.join();
    }
    std::cout << "Producers Done" << std::endl;
    std::this_thread::sleep_for(3000ms);

    penv.consumers_should_stop.store(true);  // Signal consumers to stop after queue is empty
    for (auto &t : consumer_threads)
    {
        t.join();
    }
    std::cout << "Done" << std::endl;

    return 0;
}
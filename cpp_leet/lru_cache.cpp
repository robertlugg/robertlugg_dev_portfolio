/*
Problem: Implement an LRU Cache
Design and implement a Least Recently Used (LRU) cache with the following requirements:

Class Definition:

class LRUCache {
public:
    LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);
};
Constraints:
get(int key): If the key exists in the cache, return its value. Otherwise, return -1.
put(int key, int value): Insert or update the key-value pair. If the cache reaches its capacity,
evict the least recently used item before inserting a new one.
Must run in O(1) time complexity for both get and put.
Hints:
    You will likely need a hash map for fast lookups and a doubly linked list to maintain the usage order.
    The least recently used item should always be removed in O(1) time.
Follow-up Questions:
    How would you modify this for a thread-safe implementation?
    Could you extend this to support multi-level caching?

*/
#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

class LRUCache {
    size_t capacity = 0;
    std::list<int> cache_list{};
    std::unordered_map<int, std::pair<std::list<int>::iterator, int>> cache_map;
public:
    void print() {
        std::cout << "[]";
        for(auto& item: cache_list) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        std::cout << "{}";
        for(auto& item: cache_map) {
            std::cout << item.second.second << " ";
        }
        std::cout << std::endl;
    }
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    int get(int key) {
        if (!cache_map.contains(key)) { return -1; }
        auto& value = cache_map[key];
        auto& list_iter = value.first;
        cache_list.splice(cache_list.end(), cache_list, list_iter);
        return value.second;
    };
    void put(int key, int value) {
        cache_list.push_back(key);
        auto back_ptr = std::prev(cache_list.end());
        cache_map[key] = {back_ptr, value};
        if (cache_map.size() > capacity) {
            auto key_from_list = cache_list.front();
            cache_list.pop_front();
            cache_map.erase(key_from_list);
        }
    }
};

int main() {
    LRUCache cache(3);
    cache.put(1, 301);
    cache.print();
    cache.put(2, 302);
    cache.print();
    cache.put(4, 304);
    cache.print();
    cache.put(9, 309);
    cache.print();

    std::cout << cache.get(4) << "\n"; // should be 304
    cache.print();
    std::cout << cache.get(999) << "\n"; // SHould be -1 since not in cache
    cache.print();
    std::cout << cache.get(1) << "\n"; // Should be -1 since it was oldest in cache.
    cache.print();
    std::cout << cache.get(2) << "\n"; // Should be 302.
    cache.print();
    cache.put(7, 307);
    cache.print();
    std::cout << cache.get(7) << "\n"; // Should be 307.
    cache.print();
    std::cout << cache.get(2) << "\n"; // Should be 302 since it was read before, so no longer
    cache.print();
                                        // the first item on the stack.
    cache.put(8, 308);
    cache.print();
    cache.put(9, 309);
    cache.print();
    std::cout << cache.get(7) << "\n"; // Should be -1.
    cache.print();
    std::cout << cache.get(2) << "\n"; // Should be still 302
    cache.print();

}
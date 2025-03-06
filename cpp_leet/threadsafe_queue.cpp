#include <iostream>
#include <string>
#include <deque>

using WordSet = std::pair<std::string, std::string>;
void print(const WordSet& ws, const std::string prefix_string="WordSet = ") {
    auto& [v1, v2] = ws;
    std::cout << prefix_string << v1 << "," << v2 << std::endl;
}

class ThreadsafeQueue {


public:
    std::deque<WordSet> queue; //Allow access for now but clean up later
    
    bool incoming(WordSet&& input) {
        queue.push_back(std::move(input));
        return true;
    }

    WordSet& outgoing() {
        if (queue.size()) {
            auto& front_value = queue.front();
            std::cout << front_value.first << std::endl;
            queue.pop_front();
            return front_value;
        }
        return queue.front();
    }
    
    std::size_t size() {
        return queue.size();
    }

};

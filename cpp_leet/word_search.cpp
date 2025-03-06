#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <unordered_set>
#include <deque>
#include <cstring>

constexpr int ROWS = 20;
constexpr int COLS = 20;
constexpr const char* WORD = "word";

// Generate board at runtime
std::vector<std::vector<char>> generate_board() {
    std::vector<std::vector<char>> board(ROWS, std::vector<char>(COLS));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis('a', 'z');
    
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            board[i][j] = dis(gen);
        }
    }
    
    // Insert the word horizontally at a random position
    int start_row = gen() % ROWS;
    int start_col = gen() % (COLS - strlen(WORD));
    
    for (size_t i = 0; i < strlen(WORD); ++i) {
        board[start_row][start_col + i] = WORD[i];
    }
    
    return board;
}

void print_board(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (char c : row) {
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Base class for word search variants
class WordSearchBase {
public:
    virtual bool exist(const std::vector<std::vector<char>>& board, std::string word) = 0;
    virtual ~WordSearchBase() = default;
};

// Basic DFS Implementation
class WordSearchBasic : public WordSearchBase {
public:
    bool exist(const std::vector<std::vector<char>>& board, std::string word) override {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }
protected:
    virtual bool dfs(const std::vector<std::vector<char>>& board, std::string &word, int i, int j, int index) {
        if (index == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index])
            return false;
        return dfs(board, word, i + 1, j, index + 1) ||
               dfs(board, word, i - 1, j, index + 1) ||
               dfs(board, word, i, j + 1, index + 1) ||
               dfs(board, word, i, j - 1, index + 1);
    }
};

// Optimized DFS with pruning
class WordSearchOptimized : public WordSearchBasic {
protected:
    bool dfs(std::vector<std::vector<char>>& board, std::string &word, int i, int j, int index) override {
        if (index == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index])
            return false;
        char temp = board[i][j];
        board[i][j] = '#'; // Mark visited
        bool found = dfs(board, word, i + 1, j, index + 1) ||
                     dfs(board, word, i - 1, j, index + 1) ||
                     dfs(board, word, i, j + 1, index + 1) ||
                     dfs(board, word, i, j - 1, index + 1);
        board[i][j] = temp; // Unmark
        return found;
    }
};

int main() {
    auto board = generate_board();
    print_board(board);
    
    std::vector<WordSearchBase*> solvers = { new WordSearchBasic(), new WordSearchOptimized() };
    std::vector<std::string> solver_names = { "Basic DFS", "Optimized DFS" };
    
    for (size_t i = 0; i < solvers.size(); i++) {
        auto start = std::chrono::high_resolution_clock::now();
        bool found = solvers[i]->exist(board, WORD);
        auto end = std::chrono::high_resolution_clock::now();
        
        std::cout << solver_names[i] << ": " << (found ? "Yes" : "No") << '\n';
        std::cout << "Execution Time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
    }
    
    for (WordSearchBase* solver : solvers)
        delete solver;
    
    return 0;
}

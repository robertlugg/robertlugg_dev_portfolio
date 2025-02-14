#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> grades = {94, 89, 72, 96};
    grades.back() = 70;
    grades.push_back(89);
    for (auto iter=grades.begin(); iter != grades.end(); ++iter) {
        cout << *iter << endl;
    }
    cout << flush;
    return 0;
}

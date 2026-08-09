#include <functional>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    int add_num, get_num;
    std::cin >> add_num >> get_num;

    std::vector<int> add_commands(add_num + 1);
    for (int i = 1; i <= add_num; i++) {
        std::cin >> add_commands[i];
    }

    std::vector<int> get_commands(get_num + 1);
    for (int i = 1; i <= get_num; i++) {
        std::cin >> get_commands[i];
    }

    std::priority_queue<int> left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right;

    int get_index = 1;
    for (int i = 1; i <= add_num; i++) {
        left.push(add_commands[i]);
        right.push(left.top());
        left.pop();

        while (get_index <= get_num && get_commands[get_index] == i) {
            left.push(right.top());
            right.pop();
            std::cout << left.top() << '\n';
            get_index++;
        }
    }

    return 0;
}

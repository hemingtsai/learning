#include <iostream>
#include <string>
#include <vector>

int lowbit(int i) {
    return i & -i;
}

int sum(const std::vector<int>& object, int index) {
    int result = 0;
    while (index > 0) {
        result += object[index];
        index -= lowbit(index);
    }
    return result;
}

void add(std::vector<int>& object, int index, int value) {
    while (index < object.size()) {
        object[index] += value;
        index += lowbit(index);
    }
}

void init_tree_array(const std::vector<int>& raw, std::vector<int>& tree_array) {
    for (int i = 1; i < raw.size(); ++i) {
        add(tree_array, i, raw[i]);
    }
}

enum Command {
    SUM = 0,
    ADD = 1
};

std::string do_command(std::vector<int>& object, Command cmd, int param1, int param2) {
    switch (cmd) {
        case Command::SUM:
            return std::to_string(sum(object, param2) - sum(object, param1 - 1));
        case Command::ADD:
            add(object, param1, param2);
            return "";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int N, M;
    std::cin >> N >> M;
    std::vector<int> raw(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        std::cin >> raw[i];
    }
    std::vector<int> tree_array(N + 1, 0);
    init_tree_array(raw, tree_array);

    while (M--) {
        int operate, param1, param2;
        std::cin >> operate >> param1 >> param2;
        std::string result = do_command(tree_array, static_cast<Command>(operate), param1, param2);
        if (!result.empty()) {
            std::cout << result << '\n';
        }
    }
}

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

int lowbit(int i) {
    return i & -i;
}

int sum(const std::vector<uint64_t>& object, int index) {
    uint64_t result = 0;
    while (index > 0) {
        result += object[index];
        index -= lowbit(index);
    }
    return result;
}

void add(std::vector<uint64_t>& object, int index, int value) {
    while (index < object.size()) {
        object[index] += value;
        index += lowbit(index);
    }
}

void del(std::vector<uint64_t>& object, int index, int value){
    while (index < object.size()) {
        object[index] -= value;
        index += lowbit(index);
    }
}

void init_tree_array(const std::vector<uint64_t>& raw, std::vector<uint64_t>& tree_array) {
    for (int i = 1; i < raw.size(); ++i) {
        add(tree_array, i, raw[i]);
    }
}

enum Command {
    SUM = 'A',
    ADD = 'B',
    DEL = 'C'
};

std::string do_command(std::vector<uint64_t>& object, Command cmd, int param1, int param2) {
    switch (cmd) {
        case Command::SUM:
            return std::to_string(sum(object, param2) - sum(object, param1 - 1));
        case Command::ADD:
            add(object, param1, param2);
            return "";
        case Command::DEL:
            del(object, param1, param2);
            return "";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int N, M;
    std::cin >> N >> M;
    std::vector<uint64_t> tree_array(N + 1, 0);

    while (M--) {
        char operate;
        int param1, param2;
        std::cin >> operate;
        if(operate == Command::SUM){
            std::cin >> param2;
            param1 = 1;
        }else{
            std::cin >> param1>>param2;
        }
        std::string result = do_command(tree_array, static_cast<Command>(operate), param1, param2);
        if (!result.empty()) {
            std::cout << result << '\n';
        }
    }
}

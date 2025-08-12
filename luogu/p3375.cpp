#include <iostream>
#include <string>
#include <vector>

std::vector<int> get_next_array(const std::string &t) {
    int m = t.size();
    std::vector<int> next(m, 0);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && t[i] != t[j]) j = next[j - 1];
        if (t[i] == t[j]) j++;
        next[i] = j;
    }
    return next;
}

std::vector<int> KMP(const std::string &str, const std::string &target,
                     const std::vector<int> &next) {
    std::vector<int> result;
    int n = str.size(), m = target.size();
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && str[i] != target[j]) j = next[j - 1];
        if (str[i] == target[j]) j++;
        if (j == m) {
            result.push_back(i - m + 2); // 1-based
            j = next[j - 1];
        }
    }
    return result;
}

int main() {
    std::string str, target;
    std::cin >> str;
    std::cin >> target;

    auto next = get_next_array(target);
    auto result = KMP(str, target, next);

    for (auto v : result) {
        std::cout << v << "\n";
    }

    for (int i = 0; i < (int)next.size(); i++) {
        std::cout << next[i] << (i + 1 < (int)next.size() ? ' ' : '\n');
    }
}

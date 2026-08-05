#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct DancingPair {
    int diff;
    int i, j;
    bool operator>(const DancingPair& other) const {
        if (diff != other.diff) return diff > other.diff;
        return i > other.i;
    }
};

struct Dancer {
    bool is_male;
    int skill;
};

int main() {
    int n;
    std::cin >> n;

    std::string genders;
    std::cin >> genders;

    std::vector<Dancer> dancers(n + 1);
    for (int i = 1; i <= n; i++) {
        dancers[i].is_male = (genders[i - 1] == 'B');
        std::cin >> dancers[i].skill;
    }

    std::vector<int> prev(n + 2), next(n + 2);
    for (int i = 1; i <= n; i++) {
        prev[i] = i - 1;
        next[i] = i + 1;
    }

    std::priority_queue<DancingPair, std::vector<DancingPair>, std::greater<DancingPair>> pq;
    for (int i = 1; i < n; i++) {
        if (dancers[i].is_male != dancers[i + 1].is_male) {
            pq.push({std::abs(dancers[i].skill - dancers[i + 1].skill), i, i + 1});
        }
    }

    std::vector<bool> removed(n + 1, false);
    std::vector<std::pair<int, int>> answers;

    while (!pq.empty()) {
        DancingPair cur = pq.top();
        pq.pop();

        // 跳过已移除的舞者
        if (removed[cur.i] || removed[cur.j]) continue;

        answers.push_back({cur.i, cur.j});
        removed[cur.i] = removed[cur.j] = true;

        // 连接左右邻居：... l → (i, j 移除) → r ...
        int l = prev[cur.i];
        int r = next[cur.j];
        next[l] = r;
        prev[r] = l;

        // 新相邻的两人能否配对
        if (l >= 1 && r <= n && dancers[l].is_male != dancers[r].is_male) {
            pq.push({std::abs(dancers[l].skill - dancers[r].skill), l, r});
        }
    }

    std::cout << answers.size() << '\n';
    for (auto& p : answers) {
        std::cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}

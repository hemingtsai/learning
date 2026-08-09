#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

std::vector<int> graph[MAXN];   // 正向图
std::vector<int> reversed_graph[MAXN];  // 反向图
int price[MAXN];
int min_price[MAXN];  // 从 1 出发到 i 的路径上的最小价格
int max_price[MAXN];  // 从 i 出发到 n 的路径上的最大价格
bool is_in_queue[MAXN];

int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        std::cin >> price[i];
    }

    for (int i = 0; i < m; i++) {
        int x, y, z;
        std::cin >> x >> y >> z;
        graph[x].push_back(y);
        reversed_graph[y].push_back(x);
        if (z == 2) {  // 双向边
            graph[y].push_back(x);
            reversed_graph[x].push_back(y);
        }
    }

    // 正向 BFS：从 1 出发，求到每个点的路径上的最小价格
    std::memset(min_price, 0x3f, sizeof(min_price));
    std::queue<int> q;
    q.push(1);
    min_price[1] = price[1];
    is_in_queue[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        is_in_queue[u] = false;

        for (int current : graph[u]) {
            int next_min_value = std::min(min_price[u], price[current]);
            if (next_min_value < min_price[current]) {
                min_price[current] = next_min_value;
                if (!is_in_queue[current]) {
                    q.push(current);
                    is_in_queue[current] = true;
                }
            }
        }
    }

    // 反向 BFS：从 n 出发（在反向图上），求每个点到 n 的路径上的最大价格
    std::memset(max_price, 0, sizeof(max_price));
    q.push(n);
    max_price[n] = price[n];
    is_in_queue[n] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        is_in_queue[u] = false;

        for (int current : reversed_graph[u]) {
            int next_max_value = std::max(max_price[u], price[current]);
            if (next_max_value > max_price[current]) {
                max_price[current] = next_max_value;
                if (!is_in_queue[current]) {
                    q.push(current);
                    is_in_queue[current] = true;
                }
            }
        }
    }

    // 枚举中间点 i，计算最大差价
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, max_price[i] - min_price[i]);
    }
    std::cout << ans << '\n';

    return 0;
}

#include <algorithm>
#include <iostream>

const int MAXN = 5005;
const int MAXM = 2e5 + 5;

struct Edge {
    int u, v, w;
} edges[MAXM];

int parent[MAXN];
int N, M;

int find(int x) {
    while (parent[x] != x)
        x = parent[x] = parent[parent[x]];
    return x;
}

void merge(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> N >> M;
    for (int i = 0; i < M; i++) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    std::sort(edges, edges + M, [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    for (int i = 1; i <= N; i++)
        parent[i] = i;

    int total = 0, edge_count = 0;
    for (int i = 0; i < M && edge_count < N - 1; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            merge(edges[i].u, edges[i].v);
            total += edges[i].w;
            edge_count++;
        }
    }

    if (edge_count == N - 1)
        std::cout << total << '\n';
    else
        std::cout << "orz\n";

    return 0;
}

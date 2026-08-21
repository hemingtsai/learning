#include <algorithm>
#include <iostream>

const int MAXN = 505;
const int MAXM = 125255;

struct Edge {
    int u, v, w;
} edges[MAXM];

int parent[MAXN];
int A, B;

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

    std::cin >> A >> B;

    int edge_count = 0;
    for (int i = 1; i <= B; i++) {
        edges[edge_count++] = {0, i, A};
    }
    for (int i = 1; i <= B; i++) {
        for (int j = 1; j <= B; j++) {
            int k;
            std::cin >> k;
            if (i < j && k > 0) {
                edges[edge_count++] = {i, j, k};
            }
        }
    }

    std::sort(edges, edges + edge_count, [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    int N = B + 1;
    for (int i = 0; i < N; i++)
        parent[i] = i;

    int total = 0, used = 0;
    for (int i = 0; i < edge_count && used < N - 1; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            merge(edges[i].u, edges[i].v);
            total += edges[i].w;
            used++;
        }
    }

    std::cout << total << '\n';

    return 0;
}

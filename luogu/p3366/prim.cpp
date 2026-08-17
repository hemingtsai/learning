#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

struct Edge {
    int to;
    int weight;
};
typedef std::vector<std::vector<Edge>> Graph;

int N, M;
Graph g;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> N >> M;

    g = std::vector<std::vector<Edge>>(N + 1, std::vector<Edge>());
    for(int i=0;i<M;i++){
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    std::vector<bool> visited(N + 1, false);
    std::vector<int> min_dist(N + 1, INT_MAX);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;

    min_dist[1] = 0;
    pq.push({0, 1});

    int total = 0, count = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        total += d;
        count++;

        for (const Edge& e : g[u]) {
            if (!visited[e.to] && e.weight < min_dist[e.to]) {
                min_dist[e.to] = e.weight;
                pq.push({e.weight, e.to});
            }
        }
    }

    if (count == N)
        std::cout << total << '\n';
    else
        std::cout << "orz\n";

    return 0;
}

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

int N;
Graph g;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> N;

    g = std::vector<std::vector<Edge>>(N + 1);
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            int w;
            std::cin >> w;
            if(i < j && w > 0){
                g[i].push_back({j,w});
                g[j].push_back({i,w});
            }
        }
    }

    std::vector<bool> visited(N + 1, false);
    std::vector<int> min_dist(N + 1, INT_MAX);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;

    min_dist[1] = 0;
    pq.push({0, 1});

    int total = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        total += d;

        for (const Edge& e : g[u]) {
            if (!visited[e.to] && e.weight < min_dist[e.to]) {
                min_dist[e.to] = e.weight;
                pq.push({e.weight, e.to});
            }
        }
    }

    std::cout << total << '\n';

    return 0;
}

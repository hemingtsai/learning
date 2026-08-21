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

int A, B;
Graph g;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> A >> B;

    int N = B + 1;
    g = std::vector<std::vector<Edge>>(N, std::vector<Edge>());
    for(int i=1;i<=B;i++){
        g[0].push_back({i,A});
        g[i].push_back({0,A});
    }
    for(int i=1;i<=B;i++){
        for(int j=1;j<=B;j++){
            int k;
            std::cin >> k;
            if(i < j && k > 0){
                g[i].push_back({j,k});
                g[j].push_back({i,k});
            }
        }
    }

    std::vector<bool> visited(N, false);
    std::vector<int> min_dist(N, INT_MAX);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;

    min_dist[0] = 0;
    pq.push({0, 0});

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

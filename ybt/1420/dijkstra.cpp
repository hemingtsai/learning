#include <queue>
#include <vector>
#include <cstdio>

const long long inf = 9223372036854775000;

struct Node {
    long long u;
    long long v;

    bool operator<(const Node &b) const{
        return v>b.v;
    }
};

std::vector<long long> dijkstra(std::vector<std::vector<Node>> Graph, long long n){
    std::vector<long long> dist(n+1,inf);
    dist[1] = 0;

    std::vector<bool> visited(n+1,false);

    std::priority_queue<Node> q;

    Node d = {1,0};
    q.push(d);
    while(!q.empty()){
        Node cur = q.top();
        q.pop();

        if(visited[cur.u])
            continue;
        visited[cur.u] = true;

        for(long long i=0;i<Graph[cur.u].size();i++){
            if(dist[Graph[cur.u][i].u] > dist[cur.u] + Graph[cur.u][i].v){
                dist[Graph[cur.u][i].u] = dist[cur.u] + Graph[cur.u][i].v;
                Node tmp = {Graph[cur.u][i].u, dist[Graph[cur.u][i].u] };
                q.push(tmp);
            }
        }
    }

    return dist;
}

int main(){
    long long n,m;
    std::scanf("%lld%lld",&n,&m);

    std::vector<std::vector<Node>> Graph(n+1);

    for(long long i=0;i<m;i++){
        long long a,b,c;
        std::scanf("%lld%lld%lld",&a,&b,&c);
        Graph[a].push_back({b,c});
        Graph[b].push_back({a,c});
    }

    long long res = dijkstra(Graph, n)[n];

    std::printf("%lld",res);

    return 0;
}

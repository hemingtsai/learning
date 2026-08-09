#include <queue>
#include <vector>
#include <cstdio>

const int inf = 0x3f3f3f3f;

struct Node {
    int u;
    int v;

    bool operator<(const Node &b) const{
        return v>b.v;
    }
};

std::vector<int> dijkstra(std::vector<std::vector<Node>> Graph, int n, int start){
    std::vector<int> dist(n+1,inf);
    dist[start] = 0;

    std::vector<bool> visited(n+1,false);

    std::priority_queue<Node> q;

    Node d = {start,0};
    q.push(d);
    while(!q.empty()){
        Node cur = q.top();
        q.pop();

        if(visited[cur.u])
            continue;
        visited[cur.u] = true;

        for(int i=0;i<Graph[cur.u].size();i++){
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
    int n,m,start;
    std::scanf("%d%d%d",&n,&m,&start);

    std::vector<std::vector<Node>> Graph(n+1);

    for(int i=0;i<m;i++){
        int a,b,c;
        std::scanf("%d%d%d",&a,&b,&c);
        Node d{b,c};
        Graph[a].push_back(d);
    }

    auto res = dijkstra(Graph, n, start);

    for(int i=1;i<=n;i++){
        std::printf("%d ",res[i]);
    }
    std::printf("\n");

    return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

const int inf = 0x3f3f3f3f;

std::vector<std::vector<int>> floyd(std::vector<std::vector<int>> dist){
    for(int k=0;k<dist.size();k++){
        for(int i=0;i<dist.size();i++){
            for(int j=0;j<dist.size();j++){
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

void print(std::vector<std::vector<int>> dist){
    for(auto v:dist){
        for(auto i:v){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> Graph(n, std::vector<int>(n,inf));
    for(int _=0;_<m;_++){
        int u,v,w;
        std::cin >> u >> v >> w;
        Graph[u][v] = std::min(Graph[u][v],w);
    }
    auto dist = floyd(Graph);
    print(dist);
    {
        int u, v;
        std::cin >> u >> v;
        std::cout << dist[u][v] << std::endl;
    }
    return 0;
}

/*
Test in:
4 8
0 1 1
0 3 4
1 2 9
1 3 2
2 0 3
2 1 5
2 3 8
3 2 6
0 2
*/

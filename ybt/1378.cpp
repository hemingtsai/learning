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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::string s;
            std::cin >> s;
            if (s != "-") {
                Graph[i][j] = std::stoi(s);
            }
        }
    }
    auto dist = floyd(Graph);
    for(int i=0;i<n;i++){
        if(dist[m-1][i] != inf && dist[m-1][i] != 0)
            std::printf("(%d -> %d) = %d\n",m,i+1,dist[m-1][i]);
    }
    return 0;
}

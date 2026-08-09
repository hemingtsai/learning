#include <iostream>
#include <vector>

int main(){
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> rect(N+1,std::vector<int>(N+1,0));
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            std::cin >> rect[i][j];
            rect[i][j] += rect[i-1][j] + rect[i][j-1] - rect[i-1][j-1];
        }
    }

    int max_rect = 0;
    for(int x1=1;x1<=N;x1++){
        for(int y1=1;y1<=N;y1++){
            for(int x2=x1;x2<=N;x2++){
                for(int y2=y1;y2<=N;y2++){
                    int area = rect[x2][y2] - rect[x1-1][y2] - rect[x2][y1-1] + rect[x1-1][y1-1];
                    if(area > max_rect) max_rect = area;
                }
            }
        }
    }

    std::cout << max_rect << std::endl;
}
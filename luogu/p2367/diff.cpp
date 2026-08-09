// P2367 语文成绩
// 链接：https://www.luogu.com.cn/problem/P2367
// 差分算法实现

#include <iostream>
#include <vector>

int main(){
    int n,m;
    std::cin >> n >> m;
    std::vector<int> score(n+1,0);

    for(int i=1;i<=n;i++){
        std::cin >> score[i];
    }

    std::vector<int> diff(n+2,0);
    for (int i=1; i<=n; i++) {
        diff[i] = score[i] - score[i-1];
    }

    for(int i=0;i<m;i++){
        int l,r,c;
        std::cin >> l >> r >> c;
        diff[l] += c;
        diff[r+1] -= c;
    }

    int min = 6e5;
    for (int i=1; i<=n; i++) {
        score[i] = score[i-1] + diff[i];
        if (score[i] < min) {
            min = score[i];
        }
    }

    std::cout << min << std::endl;
}
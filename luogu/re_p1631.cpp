#include <functional>
#include <iostream>
#include <queue>
#include <vector>

struct ResultValue {
    int sum;
    int i;
    int j;
    bool operator>(const ResultValue& other) const { return sum > other.sum; }
};

int main(){
    std::priority_queue<ResultValue, std::vector<ResultValue>, std::greater<ResultValue>> pq;

    int N;
    std::cin >> N;

    std::vector<int> list_a(N);
    for(auto &v:list_a){
        std::cin >> v;
    }

    std::vector<int> list_b(N);
    for(auto &v:list_b){
        std::cin >> v;
    }

    for(int i = 0; i < N; i++){
        pq.push({list_a[i] + list_b[0], i, 0});
    }
    
    for(int k = 0; k < N; k++){
        ResultValue cur = pq.top();
        pq.pop();
        std::cout << cur.sum;
        if(k != N - 1) std::cout << " ";

        if(cur.j + 1 < N){
            pq.push({list_a[cur.i] + list_b[cur.j + 1], cur.i, cur.j + 1});
        }
    }
    return 0;
}

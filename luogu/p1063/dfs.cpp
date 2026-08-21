#include <iostream>
#include <vector>

bool is_prime(int a) {
  if (a < 2) return 0;
  for (int i = 2; i * i <= a; ++i)
    if (a % i == 0) return 0;
  return 1;
}

int dfs(const std::vector<int> &numbers, int start, int step, int k, int sum){
    if(step == k){
        return is_prime(sum);
    }

    int answer = 0;
    for(int i=start;i<numbers.size();i++){
        answer += dfs(numbers, i+1, step+1, k, sum+numbers[i]);
    }

    return answer;
}

int main(){
    int n, k;
    std::cin >> n >> k;
    std::vector<int> numbers(n);
    for(auto &v:numbers){
        std::cin >> v;
    }
    std::cout << dfs(numbers, 0, 0, k, 0) << std::endl;
}

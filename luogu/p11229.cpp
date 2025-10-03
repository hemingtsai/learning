#include <bits/stdc++.h>
#include <cstddef>
#include <string>

// 每个数字需要的木棍数
int stick[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

std::string work(int n, bool is_first_number = true){
    if(n<=2){
        return "";
    }
    std::string result = "0";

    for(int first_number = 0; first_number <= 9; first_number++){
        if(is_first_number && first_number == 0) continue;
        auto work_tmp = work(n - stick[first_number], false).insert(0, 1, '0' + first_number);
        if(std::stoi(work_tmp) > std::stoi(result) && n - stick[first_number] >= 0){
            result = work_tmp;
        }
    }

    return result;
}

int main() {
  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::cout << work(n) << "\n";
  }
}
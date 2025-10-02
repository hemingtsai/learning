#include <cstdint>
#include <iostream>
#include <string>

const int sticks[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

/*
 * 1. 拼出这个数恰好使用 n 根小木棍；
 * 2. 拼出的数没有前导 0；
 * 3. 在满足以上两个条件的前提下，这个数尽可能小。
 */
std::string work(int n){
    if(n == 2) return "1";
    if(n == 3) return "7";
    if(n == 4) return "4";
    if(n == 5) return "2";
    if(n == 6) return "6";   // 不能选0，因为不能前导零
    if(n == 7) return "8";

    std::string ans;
    if(n % 2 == 1){
        ans = "7";
        n -= 3;
    }else{
        ans = "1";
        n -= 2;
    }
    ans += std::string(n / 2, '1');
    return ans;
}

int main(){
    int T;
    std::cin >> T;
    while(T--){
        int n;
        std::cin >> n;
        std::cout << work(n) << "\n";
    }
    return 0;
}

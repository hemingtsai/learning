#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int N;
    std::cin >> N;

    int result = -2e5;
    while(N--){
        int input;
        std::cin >> input;
        int next_result = result + input;
        if(input > next_result){
            result = input;
        }else{
            result = next_result;
        }
    }
    std::cout << result;
}
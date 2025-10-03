#include <iostream>
#include <vector>

int main(){
    int faucet_num, people_num;
    std::cin >> people_num >> faucet_num;
    std::vector<int> faucet_status(faucet_num, 0);
    for(int i=0;i<people_num;i++){
        int time;
        std::cin >> time;
        auto it = std::min_element(faucet_status.begin(), faucet_status.end());
        *it += time;
    }
    std::cout << *std::max_element(faucet_status.begin(), faucet_status.end()) << "\n";
}
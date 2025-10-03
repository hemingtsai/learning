#include <algorithm>
#include <iostream>
#include <vector>

int main(){
    int cards_num;
    std::cin >> cards_num;

    std::vector<int> cards(cards_num);
    for(auto &v: cards){
        std::cin >> v;
    }

    std::sort(cards.begin(), cards.end());

    int attacked = 0, defeated = 0;
    while(attacked != cards_num){
        if(cards[attacked] > cards[defeated]){
            defeated++;
        }
        attacked++;
    }

    std::cout << cards_num - defeated << "\n";
}
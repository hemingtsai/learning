#include <iostream>

std::string judge(std::string s){
    for(int i=0;i<s.length()/2;i++){
        if(s[i]!=s[s.length()-i-1]){
            return "no";
        }
    }
    return "yes";
}

int main(){
    std::string str;
    std::cin >> str;
    std::cout << judge(str);
    return 0;
}
#include <iostream>
#include <set>
#include <utility>

int main(){
    std::set<int> A,B;
    int n,m;
    std::cin>>n>>m;

    for(int i=0;i<m;i++){
        int u,v;
        std::cin >> u >> v;
        if(u<v){
            std::swap(u,v);
        }
        auto fA = A.count(u);
        auto fB = B.count(u);
        if(!fA && !fB){
            A.insert(u);
            B.insert(v);
        }else if(fA && !fB){
            B.insert(v);
        }else{
            A.insert(v);
        }
    }

    if(A.size() < B.size())
        std::cout << A.size() << " " << n-A.size() << std::endl;
    else
        std::cout << B.size() << " "<< n-B.size() << std::endl;

    return 0;
}

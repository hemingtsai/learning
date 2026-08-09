#include <iostream>

const int MAXN = 5e5 + 5;
int n, m;
int a[MAXN], c[MAXN];

int lowbit(int x) { return x & -x; }

void add(int i, int z){
    for(;i<=n;i+=lowbit(i)){
        c[i] += z;
    }
}

int sum(int i){
    int result = 0;
    for(;i>0;i-=lowbit(i)){
        result += c[i];
    }
    return result;
}

int range_sum(int l, int r){
    return sum(r) - sum(l-1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for(int i=1;i<=n;i++){
        std::cin >> a[i];
        add(i,a[i]);
    }

    while(m--){
        int op, x, y;
        std::cin >> op >> x >> y;
        if(op == 1)
            add(x,y);
        else
            std::cout << range_sum(x,y) << '\n';
    }
}

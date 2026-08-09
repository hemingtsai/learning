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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for(int i=1;i<=n;i++){
        std::cin >> a[i];
        add(i, a[i] - a[i-1]);  // 差分初始化
    }

    while(m--){
        int op;
        std::cin >> op;
        if(op == 1){
            int l, r, k;
            std::cin >> l >> r >> k;
            add(l, k);
            add(r + 1, -k);
        } else {
            int x;
            std::cin >> x;
            std::cout << sum(x) << '\n';  // 点查询 = 差分前缀和
        }
    }
    return 0;
}

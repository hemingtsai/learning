#include <algorithm>
#include <iostream>

const int maxn = 5e5 + 5;
int a[maxn], b[maxn], c[maxn];

int n;
long long answer;

int lowbit(int x) { return x & -x; }

void add(int i, int x) {
  for (; i <= n; i += lowbit(i)) {
    c[i] += x;
  }
}

int sum(int i) {
  int s = 0;
  for (; i > 0; i -= lowbit(i)) {
    s += c[i];
  }
  return s;
}

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    b[i] = a[i];
  }
  std::sort(b + 1, b + n + 1);
  int m = std::unique(b + 1, b + n + 1) - b - 1;
  for(int i=1;i<=n;i++){
      a[i]=std::lower_bound(b+1,b+m+1,a[i])-b;
  }
  for(int i=n;i>=1;i--){
      int v=a[i];
      answer+=sum(v-1);
      add(v,1);
  }
  std::cout << answer << std::endl;
}

#include <algorithm>
#include <iostream>
#include <vector>

const int mod = 1e8 - 3;
const int maxn = 1e5 + 5;
int n;
int a[maxn], b[maxn];
int p[maxn];
int c[maxn];

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
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> b[i];
  }
  std::vector<std::pair<int, int>> va, vb;
  for (int i = 1; i <= n; i++) {
    va.push_back({a[i], i});
    vb.push_back({b[i], i});
  }
  std::sort(va.begin(), va.end());
  std::sort(vb.begin(), vb.end());
  for (int i = 0; i < n; i++) {
    p[va[i].second] = vb[i].second;
  }
  long long answer = 0;
  for (int i = n; i >= 1; i--) {
    answer = (answer + sum(p[i] - 1)) % mod;
    add(p[i], 1);
  }
  std::cout << answer << '\n';
}

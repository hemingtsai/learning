#include <cstdio>

int v[(int)1e6];

int binary_search(int target, int l, int r) {
  int ans = -2;
  int mid;

  while (l <= r) {
    mid = (l + r) / 2;
    if (target == v[mid]) {
      ans = mid;
      r = mid - 1;
    } else if (target < v[mid]) {
      r = mid - 1;
    } else if (v[mid] < target) {
      l = mid + 1;
    }
  }

  return ans;
}

int main() {
  int n, m;
  std::scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    std::scanf("%d", &v[i]);
  }
  for (int i = 0; i < m; i++) {
    int target;
    std::scanf("%d", &target);
    std::printf("%d ", binary_search(target, 0, n - 1) + 1);
  }
  return 0;
}
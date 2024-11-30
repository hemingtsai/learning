#include <iostream>

constexpr int N = 1e5 + 10;

int a[N], t[N];
long long count = 0;

void merge_sort(int begin, int end) {
  if (begin == end) {
    return;
  }
  int mid = (begin + end) >> 1;
  merge_sort(begin, mid);
  merge_sort(mid + 1, end);

  int i = begin, j = mid + 1, k = begin;
  while (i <= mid && j <= end) {
    if (a[i] > a[j]) {
      t[k++] = a[j++];
      count += mid - i + 1;
    } else {
      t[k++] = a[i++];
    }
  }

  while (i <= mid) {
    t[k++] = a[i++];
  }
  while (j <= end) {
    t[k++] = a[j++];
  }

  for (int i = begin; i <= end; i++) {
    a[i] = t[i];
  }
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++)
    std::cin >> a[i];
  merge_sort(0, n - 1);
  std::cout << count << std::endl;
}
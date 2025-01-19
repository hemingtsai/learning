#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (int &i : v) {
    std::cin >> i;
  }
  int count = 0;
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (v[i] > v[j])
        count ++;
    }
  }

  std::cout << count;
  return 0;
}
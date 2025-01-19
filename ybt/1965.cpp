#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int N;
  std::cin >> N;

  std::vector<int> vN(N, 0);
  for (auto &v : vN)
    std::cin >> v;

  std::sort(vN.begin(), vN.end());

  for(int i=0)
}
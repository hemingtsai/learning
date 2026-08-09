#include <iostream>
#include <vector>

int main() {
  int N;
  std::cin >> N;

  std::vector<int> v(N + 1);
  for (auto &i : v) {
    std::cin >> i;
  }

  for (int i = N; i > 0; i--) {
    if (v[N - i] == 0) {
      continue;
    }

    if (i == N) {
      if (v[N - i] == -1)
        std::cout << '-';
      else if (v[N - i] != 1)
        std::cout << v[N - i];
      std::cout << "x^" << i;
      continue;
    }

    if (v[N - i] <= 0) {
      if (v[N - i] == -1) {
        std::cout << '-';
      } else {
        std::cout << v[N - i];
      }
    } else {
      if (v[N - i] != 1)
        std::cout << '+' << v[N - i];
      else
        std::cout << '+';
    }

    if (i==1) {
      std::cout << "x";
    }else{
      std::cout << "x^" << i;
    }
  }

  if (v[N] > 0) {
    std::cout << '+' << v[N];
  } else if (v[N] < 0) {
    std::cout << v[N];
  }
}
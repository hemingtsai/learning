#include <iostream>

double answer = 0;

double S(int i) {
  answer += 1.0 / i;
  return answer;
}

int main() {
  int K;
  std::cin >> K;

  {
    int i = 1;
    while (S(i) <= K) {
      i++;
    }
    std::cout<<i;
  }

  return 0;
}
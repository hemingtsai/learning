#include <algorithm>
#include <iostream>
int main() {
  int a[3] = {1, 2, 3};
  do {
    std::cout << a[0] << a[1] << a[2]<<std::endl;
  } while (std::next_permutation(a, a + 3));
  do {
    std::cout << a[0] << a[1] << a[2]<<std::endl;
  } while (std::prev_permutation(a, a + 3));
  return 0;
}
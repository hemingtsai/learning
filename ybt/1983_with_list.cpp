#include <iostream>
#include <list>
#include <utility>

int n, ans;
std::list<std::pair<int, int>> l;
std::list<std::pair<int, int>>::iterator it;

int main() {
  std::cin >> n;
  int k, p, t;
  bool f;
  for (int i = 1; i <= n; i++) {
    std::cin >> k >> p >> t;
    if (k == 0) {
      ans += p;
      l.push_back(std::make_pair(p, t));
    } else {
      it = l.begin();
      f = false;
      while (it != l.end()) {
        if (t - it->second > 45) {
          it = l.erase(it);
        } else if (it->first >= p) {
          l.erase(it);
          f = true;
          break;
        } else {
          it++;
        }
      }

      if (f == false)
        ans += p;
    }
  }
  std::cout << ans << std::endl;
}
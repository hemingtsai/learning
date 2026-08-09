#include <iostream>

const int MAXN = 100005;
struct Ticket {
  int price, time;
  bool used;
} q[MAXN];

int head, tail, n, cost;

int main() {
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int op, price, time;
    std::cin>>op>>price>>time;
    if (op == 0) {
      cost += price;
      q[tail].time = time + 45;
      q[tail++].price = price;
    } else {
      while (head < tail && q[head].time < time) {
        q[head].used = 1;
        head++;
      }
      bool found = false;
      for (int j = head; j < tail; j++) {
        if (q[j].price >= price && q[j].used == 0) {
          found = true;
          q[j].used = 1;
          break;
        }
      }
      if (!found)
        cost += price;
    }
  }
  std::cout << cost << std::endl;
  return 0;
}
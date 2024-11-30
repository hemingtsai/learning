#include <bits/stdc++.h>
#include <queue>
using namespace std;
int x[12] = {-2, -1, -2, -2, -1, -2, 2, 1, 2, 2, 1, 2};
int y[12] = {-1, -2, -2, 1, 2, 2, -1, -2, -2, 1, 2, 2};
int n1, n2, m1, m2, r, l, st;
int v[105][105];
struct node {
  int xx, yy, step;
};
void bfs(int xx, int yy) {
  queue<node> q;
  memset(v, 0, sizeof v);
  node s, ss;
  s.xx = xx;
  s.yy = yy;
  s.step = 0;
  q.push(s);
  while (!q.empty()) {
    s = q.front();
    q.pop();
    for (int i = 0; i < 12; i++) {
      r = s.xx + x[i];
      l = s.yy + y[i];
      if (r <= 100 && r > 0 && l <= 100 && l > 0 && v[r][l] == 0) {
        v[r][l] = 1;
        ss.xx = r;
        ss.yy = l;
        ss.step = s.step + 1;
        q.push(ss);
        if (r == 1 && l == 1) {
          std::cout << s.step + 1 << endl;
          return;
        }
      }
    }
  }
}

int main() {
  std::cin >> n1 >> m1;
  std::cin >> n2 >> m2;
  bfs(n1, m1);
  bfs(n2, m2);
  return 0;
}
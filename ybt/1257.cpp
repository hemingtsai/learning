#include <bits/stdc++.h>
#include <queue>
using namespace std;
int x[8] = {-2, -1,  -2, -1, 2, 1, 2, 1};
int y[8] = {-1, -2,  1, 2, -1, -2, 1, 2};
int r, l, st;
int ex,ey;
int L;
int v[305][305];
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
  v[xx][yy]=1;
  q.push(s);
  while (!q.empty()) {
    s = q.front();
    q.pop();
    for (int i = 0; i < 8; i++) {
      r = s.xx + x[i];
      l = s.yy + y[i];
      if (r <= L && r >= 0 && l <= L && l >= 0 && v[r][l] == 0) {
        v[r][l] = 1;
        ss.xx = r;
        ss.yy = l;
        ss.step = s.step + 1;
        q.push(ss);
        if (r == ex && l == ey) {
          std::cout << s.step + 1 << endl;
          return;
        }
      }
    }
  }
}

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int x, y;
    std::cin >> L >> x >> y >> ex >> ey;
    if (x == ex && y == ey) {
      std::cout<<0;
    } else {
      bfs(x,y);
    }
  }
  return 0;
}
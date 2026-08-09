#include <iostream>

int father[1000];

int find(int x) {
  if (father[x] != x)
    father[x] = find(father[x]);
  return father[x];
}

void f_union(int x, int y) {
  x = find(x);
  y = find(y);
  if (x != y)
    father[y]=std::min(x,y);
}

bool judge(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y)
    return true;
  return false;
}

int main() {
  
  return 0;
}
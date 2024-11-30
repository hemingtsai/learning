#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

char str[100010];
int cnt = 0;

void show(int n) {
  int a = 0, b = 0;
  for (int i = 0; i < cnt; i++) {
    if (str[i] == 'W')
      a++;
    if (str[i] == 'L')
      b++;
    if ((a >= n || b >= n) && abs(a - b) >= 2) {
      printf("%d:%d\n", a, b);
      a=b=0;
    }
  }
  printf("%d:%d\n",a,b);
}

int main() {
  char ch;
  while (cin >> ch && ch != 'E') {
    if (ch == 'W' || ch == 'L') {
      str[cnt++] = ch;
    }
  }

  show(11);
  cout << endl;
  show(21);
}
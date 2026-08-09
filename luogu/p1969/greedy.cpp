#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int prev = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        int h;
        cin >> h;
        if (h > prev) ans += h - prev;
        prev = h;
    }
    cout << ans << endl;
}
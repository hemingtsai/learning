#include <cmath>
#include <iostream>
using namespace std;

int t_time[100001], price[100001], judge[100001];
bool flag = true;
int main() {
  int n, sum = 0, count1 = 0, count2 = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int trans, price1, time1;
    cin >> trans;
    if (trans == 0) {
      cin >> price[count1++] >> t_time[count2++];
      sum += price[count1 - 1];
      // cout<<"subway:"<<" "<<sum<<endl;
    }
    if (trans == 1) {
      cin >> price1 >> time1;
      // cout<<"bus"<<endl;
      for (int j = 0; j <= count1 - 1; j++) {
        // cout<<" "<<price[j]<<" "<<abs(time1-time[j])<<" "<<judge[j]<<endl;
        if (price1 <= price[j] && abs(t_time[j] - time1) <= 45 && judge[j] == 0) {
          judge[i] = 1;
          flag = false;
        }
      }
      if (flag) {
        sum += price1;
        // cout<<"moneyadd"<<endl;
      }
      flag = true;
      // cout<<sum<<endl;
    }
  }
  cout << sum;

  return 0;
}
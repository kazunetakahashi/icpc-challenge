#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const unsigned T[5] = {5, 7, 5, 7, 7};

int main() {
  int n;
  while (cin >> n && n) {
    string w[100];
    for (auto i=0; i<n; i++) {
      cin >> w[i];
    }
    for (auto i=0; i<n; i++) {
      int ku = 0;
      int j = i;
      bool ok = true;
      string now = "";
      while (ku < 5) {
        now += w[j++];
        if (now.size() == T[ku]) {
          ku++;
          now = "";
        } else if (now.size() > T[ku]) {
          ok = false;
          break;
        }
      }
      if (ok) {
        cout << i+1 << endl;
        break;
      }
    }
  }
}

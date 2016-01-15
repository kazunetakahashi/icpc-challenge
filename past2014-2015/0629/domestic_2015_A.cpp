#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int m, nmin, nmax;
  while (cin >> m >> nmin >> nmax && m) {
    int P[300];
    for (auto i=0; i<m; i++) {
      cin >> P[i];
    }
    int ans = 0;
    int gap = 0;
    for (auto i=nmin-1; i<nmax; i++) {
      if (gap <= P[i] - P[i+1]) {
        gap = P[i] - P[i+1];
        ans = i;
        // cerr << gap << " " << ans << endl;
      }
    }
    cout << ans+1 << endl;
  }
}

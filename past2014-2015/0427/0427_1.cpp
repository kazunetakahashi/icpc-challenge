// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0517
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int n, k;
  while (cin >> n >> k && n && k) {
    int card[100010];
    for (auto i=0; i<k; i++) {
      cin >> card[i];
    }
    sort(card, card+k);
    bool zero = (card[0] == 0);
    vector< pair<int, bool> > V;
    int tnow = 1;
    for (int i=(zero ? 1 : 0); i<k; i++) {
      if (i == k-1) {
        V.push_back(make_pair(tnow, false));
        break;
      }
      // cerr << "card[" << i << "] = " << card[i] << ", card[" << i+1 << "] = " << card[i+1] << endl;
      if (card[i] == card[i+1] - 1) {
        tnow++;
      } else {
        if (zero && card[i] == card[i+1] - 2) {
          V.push_back(make_pair(tnow, true));
        } else {
          V.push_back(make_pair(tnow, false));
        }
        tnow = 1;
      }
    }
    int ans = 0;
    for (auto it = V.begin(); it != V.end(); it++) {
      if ((*it).second) {
        ans = max(ans, (*it).first + (*(it+1)).first + 1);
      } else if (zero) {
        ans = max(ans, (*it).first + 1);
      } else {
        ans = max(ans, (*it).first);
      }
    }
    cout << ans << endl;
  }
}

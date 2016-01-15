// http://main.edu.pl/en/archive/oi/3/wie
// 解法は英国少女がホームステイしているアレを深夜に見ている時に気づいた。
// main.edu.pl は C++11 が使えないので(本質と関係ないところで)苦労した。
// やはりAOJ、atcoderが最強ですね。pojとmainはやる気半減です…
// 他にハマったところ：V[id++].first.firstと書くと(処理系によっては？)2回インクリメントしてしまう。

#include <iostream>
#include <queue>
#include <algorithm>
// #include <tuple>
using namespace std;

int n;
vector< pair< pair<int, int>, int > > V[2]; // start, goal, no
vector<int> ans[2]; // no, haichi
bool ok = true;

int main() {
  cin >> n;
  int a, b, c, d;
  for (int i=0; i<n; i++) {
    cin >> a >> b >> c >> d;
    a--; b--; c--; d--;
    V[0].push_back(make_pair(make_pair(a, c), i));
    V[1].push_back(make_pair(make_pair(b, d), i));
  }
  for (int i=0; i<2; i++) {
    ans[i] = vector<int>(n);
    int id = 0;
    priority_queue< pair<int, int> > Q; // goal, no
    if (!ok) goto EXIT;
    sort(V[i].begin(), V[i].end());
    for (int j=0; j<n; j++) {
      // cerr << V[i][j].first.first << " " << V[i][j].first.second << " " << V[i][j].second << endl;
    }
    for (int j=0; j<n; j++) {
      while (id < n && V[i][id].first.first <= j) {
        Q.push(make_pair(-1 * V[i][id].first.second, V[i][id].second));
        // cerr << "pushes " << V[i][id].first.second << " " << V[i][id].second << endl;
        id++;
      }
      pair<int, int> X = Q.top();
      Q.pop();
      if (-1 * X.first < j) {
        // cerr << "j = " << j << ", X.first = " << X.first << ", X.second = " << X.second << endl;
        ok = false;
        goto EXIT;
      } else {
        ans[i][X.second] = j;
      }
    }
  EXIT:
    continue;
  }
  if (!ok) {
    cout << "NIE" << endl;
  } else {
    for (int i=0; i<n; i++) {
      cout << ans[0][i]+1 << " " << ans[1][i]+1 << endl; 
    }
  }
}

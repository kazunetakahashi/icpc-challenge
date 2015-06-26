// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1182&lang=jp
// 解答方針：まず、任意の路線を選ぶ。その路線のみを使用し、任意の駅を出発点として、任意の駅への最短距離をダイクストラ法で求める。この状態でかかる料金を算出するのは可能である。ここで仮想的な路線図を作る。出発駅・到着駅が、この料金のPassで結ばれているとみなす。この仮想的な路線図でダイクストラ法を実行すれば正答に至る。
// コメント：方針は1週間くらいで思いついた。実装が大変だった。そもそも問題文の文字がかぶっている(cが添字付きと添字無しで使われている、sも自分で置いた文字で被ってしまった)上に、同じようなことを繰り返しやるので文字がかぶりやすい。ゆえに、バグを出してしまいやすい。バグ取りに2時間以上かかりました。

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

typedef long long ll;

typedef tuple<int, int> rail; // dst, cost
typedef tuple<int, int> state; // cost, dst
typedef tuple<ll, int> statell; // cost, dst

const ll infty = 100100100100;

int p[30];
vector<int> q[30];
vector<int> r[30];

int cal_cost(int camp, int now, int dist) {
  int ans = 0;
  int pt = now;
  int rem = dist;
  for (auto i=0; i<p[camp]; i++) {
    if (q[camp][i] <= now) {
      continue;
    } else if (pt + rem <= q[camp][i]) {
      ans += rem * r[camp][i];
      break;
    } else {
      ans += (q[camp][i] - pt) * r[camp][i];
      rem -= q[camp][i] - pt;
      pt = q[camp][i];
      // cerr << "i = " << i << ", ans = " << ans << endl;
    }
  }
  return ans;
}

int main() {
  int n, m, c, s, g;
  /* sample check
  p[0] = 3;
  q[0].push_back(3);
  q[0].push_back(6);
  q[0].push_back(100010);
  r[0].push_back(10);
  r[0].push_back(5);
  r[0].push_back(3);
  for (auto i=0; i<3; i++) {
    cerr << q[0][i] << ", " << r[0][i] << endl;
  }
  for (auto i=0; i<=9; i++) {
    cerr << "dist = " << i << ", cost = " << cal_cost(0, 0, i) << endl;
  }
  p[1] = 3;
  q[1].push_back(100010);
  r[1].push_back(10);
  for (auto i=0; i<1; i++) {
    cerr << q[1][i] << ", " << r[1][i] << endl;
  }
  for (auto i=0; i<=9; i++) {
    cerr << "dist = " << i << ", cost = " << cal_cost(1, 0, i) << endl;
  }
  */
  while (cin >> n >> m >> c >> s >> g && n) {
    s--; g--;
    vector<rail> V[30][110]; // company, src
    vector<rail> W[110]; // 仮想空間
    for (auto i=0; i<30; i++) {
      q[i].clear();
      r[i].clear();
      for (auto j=0; j<110; j++) {
        V[i][j].clear();
      }
    }
    int x, y, d, k;
    for (auto i=0; i<m; i++) {
      cin >> x >> y >> d >> k;
      x--; y--; k--;
      V[k][x].push_back(make_tuple(y, d));
      V[k][y].push_back(make_tuple(x, d));
    }
    for (auto i=0; i<c; i++) {
      cin >> p[i];
    }
    for (auto i=0; i<c; i++) {
      q[i] = vector<int>(p[i]);
      r[i] = vector<int>(p[i]);
      for (auto j=0; j<p[i]-1; j++) {
        cin >> q[i][j];
      }
      q[i][p[i]-1] = 100010;
      for (auto j=0; j<p[i]; j++) {
        cin >> r[i][j];
      }
    }
    for (auto cmp=0; cmp<c; cmp++) {
      for (auto src=0; src<n; src++) {
        vector<ll> D = vector<ll>(n, infty);
        priority_queue<state, vector<state>, greater<state> > Q;
        Q.push(make_tuple(0, src));
        while (!Q.empty()) {
          int nc = get<0>(Q.top());
          int ns = get<1>(Q.top());
          Q.pop();
          if (D[ns] == infty) {
            D[ns] = nc;
            for (unsigned i=0; i<V[cmp][ns].size(); i++) {
              rail tr = V[cmp][ns][i];
              int nd = get<0>(tr);
              int tc = get<1>(tr);
              if (D[nd] == infty) {
                Q.push(make_tuple(nc + tc, nd));
              }
            }
          }
        }
        // cerr << "cmp = " << cmp << ", src = " << src << endl;
        for (auto dst=0; dst<n; dst++) {
          if (src == dst) continue;
          if (D[dst] < infty) {
            W[src].push_back(make_tuple(dst, cal_cost(cmp, 0, D[dst])));
            //cerr << dst << " : " << D[dst] << " -> "
            //     << cal_cost(cmp, 0, D[dst]);
            //if (dst != n-1) {
            //  cerr << ", ";
            //}
          }
        }
        //cerr << endl;
      }
    }
    vector<ll> D = vector<ll>(n, infty);
    priority_queue<statell, vector<statell>, greater<statell> > Q;
    // cerr << s << " to " << g << endl;
    Q.push(make_tuple(0, s));
    ll ans = -1;
    while (!Q.empty()) {
      ll nc = get<0>(Q.top());
      int ns = get<1>(Q.top());
      Q.pop();
      if (ns == g) {
        ans = nc;
        break;
      }
      if (D[ns] == infty) {
        D[ns] = nc;
        // cerr << "D[" << ns << "] = " << D[ns] << endl;
        for (unsigned i=0; i<W[ns].size(); i++) {
          rail tr = W[ns][i];
          int nd = get<0>(tr);
          int tc = get<1>(tr);
          if (D[nd] == infty) {
            // cerr << "dst = " << nd << endl;
            Q.push(make_tuple(nc + tc, nd));
          }
        }
      }
    }
    cout << ans << endl;
  }
}

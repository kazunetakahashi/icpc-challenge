// marked ancester
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170
/*
  求められているのは Q v の和なので、クエリを逆順に処理しても結果は同じ。
  逆に処理すれば「分解」が発生しないので union-find 木で
  高速にクエリに回答できる。具体的には次の通り。

  1：まず「指定された木」をつくって持っておく。
  2：まずマークする＝親を切り離しその頂点を根とする。全部やる。
  3：命令を逆順に処理する。
  ・クエリに回答する＝rootを回答する。
  ・マークする＝「指定された木」で、親となっているものと結合する。

  この時に陥りやすい罠は、同じ点を2回以上マークすることも命令としては
  許されることである。単純に逆に処理するだけでは、「最後のマーク命令」で
  マークを外してしまい、誤答する。有効なのは「最初のマーク命令」だけ
  なのだから「最初のマーク命令」以外は2の段階で無視しておく。
 */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int C = 100010;
const int UFSIZE = 100010;
int P[UFSIZE]; // 親
int T[UFSIZE]; // 木

void init() {
  for (auto i=0; i<UFSIZE; i++) {
    P[i] = i;
  }
}

int root(int a) {
  if (a == P[a]) return a;
  return (P[a] = root(P[a]));
}

bool issame(int a, int b) {
  return root(a) == root(b);
}

void unite(int a, int b) {
  P[root(a)] = root(b);
}

bool isroot(int a) {
  return root(a) == a;
}

int main() {
  int N, Q;
  while (cin >> N >> Q && N) {
    T[0] = 0;
    for (auto i=1; i<N; i++) {
      cin >> T[i];
      T[i]--;
    }
    vector< pair<bool, int> > V;
    bool marked[C];
    fill(marked, marked+C, false);
    for (auto i=0; i<Q; i++) {
      char op;
      int v;
      cin >> op >> v;
      v--;
      if (op == 'M' && marked[v]) continue;
      if (op == 'M') marked[v] = true;
      V.push_back(make_pair((op == 'M'), v));
    }
    for (auto i=0; i<N; i++) {
      P[i] = T[i];
    }
    Q = (int) V.size();
    for (auto i=0; i<Q; i++) {
      if (V[i].first) {
	P[V[i].second] = V[i].second;
      }
    }
    reverse(V.begin(), V.end());
    long long ans = 0;
    for (auto i=0; i<Q; i++) {
      if (V[i].first) {
	unite(V[i].second, T[V[i].second]);
      } else {
	ans += root(V[i].second)+1;
      }
    }
    cout << ans << endl;
  }
}

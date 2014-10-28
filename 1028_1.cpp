// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1161&lang=jp
/* 方針
   各文字に数字を入れて、等式が成立するかどうかを判定し、すべての場合を尽くす。
   しかし愚直にやると数字の組み合わせは約10!通りあるので、間に合わない。
   次の2点を実施すると速くなる。

   1：ABC = 100 * A + 10 * B + 1 * C のようにわけ、
   移行し、係数の計算だけは済ませておく。
   係数をa_iとし、その都度与えられる数をn_iとし、
   最終的に \sum_{i=0}^9 a_i * n_i = 0 \label{eq:hantei}を判定する。
   しかしこれは、約10!通りの場合の数が減るわけではない。

   2：そこで\eqref{eq:hantei}式を更に変形し、
   \sum_{i=0}^4 a_i * n_i = - \sum_{j=5}^9 a_i * n_i \label{eq:hantei_2}
   とする。代入計算は、\eqref{eq:hantei_2}の右辺と左辺で独立して行う。
   右辺・左辺それぞれについて(計算結果, 使った数字)のペアを覚えておく。
   右辺・左辺の結果を突き合わせる。計算結果が一致し、かつ
   使った数字が重複していなければ、それは\eqref{eq:hantei_2}を
   成立させる数字の組み合わせが1つ存在することを意味する。
   
   2はどうして高速なのか？
   ・右辺、左辺の場合の数はせいぜい N = 10*9*8*7*6 通りであり、
   10!通りの1/60である。
   ・計算結果を昇順にソート(O(N \log N))しておけば
   「計算結果が一致」の部分はO(N)で判定できる。
   ・見過ごされやすいのは「使った数字の重複」の判定である。
   これは「計算結果が一致」する右辺・左辺の組を2重ループするしか思いつかない。
   すなわち、最悪の場合O(N^2)かかる…ように見える。
   これでは失敗になるとずっと悩んでいた。
   しかし今回の場合は「文字列の長さは8文字」という条件がある。
   すなわち「最悪」なのは、恒等式の場合、つまり
   $ 2
   $ ABCDEFGH
   $ ABCDEFGH
   の入力である。しかし8文字だとせいぜい2重ループは
   1632960回しか回らないので、なんとかなるというわけである。
   9文字以上だと絶望的である。(そもそもintに収まらないが)
   
   下のソースコードは\eqref{eq:hantei_2}のかわりに
   \sum_{i=0}^4 a_i * n_i + \sum_{j=5}^9 a_i * n_i = 0 \label{eq:hantei_3}
   を採用している。
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

int N;
vector<string> V; // stringを入れる
set<char> S; // 使われている文字の集合
map<char, int> M; // 文字を番号付けする
int L; // 使われている文字の数
vector<int> K; // 係数
vector<bool> istop; // 先頭文字ならtrue。0を代入しない。
vector<pair<int, int> > X, Y; // 半分ずつ入れる。

void init() {
  V.clear();
  S.clear();
  M.clear();
  L = 0;
  K.clear();
  istop.clear();
  X.clear();
  Y.clear();
}

void keisu(string str, bool b) {
  int mp = ( b ? 1 : -1 );
  int tens = 1;
  // // cerr << str << endl;
  for (int i=(int)str.size()-1; i>=0; i--) {
    K[M[str[i]]] += tens * mp;
    // cerr << "K[" << M[str[i]] << "] = " << K[M[str[i]]] << endl;
    tens *= 10;
  }
}

void ipt() {
  for (auto i=0; i<N; i++) {
    string str;
    cin >> str;
    V.push_back(str);
  }
  for (auto i=0; i<N; i++) {
    for (unsigned int j=0; j<V[i].size(); j++) {
      S.insert(V[i][j]);
    }
  }
  L = S.size();
  K = vector<int>(L, 0);
  istop = vector<bool>(L, false);
  int k = 0;
  for (auto itt=S.begin(); itt!=S.end(); itt++) {
    M[*itt] = k++;
  }
  for (auto i=0; i<N; i++) {
    if (V[i].size() > 1) {
      istop[M[V[i][0]]] = true;
      // cerr << "top " << V[i][0] << endl;
    }
  }
  for (auto i=0; i<N; i++) {
    keisu(V[i], (i != N-1));
  }
}

void dfs(int start, int end, int used, int temp, bool kiroku) {
  if (start == end) {
    pair<int, int> P = make_pair(temp, used);
    if (kiroku) {
      X.push_back(P);
      // cerr << "X temp = " << temp << ", used = " << used << endl;
    } else {
      Y.push_back(P);
      // cerr << "Y temp = " << temp << ", used = " << used << endl;
    }
  } else {
    for (auto i=0; i<10; i++) {
      if ((((used >> i) & 1) != 1) && (i != 0 || !istop[start])) {
	dfs(start+1, end, (used | (1 << i)), temp + K[start]*i, kiroku);
      }
    }
  }
}

int solve() {
  sort(X.begin(), X.end());
  sort(Y.begin(), Y.end());
  reverse(Y.begin(), Y.end());
  unsigned int xi = 0;
  unsigned int yi = 0;
  int ans = 0;
  while(xi < X.size() && yi < Y.size()) {
    int xv = X[xi].first;
    int yv = Y[yi].first;
    int sum = xv + yv;
    if (sum > 0) {
      yi++;
    } else if (sum < 0) {
      xi++;
    } else {
      // // cerr << "xi = " << xi << endl;
      for (unsigned int i=xi; i < X.size() && X[i].first == xv; i++) {
	for (unsigned int j=yi; j < Y.size() && Y[j].first == yv; j++) {
	  if ((X[i].second & Y[j].second) == 0) { 
	    ans++;
	    // cerr << X[i].second << " " << Y[j].second << endl;
	  }
	}
      }
      while (X[xi].first == xv) xi++;
      while (Y[yi].first == yv) yi++;
    }
  }
  return ans;
}

int main() {
  while (cin >> N && N) {
    init();
    ipt();
    dfs(0, L/2, 0, 0, true);
    dfs(L/2, L, 0, 0, false);
    cout << solve() << endl;
  }
}

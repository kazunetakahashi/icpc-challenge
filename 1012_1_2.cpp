// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1302
// Twenty Questions
/* 
   x日間悩み、
   動的計画法(メモ化)でやろうということを思いついた。
   数学的に解が得られる方法は複数ありうる。
   しかし、0 < m \leq 11 and 0 < n \leq 128 という制約の中で
   制限に引っかからなそうなものとなると、状態の持ち方が限られる。
   
   たとえば自然な発想として、
   「n個のonjectの各部分集合を状態として持ち、それを類別するために必要な最小の
   質問回数」を配列で持とうとするものが考えられる。
   しかし2^{128}個のintはメモリの上においておくのは無理である。
   よく考えてみると相当無駄がある。質問はm \leq 11個しかない
   だから「出てきうる」部分集合の個数は、せいぜい3^{11}個であり、2^{128}より
   はるかに少ない。
   
   そこで、
   「m個の質問それぞれを『未回答』『はい』『いいえ』をみたす
   onjectの集合を状態として持ち、それを類別するために必要な最小の
   質問回数」を配列で持とう。これなら3^{11}個である。
   (ただし以下の実装の2次元配列のサイズは2^{11} \times 2^{11}である)
   
   次なる問題はどのようにしてこの動的計画法を進めるかである。
   ここでさらにy日悩んだが、
   「集合の元の数が1個か0個」は0とし、
   あとは深さ優先探索を併用している。
   完全に再帰でやるとメモリ足りないかもしれないので、
   『未回答』が少ない集合からまわしていき、
   あまり深すぎないようにしようとしたが、結果的に必要なかったようだ。
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
using namespace std;

vector< vector<int> > V; // [0:未回答 1:回答済み][0:Yes 1:No]
int n, m, C;
vector<int> W;
const int infty = 1000;
// vector< vector<int> > X; // X[i] = i個bitが立っている集合

void init() {
  C = (1 << m);
  V.clear();
  V = vector< vector<int> >(C, vector<int>(C, infty));
  W.clear();
  for (auto i=0; i<n; i++) {
    long long w;
    string s;
    cin >> s;
    w = stoll(s);
    int x = 0;
    int y = 1;
    for (auto j=0; j<m; j++) {
      x += w%10 * y;
      y *= 2;
      w /= 10;
    }
    // cerr << x << endl;
    W.push_back(x);
  }
  /*X.clear();
  X = vector< vector<int> >(m+1, vector<int>(0));
  for (auto i=0; i<C; i++) {
    int count = 0;
    for (auto k=0; k<m; k++) {
      if ((i >> k) & 1) {
	count++;
      }
    }
    X[count].push_back(i);
    // cerr << "X[" << count << "] pushed " << i << endl; 
    }*/
}

bool ok(int i, int j) { // 未回答なのにjに1が立っているものを弾く
  for (auto k=0; k<m; k++) {
    if ( ((j >> k) & 1) && (((i >> k) & 1) == 0) ) {
      return false;
    }
  }
  return true;
}

void costzero() {
  for(auto i=0; i<C; i++) {
    for (auto j=0; j<C; j++) {
      if (ok(i, j)) {
	// cerr << "i = " << i << ", j = " << j << endl;
	vector<int> K = W;
	for (auto k=0; k<m; k++) {
	  if ((i >> k) & 1) {
	    vector<int> L;
	    int x = (j >> k) & 1;
	    for (unsigned int l=0; l<K.size(); l++) {
	      if (((K[l] >> k) & 1) == x) {
		L.push_back(K[l]);
	      }
	    }
	    K.clear();
	    K = L;
	  }
	}
	// cerr << K.size() << endl;
	if (K.size() <= 1) {
	  V[i][j] = 0;
	  // cerr << "i = " << i << ", j = " << j << endl;
	}
      }
    }
  }
}

int cost(int i, int j) {
  if (V[i][j] < infty) { // もう計算してあるなら使えばいい
    return V[i][j];
  }
  int ans = infty;
  for (auto k=0; k<m; k++) { // 性質kの質問を追加する
    if (((i >> k) & 1) == 0) { // まだしてないことを確認
      int ansk = 0;
      int ni = i | (1 << k);
      for (auto l=0; l<2; l++) { // yes, no
	int nj = j | (l << k);
	int anskl = cost(ni, nj);
	if (ansk < anskl) ansk = anskl; // 両方決定するのにかかる多い方
      }
      if (ans > ansk) ans = ansk; // よりよい質問の仕方
    }
  }
  /* if (ans == infty) {
    cerr << "infty i = " << i << " j = " << j << endl;
    }*/
  assert(ans < infty); // 必ず区別できるという仮定
  ans++;  // 質問を追加するので1ステップ多い
  V[i][j] = ans; // メモする
  return ans;
}

int main() {
  while(cin >> m >> n && m) {
    init();
    costzero();
    /*for (int i=m; i>=0; i--) {
      for (unsigned int j=0; j<X[i].size(); j++) {
	for (auto k=0; k<C; k++) {
	  if (ok(X[i][j], k)) {
	    cost(X[i][j], k);
	  }
	}
      }
      }*/
    cout << cost(0, 0) << endl;
  }
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2162
// 13以上の素数以外の惑星は愚直に最小公倍数まで演算する。このmaxをAとする。
// Lと13,17,19,23は互いに素である。
// よってAと、13,17,19,23のmaxはすべて必ず重なる瞬間が来る。
// 1のmaxも特別扱いすると毎回同じ数を足す虚しさが減る。

#include <iostream>
using namespace std;

const int L = 16*9*5*7*11;

int main() {
  int N;
  while (cin >> N && N) {
    int Q[30][30] = {{0}};
    for (int i=0; i<N; i++) {
      int d, t;
      cin >> d >> t;
      for (int j=0; j<d; j++) {
	int q;
	cin >> q;
	Q[d][(j+d-t)%d] += q;
      }
    }
    int sum = 0;
    int T[L] = {0};
    for (int d=1; d<=24; d++) {
      if (d == 13 || d == 17 || d == 19 || d == 23 || d == 1) {
	int M = 0;
	for (int i=0; i<d; i++) {
	  if (M < Q[d][i]) M = Q[d][i];
	}
	sum += M;
      } else {
	for (int i=0; i<L; i++) {
	  T[i] += Q[d][i%d];
	}
      }
    }
    int MM = 0;
    for (int i=0; i<L; i++) {
      if (MM < T[i]) MM = T[i];
    }
    cout << sum + MM << endl;
  }
}

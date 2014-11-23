// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=jp
#include <iostream>
using namespace std;

int V[110][10010]; // V[i][c] 品物iまでの世界でコスト制限cでの価値最大値

int main() {
  int N, M;
  cin >> N >> M;
  int v[110];
  int w[110];
  for (auto i=0; i<N; i++) {
    cin >> v[i] >> w[i];
  }
  for (auto j=0; j<=M; j++) {
    if (j < w[0]) {
      V[0][j] = 0;
    } else {
      V[0][j] = v[0];
    }
  }
  for (auto i=1; i<N; i++) {
    for (auto j=0; j<=M; j++) {
      if (j - w[i] >= 0) {
        V[i][j] = max(V[i-1][j], V[i-1][j-w[i]] + v[i]);
      } else {
        V[i][j] = V[i-1][j];
      }
    }
  }
  cout << V[N-1][M] << endl;
}

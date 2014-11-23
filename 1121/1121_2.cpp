// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=jp
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
    int k = j/w[0];
    V[0][j] = k*v[0];
  }
  for (auto i=1; i<N; i++) {
    for (auto j=0; j<=M; j++) {
      V[i][j] = V[i-1][j];
      /* 次のように書くとTLEする。
      int k = 0;
      int tw;
      while ((tw = j - k*w[i]) >= 0) {
        V[i][j] = max(V[i][j], V[i-1][tw] + k*v[i]);
        k++;
      }
      これは、V[i][j-w[i]]を計算するときも、
      j方向に同じ計算をしていることになる。
      これに気づけば次のように書ける。
      */
      if (j - w[i] >= 0) {
        V[i][j] = max(V[i][j], V[i][j-w[i]] + v[i]);
      }
    }
  }
  cout << V[N-1][M] << endl;
}

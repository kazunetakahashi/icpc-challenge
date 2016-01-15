// J,O,Iはひとまとめで3次元配列にするべきだった。
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0560
#include <iostream>
#include <algorithm>
using namespace std;

int output(int X[1010][1010], int p, int q, int r, int s) {
  return X[r][s] - X[p][s] - X[r][q] + X[p][q];
}

char JOI[1010][1010];
int a[100010], b[100010], c[100010], d[100010];
int J[1010][1010], O[1010][1010], I[1010][1010];

int main() {
  int M, N;
  cin >> M >> N;
  int K;
  cin >> K;
  for (auto i=1; i<=M; i++) {
    for (auto j=1; j<=N; j++) {
      cin >> JOI[i][j];
    }
  }
  for (auto i=0; i<K; i++) {
    cin >> a[i] >> b[i] >> c[i] >> d[i];
    a[i]--; b[i]--;
  }
  fill(&J[0][0], &J[0][0]+1010*1010, 0);
  fill(&O[0][0], &O[0][0]+1010*1010, 0);
  fill(&I[0][0], &I[0][0]+1010*1010, 0);
  for (auto i=1; i<=M; i++) {
    for (auto j=1; j<=N; j++) {
      J[i][j] = ((JOI[i][j] == 'J') ? 1 : 0);
      O[i][j] = ((JOI[i][j] == 'O') ? 1 : 0);
      I[i][j] = ((JOI[i][j] == 'I') ? 1 : 0);
    }
  }
  for (auto i=1; i<=M; i++) {
    for (auto j=0; j<=N; j++) {
      J[i][j] += J[i-1][j];
      O[i][j] += O[i-1][j];
      I[i][j] += I[i-1][j];
    }
  }
  for (auto i=0; i<=M; i++) {
    for (auto j=1; j<=N; j++) {
      J[i][j] += J[i][j-1];
      O[i][j] += O[i][j-1];
      I[i][j] += I[i][j-1];
    }
  }
  for (auto i=0; i<K; i++) {
    cout << output(J, a[i], b[i], c[i], d[i])
         << " "
         << output(O, a[i], b[i], c[i], d[i])
         << " "
         << output(I, a[i], b[i], c[i], d[i])
         << endl;
  }
}

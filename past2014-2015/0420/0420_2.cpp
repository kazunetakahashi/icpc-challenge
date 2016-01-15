#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  int X[110], Y[110];
  double R[110];
  for (int i=0; i<M; i++) {
    cin >> X[i] >> Y[i] >> R[i];
    X[i]--; Y[i]--;
  }
  double S[110][110];
  fill(&S[0][0], &S[0][0]+110*110, -1);
  for (int i=0; i<M; i++) {
    double *x = &S[X[i]][Y[i]];
    if (*x == -1) {
      *x = R[i];
    } else {
      *x = (*x) * R[i] / (R[i] + (*x));
    }
  }
  for (int k=0; k<N; k++) {
    for (int i=0; i<N; i++) {
      for (int j=0; j<N; j++) {
        if (i < k && k < j && S[i][k] != -1 && S[k][j] != -1) {
          if (S[i][j] == -1) {
            S[i][j] = S[i][k] + S[k][j];
          } else {
            double r = S[i][k] + S[k][j];
            S[i][j] = S[i][j] * r / (S[i][j] + r);
          }
        }
      }
    }
  }
  /*
  for (int i=1; i<N; i++) { // 0からiまでの仮想抵抗を求める
    double *x = &S[0][i];
    bool isinfty = (*x == -1);
    for (int j=1; j<i; j++) {
      if (S[0][j] != -1 && S[j][i] != -1) {
        if (isinfty) {
          isinfty = false;
          *x = S[0][j] + S[j][i];
        } else {
          double r = S[0][j] + S[j][i];
          *x = (*x) * r / (r + (*x));
        }
      }
    }
  }
  */
  cout << fixed << setprecision(2) << round(S[0][N-1] * 100)/100 << endl;
}

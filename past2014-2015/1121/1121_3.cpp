// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C
#include <iostream>
#include <string>
using namespace std;

int DP[1010][1010];

int main() {
  int n;
  cin >> n;
  for (auto t=0; t<n; t++) {
    string A, B;
    cin >> A >> B;
    int LA = (int) A.size();
    int LB = (int) B.size();
    fill(&DP[0][0], &DP[0][0]+1010*1010, 0);
    for (auto i=-1; i<LA; i++) {
      for (auto j=-1; j<LB; j++) {
        if (i == -1 || j == -1) {
          DP[i+1][j+1] = 0;
        } else if (A[i] == B[j]) {
          DP[i+1][j+1] = 1 + DP[i][j];
        } else {
          DP[i+1][j+1] = max(DP[i+1][j], DP[i][j+1]);
        }
      }
    }
    cout << DP[LA][LB] << endl;
  }
}

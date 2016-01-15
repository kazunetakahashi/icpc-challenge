#include <iostream>
#include <cmath>
using namespace std;

const int C = 100010;

int L[C];
int A[C];

int main() {
  int n, m;
  cin >> n >> m;
  L[0] = 0;
  for (int i=1; i<=n-1; i++) {
    cin >> L[i];
  }
  for (int i=0; i<m; i++) {
    cin >> A[i];
  }
  for (int i=1; i<=n-1; i++) {
    L[i] += L[i-1];
  }
  int ans = 0;
  int now = 0;
  for (int i=0; i<m; i++) {
    int next = now + A[i];
    ans += abs(L[next] - L[now]);
    now = next;
    ans %= 100000;
  }
  cout << ans << endl;
}

/**
 * File    : JOI_2007_darts.cpp
 * Author  : Kazune Takahashi
 * Created : 2018-3-8 20:45:20
 * Powered by Visual Studio Code
 */

#include <iostream>
#include <iomanip>   // << fixed << setprecision(xxx)
#include <algorithm> // do { } while ( next_permutation(A, A+xxx) ) ;
#include <vector>
#include <string> // to_string(nnn) // substr(m, n) // stoi(nnn)
#include <complex>
#include <tuple>
#include <queue>
#include <stack>
#include <map> // if (M.find(key) != M.end()) { }
#include <set>
#include <random> // random_device rd; mt19937 mt(rd());
#include <cctype>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define DEBUG 0 // change 0 -> 1 if we need debug.

typedef long long ll;

// const int dx[4] = {1, 0, -1, 0};
// const int dy[4] = {0, 1, 0, -1};

// const int C = 1e6+10;
// const ll M = 1000000007;

int N, M;
int P[1010];
vector<int> S;

int main()
{
  while (cin >> N >> M && N && M)
  {
    S.clear();
    for (auto i = 0; i < N; i++)
    {
      cin >> P[i];
    }
    P[N] = 0;
    N++;
    for (auto i = 0; i < N; i++)
    {
      for (auto j = i; j < N; j++)
      {
        int sum = P[i] + P[j];
        if (sum <= M)
        {
          S.push_back(sum);
        }
      }
    }
    sort(S.begin(), S.end());
    int ans = 0;
    int l = 0;
    int r = S.size() - 1;
    while (l <= r)
    {
      int sum = S[l] + S[r];
      if (sum <= M)
      {
        ans = max(ans, sum);
        l++;
      }
      else
      {
        r--;
      }
    }
    cout << ans << endl;
  }
}
/**
 * File    : JOI_2005_triangle_types.cpp
 * Author  : Kazune Takahashi
 * Created : 2018-3-8 21:20:52
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

int cnt[3] = {0, 0, 0};

int main()
{
  int a[3];
  while (cin >> a[0] >> a[1] >> a[2])
  {
    sort(a, a + 3);
    if (a[0] + a[1] <= a[2])
    {
      cout << cnt[0] + cnt[1] + cnt[2] << " "
           << cnt[1] << " " << cnt[0] << " " << cnt[2] << endl;
      return 0;
    }
    int s = a[0] * a[0] + a[1] * a[1];
    int t = a[2] * a[2];
    if (s < t)
    {
      cnt[2]++;
    }
    else if (s == t)
    {
      cnt[1]++;
    }
    else
    {
      cnt[0]++;
    }
  }
}
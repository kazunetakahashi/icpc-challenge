#define DEBUG 1
/**
 * File    : ALDS1_5_B.cpp
 * Author  : Kazune Takahashi
 * Created : 2019-6-26 18:20:31
 * Powered by Visual Studio Code
 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <complex>
#include <tuple>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <functional>
#include <random>
#include <chrono>
#include <cctype>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define maxs(x, y) (x = max(x, y))
#define mins(x, y) (x = min(x, y))
using ll = long long;
void Yes()
{
  cout << "Yes" << endl;
  exit(0);
}
void No()
{
  cout << "No" << endl;
  exit(0);
}
const int MAX_SIZE = 1000010;
class mint
{
public:
  static ll MOD;
  ll x;
  mint() : x(0) {}
  mint(ll x) : x(x % MOD) {}
  mint operator-() const { return x ? MOD - x : 0; }
  mint &operator+=(const mint &a)
  {
    if ((x += a.x) >= MOD)
    {
      x -= MOD;
    }
    return *this;
  }
  mint &operator-=(const mint &a) { return *this += -a; }
  mint &operator*=(const mint &a)
  {
    (x *= a.x) %= MOD;
    return *this;
  }
  mint &operator/=(const mint &a) { return (*this *= power(MOD - 2)); }
  mint operator+(const mint &a) const { return mint(*this) += a; }
  mint operator-(const mint &a) const { return mint(*this) -= a; }
  mint operator*(const mint &a) const { return mint(*this) *= a; }
  mint operator/(const mint &a) const { return mint(*this) /= a; }
  bool operator<(const mint &a) const { return x < a.x; }
  bool operator==(const mint &a) const { return x == a.x; }
  const mint power(ll N)
  {
    if (N == 0)
    {
      return 1;
    }
    else if (N % 2 == 1)
    {
      return *this * power(N - 1);
    }
    else
    {
      mint half = power(N / 2);
      return half * half;
    }
  }
};
ll mint::MOD = 1e9 + 7;
istream &operator>>(istream &stream, mint &a) { return stream >> a.x; }
ostream &operator<<(ostream &stream, const mint &a) { return stream << a.x; }
mint inv[MAX_SIZE];
mint fact[MAX_SIZE];
mint factinv[MAX_SIZE];
void init()
{
  inv[1] = 1;
  for (int i = 2; i < MAX_SIZE; i++)
  {
    inv[i] = (-inv[mint::MOD % i]) * (mint::MOD / i);
  }
  fact[0] = factinv[0] = 1;
  for (int i = 1; i < MAX_SIZE; i++)
  {
    fact[i] = mint(i) * fact[i - 1];
    factinv[i] = inv[i] * factinv[i - 1];
  }
}
mint choose(int n, int k)
{
  if (n >= 0 && k >= 0 && n - k >= 0)
  {
    return fact[n] * factinv[k] * factinv[n - k];
  }
  return 0;
}
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
// const double epsilon = 1e-10;
// const ll infty = 1000000000000000LL;
// const int dx[4] = {1, 0, -1, 0};
// const int dy[4] = {0, 1, 0, -1};

constexpr int infty = 1000000007;

int RES = 0;

void merge(vector<int> &A, int left, int mid, int right)
{
  if (!(0 <= left && left <= mid && mid <= right && right <= static_cast<int>(A.size())))
  {
    throw out_of_range("merge");
  }
  int N = mid - left;
  int M = right - mid;
  vector<int> L(N + 1), R(M + 1);
  copy(A.begin() + left, A.begin() + mid, L.begin());
  copy(A.begin() + mid, A.begin() + right, R.begin());
  L[N] = R[M] = infty;
  int l = 0, r = 0;
  for (auto i = left; i < right; i++)
  {
    ++RES;
    if (L[l] <= R[r])
    {
      A[i] = L[l++];
    }
    else
    {
      A[i] = R[r++];
    }
  }
}

void merge_sort(vector<int> &A, int left, int right)
{
  if (right - left <= 1)
  {
    return;
  }
  int mid = (left + right) / 2;
  merge_sort(A, left, mid);
  merge_sort(A, mid, right);
  merge(A, left, mid, right);
}

void merge_sort(vector<int> &A)
{
  merge_sort(A, 0, A.size());
}

int main()
{
  int N;
  cin >> N;
  vector<int> A(N);
  for (auto i = 0; i < N; i++)
  {
    cin >> A[i];
  }
  merge_sort(A);
  for (auto i = 0; i < N; i++)
  {
    cout << A[i];
    if (i < N - 1)
    {
      cout << " ";
    }
    else
    {
      cout << endl;
    }
  }
  cout << RES << endl;
}
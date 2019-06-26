#define DEBUG 1
/**
 * File    : ALDS1_6_C.cpp
 * Author  : Kazune Takahashi
 * Created : 2019-6-26 14:17:49
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

struct Card
{
  char c;
  int d;

  const bool operator<=(const Card &left) const
  {
    return d <= left.d;
  }
  const bool operator!=(const Card &left) const
  {
    return !(c == left.c && d == left.d);
  }
};

ostream &operator<<(ostream &st, const Card &cd)
{
  return st << cd.c << " " << cd.d;
}
const istream &operator>>(istream &st, Card &cd)
{
  return st >> cd.c >> cd.d;
}

template <typename T>
int partition(vector<T> &A, int p, int r)
{
  if (!(0 <= p && p < r && r <= static_cast<int>(A.size())))
  {
    throw out_of_range("partition error");
  }
  T x = A[r - 1];
  int i = p;
  for (auto j = p; j < r - 1; j++)
  {
    if (A[j] <= x)
    {
      swap(A[i++], A[j]);
    }
  }
  swap(A[i], A[r - 1]);
  return i;
}

template <typename T>
void quick_sort(vector<T> &A, int p, int r)
{
  if (p < r)
  {
    int q = partition(A, p, r);
    quick_sort(A, p, q);
    quick_sort(A, q + 1, r);
  }
}

void stable_sort(vector<Card> &A)
{
  map<int, vector<Card>> M;
  for (auto cd : A)
  {
    M[cd.d].push_back(cd);
  }
  vector<Card> res;
  for (auto mp : M)
  {
    res.insert(res.end(), mp.second.begin(), mp.second.end());
  }
  A = res;
}

int main()
{
  int N;
  cin >> N;
  vector<Card> X;
  for (auto i = 0; i < N; i++)
  {
    Card cd;
    cin >> cd;
    X.push_back(cd);
  }
  vector<Card> QS{X}, SS{X};
  quick_sort(QS, 0, N);
  stable_sort(SS);
  bool st = true;
  for (auto i = 0; i < N; i++)
  {
    if (QS[i] != SS[i])
    {
      st = false;
      break;
    }
  }
  /*
  for (auto i = 0; i < N; i++)
  {
    cerr << "QS[" << i << "] = " << QS[i] << ", SS[" << i << "] = " << SS[i] << endl;
  }
  */
  cout << (st ? "Stable" : "Not stable") << endl;
  for (auto x : QS)
  {
    cout << x << endl;
  }
}
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D
#include <iostream>
#include <tuple>
#include <set>
using namespace std;

/* 解説を読まずにsetを使って解いた。

   前から単純に貪欲に選ぼうとしても、失敗する。
   後ろでどれだけ「緩やかな増加列」が控えているかはわからない。
   この増加列に接続すると最終的に長さの「逆転」が起こるかもしれない。
   
   a[0]からa[i-1]まででできる増加列に、a[i]をつなげることを検討する。
   a[i]を検討するまでに持っておく価値がある列は、
   ・列kは tail_k を末尾とするもののうち最長列(の1つ)である。
   ・length_k < length_j \longleftrightarrow tail_k \leq tail_j をみたしている。
   不等号が崩れる関係になっている k, j があるとすると、どちらかはいらない。
   
   (tail, length) で標準的に整列する。
   各a[i]に対して次の動作を行う。
   tail < a[i] となっている列に接続できるから、この内tailが一番大きい
   もので、lengthも一番大きいものを選ぶ(列k)とする。
   ここにa[i]を接続したものを候補に加える(もとの列も残しておく)。
   加えた列は列k+1になる(または、k+2になって、k+1とtail, lengthが同じ)。
   列k+2との関係は、
   ・tail_{k+1} \leq tail_{k+2} は必ずみたされている
   ・length_{k+1} == length_{k+2} となっているかもしれない
   後者が成立している場合は、列 k+2 を考える価値はないので削除する。

   こうやって最後まで行って最長列が求まる。
   setを使うと、各a[i]でやる動作は全て \log時間なので、
   結局時間計算量はO(n \log n)である。
 */

typedef tuple<int, int> seq; // tail, length
const int infty = 1e9+10;

int main () {
  int n;
  cin >> n;
  int a[100010];
  for (auto i=0; i<n; i++) {
    cin >> a[i];
  }
  set<seq> S;
  S.insert(make_tuple(infty, 100010));
  S.insert(make_tuple(-1, 0));
  for (auto i=0; i<n; i++) {
    auto it = S.lower_bound(make_tuple(a[i], -1));
    it--;
    seq temp = *it;
    get<0>(temp) = a[i];
    int tl = ++get<1>(temp);
    S.insert(temp);
    // cerr << "insert: " << get<0>(temp) << " " << get<1>(temp) << endl;
    it++; it++;
    while (it != S.end() && get<1>(*it) <= tl) { // どうせ1個しか削除しない
      // cerr << "erase: " << get<0>(*it) << " " << get<1>(*it) << endl;
      S.erase(it++);
    }
  }
  auto it = S.end();
  it--; it--;
  cout << get<1>(*it) << endl;
}

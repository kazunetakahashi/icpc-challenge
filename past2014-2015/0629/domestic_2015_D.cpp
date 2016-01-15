/*
  解答方針

  定義：以下では500円玉以外の硬貨を小銭と定義する。

  500円は他の硬貨の額面で割り切れるので、小銭は合計金額で管理しておけば十分である。
  
  dp[x][y][z] = x番目までの商店の利用でy円の小銭とz枚の500円玉を得るための最小金額
  でもなんとかなると思われるが、懸念点がある。
  yのバウンドが厳しい。例えば、
         100円、100円、100円、100円、………、1000円、1000円、1000円、……
  だと、900円のお釣り(->400円のお釣り)を愚直に管理する必要がある。
  あとの1000円ラッシュでこの辺も500円にできるからだ。
  だから少なくとも 500 * 100 / 2 はyのバウンドとして持っておく必要がある。
  先ほどのDPだと、AOJだと通らない可能性が高い。

  (500円玉枚数, -1 * 合計金額)に自然な順序を入れたものの最大元を求める問題だから、
  dp[x][y] = x番目までの商店の利用でy円の小銭を得た時の
             (500円玉枚数, -1 * 合計金額)の最大元
  でなんとかなる。サンプルでも少しもっさりしているが、
  待てない時間というほどではなかろう。
  
  さらなる改善を考察している。
  小銭を愚直に持っておくのをなんとかできないだろうか。
  500円玉の最大枚数を求めるだけなら、おみやげは全部買えば良い。だからこの数字は
  予め知ることができる。
  それを最小の金額で達成しようとしようとすると、難しい。
  1回の買い物でもらえる500円玉は、0枚か1枚である。
  1回の買い物で500円玉が増えるときはかならず買うことになる。
  故に、下3桁が499円以下の商品は必ず買ったほうが良い。
  500円玉が増えない時も、お釣りがもらえるので、
  買ったほうが良いかもしれないし、そうでないかもしれない。
  そうするとやはり、小銭を持ったDPでは…
  
 */

#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;

typedef tuple<int, int> state;
const state minfty = make_tuple(0, -10000000);
const state zero = make_tuple(0, 0);

state dp[110][25000];

int main() {
  int n;
  while (cin >> n && n) {
    int P[110];
    int Q[110]; // 小銭(+500円玉)
    for (auto i=0; i<n; i++) {
      cin >> P[i];
      Q[i] = ((P[i]-1)/1000 + 1) * 1000 - P[i];
    }
    fill(&dp[0][0], &dp[0][0]+110*25000, minfty);
    for (auto x=0; x<n; x++) {
      int kozenibound = min(x * 500, 24999);
      dp[x][0] = max(dp[x][0], zero);
      for (auto y=0; y<=kozenibound; y++) {
        if (dp[x][y] == minfty) continue;
        // cerr << "Visiting : " << "dp[" << x << "][" << y << "] = (" << get<0>(dp[x][y]) << ", " << -get<1>(dp[x][y]) << ")" << endl; 
        dp[x+1][y] = max(dp[x+1][y], dp[x][y]);
        // cerr << "dp[" << x+1 << "][" << y << "] = (" << get<0>(dp[x+1][y]) << ", " << -get<1>(dp[x+1][y]) << ")" << endl; 
        int tgo = get<0>(dp[x][y]);
        int tcost = -1 * get<1>(dp[x][y]);
        int nko = y + Q[x];
        int ngo = tgo;
        int ncost = tcost + P[x];
        if (nko >= 500) {
          nko -= 500;
          ngo++;
        }
        nko = min(nko, 24999);
        dp[x+1][nko] = max(dp[x+1][nko], make_tuple(ngo, (-1) * ncost));
        // cerr << "dp[" << x+1 << "][" << nko << "] = (" << get<0>(dp[x+1][nko]) << ", " << -get<1>(dp[x+1][nko]) << ")" << endl; 
      }
    }
    state ans = minfty;
    for (auto i=0; i<=25000; i++) {
      ans = max(ans, dp[n][i]);
    }
    cout << get<0>(ans) << " " << -1 * get<1>(ans) << endl;
  }
}

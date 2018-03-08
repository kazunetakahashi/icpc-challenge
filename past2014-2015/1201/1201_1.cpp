// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp
/* 解説
   http://judge.u-aizu.ac.jp/onlinejudge/commentary.jsp?id=GRL_3_A
   先生のアドバイス通り、prenumは木のdepthで考えなおした。
   
   最初に、関節点を求まる理由を理解するポイントを書いておく。
   まず、各ノードuを端点とする「辺」は次の3つに分かれている。
   ・親への辺
   ・子への辺
   ・backedge
   lowest[u]は、後者2つの辺だけをたどっていける最上位層である。
   prenum[parent[u]] > lowest[u] ならば、
   parent[u]が取り除かれても、uから上へいける。
   上へ行けるということはすなわち、
   parent[u]が取り除かれて分断された木の連結成分の「もう一方」へ、
   backedgeを利用して移動できるということである。
   その反対に、prenum[parent[u]] \leq lowest[u] ならば、
   parent[u]が取り除かれて分断された木の連結成分の「もう一方」へ移動できない。
   すなわち、元のグラフが分断されているということである。
   
   私はstackを使うのがスキなので、その解法を書く。
   具体的には、depth, parent, lowestの求め方を書く。
   ・depth[u]は、uを訪れたときに、depth[parent[u]]を見て記録すれば良い。
   ・parent[u]は、stackに子を放り込むときに、俺が親だと記録すれば良い。
   stackに子を放り込むときには、真の親が確定していないが、
   今やっているのは深さ優先探索であるので、
   間違いなく言えることは、最後に俺が親だと言った頂点が親である。
   気にせず更新し続ければその頂点を訪れた時点でparentが確定する。
   ・lowest[u]が一番難しい。まず、lowest[u]を求めるタイミングが大事である。
   実習資料にも書かれている方法でやる。
   頂点を訪れた際、子をstackに入れる前に、自分自身を入れる。
   すると、自分の子をすべて訪れた時点で、自分自身を
   もう一度訪れることになる。この2度目の訪問が、記録するタイミングである。
   このタイミングが「訪問が終了する」タイミングである。
   3度目以降に訪れるのは「子としてスタックに入れたものの、実際は
   その子は自分の子ではなかった」という場合である。これは(通常通り)弾く。
   次に、どのようにlowest[u]を更新するかを書く。
   辺は先ほど書いたとおり、
   ・親への辺
   ・子への辺
   ・backedge
   の3つにわかれている。parent[u]を記録しているので、親への辺は
   即座に見分けが付く。問題は子への辺とbackedgeの見分け方である。
   lowest[u]は「訪問が終了する」タイミングで記録するのだから、
   はじめにlowest[u]にダミーの数値を入れておけばよい。
   すなわち、uを端点とする辺のもう一方の端点をchildとすると、
   「lowest[child]がダミーであるならば、この辺は必ずbackedge」
   となる。depth[child]を考慮する。
   lowest[child]がダミーでないならば、
   backedgeか子への辺のどちらかは判定がつかない。しかし、気にする必要はない。
   この場合backedgeをたどっても得することがないからである。
   下方向へ向かうのだから、backedgeをたどらずとも
   必ず到達する。子だと思ってlowest[child]をdepth[child]の代わりに
   採用しても、結果は変わらない。その結果は既に確定している真の子の
   lowestにきちんと反映されているからである。
 */

#include <iostream>
#include <vector>
#include <stack>
#include <set>
using namespace std;

vector<int> V[100010];

int main() {
  int N; // 頂点の数
  int M; // 辺の数
  cin >> N >> M;
  for (auto i=0; i<M; i++) {
    int s, t;
    cin >> s >> t;
    V[s].push_back(t);
    V[t].push_back(s);
  }
  // 深さ優先探索
  stack<int> S;
  int visited[100010];
  int depth[100010];
  int parent[100010];
  int lowest[100010];
  S.push(0);
  parent[0] = -1;
  fill(visited, visited+N, 0);
  fill(lowest, lowest+N, -1);
  while (!S.empty()) {
    int node = S.top();
    S.pop();
    if (visited[node] == 0) {
      visited[node]++;
      depth[node] = ((parent[node] >= 0) ? depth[parent[node]]+1 : 0);
      S.push(node); // 訪問を終えたらlowestを求めるためにまた入れる。
      for (unsigned int i=0; i<V[node].size(); i++) {
        int child = V[node][i];
        if (!visited[child]) {
          S.push(child);
          parent[child] = node; // 何回も書き換わるかもしれないが、最後に更新したものが正しい親である。
        }
      }
    } else if (visited[node] == 1) {
      visited[node]++;
      lowest[node] = depth[node];
      for (unsigned int i=0; i<V[node].size(); i++) {
        int child = V[node][i];
        if (child != parent[node]) {
          if (lowest[child] == -1) { // この場合backedge
            lowest[node] = min(lowest[node], depth[child]);
          } else {
            lowest[node] = min(lowest[node], lowest[child]);
          }
        }
      }
    }
  }
  // 関節点を求める。
  set<int> A;
  // rootが関節点か。
  int root_children = 0;
  for (auto i=0; i<N; i++) {
    if (parent[i] == 0) root_children++;
  }
  if (root_children >= 2) { 
    A.insert(0);
  }
  // その他の辺は関節点か。
  for (auto i=1; i<N; i++) {
    if (parent[i] != 0 && depth[parent[i]] <= lowest[i]) {
      A.insert(parent[i]);
    }
  }
  // 出力
  for (auto it=A.begin(); it!=A.end(); it++) {
    cout << *it << endl;
  }
}

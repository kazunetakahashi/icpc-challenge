#include <iostream>
#include <iomanip> // << fixed << setprecision(xxx)
#include <algorithm> // do { } while ( next_permutation(A, A+xxx) ) ;
#include <vector>
#include <string> // to_string(nnn) // substr(m, n) // stoi(nnn)
#include <complex>
#include <tuple> // get<n>(xxx)
#include <queue>
#include <stack>
#include <map> // if (M.find(key) != M.end()) { }
#include <set> // S.insert(M);
// if (S.find(key) != S.end()) { }
// for (auto it=S.begin(); it != S.end(); it++) { }
// auto it = S.lower_bound(M);
#include <random> // random_device rd; mt19937 mt(rd());
#include <cctype>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib> // atoi(xxx)
using namespace std;

#define DEBUG 0 // change 0 -> 1 if we need debug.
// insert #if<tab> by my emacs. #if DEBUG == 1 ... #end

typedef long long ll;

// const int dx[4] = {1, 0, -1, 0};
// const int dy[4] = {0, 1, 0, -1};

// const int C = 1e6+10;
// const ll M = 1000000007;

class UnionFind {
public:
  int N;
  int* root;
  int* rank;

  UnionFind(int n) : N(n) {
    root = new int[N];
    rank = new int[N];
    for (auto i = 0; i < N; ++i) {
      root[i] = i;
      rank[i] = 0;
    }
  }

  ~UnionFind() {
    delete[] root;
    delete[] rank;
  }

  int find(int x) {
    if (root[x] == x) return x;
    return root[x] = find(root[x]);
  }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
      root[x] = y;
    } else {
      root[y] = x;
      if (rank[x] == rank[y]) ++(rank[x]);
    }
  }

  bool same(int x, int y) {
    return (find(x) == find(y));
  }
};

class Edge {
public:
  int src, dst;
  ll cost;
  Edge(int s, int d, ll c)
    : src(s), dst(d), cost(c) {}
  friend bool operator<(const Edge& x, const Edge& y) {
    return x.cost < y.cost;
  }
};

typedef Edge State;

class Graph {
public:
  static const ll infty = 100000000000000000;
  int N;
  vector<Edge>* V;
  vector<Edge> W;
  // dfs, bfs 共通
  int* component;
  // dfs
  vector<int> dfs_start;
  int* dfs_visited;
  int* dfs_from;
  int dfs_time;
  int* dfs_time_d;
  int* dfs_time_f;
  // bfs
  vector<int> bfs_start;
  int* bfs_visited;
  int* bfs_from;
  ll* bfs_dist;
  // kruskal
  ll kruskal_cost;
  vector<Edge>* kruskal_V;
  vector<Edge> kruskal_W;
  // bellman_ford, dijkstra
  set<int> sh_start;
  ll** sh_dist;
  int** sh_prev;

  Graph(int n)
    : N(n), dfs_time(0), kruskal_cost(-1) {
    V = new vector<Edge>[N];
    component = new int[N];
    dfs_visited = new int[N];
    fill(dfs_visited, dfs_visited+N, 0);
    dfs_from = new int[N];
    dfs_time_d = new int[N];
    dfs_time_f = new int[N];
    bfs_visited = new int[N];
    fill(bfs_visited, bfs_visited+N, 0);
    bfs_from = new int[N];    
    bfs_dist = new ll[N];
    kruskal_V = new vector<Edge>[N];
    sh_dist = new ll*[N];
    sh_prev = new int*[N];    
  }
  ~Graph() {
    delete[] V;
    delete[] component;
    delete[] dfs_visited;
    delete[] dfs_from;
    delete[] dfs_time_d;
    delete[] dfs_time_f;
    delete[] bfs_visited;
    delete[] bfs_from;
    delete[] bfs_dist;
    delete[] kruskal_V;
    for (auto x : sh_start) {
      delete[] sh_dist[x];
      delete[] sh_prev[x];
    }
    delete[] sh_dist;
    delete[] sh_prev;
  }

  void add_edge(int src, int dst, ll cost = 1) {
    Edge e(src, dst, cost);
    V[src].push_back(e);
    W.push_back(e);
  }

  bool is_connected(int s, int t) {
    if (dfs_visited[s] == 0) {
      dfs(s);
    }
    if (dfs_visited[t] == 0) {
      dfs(t);
    }
    return (component[s] == component[t]);
  }

  void dfs(int start) {
    stack<State> S;
    S.push(State(-1, start, 0));
    dfs_start.push_back(start);
    while (!S.empty()) {
      State s = S.top();
      S.pop();
      if (dfs_visited[s.dst] == 0) {
        dfs_visited[s.dst] = 1;
        dfs_time_d[s.dst] = dfs_time++;
        dfs_from[s.dst] = s.src;
        component[s.dst] = start;
        S.push(s);
        for (auto x : V[s.dst]) {
          if (dfs_visited[x.dst] == 0) {
            S.push(State(s.dst, x.dst, s.cost + x.cost));
          }
        }
      } else if (dfs_visited[s.dst] == 1) {
        dfs_visited[s.dst] = 2;
        dfs_time_f[s.dst] = dfs_time++;
      }
    }
  }

  void bfs() {
    assert(!bfs_start.empty());
    queue<State> Q;
    for (auto x : bfs_start) {
      Q.push(State(-1, x, 0));
    }
    while (!Q.empty()) {
      State s = Q.front();
      Q.pop();
      if (bfs_visited[s.dst] == 0) {
        bfs_visited[s.dst] = 1;
        bfs_from[s.dst] = s.src;
        bfs_dist[s.dst] = s.cost;
        component[s.dst] = bfs_start[0];
        for (auto x : V[s.dst]) {
          if (bfs_visited[x.dst] == 0) {
            Q.push(State(s.dst, x.dst, s.cost + x.cost));
          }
        }
      }
    }
  }

  int kruskal() {
    if (kruskal_cost != -1) return kruskal_cost;
    sort(W.begin(), W.end());
    UnionFind u(N);
    int kruskal_cost = 0;
    for (auto e : W) {
      if (!u.same(e.src, e.dst)) {
        kruskal_V[e.src].push_back(e);
        kruskal_W.push_back(e);
        u.unite(e.src, e.dst);
        kruskal_cost += e.cost;
      }
    }
    return kruskal_cost;
  }

  void new_sh_dist(int i) {
    if (sh_start.find(i) == sh_start.end()) {
      sh_dist[i] = new ll[N];
      sh_prev[i] = new int[N];
      sh_start.insert(i);
    }
  }
  
  void bellman_ford(int s) {
    new_sh_dist(s);
    for (auto i = 0; i < N; ++i) {
      sh_dist[s][i] = infty;
    }
    sh_dist[s][s] = 0;
    sh_prev[s][s] = -1;
    while (true) {
      bool update = false;
      for (auto e : W) {
        if (sh_dist[s][e.src] != infty
            && sh_dist[s][e.dst] > sh_dist[s][e.src] + e.cost) {
          sh_dist[s][e.dst] = sh_dist[s][e.src] + e.cost;
          sh_prev[s][e.dst] = e.src;
          update = true;
        }
      }
      if (!update) break;
    }
  }

  vector<int> get_shortest_path(int s, int t) {
    vector<int> path;
    for (; t != -1; t = sh_prev[s][t]) path.push_back(t);
    reverse(path.begin(), path.end());
    return path;
  }
  
};

int main () {
  int n;
  cin >> n;
  Graph g(n);
  for (auto i = 0; i < n; ++i) {
    int u, k;
    cin >> u >> k;
    for (auto j = 0; j < k; ++j) {
      int v;
      ll c;
      cin >> v >> c;
      g.add_edge(u, v, c);
    }
  }
  g.bellman_ford(0);
  for (auto i = 0; i < g.N; ++i) {
    cout << i << " " << g.sh_dist[0][i] << endl;
  }
}

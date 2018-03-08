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
  int src, dst, cost;
  Edge(int s, int d, int c)
    : src(s), dst(d), cost(c) {}
  friend bool operator<(const Edge& x, const Edge& y) {
    return x.cost < y.cost;
  }
};

typedef Edge State;

class Graph {
public:
  int N;
  vector<Edge>* V;
  vector<Edge> W;
  // dfs, bfs 共通
  int* component;
  // dfs
  int* dfs_visited;
  int* dfs_from;
  int dfs_time;
  int* dfs_time_d;
  int* dfs_time_f;
  // bfs
  int* bfs_visited;
  int* bfs_from;
  int* bfs_dist;
  // kruskal
  int kruskal_cost;
  vector<Edge>* kruskal_V;
  vector<Edge> kruskal_W;

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
    bfs_dist = new int[N];
    kruskal_V = new vector<Edge>[N];
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
  }
  

  void add_edge(int src, int dst, int cost = 1) {
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

  void bfs(vector<int> start) {
    assert(!start.empty());
    queue<State> Q;
    for (auto x : start) {
      Q.push(State(-1, x, 0));
    }
    while (!Q.empty()) {
      State s = Q.front();
      Q.pop();
      if (bfs_visited[s.dst] == 0) {
        bfs_visited[s.dst] = 1;
        bfs_from[s.dst] = s.src;
        bfs_dist[s.dst] = s.cost;
        component[s.dst] = start[0];
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
};

int main () {
  int n;
  cin >> n;
  Graph g(n);
  for (auto i = 0; i < n; ++i) {
    for (auto j = 0; j < n; ++j) {
      int a;
      cin >> a;
      if (a != -1) {
        g.add_edge(i, j, a);
      }
    }
  }
  cout << g.kruskal() << endl;
}

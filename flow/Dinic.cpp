可以慢慢增流，再叫一次flow.solve()會輸出增加的流量。
struct Dinic{
  static const int MAXV = 10005;
  typedef ll type;
#define inf 9999999999999999ll
  struct Edge{
    int from, to;
    type cap, flow; int ori;
  };
  int N, s, t;
  vector<Edge> edges;
  vector<int> G[MAXV];
  bool vis[MAXV];
  int d[MAXV];
  int cur[MAXV];
  void init(int _n){
    N = _n + 2; s = _n + 1; t = _n + 2;
    edges.clear();
    for (int i = 0; i <= N; i++) G[i].clear();
  }
  void add_edge(int from, int to, type cap){
    edges.push_back(Edge{from, to, cap, 0, 1});
    edges.push_back(Edge{to, from, 0, 0, 0});
    int m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }
  bool BFS(){
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(s);
    d[s] = 0; vis[s] = 1;
    while (!q.empty()){
      int x = q.front();
      q.pop();
      for (int i = 0; i < G[x].size(); i++){
        Edge &e = edges[G[x][i]];
        if (!vis[e.to] && e.cap > e.flow){
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          q.push(e.to);
        }
      }
    }
    return vis[t];
  }
  type DFS(int x, type a){
    if (x == t || a == 0) return a;
    type flow = 0, f;
    for (int &i = cur[x]; i < G[x].size(); i++){
      Edge &e = edges[G[x][i]];
      if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0){
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a == 0) break;
      }
    }
    return flow;
  }
  type solve(){
    type flow = 0;
    while (BFS()){
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, inf);
    }
    return flow;
  }
} flow;

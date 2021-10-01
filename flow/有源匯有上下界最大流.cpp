dinic加
int def[210];
memset(def, 0, sizeof(def)); // init()
void build(int ss, int tt, int down, int up)
{ //從s到t的邊，流量限制在區間[down,up]
    add_edge(ss, tt, up - down);
    def[ss] += down, def[tt] -= down;
}
int solveMax(int st, int de){
  int sum = 0;
  for (int i = 1; i <= N; i++){
      if (def[i] > 0)
        sum += def[i], add_edge(i, t, def[i]);
      if (def[i] < 0) add_edge(s, i, -def[i]);
  }
  add_edge(de, st, 1 << 30);
  if (solve() == sum){
      G[s].clear(); G[t].clear();
      s = st; t = de;
      return solve();
  } else return -1; //無可行解
}

設輸入的源點/匯點為s/t
直接跑dinic，cap為up-down，加邊u, v時紀錄def[u]加down，def[v]減down (def:out-in)
令所有def大於0的總和為sum。
加入t到s無限大的邊。
對於與源點/匯點(n+1/n+2)連線的邊的容量和代表著全圖的流量總和。流滿sum時才能平衡。
判斷最大流是否等於sum，若是，則將源點/匯點(n+1/n+2)邊清空，源點/匯點設為s,t，再輸出最大流。
無源匯: 跑Dinic，判斷最大流是否等於sum。


// 1<=點數<=202,1<=邊數<=999
#define MAXN 70005
int sp, tp, cnt, head[210], nxt[MAXN], to[MAXN], cap[MAXN], dis[1010], st, de, def[210], n;
inline void addedge(int u, int v, int p){
    nxt[++cnt] = head[u], head[u] = cnt, to[cnt] = v, cap[cnt] = p;
    nxt[++cnt] = head[v], head[v] = cnt, to[cnt] = u, cap[cnt] = 0;
}
inline bool bfs(){
    int u, e, v;
    queue<int> que;
    memset(dis, -1, sizeof(dis));
    que.push(sp), dis[sp] = 0;
    while (!que.empty()){
        u = que.front(), que.pop();
        for (int e = head[u]; e; e = nxt[e]){
            if (cap[e] > 0 && dis[v = to[e]] == -1){
                dis[v] = dis[u] + 1, que.push(v);
                if (v == tp)
                    return true;
            }
        }
    }
    return false;
}
inline int dfs(const int &u, const int &flow){
    if (u == tp)
        return flow;
    int res = 0, v, flw;
    for (int e = head[u]; e; e = nxt[e]){
        if (cap[e] > 0 && dis[u] < dis[v = to[e]]){
            flw = dfs(v, min(cap[e], flow - res));
            if (flw == 0)
                dis[v] = -1;
            cap[e] -= flw, cap[e ^ 1] += flw;
            res += flw;
            if (res == flow)
                break;
        }
    }
    return res;
}
inline int dinic(int sp, int tp){
    int ans = 0;
    while (bfs())
        ans += dfs(sp, 1 << 30);
    return ans;
}
void init(int _n, int _st, int _de){
    n = _n, st = _st, de = _de;
    cnt = 1;
    sp = tp = 0;
    memset(head, -1, sizeof(head));
    memset(def, 0, sizeof(def));
}
void build(int s, int t, int down, int up)
{ //從s到t的邊，流量限制在區間[down,up]
    addedge(s, t, up - down);
    def[s] += down, def[t] -= down;
}
int solve(){
    int sum = 0;
    sp = n + 1, tp = n + 2;
    for (int i = 1; i <= n; i++){
        if (def[i] > 0)
            sum += def[i], addedge(i, tp, def[i]);
        if (def[i] < 0)
            addedge(sp, i, -def[i]);
    }
    addedge(de, st, 1 << 30);
    if (dinic(sp, tp) == sum){
        head[sp] = 0, head[tp] = 0;
        sp = st;
        tp = de;
        return dinic(sp, tp);
    }
    else return -1; //無可行解
}

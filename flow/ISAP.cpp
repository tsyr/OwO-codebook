//不能慢慢增流！！要增流請用Dinic。
#define SZ(c) ((int)(c).size())
struct Maxflow{
    typedef int type;
    static const int MAXV = 20010;
    type INF = 1000000; // type改變這裡也要跟著變
    struct Edge{
        int v, r;
        type c;
        Edge(int _v, type _c, int _r) : 
           v(_v), c(_c), r(_r) {}
    };
    int s, t;
    vector<Edge> G[MAXV * 2];
    int iter[MAXV *2], d[MAXV *2], gap[MAXV *2], tot;
    void init(int x){
        tot = x + 2;
        s = x + 1, t = x + 2;
        for (int i = 0; i <= tot; i++){
            G[i].clear();
            iter[i] = d[i] = gap[i] = 0;
        }
    }
    void addEdge(int u, int v, type c){
        G[u].push_back(Edge(v, c, SZ(G[v])));
        G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
    }
    type dfs(int p, type flow){
        if (p == t)
            return flow;
        for (int &i = iter[p]; i < SZ(G[p]); i++){
            Edge &e = G[p][i];
            if (e.c > 0 && d[p] == d[e.v] + 1){
                type f = dfs(e.v, min(flow, e.c));
                if (f){
                    e.c -= f;
                    G[e.v][e.r].c += f;
                    return f;
                }
            }
        }
        if ((--gap[d[p]]) == 0) d[s] = tot;
        else{
            d[p]++;
            iter[p] = 0;
            ++gap[d[p]];
        }
        return 0;
    }
    type solve(){
        type res = 0;
        gap[0] = tot;
        for (res = 0; d[s] < tot; res += dfs(s, INF));
        return res;
    }
} flow;

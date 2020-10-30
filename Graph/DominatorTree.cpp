對於有向圖 G（可能有環），其中起點 r 可以到達所有點，當 u 是所有到達 v 的路徑的必經點時，稱 u支配 v。可以構建支配樹，其中每個點被所有它的祖先支配，又支配它子樹中的結點。
const int MAXN = 100010;
#define REP(i, s, e) for (int i = (s); i <= (e); i++)
#define REPD(i, s, e) for (int i = (s); i >= (e); i--)
struct DominatorTree{
    int n, m, s; //點數n，邊數m，起點為s
    vector<int> g[MAXN], pred[MAXN];
    vector<int> cov[MAXN];
    int dfn[MAXN], nfd[MAXN], ts;
    int par[MAXN];
    int sdom[MAXN], idom[MAXN];
    //支配樹上i的parent為idom[i]，若無parent就會是0
    int mom[MAXN], mn[MAXN];
    inline bool cmp(int u, int v) { return dfn[u] < dfn[v]; }
    int eval(int u){
        if (mom[u] == u)
            return u;
        int res = eval(mom[u]);
        if (cmp(sdom[mn[mom[u]]], sdom[mn[u]]))
            mn[u] = mn[mom[u]];
        return mom[u] = res;
    }
    void init(int _n, int _m, int _s){
        ts = 0;
        n = _n; m = _m; s = _s;
        REP(i, 1, n)
        g[i].clear(),
            pred[i].clear();
    }
    void addEdge(int u, int v){
        g[u].push_back(v);
        pred[v].push_back(u);
    }
    void dfs(int u){
        ts++;
        dfn[u] = ts;
        nfd[ts] = u;
        for (int v : g[u])
            if (dfn[v] == 0){
                par[v] = u;
                dfs(v);
            }
    }
    void build(){
        REP(i, 1, n){
            dfn[i] = nfd[i] = 0;
            cov[i].clear();
            mom[i] = mn[i] = sdom[i] = i;
        }
        dfs(s);
        REPD(i, n, 2){
            int u = nfd[i];
            if (u == 0)
                continue;
            for (int v : pred[u])
                if (dfn[v]){
                    eval(v);
                    if (cmp(sdom[mn[v]], sdom[u]))
                        sdom[u] = sdom[mn[v]];
                }
            cov[sdom[u]].push_back(u);
            mom[u] = par[u];
            for (int w : cov[par[u]]){
                eval(w);
                if (cmp(sdom[mn[w]], par[u]))
                    idom[w] = mn[w];
                else
                    idom[w] = par[u];
            }
            cov[par[u]].clear();
        }
        REP(i, 2, n){
            int u = nfd[i];
            if (u == 0)
                continue;
            if (idom[u] != sdom[u])
                idom[u] = idom[idom[u]];
        }
    }
} domT;

struct BCC{
    struct edge{ int u, v; };
    int dfs_clock;
    int bcc_cnt;           //Number of bcc
    vector<int> bcc[maxn]; //1~bcc_cnt
    int pre[maxn], iscut[maxn], bccno[maxn];

    vector<int> v[maxn];
    vector<edge> S;

    void init(int _n){
        for (int i = 0; i <= _n; i++)
            v[i].clear();
        S.clear();
    }
    void add_edge(int x, int y){
        v[x].push_back(y);
        v[y].push_back(x);
        S.push_back(edge{x, y});
    }
    int dfs_bcc(int u, int fa){
        int lowu = pre[u] = ++dfs_clock;
        int child = 0;
        for (int i = 0; i < v[u].size(); i++){
            int x = v[u][i];
            if (!pre[x]){
                child++;
                S.push_back(edge{u, x});
                int lowx = dfs_bcc(x, u);
                lowu = min(lowu, lowx);
                if (lowx >= pre[u]){
                    bcc_cnt++;
                    iscut[u] = 1;
                    while (1){
                        edge now = S.back();
                        S.pop_back();
                        if (bccno[now.u] != bcc_cnt) {
                            bccno[now.u] = bcc_cnt;
                        bcc[bcc_cnt].push_back(now.u);
                        }
                        if (bccno[now.v] != bcc_cnt){
                            bccno[now.v] = bcc_cnt;
                        bcc[bcc_cnt].push_back(now.v);
                        }
                        if (now.u == u && now.v == x)
                            break;
                    }
                }
            }
            else if (pre[x] < pre[u] && x != fa) {
                S.push_back(edge{u, x});
                lowu = min(lowu, pre[x]);
            }
        }
        if (fa < 0 && child == 1)
            iscut[u] = 0;
        return lowu;
    }
    void solve(int nn)  {
        memset(pre, 0, sizeof(pre));
        memset(iscut, 0, sizeof(iscut));
        memset(bccno, 0, sizeof(bccno));
        dfs_clock = bcc_cnt = 0;
        for (int i = 0; i < nn; i++)
            bcc[i].clear();
        for (int i = 0; i < nn; i++) { 
            //Note that you may want to change the range of index.
            if (!pre[i])
                dfs_bcc(i, -1);
        }
    }
} graph;

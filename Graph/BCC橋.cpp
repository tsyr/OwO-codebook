struct BCC{
    int n, m;
    vector<int> v[maxn];
    int dfs_clock;
    int bcc_cnt;           //Number of bcc
    vector<int> bcc[maxn]; //1~bcc_cnt
    map<int, bool> bridge[maxn];
    // Using bridge[i][j] to record the edge connects point i and point j.
    // complexity O(log)
    int pre[maxn], bccno[maxn];
    bool book[maxn];
    void init(int _n){
        n = _n;
        for (int i = 1; i <= n; i++)
            v[i].clear();
    }
    void add_edge(int x, int y){
        v[x].push_back(y);
        v[y].push_back(x);
    }
    int dfs_bcc(int u, int fa){
        int lowu = pre[u] = ++dfs_clock;
        for (int i = 0; i < v[u].size(); i++){
            int x = v[u][i];
            if (!pre[x]){
                int lowx = dfs_bcc(x, u);
                lowu = min(lowu, lowx);
                if (lowx > pre[u]) {
                    bridge[u][x] = 1;
                    bridge[x][u] = 1;
                }
            }
            else if (pre[x] < pre[u] && x != fa)
                lowu = min(lowu, pre[x]);
        }
        return lowu;
    }
    void dfs_getbcc(int now){
        book[now] = 1;
        bccno[now] = bcc_cnt;
        bcc[bcc_cnt].push_back(now);
        for (int i = 0; i < v[now].size(); i++){
            if (!book[v[now][i]] && !bridge[now][v[now][i]])
                dfs_getbcc(v[now][i]);
        }
    }
    void find_bcc(int nn){
        memset(pre, 0, sizeof(pre));
        memset(bccno, 0, sizeof(bccno));
        dfs_clock = bcc_cnt = 0;
        for (int i = 1; i <= nn; i++)
            bridge[i].clear();
        for (int i = 1; i <= nn; i++)
            bcc[i].clear();
        for (int i = 1; i <= nn; i++)
        { //Note that you may want to change the node range.
            if (!pre[i])
                dfs_bcc(i, -1);
        }
        memset(book, 0, sizeof(book));
        for (int i = 1; i <= nn; i++){
            if (!book[i]) {
                bcc_cnt++;
                dfs_getbcc(i);
            }
        }
    }
} graph;

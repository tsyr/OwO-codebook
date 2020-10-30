/*
    最大匹配+最小邊涵蓋=最大獨立集合+最小點涵蓋=V(general)
    最大匹配=最小點涵蓋(二分圖)
    DAG最小路徑覆蓋=點數-最大匹配
*/
#define MAX_V 1005 //max(|U|,|V|)
struct Bipartite_Matching {
    int V;
    vector<int> G[MAX_V];  //V -> U
    vector<int> rG[MAX_V]; //V -> U 可註解掉
    int match_u[MAX_V];    //match[U]=V
    int match_v[MAX_V];    //match[V]=U 可註解掉
    bool used[MAX_V];      //used[V] are used for dfs

    bool r[MAX_V], c[MAX_V]; //最小點覆蓋用，所求點i為r[i]=0或者c[i]=1
    void INIT(int x){
        V = x;
        for (int i = 0; i < MAX_V; i++){
            G[i].clear();
            rG[i].clear(); //可註解掉
        }
    }
    void add_edge(int x, int y){
        G[x].push_back(y);
        rG[y].push_back(x); //可註解掉
    }
    bool dfs(int now){
        used[now] = 1;
        r[now] = 1; //最小點覆蓋
        for (int i = 0; i < G[now].size(); i++){
            int x = G[now][i], w = match_u[x];
            c[x] = 1; //最小點覆蓋
            if (w == -1 || (!used[w] && dfs(w))){
                match_u[x] = now;
                match_v[now] = x; //可註解掉
                return 1;
            }
        }
        return 0;
    }
    int bipartite_matching(){
        int res = 0;
        memset(match_u, -1, sizeof(match_u));
        memset(match_v, -1, sizeof(match_v)); //可註解掉
        for (int i = 0; i < V; i++){
            if (match_v[i] == -1) { //可註解掉
                memset(used, 0, sizeof(used));
                if (dfs(i))
                    res++;
            }
        }
        return res;
    }
    void min_point_cover() {
        for (int i = 0; i < V; i++)
            r[i] = c[i] = 0;
        for (int i = 0; i < V; i++) {
            memset(used, 0, sizeof(used));
            if (match_v[i] == -1)
                dfs(i);
        }
    }
} BM;

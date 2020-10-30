int n, m;
vector<int> v[maxn], rv[maxn]; //都要連!!
int scc_cnt; //Number of scc 
int used[maxn], sccno[maxn];
vector<int> vs;

void dfs1(int now){
    used[now] = 1;
    for (int i = 0; i < v[now].size(); i++) {
        if (!used[v[now][i]])
            dfs1(v[now][i]);
    }
    vs.push_back(now);
}
void dfs2(int now){
    used[now] = 1;
    sccno[now] = scc_cnt;
    for (int i = 0; i < rv[now].size(); i++){
        if (!used[rv[now][i]])
            dfs2(rv[now][i]);
    }
}
void find_scc(int nn){
    memset(sccno, 0, sizeof(sccno));
    scc_cnt = 0;
    memset(used, 0, sizeof(used));
    for (int i = 1; i <= nn; i++){ 
        //Note that you may want to change the node range.
        if (!used[i]) dfs1(i);
    }
    memset(used, 0, sizeof(used));
    for (int i = vs.size() - 1; i >= 0; i--){
        if (!used[vs[i]]){
            scc_cnt++;
            dfs2(vs[i]);
        }
    }
    vs.clear();
}

/*
i表示第i個敘述為真，i+n表示第i個敘述為假
sccno[i]==sccno[i+n]相等=>炸掉
sccno[i]>sccno[i+n] true
*/

struct MDST{
#define MAXN 1010
#define MAXM 1000010
#define INF INT_MAX
  struct Edge{ int from, to, cost; };
  int n, m;
  Edge edge[MAXM];
  int pre[MAXN]; //存儲父節點
  int vis[MAXN]; //標記作用
  int id[MAXN];  //id[i]記錄節點i所在環的編號
  int in[MAXN];  //in[i]記錄i入邊中最小的權值
  void init(int _n){
    n = _n;
    m = 0;
  }
  void addEdge(int u, int v, int c) { edge[m++] = Edge{u, v, c}; }
  int zhuliu(int root) { //root根 n點數 m邊數
    int res = 0, u, v;
    while (1){
      for (int i = 0; i < n; i++)
        in[i] = INF; //初始化
      for (int i = 0; i < m; i++){
        Edge E = edge[i];
        if (E.from != E.to && E.cost < in[E.to]){
          pre[E.to] = E.from; //記錄前驅
          in[E.to] = E.cost;  //更新
        }
      }
      for (int i = 0; i < n; i++)
        if (i != root && in[i] == INF)
          return -1; //有其他孤立點 則不存在最小樹狀圖
      //找有向環
      int tn = 0; //記錄當前查找中 環的總數
      memset(id, -1, sizeof(id));
      memset(vis, -1, sizeof(vis));
      in[root] = 0; //根
      for (int i = 0; i < n; i++){
        res += in[i]; //累加
        v = i;
        //找圖中的有向環 三種情況會終止while迴圈
        //1,直到出現帶有同樣標記的點說明成環
        //2,節點已經屬於其他環
        //3,遍歷到根
        while (vis[v] != i && id[v] == -1 && v != root)
        {
          vis[v] = i; //標記
          v = pre[v]; //一直向上找
        }//因為找到某節點屬於其他環  或者 遍歷到根  說明當前沒有找到有向環
        if (v != root && id[v] == -1) { //必須上述查找已經找到有向環
          for (int u = pre[v]; u != v; u = pre[u])
            id[u] = tn; //記錄節點所屬的 環編號
          id[v] = tn++; //記錄節點所屬的 環編號  環編號累加
        }
      }
      if (tn == 0)
        break; //不存在有向環
      //可能存在獨立點
      for (int i = 0; i < n; i++)
        if (id[i] == -1)
          id[i] = tn++; //環數累加
      //對有向環縮點  和SCC縮點很像吧
      for (int i = 0; i < m; i++) {
        v = edge[i].to;
        edge[i].from = id[edge[i].from];
        edge[i].to = id[edge[i].to];
        //<u, v>有向邊
        //兩點不在同一個環 u到v的距離為 邊權cost - in[v]
        if (edge[i].from != edge[i].to)
          edge[i].cost -= in[v]; //更新邊權值 繼續下一條邊的判定
      }
      n = tn; //以環總數為下次操作的點數 繼續執行上述操作 直到沒有環
      root = id[root];
    }
    return res;
  }
} graph;

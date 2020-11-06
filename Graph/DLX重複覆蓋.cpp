#define N 100010
#define M 1010
struct DancingLink{
  int n, s, ansd; //列數 節點總數，(重複覆蓋)答案存在ansd
  int S[M],A[M],H[M];//S[]該列節點總數A[]答案H[]行首指標
  int L[N], R[N], U[N], D[N]; //L[],R[],U[],D[] 上下左右
  int X[M], C[M], vis[M];     //X[] C[] 行列編號
  void init(int n){ //初始化
    this->n = n;
    for (int i = 0; i <= n; i++)
      U[i] = i, D[i] = i, L[i] = i - 1, R[i] = i + 1;
    R[n] = 0, L[0] = n;
    s = n + 1;
    memset(S, 0, sizeof(S));
    memset(H, -1, sizeof(H));
    ansd = INT_MAX;
  }
  void DelCol(int c){ //刪除列
    for (int i = D[c]; i != c; i = D[i])
      L[R[i]] = L[i], R[L[i]] = R[i];
  }
  void ResCol(int c) { //恢復列
    for (int i = U[c]; i != c; i = U[i])
      L[R[i]] = R[L[i]] = i;
  }
  void AddNode(int r, int c) { //新增節點
    ++S[c], C[++s] = c, X[s] = r;
    D[s] = D[c], U[D[c]] = s, U[s] = c, D[c] = s;
    if (H[r] < 0)
      H[r] = L[s] = R[s] = s; //行首節點
    else
      R[s]=R[H[r]],L[R[H[r]]]=s,L[s]=H[r],R[H[r]]=s;
  }
  int f(){
    int ret = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = R[0]; i; i = R[i])
      if (!vis[i]) {
        ret++;
        vis[i] = 1;
        for (int j = D[i]; j != i; j = D[j])
          for (int k = R[j]; k != j; k = R[k])
            vis[C[k]] = 1;
      }
    return ret;
  }
  void dfs(int d){ //深度，深搜遍歷
    if (d + f() >= ansd)
      return;
    if (!R[0]){
      if (d < ansd)
        ansd = d;
      return;
    }
    int c = R[0];
    for (int i = R[0]; i; i = R[i])
      if (S[i] < S[c])
        c = i;
    for (int i = D[c]; i != c; i = D[i]) {
      DelCol(i);
      A[d] = X[i];
      for (int j = R[i]; j != i; j = R[j])
        DelCol(j);
      dfs(d + 1);
      for (int j = L[i]; j != i; j = L[j])
        ResCol(j);
      ResCol(i);
    }
  }
} dlx;

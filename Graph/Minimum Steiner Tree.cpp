在無向圖上找一棵子樹，可以把P中的點連通起來，且邊權總和最小。
令dp[S][i]表示以點i為根，以S⊆P為terminal set構造出來的斯坦納樹，這樣我們最後的答案就會是dp[P][u∈P]。
dp[S][i]=min(dp[T][j]+dp[S−T][j]+dis(i,j):j∈V,T⊂S)
dis(i,j)表示i∼j的最短路徑
這其實還可以優化，令H[j]=min(dp[T][j]+dp[S−T][j]:T⊂S)
則dp[S][i]=min(H[j]+dis(i,j):j∈|V|)
H[]是可以被預先算出來的。
// O(V 3^T + V^2 2^T)
struct SteinerTree{
#define V 33
#define T 8
#define INF 1023456789
  int n, dst[V][V], dp[1 << T][V], tdst[V];
  void init(int _n){
    n = _n;
    for (int i = 0; i < n; i++){
      for (int j = 0; j < n; j++)
        dst[i][j] = INF;
      dst[i][i] = 0;
    }
  }
  void add_edge(int ui, int vi, int wi){
    dst[ui][vi] = min(dst[ui][vi], wi);
    dst[vi][ui] = min(dst[vi][ui], wi);
  }
  void shortest_path(){
    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
         dst[i][j]=min(dst[i][j],dst[i][k]+dst[k][j]);
  }
  int solve(const vector<int> &ter){
    shortest_path();
    int t = (int)ter.size();
    for (int i = 0; i < (1 << t); i++)
      for (int j = 0; j < n; j++)
        dp[i][j] = INF;
    for (int i = 0; i < n; i++)
      dp[0][i] = 0;
    for (int msk = 1; msk < (1 << t); msk++){
      if (msk == (msk & (-msk))){
        int who = __lg(msk);
        for (int i = 0; i < n; i++)
          dp[msk][i] = dst[ter[who]][i];
        continue;
      }
      for (int i = 0; i < n; i++)
        for (int submsk = (msk - 1) & msk; submsk; submsk = (submsk - 1) & msk)
          dp[msk][i] = min(dp[msk][i], dp[submsk][i] + dp[msk ^ submsk][i]);
      for (int i = 0; i < n; i++){
        tdst[i] = INF;
        for (int j = 0; j < n; j++)
          tdst[i]=min(tdst[i],dp[msk][j]+dst[j][i]);
      }
      for (int i = 0; i < n; i++)
        dp[msk][i] = tdst[i];
    }
    int ans = INF;
    for (int i = 0; i < n; i++)
      ans = min(ans, dp[(1 << t) - 1][i]);
    return ans;
  }
} solver;

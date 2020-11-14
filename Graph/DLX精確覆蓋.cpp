// 別用這個爛東西 去用DLX.cpp啦OwO
// given n*m 0-1 matrix
// find a set of rows s.t.
// for each column, there's exactly one 1
#define N 1024 //row
#define M 1024 //column
#define NM ((N + 2) * (M + 2))
struct DLX{
  char A[N][M]; //n*m 0-1 matrix
  int used[N];  //answer: the row used
  int id[N][M];
  int L[NM], R[NM], D[NM], U[NM], C[NM], S[NM], ROW[NM];
  multiset<int> rowSizes;
  int RS[N];
  int availColumn;
  int ans; //exact cover的最小列數
  int cnt; //用來更新ans
  void remove(int c){
    availColumn--;
    L[R[c]] = L[c];
    R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i])
      for (int j = R[i]; j != i; j = R[j])
      {
        U[D[j]] = U[j];
        D[U[j]] = D[j];
        S[C[j]]--;
      }
  }
  void resume(int c) {
    availColumn++;
    for (int i = D[c]; i != c; i = D[i])
      for (int j = L[i]; j != i; j = L[j])  {
        U[D[j]] = D[U[j]] = j;
        S[C[j]]++;
      }
    L[R[c]] = R[L[c]] = c;
  }
  void dfs(){
    // cut any larger answer
    if (cnt >= ans)
      return;
    // compute maximum columns we can get
    int canCol = 0;
    multiset<int>::reverse_iterator it = rowSizes.rbegin();
    for (int i = cnt; i < ans - 1 && it != rowSizes.rend(); i++, it++) {
      canCol += *it;
    }
    if (canCol < availColumn)
      return;

    if (R[0] == 0)  {
      //printf("yes\n");
      ans = cnt;
      return;
    }
    int md = 100000000, c;
    for (int i = R[0]; i != 0; i = R[i])
      if (S[i] < md) {
        md = S[i];
        c = i;
      }
    if (md == 0)
      return;
    remove(c);
    for (int i = D[c]; i != c; i = D[i]){
      rowSizes.erase(rowSizes.find(RS[ROW[i]]));
      used[ROW[i]] = 1;
      cnt++;
      for (int j = R[i]; j != i; j = R[j])
        remove(C[j]);
      dfs();
      rowSizes.insert(RS[ROW[i]]);
      for (int j = L[i]; j != i; j = L[j])
        resume(C[j]);
      used[ROW[i]] = 0;
      cnt--;
    }
    resume(c);
    return;
  }
  void exact_cover(int n, int m){
    ans = INT_MAX;
    cnt = 0;
    availColumn = m;
    rowSizes.clear();
    for (int i = 0; i <= m; i++){
      R[i] = i + 1;
      L[i] = i - 1;
      U[i] = D[i] = i;
      S[i] = 0;
      C[i] = i;
    }
    R[m] = 0;
    L[0] = m;
    int t = m + 1;
    for (int i = 0; i < n; i++) {
      int k = -1;
      RS[i] = 0;
      for (int j = 0; j < m; j++) {
        if (!A[i][j])
          continue;
        if (k == -1)
          L[t] = R[t] = t;
        else {
          L[t] = k;
          R[t] = R[k];
        }
        k = t;
        D[t] = j + 1;
        U[t] = U[j + 1];
        L[R[t]] = R[L[t]] = U[D[t]] = D[U[t]] = t;
        C[t] = j + 1;
        S[C[t]]++;
        ROW[t] = i;
        id[i][j] = t++;
        RS[i]++;
      }
      rowSizes.insert(RS[i]);
    }
    for (int i = 0; i < n; i++) used[i] = 0;
    dfs();
    return;
  }
} dlx;

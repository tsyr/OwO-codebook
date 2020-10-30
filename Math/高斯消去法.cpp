#define eps 1e-8
void gauss(vector<vector<double>> &A, vector<int> &cols, vector<int> &rows, vector<int> &ind)
{ //哪些cols是係數(等號左邊，要排在A的最前面幾行)，要對哪些rows做高斯消去，ind為哪些行消完不全零
  int N = min(rows.size(), cols.size());
  for (int i = 0; i < N; i++) {
    int x = i, y = i;
    for (int j = i; j < rows.size(); j++)
      for (int k = i; k < cols.size(); k++)
        if(fabs(A[rows[j]][cols[k]]) > fabs(A[rows[x]][cols[y]])) x = j, y = k;
    if (fabs(A[rows[x]][cols[y]]) < eps) return;
    swap(rows[i], rows[x]), swap(cols[i], cols[y]);
    ind.emplace_back(rows[i]);
    for (int j = 0; j < rows.size(); j++){
      if (j == i)   continue;
      for (int k = i + 1; k < cols.size(); k++)
        A[rows[j]][cols[k]] -= A[rows[i]][cols[k]] * (A[rows[j]][cols[i]] / A[rows[i]][cols[i]]);
      for (int k = cols.size(); k < A[0].size(); k++)
        A[rows[j]][k] -= A[rows[i]][k] * (A[rows[j]][cols[i]] / A[rows[i]][cols[i]]);
      A[rows[j]][cols[i]] = 0;
    }
  }
}
vector<double> solve(vector<vector<double>> &A)
{ //n*(n+1)的高斯消去，A是增廣矩陣
  int n = A.size();
  vector<int> cols, rows, ind;
  for (int i = 0; i < n; i++)
    rows.push_back(i), cols.push_back(i);
  gauss(A, cols, rows, ind);
  if (ind.size() < n)
    return vector<double>(0); // no or infinite sols
  vector<double> ans(n);
  for (int i = 0; i < n; i++)
    ans[cols[i]] = A[rows[i]][n] / A[rows[i]][cols[i]];
  return ans;
}

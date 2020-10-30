struct SuffixArray{
  string s;
  int n;
  vector<int> sa, pos, lcp, tmp, cnt; //lcp就是height
  vector<vector<int>> sparse;
  SuffixArray(string t) : s(t) {
    n = s.size();
    sa.assign(n, 0);    pos.assign(n, 0);
    tmp.assign(n, 0);   cnt.assign(max(n, 256), 0);
    lcp.assign(n - 1, 0);    sparse.clear();
    BuildSA();    BuildLCP();
  }
  void CountingSort(int gap){
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; ++i){
      if (i + gap >= n){ ++cnt[0];  continue; }
      ++cnt[pos[i + gap] + 1];
    }
    int sum = 0;
    for (int i = 0; i < (int)cnt.size(); ++i){
      int cur = cnt[i];
      cnt[i] = sum;
      sum += cur;
    }
    for (int i = 0; i < n; ++i) {
      int cur = sa[i];
      if (cur + gap >= n)  tmp[cnt[0]++] = cur;
      else   tmp[cnt[pos[cur + gap] + 1]++] = cur;
    }
    for (int i = 0; i < n; ++i) sa[i] = tmp[i];
  }
  void BuildSA() {
    for (int i = 0; i < n; ++i)
      sa[i] = i, pos[i] = s[i];
    for (int gap = 1;; gap <<= 1)  {
      auto cmp = [&](int a, int b) {
        if (pos[a] - pos[b])
          return pos[a] < pos[b];
        a += gap;
        b += gap;
        return (a<n && b<n) ? pos[a]<pos[b] : a>b;
      };
      // sort(sa.begin(), sa.end(), cmp);
      CountingSort(gap);
      CountingSort(0);
      tmp[0] = 0;
      for (int i = 1; i < n; ++i)
        tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
      for (int i = 0; i < n; ++i)
        pos[sa[i]] = tmp[i];
      if (tmp[n - 1] == n - 1)  break;
    }
  }
  void BuildLCP() {
    for (int i = 0, k = 0; i < n; ++i)
      if (pos[i] - n + 1)  {
        for (int j=sa[pos[i]+1]; s[j+k]==s[i+k]; ++k);
        lcp[pos[i]] = k;
        if (k) k--;
      }
    sparse.push_back(lcp);
    for (int i = 0;; ++i)    {
      int len = n - (1 << (i + 1));
      if (len <= 0)   break;
      sparse.push_back(vector<int>(len));
      for (int j = 0; j < len; ++j)  {
      int left=sparse[i][j],right=sparse[i][j+(1<<i)];
        sparse[i + 1][j] = min(left, right);
      }
    }
  }
  int GetLCP(int l, int r)
  { // rank(就是pos，0-based)為[l,r]中間height的最小值
    if (l >= r)
      return n;
    int len = r - l;
    int lg = 31 - __builtin_clz(len);
    return min(sparse[lg][l], sparse[lg][r-(1<<lg)]);
  }
  int solve_LCP(int a, int b)
  { // 字串為0-based，a,b為原本位置
    int l = min(pos[a], pos[b]);
    int r = max(pos[a], pos[b]);
    return min(min(n - a, n - b), GetLCP(l, r));
  }
  pair<int, int> FindOccurs(int p, int len)
  {  //p=pos[原本位置] // rank p的長度為len的前綴在rank為[ret.first, ret.second]的前綴有出現
    pair<int, int> ret = {p, p};
    int lo = 0, hi = p;
    while (lo < hi) {
      int mid = (lo + hi) >> 1;
      if (GetLCP(mid, p) < len)  lo = mid + 1;
      else   hi = mid;
    }
    ret.first = lo;
    lo = p, hi = n - 1;
    while (lo < hi) {
      int mid = (lo + hi + 1) >> 1;
      if (GetLCP(p, mid) < len)  hi = mid - 1;
      else   lo = mid;
    }
    ret.second = hi;
    return ret; //sa[ret.first]~sa[ret.second]
  }
};

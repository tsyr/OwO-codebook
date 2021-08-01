struct SuffixArray{
	int n;
	int m[2][maxn], sa[maxn];
	char s[maxn];
	void indexSort(int sa[], int ord[], int id[], int nId){
		static int cnt[maxn];
		memset(cnt, 0, sizeof(0) * nId);
		for (int i = 0; i < n; i++)
			cnt[id[i]]++;
		partial_sum(cnt, cnt + nId, cnt);
		for (int i = n - 1; i >= 0; i--)
			sa[--cnt[id[ord[i]]]] = ord[i];
	}
	int *id, *oId;
	void init(){
		s[n] = 很小的東西, n++;
		static int w[maxn];
		for (int i = 0; i <= n; i++)
			w[i] = s[i];
		sort(w, w + n);
		int nId = unique(w, w + n) - w;
		id = m[0], oId = m[1];
		for (int i = 0; i < n; i++)
			id[i] = lower_bound(w, w + nId, s[i]) - w;
		static int ord[maxn];
		for (int i = 0; i < n; i++)
			ord[i] = i;
		indexSort(sa, ord, id, nId);
		for (int k = 1; k <= n && nId < n; k <<= 1){
			int cur = 0;
			for (int i = n - k; i < n; i++)
				ord[cur++] = i; 
			for (int i = 0; i < n; i++)
				if (sa[i] >= k)
					ord[cur++] = sa[i] - k;
			indexSort(sa, ord, id, nId);
			cur = 0;
			swap(oId, id);
			for (int i = 0; i < n; i++){
				int c = sa[i], p = i ? sa[i - 1] : 0;
				id[c] = (i == 0 || oId[c] != oId[p] || oId[c + k] != oId[p + k]) ? cur++ : cur - 1;
			}
			nId = cur;
		}
	}
	int rk[maxn], lcp[maxn];
	void getlcp(){
		for (int i = 0; i < n; i++)  rk[sa[i]] = i;
		int h = 0;
		lcp[0] = 0;
		for (int i = 0; i < n; i++){
			int j = sa[rk[i] - 1];
			for (h ? h-- : 0; i + h < n && j + h < n && s[i + h] == s[j + h]; h++) ;
			lcp[rk[i] - 1] = h;
		}
	}
	int d[maxn + 50][25];
	void getrmq(){
		for (int i = 0; i < n; i++)
			d[i][0] = lcp[i];
		for (int j = 1; (1 << j) < n; j++)
			for (int i = 0; (i + (1 << j) - 1) < n; i++)
				d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
	}
	int rmq_query(int l, int r){
		if (l > r) swap(l, r);
		r -= 1;
		int k = 0;
		int len = r - l + 1;
		while ((1 << (k + 1)) < len)  k++;
		return min(d[l][k], d[r - (1 << k) + 1][k]);
	}
};

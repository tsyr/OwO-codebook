// codechef June Challenge 2021, Maximum Frequent Subarray Sum
// https://www.codechef.com/JUNE21B/problems/MFSS 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define mod 1000000007

const int maxn = 100010;

struct SuffixArray
{
	int n;
	int m[2][maxn], sa[maxn];
	int s[maxn];
	void indexSort(int sa[], int ord[], int id[], int nId)
	{
		static int cnt[maxn];
		memset(cnt, 0, sizeof(0) * nId);
		for (int i = 0; i < n; i++)
			cnt[id[i]]++;
		partial_sum(cnt, cnt + nId, cnt);
		for (int i = n - 1; i >= 0; i--)
			sa[--cnt[id[ord[i]]]] = ord[i];
	}
	int *id, *oId;
	void init()
	{
		s[n] = INT_MIN, n++;
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
		for (int k = 1; k <= n && nId < n; k <<= 1)
		{
			int cur = 0;
			for (int i = n - k; i < n; i++)
				ord[cur++] = i;
			for (int i = 0; i < n; i++)
				if (sa[i] >= k)
					ord[cur++] = sa[i] - k;
			indexSort(sa, ord, id, nId);
			cur = 0;
			swap(oId, id);
			for (int i = 0; i < n; i++)
			{
				int c = sa[i], p = i ? sa[i - 1] : 0;
				id[c] = (i == 0 || oId[c] != oId[p] || oId[c + k] != oId[p + k]) ? cur++ : cur - 1;
			}
			nId = cur;
		}
	}
	int rk[maxn], lcp[maxn];
	void getlcp()
	{
		for (int i = 0; i < n; i++)
			rk[sa[i]] = i;
		int h = 0;
		lcp[0] = 0;
		for (int i = 0; i < n; i++)
		{
			int j = sa[rk[i] - 1];
			for (h ? h-- : 0; i + h < n && j + h < n && s[i + h] == s[j + h]; h++)
				;
			lcp[rk[i] - 1] = h;
		}
	}
	int d[maxn + 50][25];
	void getrmq()
	{
		for (int i = 0; i < n; i++)
			d[i][0] = lcp[i];
		for (int j = 1; (1 << j) < n; j++)
			for (int i = 0; (i + (1 << j) - 1) < n; i++)
				d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
	}
	int rmq_query(int l, int r)
	{
		if (l > r)
			swap(l, r);
		r -= 1;
		int k = 0;
		int len = r - l + 1;
		while ((1 << (k + 1)) < len)
			k++;
		return min(d[l][k], d[r - (1 << k) + 1][k]);
	}
} sf;

int n;
ll sum[maxn];
vector<P> st;

ll smt[4 * maxn];
void build(int idx, int l, int r)
{
	if (l == r)
	{
		smt[idx] = sum[l];
		return;
	}
	int m = (l + r) >> 1;
	build(idx << 1, l, m);
	build(idx << 1 | 1, m + 1, r);
	smt[idx] = max(smt[idx << 1], smt[idx << 1 | 1]);
}
ll query(int idx, int l, int r, int a, int b)
{
	if (r < a || l > b)
		return LLONG_MIN;
	if (l >= a && r <= b)
		return smt[idx];
	int m = (l + r) >> 1;
	return max(query(idx << 1, l, m, a, b), query(idx << 1 | 1, m + 1, r, a, b));
}

int main()
{
	//freopen("t.txt", "r", stdin);
	//freopen("t2.out", "w", stdout);
	//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		scanf("%d", &n);
		sf.n = n;
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &sf.s[i]);
			sum[i + 1] = sum[i] + sf.s[i];
		}
		sf.s[n] = INT_MIN;
		build(1, 1, n);

		sf.s[n + 1] = INT_MIN;
		sf.init(), sf.getlcp();
		sf.lcp[n] = 0;

		/*
		for (int i = 0; i <= n; i++)
			printf("%d ", sf.sa[i]);
		printf("\n");
		for (int i = 0; i <= n; i++)
			printf("%d ", sf.rk[i]);
		printf("\n");
		for (int i = 0; i <= n; i++)
			printf("%d ", sf.lcp[i]);
		printf("\n");*/

		ll ans = LLONG_MIN;

		st.clear();
		st.push_back(P(0, 0));

		for (int i = 1; i <= n; i++)
		{
			int r = n - sf.sa[i];
			for (int j = st.size() - 1; j >= 0; j--)
			{
				if (r <= sf.lcp[i])
					break;
				int l = max(sf.lcp[i] + 1, st[j].second + 1);
				if (r >= l)
					ans = max(ans, (query(1, 1, n, sf.sa[i] + l, sf.sa[i] + r) - sum[sf.sa[i]]) * (i - st[j].first));
				r = l - 1;
			}
			while (!st.empty() && st.back().second >= sf.lcp[i])
				st.pop_back();
			st.push_back(P(i, sf.lcp[i]));
		}
		//for (P p : st)
		//    printf("%d %d\n", p.first, p.second);
		printf("%lld\n", ans);
	}

	return 0;
}

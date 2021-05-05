#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;
#define mod 1000000007

const int maxn = 100005;
struct LiChao_min
{
	struct line
	{
		ll m, c;
		line(ll _m = 0, ll _c = 0)
		{
			m = _m;
			c = _c;
		}
		ll eval(ll x) { return m * x + c; }
	};
	struct node
	{
		node *l, *r;
		line f;
		node(line v)
		{
			f = v;
			l = r = NULL;
		}
	};
	typedef node *pnode;
	pnode root;
	int sz;
#define mid ((l + r) >> 1)
	void insert(line &v, int l, int r, pnode &nd)
	{
		if (!nd)
		{
			nd = new node(v);
			return;
		}
		ll trl = nd->f.eval(l), trr = nd->f.eval(r);
		ll vl = v.eval(l), vr = v.eval(r);
		if (trl <= vl && trr <= vr)
			return;
		if (trl > vl && trr > vr)
		{
			nd->f = v;
			return;
		}
		if (trl > vl)
			swap(nd->f, v);
		if (nd->f.eval(mid) < v.eval(mid))
			insert(v, mid + 1, r, nd->r);
		else
			swap(nd->f, v), insert(v, l, mid, nd->l);
	}
	ll query(int x, int l, int r, pnode &nd)
	{
		if (!nd)
			return LLONG_MAX;
		if (l == r)
			return nd->f.eval(x);
		if (mid >= x)
			return min(nd->f.eval(x), query(x, l, mid, nd->l));
		return min(nd->f.eval(x), query(x, mid + 1, r, nd->r));
	}
	/* -sz <= query_x <= sz */
	void init(int _sz)
	{
		sz = _sz + 1;
		root = NULL;
	}
	void add_line(ll m, ll c)
	{
		line v(m, c);
		insert(v, -sz, sz, root);
	}
	ll query(ll x) { return query(x, -sz, sz, root); }
} rt[maxn];

//	u->v: dp[u]=min(dp[v]+a[u]*b[v])

int n;
ll a[maxn], b[maxn];
vector<int> g[maxn];
int sz[maxn];
ll dp[maxn];

bool cmp(int x, int y) { return sz[x] > sz[y]; }
void dfs2(int now, int fa, int s)
{
	rt[s].add_line(b[now], dp[now]);
	for (int x : g[now])
	{
		if (x == fa)
			continue;
		dfs2(x, now, s);
	}
}
void dfs(int now, int fa)
{
	vector<int> v;
	sz[now] = 1;
	for (int x : g[now])
	{
		if (x == fa)
			continue;
		v.push_back(x);
		dfs(x, now);
		sz[now] += sz[x];
	}
	g[now] = v;
	sort(g[now].begin(), g[now].end(), cmp);
	if (!g[now].empty())
	{
		rt[now] = rt[g[now][0]];
		for (int x : g[now])
		{
			if (x == g[now][0])
				continue;
			dfs2(x, now, now);
		}
		dp[now] = rt[now].query(a[now]);
	}
	else
		dp[now] = 0;
	rt[now].add_line(b[now], dp[now]);
}

int main()
{
	//freopen("t.txt", "r", stdin);
	//freopen("t2.out", "w", stdout);
	//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	for (int i = 0; i < n - 1; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for (int i = 1; i <= n; i++)
		rt[i].init(maxn);
	dfs(1, 1);
	for (int i = 1; i <= n; i++)
		printf("%lld ", dp[i]);

	return 0;
}

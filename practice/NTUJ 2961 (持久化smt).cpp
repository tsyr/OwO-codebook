// NTUJ 2961 (持久化smt), WA
// http://acm.csie.org/ntujudge/problem.php?id=2961
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> P;
#define mod 998244353

P operator+(P p1, P p2)
{
	return P(p1.first + p2.first, p1.second + p2.second);
}

const int maxn = 100005;
const int N = 80 * maxn;

struct node
{
	static node mem[N], *pmem;
	P v;
	node *lc, *rc;
	node() {}
	node(int _v, ll _iv) { lc = NULL, rc = NULL, v = P(_v, _iv); }
} node::mem[N], *node::pmem = node::mem;

void getnode(node *&now, node *t)
{
	now = new (node::pmem++) node(t->v.first, t->v.second);
}

node *update(node *t, int l, int r, int x, int val)
{
	assert(x <= r && x >= l);
	node *now;
	if (!t)
		now = new (node::pmem++) node(0, 0);
	else
		getnode(now, t);
	if (l == r)
	{
		now->v = now->v + P(val, l * val);
		return now;
	}
	int m = (l + r) / 2;
	if (x <= m)
	{
		if (t)
		{
			now->lc = update(t->lc, l, m, x, val);
			now->rc = t->rc;
		}
		else
		{
			now->lc = update(NULL, l, m, x, val);
			now->rc = NULL;
		}
	}
	else
	{
		if (t)
		{
			now->rc = update(t->rc, m + 1, r, x, val);
			now->lc = t->lc;
		}
		else
		{
			now->rc = update(NULL, m + 1, r, x, val);
			now->lc = NULL;
		}
	}
	now->v = P(0, 0);
	if (now->lc)
		now->v = now->v + now->lc->v;
	if (now->rc)
		now->v = now->v + now->rc->v;
	return now;
}
void update2(node *&t, int l, int r, int x, int val)
{
	assert(x <= r && x >= l);
	if (!t)
		t = new (node::pmem++) node(0, 0);
	if (l == r)
	{
		t->v = t->v + P(val, l * val);
		return;
	}
	int m = (l + r) / 2;
	if (x <= m)
		update2(t->lc, l, m, x, val);
	else
		update2(t->rc, m + 1, r, x, val);
	t->v = P(0, 0);
	if (t->lc)
		t->v = t->v + t->lc->v;
	if (t->rc)
		t->v = t->v + t->rc->v;
	return;
}
P query(node *t, int l, int r, int a, int b)
{
	if (!t || l > b || r < a)
		return P(0, 0);
	if (l >= a && r <= b)
		return t->v;
	int m = (l + r) >> 1;
	return query(t->lc, l, m, a, b) + query(t->rc, m + 1, r, a, b);
}

node *rt[maxn];
int n, q;
int h[maxn], l[maxn], r[maxn];

ll cal(int r, int x)
{
	P p = query(rt[r], 1, n, 1, x);
	return (ll)(x + 1) * p.first - p.second;
}

int main()
{
	//freopen("4-16.in", "r", stdin);
	//freopen("a218_09.out", "w", stdout);
	//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		node::pmem = node::mem;
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &h[i]);
			l[i] = r[i] = i;
		}
		h[0] = h[n + 1] = INT_MAX;
		for (int i = 1; i <= n; i++)
			for (; h[l[i] - 1] <= h[i]; l[i] = l[l[i] - 1])
				;
		for (int i = n; i >= 1; i--)
			for (; h[r[i] + 1] <= h[i]; r[i] = r[r[i] + 1])
				;
		for (int i = 1; i <= n; i++)
		{
			l[i] = max(l[i] - 1, 1);
			r[i] = min(r[i] + 1, n);
			rt[i] = update(rt[i - 1], 1, n, l[i], 1);
			//update2(rt[i], 1, n, l[i], 1);
			if (r[i] < n)
				update2(rt[i], 1, n, r[i] + 1, -1);
			//printf("i=%d\n", i);
		}
		while (q--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			ll ans = cal(y, y);
			if (x > 1)
				ans = ans - cal(y, x - 1) - cal(x - 1, y) + cal(x - 1, x - 1);
			printf("%lld\n", ans);
		}
		//printf("%d\n", query(rt[4], 1, n, 2, 3).first);
	}

	return 0;
}

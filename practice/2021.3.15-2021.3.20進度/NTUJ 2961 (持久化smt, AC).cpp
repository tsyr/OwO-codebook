// NTUJ 2961 (持久化smt), AC
// http://acm.csie.org/ntujudge/problem.php?id=2961
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> P;
#define mod 998244353

P add(P p1, P p2)
{
    return P(p1.first + p2.first, p1.second + p2.second);
}

const int maxn = 100005;
const int N = 40 * maxn;

struct node
{
    static node mem[N], *pmem;
    P v;
    node *lc, *rc;
    node() {}
    node(int _v, ll _iv) { lc = NULL, rc = NULL, v = P(_v, _iv); }
} node::mem[N], *node::pmem = node::mem;

node *build(int l, int r)
{
    node *t = new (node::pmem++) node(0, 0);
    if (l == r)
        return t;
    int m = (l + r) >> 1;
    t->lc = build(l, m);
    t->rc = build(m + 1, r);
    return t;
}

node *update(node *t, int l, int r, int x, int val)
{
    assert(x <= r && x >= l);
    node *now = new (node::pmem++) node(t->v.first, t->v.second);
    if (l == r)
    {
        now->v = add(now->v, P(val, l * val));
        return now;
    }
    int m = (l + r) / 2;
    if (x <= m)
    {
        now->lc = update(t->lc, l, m, x, val);
        now->rc = t->rc;
    }
    else
    {
        now->rc = update(t->rc, m + 1, r, x, val);
        now->lc = t->lc;
    }
    now->v = add(now->lc->v, now->rc->v);
    return now;
}
P query(node *t, int l, int r, int a, int b)
{
    if (l > b || r < a)
        return P(0, 0);
    if (l >= a && r <= b)
        return t->v;
    int m = (l + r) >> 1;
    return add(query(t->lc, l, m, a, b), query(t->rc, m + 1, r, a, b));
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
    //freopen("t.in", "r", stdin);
    //freopen("t2.out", "w", stdout);
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

        rt[0] = build(1, n);
        for (int i = 1; i <= n; i++)
        {
            l[i] = max(l[i] - 1, 1);
            r[i] = min(r[i] + 1, n);
            //printf("i=%d\n", i);
            rt[i] = update(rt[i - 1], 1, n, l[i], 1);
            if (r[i] < n)
            {
                rt[i] = update(rt[i], 1, n, r[i] + 1, -1);
                //printf("minus %d %d\n", i, r[i]);
            }
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
        //printf("tt %d\n", query(rt[5], 1, n, 7, 7).first - query(rt[4], 1, n, 7, 7).first);
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;
#define mod 1000000007

const int maxn = 100005;

int n, m;
vector<P> v1, v2;

ll val(P p, P p2)
{
    return (p2.first - p.first) * (p.second - p2.second);
}

struct S
{
    P p;
    bool has = 0;
    ll val(P p2)
    {
        if (!has)
            return INT_MIN;
        return (p2.first - p.first) * (p.second - p2.second);
    }
} smt[maxn * 4];

void update(int idx, int l, int r, P p)
{
    if (l == r)
    {
        if (val(p, v2[l]) > smt[idx].val(v2[l]))
        {
            smt[idx].p = p;
            smt[idx].has = 1;
        }
        return;
    }
    int m = (l + r) / 2;
    if (val(p, v2[m]) > smt[idx].val(v2[m]))
    {
        smt[idx].p = p;
        smt[idx].has = 1;
        update(idx << 1, l, m, p);
    }
    else
        update(idx << 1 | 1, m + 1, r, p);
}
ll query(int idx, int l, int r, int k)
{
    ll res = smt[idx].val(v2[k]);
    if (l == r)
        return res;
    int m = (l + r) / 2;
    if (k <= m)
        return max(res, query(idx << 1, l, m, k));
    return max(res, query(idx << 1 | 1, m + 1, r, k));
}

int main()
{
    //freopen("t.txt", "r", stdin);
    //freopen("t2.out", "w", stdout);
    //std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    scanf("%d", &n);
    ll x = 0, y = 0;
    for (int i = 0; i < n; i += 2)
    {
        ll now;
        scanf("%lld", &now);
        y += now;
        v1.push_back(P(x, y));
        scanf("%lld", &now);
        x += now;
    }
    x = y = 0;
    scanf("%d", &m);
    for (int i = 0; i < m; i += 2)
    {
        ll now;
        scanf("%lld", &now);
        x += now;
        v2.push_back(P(x, y));
        scanf("%lld", &now);
        y += now;
    }
    n /= 2, m /= 2;
    for (int i = 0; i < n; i++)
        update(1, 0, m - 1, v1[i]);
    ll ans = 0;
    for (int i = 0; i < m; i++)
        ans = max(ans, query(1, 0, m - 1, i));
    printf("%lld\n", ans);
    return 0;
}

// NTUJ 2961 (KD tree), TLE
// http://acm.csie.org/ntujudge/problem.php?id=2961 
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define mod 998244353

const int maxn = 400040;
int n, xl, xr, yl, yr;
struct node
{
    int x, y;
    ll v[4];
} s[maxn];
bool cmp1(int a, int b) { return s[a].x < s[b].x; }
bool cmp2(int a, int b) { return s[a].y < s[b].y; }
int rt, cur, d[maxn], lc[maxn], rc[maxn], L[maxn], R[maxn], D[maxn], U[maxn],
    siz[maxn];
array<ll, 4> sum[maxn]; //D,iD,jD,ijD
int g[maxn], t;
void maintain(int x)
{
    siz[x] = siz[lc[x]] + siz[rc[x]] + 1;
    for (int i = 0; i < 4; i++)
        sum[x][i] = sum[lc[x]][i] + sum[rc[x]][i] + s[x].v[i];
    L[x] = R[x] = s[x].x;
    D[x] = U[x] = s[x].y;
    if (lc[x])
        L[x] = min(L[x], L[lc[x]]), R[x] = max(R[x], R[lc[x]]),
        D[x] = min(D[x], D[lc[x]]), U[x] = max(U[x], U[lc[x]]);
    if (rc[x])
        L[x] = min(L[x], L[rc[x]]), R[x] = max(R[x], R[rc[x]]),
        D[x] = min(D[x], D[rc[x]]), U[x] = max(U[x], U[rc[x]]);
}
int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
    for (int i = l; i <= r; i++)
        av1 += s[g[i]].x, av2 += s[g[i]].y;
    av1 /= (r - l + 1);
    av2 /= (r - l + 1);
    for (int i = l; i <= r; i++)
        va1 += (av1 - s[g[i]].x) * (av1 - s[g[i]].x),
            va2 += (av2 - s[g[i]].y) * (av2 - s[g[i]].y);
    if (va1 > va2)
        nth_element(g + l, g + mid, g + r + 1, cmp1), d[g[mid]] = 1;
    else
        nth_element(g + l, g + mid, g + r + 1, cmp2), d[g[mid]] = 2;
    lc[g[mid]] = build(l, mid - 1);
    rc[g[mid]] = build(mid + 1, r);
    maintain(g[mid]);
    return g[mid];
}
array<ll, 4> query(int x)
{
    array<ll, 4> ret;
    ret[0] = ret[1] = ret[2] = ret[3] = 0;
    if (!x || xr < L[x] || xl > R[x] || yr < D[x] || yl > U[x])
        return ret;
    if (xl <= L[x] && R[x] <= xr && yl <= D[x] && U[x] <= yr)
        return sum[x];
    if (xl <= s[x].x && s[x].x <= xr && yl <= s[x].y && s[x].y <= yr)
    {
        for (int i = 0; i < 4; i++)
            ret[i] += s[x].v[i];
    }
    array<ll, 4> lll = query(lc[x]);
    array<ll, 4> rr = query(rc[x]);
    for (int i = 0; i < 4; i++)
        ret[i] += lll[i] + rr[i];
    return ret;
}
void insert(int i, int j, int t)
{
    cur++;
    s[cur].x = i, s[cur].y = j;
    s[cur].v[0] = t, s[cur].v[1] = i * t;
    s[cur].v[2] = j * t, s[cur].v[3] = (ll)i * j * t;
}
ll trans(array<ll, 4> x) { return (ll)(xr + 1) * (yr + 1) * x[0] - (ll)(yr + 1) * x[1] - (ll)(xr + 1) * x[2] + x[3]; }

int q;
int h[maxn], l[maxn], r[maxn];

int main()
{
    //freopen("4-16.in", "r", stdin);
    //freopen("a218_09.out", "w", stdout);
    //std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
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
            //printf("%d %d\n", l[i], r[i]);
        }
        cur = rt = t = 0;
        for (int i = 1; i <= n; i++)
        {
            insert(i, l[i], 1);
            insert(i, r[i] + 1, -1);
            insert(i + 1, l[i], -1);
            insert(i + 1, r[i] + 1, 1);
        }
        for (int i = 1; i <= 4 * n; i++)
            g[i] = i;
        t = cur;
        rt = build(1, cur);
        //printf("rt=%d %d\n", rt, cur);
        while (q--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            ll ans = 0;
            xl = 0, yl = 0, xr = y, yr = y;
            ans += trans(query(rt));
            xl = 0, yl = 0, xr = x - 1, yr = y;
            ans -= trans(query(rt));
            xl = 0, yl = 0, xr = y, yr = x - 1;
            ans -= trans(query(rt));
            xl = 0, yl = 0, xr = x - 1, yr = x - 1;
            ans += trans(query(rt));
            printf("%lld\n", ans);
        }
        //for (int i = 0; i <= 4 * n; i++)
        //    lc[i] = rc[i] = 0;
    }

    return 0;
}

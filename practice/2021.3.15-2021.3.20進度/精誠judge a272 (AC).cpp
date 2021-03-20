// 精誠judge a272. 最長遞增子序列的數量, AC 
// http://zerojudge.cchs.chc.edu.tw/ShowProblem?problemid=a272
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> P;
#define mod 1000000007

const int maxn = 300005;
int n;
int a[maxn];
vector<int> b;
P bit[maxn];
void update(int k, P p)
{
    while (k <= b.size())
    {
        if (bit[k].first < p.first)
            bit[k] = p;
        else if (bit[k].first == p.first)
            bit[k].second = (bit[k].second + p.second) % mod;
        k += k & -k;
    }
}
P query(int k)
{
    P p = P(0, 1);
    while (k > 0)
    {
        if (bit[k].first > p.first)
            p = bit[k];
        else if (bit[k].first == p.first)
            p.second = (p.second + bit[k].second) % mod;
        k -= k & -k;
    }
    return p;
}

int main()
{
    //freopen("t.in", "r", stdin);
    //freopen("t2.out", "w", stdout);
    //std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), b.push_back(a[i]);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
        P p = query(a[i] - 1);
        p.first += 1;
        update(a[i], p);
    }
    P p = query(b.size());
    printf("%lld\n", p.second);

    return 0;
}

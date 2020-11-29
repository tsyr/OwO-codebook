#include <bits/stdc++.h>
using namespace std;
#define maxn 1000005
typedef long long ll;
typedef pair<int, int> P;
#define ull unsigned long long

#define INIT 7
#define base 131
#define mod 998244353

ll power(ll x, ll k)
{
	ll res = 1;
	while (k)
	{
		if (k & 1)
			res = res * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return res;
}
ll inv(ll x) { return power(x, mod - 2); }
ull powerull(ull x, ull k)
{
	ull res = 1;
	while (k)
	{
		if (k & 1)
			res *= x;
		x *= x;
		k >>= 1;
	}
	return res;
}
#define MAX 1500006
bool notprime[MAX];
int p[MAX];
int top = 0; //質數個數114155
ll f[maxn], fi[maxn];

void build()
{
	for (int i = 2; i < MAX; i++)
	{
		if (!notprime[i])
		{
			p[top] = i;
			top++;
		}
		for (int j = 0; i * p[j] < MAX && j < top; j++)
		{
			notprime[i * p[j]] = 1;
			if (i % p[j])
				continue;
			else
				break;
		}
	}
	//printf("top=%d\n", top);
	f[0] = 1, fi[0] = 1;
	for (int i = 1; i < maxn; i++)
		f[i] = f[i - 1] * i % mod, fi[i] = inv(f[i]);
}

int sz[maxn];

int n;
vector<int> v[maxn];
ull h1[maxn], h2[maxn];
ull hh1[maxn], hh2[maxn];

void hash_dfs1(int now, int fa)
{
	h1[now] = INIT;
	hh1[now] = 1;
	sz[now] = 1;
	for (int x : v[now])
	{
		if (x == fa)
			continue;
		hash_dfs1(x, now);
		h1[now] += powerull(base, h1[x]);
		sz[now] += sz[x];
		hh1[now] += hh1[x] * p[sz[x] + INIT];
	}
}
void hash_dfs2(int now, int fa)
{
	if (now == 1)
	{
		h2[now] = h1[now];
		hh2[now] = hh1[now];
	}
	else
	{
		h2[now] = h1[now] + powerull(base, h2[fa] - powerull(base, h1[now]));
		hh2[now] = hh1[now] + (hh2[fa] - hh1[now] * p[sz[now] + INIT]) * p[n - sz[now] + INIT];
	}
	for (int x : v[now])
	{
		if (x == fa)
			continue;
		hash_dfs2(x, now);
	}
}

ll ans1[maxn], ans2[maxn];
int son[maxn];
map<ull, int> mp[maxn];
void ans_dfs1(int now, int fa)
{
	ans1[now] = 1;
	for (int x : v[now])
	{
		if (x == fa)
			continue;
		ans_dfs1(x, now);
		ans1[now] = ans1[now] * ans1[x] % mod;
		mp[now][hh1[x]]++;
	}
	son[now] = 0;
	for (auto it = mp[now].begin(); it != mp[now].end(); it++)
	{
		int x = it->second;
		ans1[now] = ans1[now] * fi[x] % mod;
		son[now] += x;
	}
	ans1[now] = ans1[now] * f[son[now]] % mod;
	if (now != 1)
		son[now]++;
}
void ans_dfs2(int now, int fa)
{
	if (now == 1)
		ans2[now] = ans1[now];
	else
	{
		int x = mp[fa][hh1[now]];
		ll lst = ans2[fa] * x % mod * inv(son[fa]) % mod * inv(ans1[now]) % mod;
		ull hh = h2[fa] - powerull(base, h1[now]);
		ull hhh = hh2[fa] - hh1[now] * p[sz[now] + INIT];
		x = mp[now][hhh];
		mp[now][hhh]++;
		ans2[now] = ans1[now] * lst % mod * son[now] % mod * inv(x + 1) % mod;
	}
	for (int x : v[now])
	{
		if (x == fa)
			continue;
		ans_dfs2(x, now);
	}
}

int main()
{
	//freopen("tree.txt", "r", stdin);
	//freopen("1.out", "w", stdout);
	//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	build();
	int T;
	cin >> T;
	for (int kase = 1; kase <= T; kase++)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			v[i].clear();
			mp[i].clear();
		}
		for (int i = 0; i < n - 1; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			v[x].push_back(y);
			v[y].push_back(x);
		}
		hash_dfs1(1, 1);
		hash_dfs2(1, 1);
		//for (int i = 1; i <= n; i++)
		//    cout << "i=" << i << " h[i]=" << h2[i] << endl;
		ans_dfs1(1, 1);
		ans_dfs2(1, 1);
		//for (int i = 1; i <= n; i++)
		//    cout << "i=" << i << " ans[i]=" << ans2[i] << endl;
		map<ull, ll> mpp;
		for (int i = 1; i <= n; i++)
			mpp[hh2[i]] = ans2[i];
		ll ans = 0;
		for (pair<ull, ll> p : mpp)
			ans = (ans + p.second) % mod;
		printf("%lld\n", ans);
	}

	return 0;
}

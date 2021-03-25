
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 25
typedef pair<ll, int> P;

int n;
bitset<2001> b[1 << 20];
int a[25], res[1 << 20];

int main()
{
	//freopen("4-16.in", "r", stdin);
	//freopen("t.in", "w", stdout);
	//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	b[0] = 1;
	int lg = -1;
	for (int S = 1; S < (1 << n); S++)
	{
		if ((S & -S) == S)
			lg++;
		b[S] = b[S ^ (1 << lg)] | (b[S ^ (1 << lg)] << a[lg]);
	}
	for (int S = 0; S < (1 << n); S++)
	{
		int sum = 0;
		for (int i = 0; i < n; i++)
			if (S >> i & 1)
				sum += a[i];
		for (res[S] = (sum + 1) / 2;; res[S]++)
			if (b[S][res[S]])
				break;
	}
	int ans = INT_MAX;
	for (int S = 0; S < (1 << n); S++)
		ans = min(ans, max(res[S], res[(1 << n) - 1 - S]));
	printf("%d\n", ans);

	return 0;
}

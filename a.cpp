#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long 

string n, m;

ll a[55], b[55];

     
int main(){

	cin >> n >> m;

	int dif = m.size() - n.size();
	int i = 0, j = 0;
	int nn;
	if (dif > 0){
		i = dif;
		nn = m.size();
	}else{
		j = dif;
		nn = n.size();
	}
	int ii = 0, jj = 0;
	for (; i< nn; ++ i){
		a[i] = n[ii];
		++ii;
	}
	for (; j< nn; ++ j){
		b[j] = m[jj];
		++jj;
	}

	ll ans = 0;
	for (int k = 0; k < nn; ++k){
		ll tot = a[k];
		for (int kk = k + 1; kk < nn; ++kk){
			tot = (tot * (10-b[kk]) % mod);
		}


		ll cnt  = 1;
		for (int kk = k + 1; kk < nn; ++kk){
			if (a[kk] - b[kk] >= 0){
				cnt = (cnt + a[kk] - b[kk] + 1) % mod;
			}else {
				cnt = 0;
				break;
			}
		}
		ans = (ans + tot + cnt) % mod;
	}
	cout << ans << endl;
}

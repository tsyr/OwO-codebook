// #{{{
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define ll long long
#define LDB long double
#define MS0(I) memset(I, 0, sizeof(I));
#define MS1(I) memset(I, -1, sizeof(I));
#define F(n) FI(i,n)
#define FI(i,n) FL(i,0,n)
#define FL(i,l,n) for(ll i=l;i<n;++i)
#define RDI(A) ll A; scanf("%d", &A);
#define RDII(A, B) ll A, B; scanf("%d %d", &A, &B);
#define RDIII(A, B, C) ll A, B, C; scanf("%d %d %d", &A, &B, &C);
#define RDL(A) ll A; scanf("%lld", &A);
#define RDLL(A, B) ll A, B; scanf("%lld %lld", &A, &B);
#define RDLLL(A, B, C) ll A, B, C; scanf("%lld %lld %lld", &A, &B, &C);
#define SZ(X) ((ll)X.size() )
#define ALL(I) (I).begin(), (I).end()
#define GET_POS(c,x) (lower_bound(c.begin(),c.end(),x)-c.begin())
#define X first
#define Y second
// #}}}
#include <bits/stdc++.h>
using namespace std;
#define maxn 200005
#define mod 1000000007
// #define type ll
//#{{{
typedef int type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
Pt operator+(const Pt& p1,const Pt& p2){
	return Pt(p1.X+p2.X,p1.Y+p2.Y);
}
Pt operator-(const Pt& p1,const Pt& p2){
	return Pt(p1.X-p2.X,p1.Y-p2.Y);
}
type operator*(const Pt& p1,const Pt& p2){
	return (p1.X*p2.X+p1.Y*p2.Y);
}
type operator^(const Pt& p1,const Pt& p2){
	return (p1.X*p2.Y-p1.Y*p2.X);
}
//#}}}

int n;
ll a[100005];

ll b[100005];

ll nim = 0;

vector<pair<ll, pair<ll, ll>>>  v;  // k, {group idx, new group num}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll minn = LLONG_MAX;

    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
        minn = min(minn, a[i]);
    }

    // first set k = 2
    for (int i = 0; i < n; ++i){
        b[i] = floor(log2(a[i]));
    }

    for (int i = 0; i < n; ++ i){
        nim ^= b[i];
    }

    for (int i = 0; i < n ;++i){
        int j = b[i] - 1;
        ll last_kk = 2;
        while (j > 0){
            ll kk = floor(pow(2, log2(a[i]) / (j+1))) + 1;
            // cout << log2(4) << endl;
            // cout << log2(a[i]) << endl;
            // cout << log2(a[i]) / (j+1) << endl;
            // cout << pow(2, log2(a[i]) / (j+1)) << endl;
            if (kk == last_kk) {
                --j;
                continue;
            }
            // cout << "kk i j " << kk << " " << i << " " << j  << endl;
            last_kk = kk;
            if (kk <= minn && j > 0){
                v.push_back({kk, {i, floor(log2(a[i]) / log2(kk))}});
                --j;
            }else
                break;
        }
    }
    // cout << "here\n";
    sort(v.begin(), v.end());

    int v_size = v.size();
    ll last_k = -1;
    for (int i = 0; i < v_size; ++i){
        // cout << v[i].X << " " << v[i].Y.X << " " <<  v[i].Y.Y << endl;
        if (v[i].X != last_k){
            // for (int ii = 0; ii < n; ++ii){
            //     cout << b[ii] << " ";
            // }
            // cout << endl;
            if (nim == 0){
                cout << "Bob" << endl;
                return 0;
            }
        }
        ll group_idx = v[i].Y.X;
        ll group_num = v[i].Y.Y;
        nim ^= b[group_idx];
        b[group_idx] = group_num;
        nim ^=  b[group_idx];
        last_k = v[i].X;
    }
    if (nim == 0){
        // for (int ii = 0; ii < n; ++ii){
        //     cout << b[ii] << " ";
        // }
        // cout << endl;
        cout << "Bob" << endl;
        return 0;
    }

    // for (int ii = 0; ii < n; ++ii){
    //     cout << b[ii] << " ";
    // }
    // cout << endl;

    cout << "Alice" << endl;
    return 0;


}

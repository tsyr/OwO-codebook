ans[k]=∑_(i⊕j=k)▒〖f[i]*g[j] 〗
struct Fast_Walsh_Hadamard_transform{
    inline void FWT(ll *f, int g, int n){
        int len = 1 << n;
        for (int i = 1; i < len; i <<= 1)
            for (int j = 0; j < len; j += i << 1)
                for (int k = j; k < j + i; ++k){
                    ll x = f[k], y = f[k + i];
                    f[k] = x + y, f[k + i] = x - y;
                }
        if (g == -1)
            for (int i = 0; i < len; ++i)
                f[i] >>= n;
    }
    void solve(ll *ans, ll *f, ll *g, int n)
    { // ans=f*g，f和g的長度為(1<<n)
        FWT(f, 1, n), FWT(g, 1, n);
        for (int i = 0; i < 1 << n; ++i)
            ans[i] = f[i] * g[i];
        FWT(ans, -1, n);
    }
} fwt;

#define N 262144 * 4
struct ntt {
    const int mod = 998244353;
    const int g = 3;
    int n, m, rev[N], bit = 0, len = 1;
    //ll a[N], b[N];
    void NTT(ll *a, int opt) {
        for (int i = 0; i < len; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int mid = 1; mid < len; mid <<= 1) {
            ll tmp = power(g, (mod - 1) / (mid * 2));
            if (opt == -1)
                tmp = power(tmp, mod - 2);
            for (int i = 0; i < len; i += mid * 2) {
                ll w = 1;
                for (int j = 0; j < mid; j++, w = w * tmp % mod) {
                    ll x = a[i + j], y = w * a[i + j + mid] % mod;
                    a[i + j] = (x + y) % mod, a[i + j + mid] = (x - y + mod) % mod;
                }
            }
        }
    }
    void fft(ll *c, ll *a, ll *b, int _n, int _m) { //a和b的長度分別是n+1和m+1
        n = _n, m = _m;
        while (len <= n + m)
            len <<= 1, bit++;
        for (int i = 0; i < len; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        NTT(a, 1), NTT(b, 1);
        for (int i = 0; i < len; i++)
            a[i] = a[i] * b[i] % mod;
        NTT(a, -1);
        ll inv = power(len, mod - 2);
        for (int i = 0; i <= n + m; i++)
            c[i] = a[i] * inv % mod;
    }
} f;

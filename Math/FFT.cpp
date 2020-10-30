c[k]=∑_(i+j=k)▒〖a[i]*b[j] 〗
typedef long double db;
#define N 262144 * 4
struct FFT{
    const db pi = acos(-1);
    int len, bitrev[N];
    struct Z{
        db x, y;
        Z(db _x = 0, db _y = 0) : x(_x), y(_y) {}
        friend Z operator+(Z a, Z b) { return Z(a.x + b.x, a.y + b.y); }
        friend Z operator-(Z a, Z b) { return Z(a.x - b.x, a.y - b.y); }
        friend Z operator*(Z a, Z b) { return Z(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    } t[N], A[N], B[N], C[N], W[N];

    void dft(Z *a, int n, int sig = 1){
        for (int i = 0; i < n; i++)
            if (i < bitrev[i])
                swap(a[i], a[bitrev[i]]);
        for (int i = 2; i <= n; i <<= 1){
            int half = i >> 1, times = len / i;
            for (int j = 0; j < half; j++){
                Z w = sig > 0 ? W[times * j] : W[len - times * j];
                for (int k = j; k < len; k += i){
                    Z u = a[k], v = a[k + half] * w;
                    a[k] = u + v, a[k + half] = u - v;
                }
            }
        }
        if (sig == -1)
            for (int i = 0; i < n; i++)
                a[i].x /= n;
    }
    void fft(db *c, db *a, db *b, int n, int m)
    { //c=a*b(結果)，n為a的長度，m為b的長度
        int lg;
        lg = 0;
        while ((1 << lg) <= (max(n, m) << 1))
            ++lg;
        len = 1 << lg;
        for (int i = 0; i < len; i++)
            bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
        for (int i = 0; i <= len; i++)
            W[i] = Z(cos(2 * pi * i / len), sin(2 * pi * i / len));
        for (int i = 0; i < len; i++)
            A[i] = Z(a[i], 0), B[i] = Z(b[i], 0);
        dft(A, len);
        dft(B, len);
        for (int i = 0; i < len; i++)
            C[i] = A[i] * B[i];
        dft(C, len, -1);
        for (int i = 0; i < len; i++)
            c[i] = C[i].x;
    }
};

    #include <bits/stdc++.h>
    using namespace std;
     
    namespace ntt {    
     
    constexpr int kN = 262144;
    constexpr int kMod = 998244353;
    constexpr int kRoot = 3;
    vector<int> omega;
     
    int fpow(int a, int n) {
      int res = 1;
      while (n > 0) {
        if (n & 1) res = 1LL * res * a % kMod;
        a = 1LL * a * a % kMod;
        n >>= 1;
      }
      return res;
    }
     
    void Init() {
      omega.resize(kN + 1);
      long long x = fpow(kRoot, (kMod - 1) / kN);
      omega[0] = 1;
      for (int i = 1; i <= kN; ++i) {
        omega[i] = 1LL * omega[i - 1] * x % kMod;
      }
    }
     
    void BitReverse(vector<int> &v, int n) {
      int z = __builtin_ctz(n) - 1;
      for (int i = 0; i < n; ++i) {
        int x = 0;
        for (int j = 0; j <= z; ++j) x ^= (i >> j & 1) << (z - j);
        if (x > i) swap(v[x], v[i]);
      }
    }
     
    void Transform(vector<int> &v, int n) {
      BitReverse(v, n);
      for (int s = 2; s <= n; s <<= 1) {
        int z = s >> 1;
        for (int i = 0; i < n; i += s) {
          for (int k = 0; k < z; ++k) {
            int x = 1LL * v[i + k + z] * omega[kN / s * k] % kMod;
            v[i + k + z] = (v[i + k] + kMod - x) % kMod;
            (v[i + k] += x) %= kMod;
          }
        }
      }
    }
     
    void InverseTransform(vector<int> &v, int n) {
      Transform(v, n);
      for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]);
      const int kInv = fpow(n, kMod - 2);
      for (int i = 0; i < n; ++i) v[i] = 1LL * v[i] * kInv % kMod;
    }
     
    vector<int> Multiply(vector<int> a, vector<int> b) {
      int sz = 1, N = a.size(), M = b.size();
      while (sz < N + M - 1) sz <<= 1;
      a.resize(sz);
      b.resize(sz);
      Transform(a, sz);
      Transform(b, sz);
      for (int i = 0; i < sz; ++i) {
        a[i] = 1LL * a[i] * b[i] % kMod;
      }
      InverseTransform(a, sz);
      a.resize(N + M - 1);
      return a;
    }
     
    }  // namespace ntt
     
    int main() {
      ntt::Init();
      int N, M, K;
      cin >> N >> M >> K;
      vector<int> a(N);
      for (int i = 0; i < N; ++i) {
        cin >> a[i];
      }
      sort(a.begin(), a.end());
     
      if (K == 1) {
        cout << "0\n";
        return 0;
      }
     
      constexpr int kP = 998244353;
     
      auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
          if (n & 1) res = 1LL * res * a % kP;
          a = 1LL * a * a % kP;
          n >>= 1;
        }
        return res;
      };
     
      vector<int> fc(N + 1, 1), iv(N + 1);
      for (int i = 1; i <= N; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % kP;
        iv[i] = fpow(fc[i], kP - 2);
      }
     
      vector<vector<int>> dp(N + 1, vector<int>(M + 1));
      fill(dp[0].begin(), dp[0].end(), 1);
      for (int j = 1; j <= M; ++j) {
        vector<int> X(N + 1);
        for (int i = 0; i <= N; ++i) {
          X[i] = dp[i][j - 1];
        }
        vector<int> f = ntt::Multiply(X, iv);
        for (int i = 1; i <= N; ++i) {
          if (j >= a[i - 1]) {
            dp[i][j] = f[i];
          }
          (dp[i][j] += dp[i][j - 1]) %= kP;
        }
      }
     
      int ans = 1;
      for (int i = 0; i < N; ++i) {
        ans = 1LL * ans * M % kP;
      }
      (ans += kP - 1LL * dp[N][M] * fc[N] % kP) %= kP;
      cout << ans << "\n";
      return 0;
    }

// max{cx} subject to {Ax<=b,x>=0}
vector<std::vector<double>> _a;
std::vector<double> _b;
std::vector<double> _c;
struct Simplex
{
    using Float = double;
    static constexpr Float EPS = 1e-9;
    int N, M;
    std::vector<int> idx;
    std::vector<std::vector<Float>> a;
    int i_ch, j_ch;

    void initialize(const std::vector<std::vector<Float>> &A, const std::vector<Float> &b, const std::vector<Float> &c)
    {
        N = c.size(), M = A.size();

        a.assign(M + 2, std::vector<Float>(N + 2));
        i_ch = M;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
                a[i][j] = -A[i][j];
            a[i][N] = 1, a[i][N + 1] = b[i];
            if (a[i_ch][N + 1] > a[i][N + 1])
                i_ch = i;
        }
        for (int j = 0; j < N; j++)
            a[M][j] = c[j];
        a[M + 1][N] = -1;

        idx.resize(N + M + 1);
        std::iota(idx.begin(), idx.end(), 0);
    }

    void solve()
    {
        std::vector<int> jupd;
        for (j_ch = N;;)
        {
            if (i_ch < M)
            {
                std::swap(idx[j_ch], idx[i_ch + N + 1]);
                a[i_ch][j_ch] = 1 / a[i_ch][j_ch];
                jupd.clear();
                for (int j = 0; j < N + 2; j++)
                {
                    if (j != j_ch)
                    {
                        a[i_ch][j] *= -a[i_ch][j_ch];
                        if (std::abs(a[i_ch][j]) > EPS)
                            jupd.push_back(j);
                    }
                }
                for (int i = 0; i < M + 2; i++)
                {
                    if (std::abs(a[i][j_ch]) < EPS or i == i_ch)
                        continue;
                    for (auto j : jupd)
                        a[i][j] += a[i][j_ch] * a[i_ch][j];
                    a[i][j_ch] *= a[i_ch][j_ch];
                }
            }

            j_ch = -1;
            for (int j = 0; j < N + 1; j++)
            {
                if (j_ch < 0 or idx[j_ch] < idx[j])
                {
                    if (a[M + 1][j] > EPS or (std::abs(a[M + 1][j]) < EPS and a[M][j] > EPS))
                        j_ch = j;
                }
            }
            if (j_ch < 0)
                break;

            i_ch = -1;
            for (int i = 0; i < M; i++)
            {
                if (a[i][j_ch] < -EPS)
                {
                    if (i_ch < 0)
                    {
                        i_ch = i;
                    }
                    else if (a[i_ch][N + 1] / a[i_ch][j_ch] - a[i][N + 1] / a[i][j_ch] < -EPS)
                    {
                        i_ch = i;
                    }
                    else if (a[i_ch][N + 1] / a[i_ch][j_ch] - a[i][N + 1] / a[i][j_ch] < EPS and idx[i_ch] > idx[i])
                    {
                        i_ch = i;
                    }
                }
            }
            if (i_ch < 0)
            {
                is_infty = true;
                break;
            }
        }
        if (a[M + 1][N + 1] < -EPS)
        {
            infeasible = true;
            return;
        }
        x.assign(N, 0);
        for (int i = 0; i < M; i++)
        {
            if (idx[N + 1 + i] < N)
                x[idx[N + 1 + i]] = a[i][N + 1];
        }
        ans = a[M][N + 1];
    }
    Simplex(const std::vector<std::vector<Float>> &A, const std::vector<Float> &b, const std::vector<Float> &c)
    {
        is_infty = infeasible = false;
        initialize(A, b, c);
        solve();
    }
    bool is_infty;
    bool infeasible;
    std::vector<Float> x;
    Float ans;
};
Simplex sim(_a, _b, _c); sim.ans;

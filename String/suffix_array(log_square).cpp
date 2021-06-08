int n, k;
string s;
int rk[maxn], tmp[maxn], sa[maxn], lcp[maxn];
bool cmp(int i, int j)
{
    if (rk[i] != rk[j])
        return rk[i] < rk[j];
    else
    {
        int ri = i + k <= n ? rk[i + k] : -1;
        int rj = j + k <= n ? rk[j + k] : -1;
        return ri < rj;
    }
}
void build_sa()
{
    n = s.size();
    for (int i = 0; i <= n; i++)
    {
        sa[i] = i;
        rk[i] = i < n ? s[i] : -1(something smaller than all of s[0,n-1]);
    }
    for (k = 1; k <= n; k *= 2)
    {
        sort(sa, sa + n + 1, cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        for (int i = 0; i <= n; i++)
            rk[i] = tmp[i];
    }
}
void build_lcp()
{
    for (int i = 0; i <= n; i++)
        rk[sa[i]] = i;
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int j = sa[rk[i] - 1];
        if (h > 0)
            h--;
        for (; j + h < n && i + h < n; h++)
            if (s[j + h] != s[i + h])
                break;
        lcp[rk[i] - 1] = h;
    }
}

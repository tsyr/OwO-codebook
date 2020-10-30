vector<P> minkowski(vector<P> p, vector<P> q){
    int n = p.size(), m = q.size();
    P c = P(0, 0);
    for (int i = 0; i < m; i++)
        c = c + q[i];
    c = (1.0 / m) * c;
    for (int i = 0; i < m; i++)
        q[i] = q[i] - c;
    int cur = -1;
    for (int i = 0; i < m; i++)
        if ((q[i] ^ (p[0] - p[n - 1])) > -eps)
            if (cur == -1 || (q[i] ^ (p[0] - p[n - 1])) > (q[cur] ^ (p[0] - p[n - 1])))
                cur = i;
    vector<P> h;
    p.push_back(p[0]);
    for (int i = 0; i < n; i++)
        while (true){
            h.push_back(p[i] + q[cur]);
            int nxt = (cur + 1 == m ? 0 : cur + 1);
            if ((q[cur] ^ (p[i + 1] - p[i])) < -eps)
                cur = nxt;
            else if ((q[nxt] ^ (p[i + 1] - p[i])) > (q[cur] ^ (p[i + 1] - p[i])))
                cur = nxt;
            else
                break;
        }
    for (auto &&i : h)  i = i + c;
    return ConvexHull(h);
}

void manacher(){
    string s, ss; // ss="abcdcbd", s=".a.b.c.d.c.b.d"
    cin >> ss;
    s.resize(ss.size() + ss.size() + 1, '.');
    for (int i = 0; i < ss.size(); i++)
        s[i + i + 1] = ss[i];
    vector<int> p(s.size(), 1); //p[i]為使s[i-x+1,i+x-1]為回文的最大x
    int l = 0, r = 0;
    for (int i = 0; i < s.size(); i++)    {
        p[i] = max(min(p[l + l - i], r - i), 1);
        while (0 <= i - p[i] && i + p[i] < s.size() && s[i - p[i]] == s[i + p[i]])
            l = i, r = i + p[i], p[i]++;
    }
    cout << *max_element(p.begin(), p.end()) - 1 << endl;
}

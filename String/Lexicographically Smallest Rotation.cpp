// for example, if S = "bacaa", it's five rotations are: "bacaa", "acaab", "caaba", "aabac", "abaca".
string mcp(string s){
    int n = s.length();
    s += s;
    int i = 0, j = 1;
    while (i < n && j < n){
        int k = 0;
        while (k < n && s[i + k] == s[j + k])  k++;
        if (s[i + k] <= s[j + k]) j += k + 1;
        else   i += k + 1;
        if (i == j)   j++;
    }
    int ans = i < n ? i : j;
    return s.substr(ans, n);
}

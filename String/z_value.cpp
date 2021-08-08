const int MAXn = 1e5 + 5;
int z[MAXn];
void make_z(string s){
  int l = 0, r = 0;
  for(int i = 1;i < s.size();i++){
    for(z[i] = max(0, min(r - i + 1, z[i - l]));
        i + z[i] < s.size() && s[i + z[i]] == s[z[i]];z[i]++);
    if(i + z[i] - 1 > r)l = i, r = i + z[i] - 1;
  }
}
//後綴s[i,n-1]與原字串s[0,n-1]的最長共同前綴

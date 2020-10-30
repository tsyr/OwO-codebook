//輸入一个long long 範圍內的數，是質數返回true，否則返回false。定義檢測次數為TIMES，錯誤率為(1/4)^TIMES
#define TIMES 10
long long GetRandom(long long n){
  //cout<<RAND_MAX<<endl;
  ll num = (((unsigned ll)rand()+100000007)*rand())%n;
  return num + 1;
}
long long Mod_Mul(ll a, ll b, ll Mod){
  long long msum = 0;
  while (b){
    if (b & 1)
      msum = (msum + a) % Mod;
    b >>= 1;
    a = (a + a) % Mod;
  }
  return msum;
}
long long Quk_Mul(ll a, ll b, ll Mod){
  long long qsum = 1;
  while (b) {
    if (b & 1)
      qsum = Mod_Mul(qsum, a, Mod);
    b >>= 1;
    a = Mod_Mul(a, a, Mod);
  }
  return qsum;
}
bool Miller_Rabin(long long n){
  if (n == 2 || n == 3 || n == 5 || n == 7 || n == 11)
    return true;
  if (n == 1 || n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0 || n % 11 == 0)
    return false;
  int div2 = 0;
  long long tn = n - 1;
  while (!(tn % 2)){
    div2++;
    tn /= 2;
  }
  for (int tt = 0; tt < TIMES; tt++){
    long long x = GetRandom(n - 1); //隨機得到[1,n-1]
    if (x == 1)
      continue;
    x = Quk_Mul(x, tn, n);
    long long pre = x;
    for (int j = 0; j < div2; j++){
      x = Mod_Mul(x, x, n);
      if (x == 1 && pre != 1 && pre != n - 1)
        return false;
      pre = x;
    }
    if (x != 1)
      return false;
  }
  return true;
}

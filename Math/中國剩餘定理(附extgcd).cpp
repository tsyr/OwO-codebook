x=a_i(mod m_i)
m_1,m_2,...,m_n兩兩互質，則對於任意整數a_1,a_2,...,a_n都存在x滿足上述方程組。
x≡a_1 t_1 M_1+a_2 t_2 M_2+⋯+a_n t_n M_n (mod M)
其中M=m_1 m_2…m_n，M_i=M/m_i且t_i M_i≡1(mod m_i )
ll exgcd(ll a, ll b, ll &x, ll &y){
  if (b == 0){
    x = 1;  y = 0;
    return a;
  }
  ll r = exgcd(b, a % b, x, y);
  ll t = x;
  x = y;
  y = t - a / b * y;
  return r;
}
ll chinese_remainder(int a[], int w[], int n) 
{//w存放除數,a存放餘數
  ll M = 1, ans = 0, x, y;
  for (int i = 0; i < n; i++)
    M *= w[i];
  for (int i = 0; i < n; i++){
    ll m = M / w[i];
    exgcd(m, w[i], x, y);
    ans = (ans + x * m * a[i]) % M;
  }
  return (ans % M + M) % M;
}

// Finds the primitive root modulo p
int generator(int p){
  vector<int> fact;
  int phi = p - 1, n = phi;
  for (int i = 2; i * i <= n; ++i){
    if (n % i == 0){
      fact.push_back(i);
      while (n % i == 0)
        n /= i;
    }
  }
  if (n > 1) fact.push_back(n);
  for (int res = 2; res <= p; ++res){
    bool ok = true;
    for (int factor : fact){
      if (powmod(res, phi / factor, p) == 1){
        ok = false;
        break;
      }
    }
    if (ok) return res;
  }
  return -1;
}
//finds all numbers x such that x^k=a (mod n)
vector<int> solve(int n, int k, int a){
  vector<int> ans;
  if (a == 0){
    ans.push_back(0);
    return ans;
  }
  int g = generator(n);
  // Baby-step giant-step discrete logarithm algorithm
  int sq = (int)sqrt(n + .0) + 1;
  vector<pair<int, int>> dec(sq);
  for (int i = 1; i <= sq; ++i)
    dec[i - 1] = {powmod(g, i * sq * k % (n - 1), n), i};
  sort(dec.begin(), dec.end());
  int any_ans = -1;
  for (int i = 0; i < sq; ++i){
    int my = powmod(g, i * k % (n - 1), n) * a % n;
    auto it = lower_bound(dec.begin(), dec.end(), make_pair(my, 0ll));
    if (it != dec.end() && it->first == my){
      any_ans = it->second * sq - i;
      break;
    }
  }
  if (any_ans == -1)  return ans;
  // Print all possible answers
  int delta = (n - 1) / gcd(k, n - 1);
  for (int cur=any_ans % delta;cur<n-1;cur+=delta)
    ans.push_back(powmod(g, cur, n));
  sort(ans.begin(), ans.end());
  return ans;
}

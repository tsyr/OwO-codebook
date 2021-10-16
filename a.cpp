    #include<bits/stdc++.h>
    #include<ext/pb_ds/assoc_container.hpp>
    #define ll long long
    #define ull unsigned ll
    #define N 300005
    #define SQRTN 1005
    #define P1 880301
    #define M1 998244353
    #define P2 127
    #define M2 1000000009
     
    using namespace std;
    using namespace __gnu_pbds;
     
    struct custom_hash {
      static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
      }
      size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
      }
    };
     
    vector<int> len;
    vector<int> G[N];
    string s;
    pair<int,pair<string,ull>> qrr[N];
    vector<int> qid[N];
    vector<ll> h1,h2;
    ll pp1[N],pp2[N];
    gp_hash_table<ull,int,custom_hash> cnt[N];
    int ans[N];
     
    ull hs(int l,int r){
      ll tmp1=h1[r]-h1[l]*pp1[r-l]%M1;
      tmp1=(tmp1<0?tmp1+M1:tmp1);
      ll tmp2=h2[r]-h2[l]*pp2[r-l]%M2;
      tmp2=(tmp2<0?tmp2+M2:tmp2);
      return (tmp1<<32)|tmp2;
    }
     
    void dfs(int x,int p,int d){
      h1.push_back((h1.back()*P1+s[x])%M1);
      h2.push_back((h2.back()*P2+s[x])%M2);
      for(int i=0;i<(int)len.size()&&d>=len[i];i++){
        ull ch=hs(d-len[i],d);
        if(cnt[len[i]].find(ch)!=cnt[len[i]].end())
          cnt[len[i]][ch]++;
      }
      for(int id:qid[x])
        ans[id]=cnt[qrr[id].second.first.size()][qrr[id].second.second];
      for(int i:G[x]){
        if(i!=p)
          dfs(i,x,d+1);
      }
      for(int i=0;i<(int)len.size()&&d>=len[i];i++){
        ull ch=hs(d-len[i],d);
        if(cnt[len[i]].find(ch)!=cnt[len[i]].end())
          cnt[len[i]][ch]--;
      }
      h1.pop_back(); h2.pop_back();
    }
     
    int main(){
      cin.tie(0); ios::sync_with_stdio(0);
      int n; cin>>n;
      pp1[0]=1;
      for(int i=1;i<=n;i++) pp1[i]=pp1[i-1]*P1%M1;
      pp2[0]=1;
      for(int i=1;i<=n;i++) pp2[i]=pp2[i-1]*P2%M2;
      cin>>s;
      for(int i=1;i<n;i++){
        int u,v; cin>>u>>v;
        G[u-1].push_back(v-1);
        G[v-1].push_back(u-1);
      }
      int q; cin>>q;
      for(int i=0;i<q;i++){
        cin>>qrr[i].first>>qrr[i].second.first;
        --qrr[i].first; len.push_back(qrr[i].second.first.size());
        qid[qrr[i].first].push_back(i);
        ull ch1=0,ch2=0;
        for(char c:qrr[i].second.first){
          ch1=(ch1*P1+c)%M1;
          ch2=(ch2*P2+c)%M2;
        }
        qrr[i].second.second=(ch1<<32)|ch2;
        cnt[qrr[i].second.first.size()][qrr[i].second.second]=0;
      }
      sort(len.begin(),len.end());
      len.resize(unique(len.begin(),len.end())-len.begin());
      h1.push_back(0); h2.push_back(0);
      dfs(0,0,1); 
      for(int i=0;i<q;i++) cout<<ans[i]<<"\n";
      return 0;
    }

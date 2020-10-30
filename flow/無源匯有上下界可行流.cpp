n 個點，m 條邊，每條邊 e有一個流量下界 lower(e)和流量上界 upper(e)，求一種可行方案使得在所有點滿足流量平衡條件的前提下，所有邊滿足流量限制。
輸入格式
第一行兩個正整數 n、m。
之後的 m 行，每行四個整數 s、t、lower、upper。
輸出格式
如果無解，輸出一行 NO。
否則第一行輸出 YES，之後 m行每行一個整數，表示每條邊的流量。
const int maxn=70005;
int sp,tp,cnt=0,head[205],nxt[maxn],to[maxn],cap[maxn],dis[1005],low[maxn],def[205],m,n;
inline void add(int u,int v,int p){
  nxt[cnt]=head[u],to[cnt]=v,cap[cnt]=p,head[u]=cnt++;
  nxt[cnt]=head[v],to[cnt]=u,cap[cnt]=0,head[v]=cnt++;
}
inline bool bfs(){
    int u,e,v;
    queue<int> que;
    memset(dis,-1,sizeof(dis));
    que.push(sp),dis[sp]=0;
    while(!que.empty()){
        u=que.front(),que.pop();
        for(int e=head[u];~e;e=nxt[e]){
            if(cap[e]>0&&dis[v=to[e]]==-1){
                dis[v]=dis[u]+1,que.push(v);
                if(v==tp) return true;
            }
        }
    }
    return false;
}
inline int dfs(const int &u,const int &flow){
    if(u==tp) return flow;
    int res=0,v,flw;
    for(int e=head[u];~e;e=nxt[e]){
        if(cap[e]>0&&dis[u]<dis[v=to[e]]){
            flw=dfs(v,min(cap[e],flow-res));
            if(flw==0) dis[v]=-1;
            cap[e]-=flw,cap[e^1]+=flw;
            res+=flw;
            if(res==flow) break;
        }
    }
    return res;
}
inline int dinic(int sp,int tp){
    int ans=0;
    while(bfs()) {
        ans+=dfs(sp,1<<30);
    }
    return ans;
}
int main(){
    memset(head,-1,sizeof(head));
    n=read(),m=read();
    int s,t,up,down,sum=0;
    for(int i=1;i<=m;i++){
        s=read(),t=read(),down=read(),up=read();
        add(s,t,up-down);
        low[i]=down,def[s]+=down,def[t]-=down;
    }
    sp=n+1,tp=n+2;
    for(int i=1;i<=n;i++){
        if(def[i]>0) sum+=def[i],add(i,tp,def[i]);
        if(def[i]<0) add(sp,i,-def[i]);
    }
    if(dinic(sp,tp)==sum){
        cout<<"YES"<<endl;
        for(int i=1;i<=m;i++){
            cout<<cap[((i-1)*2)^1]+low[i]<<endl;
        }
    }
    else cout<<"NO"<<endl;
    return 0;
}

n 個點，m 條邊，每條邊 e 有一個流量下界 lower(e)和流量上界 upper(e)，給定源點 s 與匯點 t，求源點到匯點的最小流。
輸入格式
第一行兩個正整數 n、m、s、t。
之後的 m行，每行四個整數 s、t、lower、upper。
輸出格式
如果無解，輸出-1，否則輸出最小流。
const int maxn=50010;
const int maxm=405000;
int n,m,sp,tp,s,t;
int nxt[maxm],head[maxn],to[maxm],cap[maxm],cnt=0,deg[maxn];
int cur[maxm],dis[maxm];
inline void add(int u,int v,int p){
  nxt[cnt]=head[u],to[cnt]=v,cap[cnt]=p,head[u]=cnt++;
  nxt[cnt]=head[v],to[cnt]=u,cap[cnt]=0,head[v]=cnt++;
}
bool bfs(int st,int en){
    memset(dis,-1,sizeof(dis));
    memcpy(cur,head,sizeof(head));
    queue<int > q;
    q.push(st);dis[st]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int e=head[u];~e;e=nxt[e]){
            int v=to[e];
            if(cap[e]>0&&dis[v]==-1){
                dis[v]=dis[u]+1;
                if(v==en) return true;
                q.push(v);
            }
        }
    }
    return false;
}
inline int dinic(int u,int flow,int ee){
    if(u==ee) return flow;
    int res=0;
    for(int &e=cur[u];~e;e=nxt[e]){
        int v=to[e];
        if(cap[e]>0&&dis[v]>dis[u]){
            int delta=dinic(v,min(flow-res,cap[e]),ee);
            if(delta){
                cap[e]-=delta;cap[e^1]+=delta;
                res+=delta;
                if(res==flow) break;
            }
        }
    }
    return res;
}
int main(){
    memset(head,-1,sizeof(head));
    n=read();m=read();s=read();t=read();
    int i,j,k;
    sp=0;tp=n+1;
    for(i=1;i<=m;++i){
        int u=read(),v=read(),ll=read(),rr=read();
        add(u,v,rr-ll);
        deg[v]+=ll;  deg[u]-=ll;
    }
    int sum=0,first;
    add(t,s,inf);
    first=cnt-1;
    for(i=1;i<=n;++i){
        if(deg[i]<0)
            add(i,tp,-deg[i]);
        else if(deg[i]>0)
            add(sp,i,deg[i]),sum+=deg[i];
    }
    int maxflow=0;
    while(bfs(sp,tp))
        maxflow+=dinic(sp,inf,tp);
    if(maxflow==sum){
        maxflow=cap[first];
        for(i=first-1;i<=cnt;++i) cap[i]=0;
        while(bfs(t,s)) maxflow-=dinic(t,inf,s);
        printf("%d\n",maxflow);
    }
    else printf("-1\n");
    return 0;
}

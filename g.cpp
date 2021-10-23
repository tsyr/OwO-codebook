#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn =200005;
struct edge
{
	int to;
	ll cost;
	
};
vector<edge> G[maxn];

ll dp1[maxn],dp2[maxn];
ll ans=0;
void dfs(int v,int p,ll haha)
{


	ll tmp=0;
	for(int i=0 ; i<G[v].size() ; i++)
	{
		if(G[v][i].to!=p) dfs(G[v][i].to,v,G[v][i].cost);
	}
	dp1[v]=1;
	dp2[v]=1;
	for(int i=0 ; i<G[v].size() ; i++ )
	{
		if(G[v][i].to!=p)
		{
			tmp+=dp2[G[v][i].to];
			if(haha!=-1)
			{
				if(G[v][i].cost>haha)
				{
					dp1[v]+=dp1[G[v][i].to];
				}
				if(G[v][i].cost<haha)
				{
					dp2[v]+=dp2[G[v][i].to];
				}

			}
		} 
	}
	int l=0;
	for(int i=0 ; i<G[v].size() ; i++)
	{	
		while(l<G[v][i].cost&&G[v][l].cost<=G[v][i].cost)
		{
			tmp-=dp2[G[v][l].to];
			l++;
		}
		ans+=(dp1[G[v][i].to]*tmp);
		ans+=dp1[G[v][i].to];
		ans+=dp2[G[v][i].to];
	}
	return ;
}
bool check(edge a,edge b)
{
	return a.cost<b.cost;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1 ; i<n ; i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		G[a].push_back((edge){b,c});
		G[b].push_back((edge){a,c});
	}
	for(int i=1;  i<=n ; i++)
	{
		sort(G[i].begin(),G[i].end(),check);
	}
	dfs(1,0,-1);
	cout<<ans<<"\n";
	return 0;
} 

// hdu 5140, 2D copy on write segment tree, WA
// http://acm.hdu.edu.cn/showproblem.php?pid=5140 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
using namespace std;
#define maxn 100005
#define N (int)5e6
typedef long long ll;
typedef pair<ll, int> P;

struct node2{
	static node2 mem2[N], *pmem2;
	int l,r;
	ll val;
	node2 *lc,*rc;
	node2() {}
	node2(int _l,int _r,ll _val){ lc=rc=NULL,l=_l,r=_r,val=_val; }
} node2::mem2[N], *node2::pmem2=mem2; 

struct node{
	static node mem[N], *pmem;
	int l,r;
	node2 *nd;
	node *lc,*rc;
	node() {}
	node(int _l,int _r){ lc=rc=NULL,nd=NULL,l=_l,r=_r; }
} node::mem[N], *node::pmem=mem; 

int n;

void update2(node2 *t,int y,ll val){
	if(t->l==t->r) {
		t->val+=val;
		return;
	}
	int mid=(t->l+t->r)/2;
	if(y<=mid){
		if(!t->lc) t->lc=new (node2::pmem2++) node2(t->l,mid,0);
		update2(t->lc,y,val);
	}else{
		if(!t->rc) t->rc=new (node2::pmem2++) node2(mid+1,t->r,0);
		update2(t->rc,y,val);
	}
	t->val=0;
	if(t->lc) t->val+=t->lc->val;
	if(t->rc) t->val+=t->rc->val;
}

void update(node *t,int x,int y,ll val){
	if(t->nd==NULL) t->nd=new (node2::pmem2++) node2(1,n,0);
	update2(t->nd,y,val);
	if(t->l==t->r)
		return;
	int mid=(t->l+t->r)/2;
	if(x<=mid){
		if(!t->lc) t->lc=new (node::pmem++) node(t->l,mid);
		update(t->lc,x,y,val);
	}else{
		if(!t->rc) t->rc=new (node::pmem++) node(mid+1,t->r);
		update(t->rc,x,y,val);
	}
}

ll query2(node2 *t,int yl,int yr){
	if(t->l>yr||t->r<yl) return 0;
	//printf("t2 %d %d \n",t->l,t->r);
	if(t->l>=yl&&t->r<=yr)
		return t->val;
	int mid=(t->l+t->r)/2;
	ll res=0;
	if(yl<=mid&&t->lc)
		res+=query2(t->lc,yl,yr);
	if(yr>mid&&t->rc)
		res+=query2(t->rc,yl,yr);
	return res; 
}

ll query(node *t,int xl,int xr,int yl,int yr){
	if(t->l>xr||t->r<xl) return 0;
	if(t->l>=xl&&t->r<=xr){
		//printf("t %d %d \n",t->l,t->r);
		if(t->nd) return query2(t->nd,yl,yr);
		else return 0;
	}
	int mid=(t->l+t->r)/2;
	ll res=0;
	if(xl<=mid&&t->lc)
		res+=query(t->lc,xl,xr,yl,yr);
	if(xr>mid&&t->rc)
		res+=query(t->rc,xl,xr,yl,yr);
	return res; 
}

ll x[maxn],y[maxn];
ll w[maxn];
vector<ll> b1,b2;

int main()
{
	//freopen("4-16.in", "r", stdin);
	//freopen("a218_09.out", "w", stdout);
	//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int q;
	
	while(scanf("%d",&n)!=EOF){
		node::pmem = node::mem;
		node2::pmem2 = node2::mem2;
		node *rt=new (node::pmem++) node(1,n);
		
		b1.clear(),b2.clear();
		for(int i=0;i<n;i++){
			scanf("%lld%lld%lld",&w[i],&x[i],&y[i]);
			b1.push_back(x[i]),b2.push_back(y[i]);
		}
		b1.erase(unique(b1.begin(),b1.end()),b1.end());
		b2.erase(unique(b2.begin(),b2.end()),b2.end());
		for(int i=0;i<n;i++){
			x[i]=lower_bound(b1.begin(),b1.end(),x[i])-b1.begin()+1;
			y[i]=lower_bound(b2.begin(),b2.end(),y[i])-b2.begin()+1;
			update(rt,x[i],y[i],w[i]);
		}
		
		scanf("%d",&q);
		ll k=0;
		while(q--){
			ll xl,xr,yl,yr;
			scanf("%lld%lld%lld%lld",&xl,&xr,&yl,&yr);
			xl+=k,xr-=k,yl+=k,yr-=k;
			if(xl>xr) swap(xl,xr);
			if(yl>yr) swap(yl,yr);
			//xl--,yl--;
			xl=lower_bound(b1.begin(),b1.end(),xl)-b1.begin()+1;
			yl=lower_bound(b2.begin(),b2.end(),yl)-b2.begin()+1;
			xr=upper_bound(b1.begin(),b1.end(),xr)-b1.begin();
			yr=upper_bound(b2.begin(),b2.end(),yr)-b2.begin();
			
			k=query(rt,xl,xr,yl,yr);
			printf("%lld\n",k);
		}
	} 

	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 200005

int n,q;
struct S
{
	int lll,rr,al,ar,sz;
	ll tot;
}smt[maxn*4];
int A[maxn];

S merge(S s1,S s2){
	S s;
	s.al=s1.al;
	s.ar=s2.ar;
	s.sz=s1.sz+s2.sz;
	if(s1.lll==s1.sz&&(s1.ar+s2.al)==1) 
		s.lll=s1.lll+s2.lll;
	else
		s.lll=s1.lll;
	if(s2.rr==s2.sz&&(s1.ar+s2.al)==1)
		s.rr=s1.rr+s2.rr;
	else 
		s.rr=s2.rr;

	s.tot=s1.tot+s2.tot;
	if((s1.ar+s2.al)==1){
		s.tot-=((ll)s1.rr*(s1.rr+1)+(ll)s2.lll*(s2.lll+1))/2;
		s.tot+=(ll)(s1.rr+s2.lll)*(s1.rr+s2.lll+1)/2;
	}
	return s;
}

void build(int idx,int l,int r){
	if(l==r){
		smt[idx].al=smt[idx].ar=A[l];
		smt[idx].lll=smt[idx].rr=1;
		smt[idx].tot=1;
		smt[idx].sz=r-l+1;
		return;
	}
	int m=(l+r)/2;
	build(idx<<1,l,m);
	build(idx<<1|1,m+1,r);
	smt[idx]=merge(smt[idx<<1],smt[idx<<1|1]);
}

void update(int idx,int l,int r,int a,int b){
	if(l>=a&&r<=b){
		smt[idx].ar=1-smt[idx].ar;
		smt[idx].al=1-smt[idx].al;
		return;
	}
	int m=(l+r)/2;
	if(m>=b)
		update(idx<<1,l,m,a,b);
	else if(m+1<=a)
		update(idx<<1|1,m+1,r,a,b);
	else{
		update(idx<<1,l,m,a,b);
		update(idx<<1|1,m+1,r,a,b);
	}
	smt[idx]=merge(smt[idx<<1],smt[idx<<1|1]);
}

S query(int idx,int l,int r,int a,int b){
	if(l>=a&&r<=b)
		return smt[idx];
	int m=(l+r)/2;
	if(m>=b)
		return query(idx<<1,l,m,a,b);
	if(m+1<=a)
		return query(idx<<1|1,m+1,r,a,b);
	return merge(query(idx<<1,l,m,a,b),query(idx<<1|1,m+1,r,a,b));
}

int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) 
		scanf("%d",&A[i]);
	build(1,1,n);
	while(q--){
		int type;
		scanf("%d",&type);
		if(type==1){
			int l,r;
			scanf("%d%d",&l,&r);
			update(1,1,n,l,r);
		}
		else{
			int l,r;
			scanf("%d%d",&l,&r);
			S s=query(1,1,n,l,r);
			printf("%lld\n",s.tot);
		}
	}
}
